#pragma once
#include "RDCase.h"
#include "Type.h"
#include "VarDeclaration.h"
#include "Statement.h"
#include "Expression.h"

/*
 MethodDeclaration -> "public" Type Identifier
 "(" [ Type Identifier { "," Type Identifier } ] ")" "{" { VarDeclaration } { Statement }
 "return" Expression ";" "}"
*/

class RDCase_MethodDeclaration : public RDCase {
public:
    RDCase_MethodDeclaration(shared_ptr<TokenReader> reader)noexcept :
        RDCase(reader) {}
protected:
    void _RunException(TreeNodePtr firstNode = nullptr) override {

        /* ���г�ʼ�� */
        _Init(TreeMainType::MethodDeclaration);

        /**** "public" ****/
        _CheckKeyword("public");

        /**** Type ****/
        auto type1 = RDCase_Type(_reader);
        type1.Run();
        _CheckSubTree(&type1);

        /**** Identifier ****/
        auto identifier1 = _CheckIdentifier();

        /* ��װAST�ĵ�һ���ӽڵ� */
        identifier1->Child.Set(type1.Root.Get());
        _root->Child.Set(identifier1);

        /**** "(" ****/
        _CheckSymbol("(");

        /**** [ Type Identifier { "," Type Identifier } ] ****/
        auto paramSeqNode = _MatchOptional1();
        _root->Child.Get()->Subling.Set(paramSeqNode);

        /**** ")" "{" ****/
        _CheckSymbol(")");
        _CheckSymbol("{");

        /**** { VarDeclaration } ****/
        TreeNodePtr varDeclarSeqNode = _MatchCaseSequence<RDCase_VarDeclaration>();
        paramSeqNode->Subling.Set(varDeclarSeqNode);

        /**** { Statement } ****/
        TreeNodePtr stateSeqNode = _MatchCaseSequence<RDCase_Statement>();
        varDeclarSeqNode->Subling.Set(stateSeqNode);

        /**** "return" ****/
        _CheckKeyword("return");

        /**** Expression ****/
        auto expression1 = RDCase_Expression(_reader);
        expression1.Run();
        _CheckSubTree(&expression1);
        stateSeqNode->Subling.Set(expression1.Root.Get());

        /**** ";" "}" ****/
        _CheckSymbol(";");
        _CheckSymbol("}");

        return;
    }

    /* 
     [ Type Identifier { "," Type Identifier } ]
     ��ѡС�ڵ�ƥ��
     �쳣�������׳��쳣
     ʧ���˻�ָ�reader��ָ��
     ����һ��sequenceNode�����ӽڵ���һϵ��С��ƥ�����ļ���
     */
    TreeNodePtr _MatchOptional1() noexcept{

        /**** ����ƥ���һ��С�� [ Type Identifier ... ] ****/
        TreeNodePtr paramSeqNode(new TreeNode(TreeMainType::Default, 0));

        bool isSectionMatch = false;    // ��ǵ�һ����ѡС���Ƿ�ƥ��ɹ�
        RUN_ONCE() {
            const int curIndex2 = _reader->Index.Get();     // ʧ�ܻ��˵�׼��

            auto type2 = RDCase_Type(_reader);
            type2.Run();
            if (type2.Root.Get() == nullptr) break;

            auto identifier2 = _MatchIdentifier();
            if (identifier2 == nullptr) {
                _reader->RecoveryIndex(curIndex2);
                break;
            }

            /* С��ƥ��ɹ�����װ�ڵ㣬���ӵ�AST�� */
            isSectionMatch = true;
            paramSeqNode->Child.Set(identifier2);
            identifier2->Child.Set(type2.Root.Get());
        }

        /* �����һС��ƥ��ʧ�ܣ��ʹ˷��� */
        if (!isSectionMatch) return paramSeqNode;

        /**** ����ƥ������С�ڣ�  { "," Type Identifier } ****/
        TreeNodePtr preNode = paramSeqNode->Child.Get();

        while (true) {
            const int curIndex3 = _reader->Index.Get();     // ʧ�ܻ��˵�׼��

            if (!_MatchSymbol(",")) break;

            auto type3 = RDCase_Type(_reader);
            type3.Run();
            if (type3.Root.Get() == nullptr) {
                _reader->RecoveryIndex(curIndex3);
                break;
            }

            auto identifier3 = _MatchIdentifier();
            if (identifier3 == nullptr) {
                _reader->RecoveryIndex(curIndex3);
                break;
            }

            /* С��ƥ��ɹ�����װ�ڵ� */
            preNode->Subling.Set(identifier3);
            identifier3->Child.Set(type3.Root.Get());
            preNode = identifier3;
        }

        return paramSeqNode;
    }
};