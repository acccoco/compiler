#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <stack>
#include <list>
#include "TokenReader.h"
#include "SyntaxTreeNode.h"
#include "SyntaxError.h"

/*
 �﷨��������ʵ��
 ���������token����������﷨��������﷨����
*/
class SyntaxParser
{
protected:
    typedef SyntaxTreeNode::Ptr SyntaxTreeNodePtr;
    friend class ParserTest;                            // ���ڲ��Ե���Ԫ��
    shared_ptr<TokenReader> _reader;                    // token�Ķ�ȡ��
    SyntaxTreeNodePtr _root;                            // �������������
    list<shared_ptr<SyntaxError>> _errorList;          // �����������������

    /*
     ʶ��ؼ��ֻ��߷���
     �������Ĳ��� keyword �� symbol ����ʶ��ʧ��
     �����ƥ�䣬reader �� index �����
    */
    bool _MatchKeywordOrSymbol(TokenTypeEnum tokenType, string str) {
        // �ж������Ƿ�ϸ�
        if (tokenType != TokenTypeEnum::KEYWORD && tokenType != TokenTypeEnum::SYMBOL) {
            return false;
        }
        // ����ƥ��
        ETokenPtr token = _reader->SeekToken();
        if (token->GetTokenType() == tokenType && token->GetStrValue() == str) {
            _reader->GetToken();
        }
        else {
            return false;
        }
    }


    /*
     ʶ��Identifier
     ���ʧ�ܣ�����ˣ����ҷ���NULL
     �ɹ��������ڵ�
    */
    SyntaxTreeNodePtr _MatchIdentifier() {
        ETokenPtr token;
        if ((token = _reader->SeekToken()) && token->GetTokenType() == TokenTypeEnum::IDENTIFIER) {
            token = _reader->GetToken();
            return SyntaxTreeNodePtr(new SyntaxTreeNode(token->GetStrValue(), token->GetLineNum()));
        }
        else {
            return NULL;
        }
    }
    /*
     ʶ��IntgetLiteral
     ���ʧ�ܣ�����ˣ����ҷ���NULL
     �ɹ��������ڵ�
    */
    SyntaxTreeNodePtr _MatchIntegerLiteral() {
        ETokenPtr token;
        if ((token = _reader->SeekToken()) && token->GetTokenType() == TokenTypeEnum::INTEGER) {
            token = _reader->GetToken();
            return SyntaxTreeNodePtr(new SyntaxTreeNode(token->GetNumValue(), token->GetLineNum()));
        }
        else {
            return NULL;
        }
    }

public:
#pragma region ���캯������������
    /*
     ֱ��ͨ��tokens�Ķ�ά��������ʼ��
    */
    SyntaxParser(vector<vector<shared_ptr<Token>>> tokens) {
        _reader = shared_ptr<TokenReader>(new TokenReader(tokens));
        if (_reader == NULL) {
            throw("Error: SyntaxParser Construction fail.");
        }
    }
    /*
     ͨ��reader����ʼ��
    */
    SyntaxParser(shared_ptr<TokenReader> reader) {
        if (!reader) {
            throw("Error: SyntaxParser Construction fail.");
        }
        else {
            _reader = reader;
        }
    }
#pragma endregion

