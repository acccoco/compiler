#include "SyntaxParser.h"
using namespace std;

/*
 MethodDeclaration -> "public" Type Identifier
 "(" [ Type Identifier { "," Type Identifier } ] ")" "{" { VarDeclaration } { Statement }
 "return" Expression ";" "}"
*/
shared_ptr<SyntaxTreeNode> SyntaxParser::MethodDeclaration(list<shared_ptr<SyntaxError>>& errorList) {
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeMainTypeEnum::MethodDeclaration);
    SyntaxTreeNodePtr preNode;          // subling�ܳ�����Ҫ�������
    SyntaxTreeNodePtr tempTypeNode;     // ����type��identifier���ӽڵ㣬���������������
    /**********************************
     "public"
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "public", curTreeType, "ʶ��publicʧ��");
    /**********************************
     Type
    ************************************/
    tempTypeNode = Type(tempErrorList);
    if (!tempTypeNode) {
        errorList.emplace_back(new SyntaxError(_reader, "", TreeNodeMainTypeEnum::MethodDeclaration));
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());
        _reader->SetIndex(curIndex);
        return NULL;
    }
    /**********************************
     Identifier
    ************************************/
    tempTreeNode = _MatchIdentifier();
    SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ��Identifierʧ��");
    tempTreeNode->SetChild(tempTypeNode);
    /**********************************
     "("
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "(", curTreeType, "ʶ��(ʧ��");
    /**********************************
     [ Type Identifier { "," Type Identifier } ]
    ************************************/
    SyntaxTreeNodePtr paramSequence(new SyntaxTreeNode(TreeNodeMainTypeEnum::Default, 0));
    root->GetChild()->SetSubling(paramSequence);
    const int curIndex1 = _reader->GetIndex();
    tempTypeNode = Type(tempErrorList);
    if (tempTypeNode) {
        tempTreeNode = _MatchIdentifier();
        if (tempTreeNode) {
            tempTreeNode->SetChild(tempTypeNode);
            paramSequence->SetChild(tempTreeNode);
            preNode = tempTreeNode;
            while (true) {
                const int curIndex2 = _reader->GetIndex();
                tempTypeNode = Type(tempErrorList);
                if (!tempTypeNode) break;
                tempTreeNode = _MatchIdentifier();
                if (!tempTreeNode) {
                    _reader->SetIndex(curIndex2);       // ���С�ڵ�ָ�����
                    break;
                }
                tempTreeNode->SetChild(tempTypeNode);
                preNode->SetSubling(tempTreeNode);
                preNode = tempTreeNode;
            }
        }
        else {
            _reader->SetIndex(curIndex1);   // ���С�ڵ�ָ�����
        }
    }
    /**********************************
     ")" "{"
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ")", curTreeType, "ʶ��)ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "{", curTreeType, "ʶ��{ʧ��");
    /**********************************
     { VarDeclaration }
    ************************************/
    SyntaxTreeNodePtr varDeclarSeq(new SyntaxTreeNode(TreeNodeMainTypeEnum::Default, 0));
    paramSequence->SetSubling(varDeclarSeq);
    if (tempTreeNode = VarDeclaration(tempErrorList)) {
        varDeclarSeq->SetChild(tempTreeNode);
        preNode = tempTreeNode;
        while (tempTreeNode = VarDeclaration(tempErrorList)) {
            preNode->SetSubling(tempTreeNode);
            preNode = tempTreeNode;
        }
    }
    /**********************************
     { Statement }
    ************************************/
    SyntaxTreeNodePtr statementSeq(new SyntaxTreeNode(TreeNodeMainTypeEnum::Default, 0));
    varDeclarSeq->SetSubling(statementSeq);
    if (tempTreeNode = Statement(tempErrorList)) {
        statementSeq->SetChild(tempTreeNode);
        preNode = tempTreeNode;
        while (tempTreeNode = Statement(tempErrorList)) {
            preNode->SetSubling(tempTreeNode);
            preNode = tempTreeNode;
        }
    }
    /**********************************
     "return"
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "return", curTreeType, "ʶ��returnʧ��");
    /**********************************
     Expression
    ************************************/
    tempTreeNode = Expression(tempErrorList);
    SET_SUBTREE_SUBLING_RETURN(tempTreeNode, statementSeq, curTreeType, "ʶ��Expressionʧ��");
    /**********************************
     ";" "}"
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ";", curTreeType, "ʶ��;ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "}", curTreeType, "ʶ��}ʧ��");
    return root;

}