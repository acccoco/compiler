#include "SyntaxParser.h"
using namespace std;

#if false
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
    const int curIndex2 = _reader->Index.Get();
    if (_MatchKeywordOrSymbol(TokenTypeEnum::KEYWORD, "extends")) {
        if (tempTreeNode = _MatchIdentifier()) {
            root->Child.Get()->Child.Set(tempTreeNode);
        }
        else {
            _reader->Index.Set(curIndex2);  // С��ָ�����
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
    root->Child.Get()->Subling.Set(varDeclarSeq);
    if (tempTreeNode = VarDeclaration(tempErrorList)) {
        varDeclarSeq->Child.Set(tempTreeNode);
        SyntaxTreeNodePtr preNode = tempTreeNode;
        while (tempTreeNode = VarDeclaration(tempErrorList)) {
            preNode->Subling.Set(tempTreeNode);
            preNode = tempTreeNode;
        }
    }
    /**********************************
     { MethodDeclaration }
    ************************************/
    SyntaxTreeNodePtr methodDeclarSeq(new SyntaxTreeNode(TreeNodeMainTypeEnum::Default, 0));
    root->Child.Get()->Subling.Get()->Subling.Set(methodDeclarSeq);
    if (tempTreeNode = MethodDeclaration(tempErrorList)) {
        methodDeclarSeq->Child.Set(tempTreeNode);
        SyntaxTreeNodePtr preNode = tempTreeNode;
        while (tempTreeNode = MethodDeclaration(tempErrorList)) {
            preNode->Subling.Set(tempTreeNode);
            preNode = tempTreeNode;
        }
    }
    /**********************************
     "}"
    ************************************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "}", curTreeType, "ʶ��}ʧ��");
    return root;
}
#endif