    /*
     �﷨����������
    */
    void Parse() {
        // ��ս��
        _root = NULL;
        _errorList.clear();

        // ���õݹ��½��㷨
        _root = Goal(_errorList);
    }
    /*
     ����﷨������������
    */
    SyntaxTreeNodePtr GetRoot() {
        return _root;
    }
    /*
     ��ô�������
    */
    list<shared_ptr<SyntaxError>> GetErrorList() {
        return _errorList;
    }


protected:
    SyntaxTreeNodePtr Goal(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr MainClass(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr ClassDeclaration(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr VarDeclaration(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr MethodDeclaration(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr Type(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr Statement(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr Expression(list<shared_ptr<SyntaxError>>& errorList);

#pragma region ʶ��Type���ӹ���
    shared_ptr<SyntaxTreeNode> Type_Identifier(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Type_boolean(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Type_Int(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Type_IntArray(list<shared_ptr<SyntaxError>>& errorList);
#pragma endregion

#pragma region ʶ��Statement���ӹ���
    shared_ptr<SyntaxTreeNode> Statement_Sequence(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Statement_while(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Statement_If(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Statement_Println(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Statement_Assign(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Statement_ArrayAssign(list<shared_ptr<SyntaxError>>& errorList);
#pragma endregion



#pragma region ʶ��Expression���ӹ���
    shared_ptr<SyntaxTreeNode> Expression_Identifier(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_IntegerLiteral(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_this(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_true(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_false(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_not(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_bracket(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_newIntArray(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_newIdentifier(list<shared_ptr<SyntaxError>>& errorList);

    shared_ptr<SyntaxTreeNode> Expression_operate(shared_ptr<SyntaxTreeNode> firstNode, list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_length(shared_ptr<SyntaxTreeNode> firstNode, list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_arrayExpression(shared_ptr<SyntaxTreeNode> firstNode, list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_functionCall(shared_ptr<SyntaxTreeNode> firstNode, list<shared_ptr<SyntaxError>>& errorList);
#pragma endregion


};

#pragma region �ظ�����ĺ궨��
/*
 �ݹ��½�������ʼ���Ĺ��̣�
 - ��� errorList
 - ���� curIndex����������_reader��λ��
 - ���� tempTreeNode
 - ���� tempErrorList
 - ���� curTreeType
 - �ж��Ƿ���ڵ�һ�� token����������ڣ��ͷ���
 - �������ڵ� root
*/
#define RECURSIVE_DESCENT_INIT_RETURN(treeType)\
    errorList.clear();\
    const int curIndex = _reader->GetIndex();\
    SyntaxTreeNodePtr tempTreeNode;\
    list<shared_ptr<SyntaxError>> tempErrorList;\
    auto curTreeType = treeType;\
    ETokenPtr firstToken = _reader->SeekToken(); \
    if (firstToken == NULL) {\
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��ʼtokenʧ��", treeType)); \
        return NULL; \
    }\
    shared_ptr<SyntaxTreeNode> root(new SyntaxTreeNode(treeType, firstToken->GetLineNum()));

/*
 �ݹ��½���ʶ�� Identifier �� IntegerLiteral
 ���ʶ��ɹ���
 - �����ڵ���Ϊָ���ڵ��child
 ���ʶ��ʧ�ܣ�
 - �� errorList ��׷�Ӵ���
 - ָ�����
 - ����
*/
#define SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, message)\
    if (tempTreeNode) {\
        root->SetChild(tempTreeNode);\
    }\
    else {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }

/*
 �ݹ��½���ʶ�� Identifier �� IntegerLiteral
 ���ʶ��ɹ���
 - �����ڵ���Ϊָ���ڵ��subling
 ���ʶ��ʧ�ܣ�
 - �� errorList ��׷�Ӵ���
 - ָ�����
 - ����
*/
#define SET_IDEN_OR_INT_SUBLING_RETURN(tempTreeNode, root, curTreeType, message)\
    if (tempTreeNode) {\
        root->SetSubling(tempTreeNode);\
    }\
    else {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }

/*
 �ݹ��½���ʶ�� ����
 ���ʶ��ɹ���
 - �������ڵ���Ϊָ���ڵ��subling
 ���ʶ��ʧ�ܣ�
 - �� errorList ��׷�Ӵ���
 - ��errorList��׷�������Ĵ���
 - ָ�����
 - ����
*/
#define SET_SUBTREE_SUBLING_RETURN(tempTreeNode, root, curTreeType, message)\
    if (tempTreeNode) {\
        root->SetSubling(tempTreeNode);\
    }\
    else {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }

/*
 �ݹ��½���ʶ�� ����
 ���ʶ��ɹ���
 - �������ڵ���Ϊָ���ڵ��child
 ���ʶ��ʧ�ܣ�
 - �� errorList ��׷�Ӵ���
 - ��errorList��׷�������Ĵ���
 - ָ�����
 - ����
*/
#define SET_SUBTREE_CHILD_RETURN(tempTreeNode, root, curTreeType, message)\
    if (tempTreeNode) {\
        root->SetChild(tempTreeNode);\
    }\
    else {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }

/*
 �ݹ��½�����ʶ�� keyword �� symbol �Ĺ��̣�����޷�ʶ�𣬾ͣ�
 -  ��errorList ��׷�Ӵ���
 - ָ�����
 - ����
*/
#define PROCESS_STR_RETURN(tokenType, tokenStr, curTreeType, message)\
    if (_MatchKeywordOrSymbol(tokenType, tokenStr) == false) {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }
#pragma endregion