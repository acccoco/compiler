#include "SyntaxParser.h"
using namespace std;

/*
 Goal -> MainClass { ClassDeclaration } EOF
*/
shared_ptr<SyntaxTreeNode> SyntaxParser::Goal(list<shared_ptr<SyntaxError>>& errorList) {

    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeMainTypeEnum::Goal);

    /**********************************
     MainClass
    ************************************/
    tempTreeNode = MainClass(tempErrorList);
    SET_SUBTREE_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ��MainClassʧ��");
    /**********************************
     { ClassDeclaration }
    ************************************/
    SyntaxTreeNodePtr preNode = tempTreeNode;
    while (tempTreeNode = ClassDeclaration(tempErrorList)) {
        preNode->SetSubling(tempTreeNode);
        preNode = tempTreeNode;
    }
    /**********************************
     EOF
    ************************************/
    if (_reader->IsEnd() == false) {
        errorList.emplace_back(new SyntaxError(_reader, "���õ����ļ���β", curTreeType));
        _reader->SetIndex(curIndex);
        return NULL;
    }

    return root;
}