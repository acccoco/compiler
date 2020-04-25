#include "SyntaxParser.h"
using namespace std;

/*
 ClassDeclaration -> "class" Identifier [ "extends" Identifier ] "{" { VarDeclaration } { MethodDeclaration } "}"
*/
shared_ptr<SyntaxTreeNode> SyntaxParser::ClassDeclaration(list<shared_ptr<SyntaxError>>& errorList) {
    
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeMainTypeEnum::ClassDeclaration);
    /**********************************
     "class"
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "class", curTreeType, "ʶ��classʧ��");
    /**********************************
     Identifier
    ************************************/
    tempTreeNode = _MatchIdentifier();
    SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ������Identifierʧ��");
    /**********************************
     ["extends" Identifier]
    ************************************/
    const int curIndex2 = _reader->GetIndex();
    if (_MatchKeywordOrSymbol(TokenTypeEnum::KEYWORD, "extends")) {
        if (tempTreeNode = _MatchIdentifier()) {
            root->GetChild()->SetChild(tempTreeNode);
        }
        else {
            _reader->SetIndex(curIndex2);   // С��ָ�����
        }
    }
    /**********************************
     "{"
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "{", curTreeType, "ʶ��{ʧ��");
    /**********************************
     { VarDeclaration }
    ************************************/
    SyntaxTreeNodePtr varDeclarSeq(new SyntaxTreeNode(TreeNodeMainTypeEnum::Default, 0));
    root->GetChild()->SetSubling(varDeclarSeq);
    if (tempTreeNode = VarDeclaration(tempErrorList)) {
        varDeclarSeq->SetChild(tempTreeNode);
        SyntaxTreeNodePtr preNode = tempTreeNode;
        while (tempTreeNode = VarDeclaration(tempErrorList)) {
            preNode->SetSubling(tempTreeNode);
            preNode = tempTreeNode;
        }
    }
    /**********************************
     { MethodDeclaration }
    ************************************/
    SyntaxTreeNodePtr methodDeclarSeq(new SyntaxTreeNode(TreeNodeMainTypeEnum::Default, 0));
    root->GetChild()->GetSubling()->SetSubling(methodDeclarSeq);
    if (tempTreeNode = MethodDeclaration(tempErrorList)) {
        methodDeclarSeq->SetChild(tempTreeNode);
        SyntaxTreeNodePtr preNode = tempTreeNode;
        while (tempTreeNode = MethodDeclaration(tempErrorList)) {
            preNode->SetSubling(tempTreeNode);
            preNode = tempTreeNode;
        }
    }
    /**********************************
     "}"
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "}", curTreeType, "ʶ��}ʧ��");
    return root;
}