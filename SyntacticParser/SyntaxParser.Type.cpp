#include "SyntaxParser.h"
using namespace std;

/*
 �ݹ��½�
 Type
*/
shared_ptr<SyntaxTreeNode> SyntaxParser::Type(list<shared_ptr<SyntaxError>>& errorList) {

    errorList.clear();
    // �жϵ�һ�������Ƿ����
    ETokenPtr firstToken = _reader->SeekToken();
    if (firstToken == NULL) {
        return NULL;
    }
    // �������ڵ�
    SyntaxTreeNodePtr root(new SyntaxTreeNode(TreeNodeMainTypeEnum::Type, firstToken->GetLineNum()));
    SyntaxTreeNodePtr temp;


    if (_MatchTokenSequence({ {TokenTypeEnum::KEYWORD, "int"} })) {
        /**********************************
         ��֧1
         "int[]"
        ************************************/
        if (_MatchTokenSequence({ {TokenTypeEnum::SYMBOL, "["}, {TokenTypeEnum::SYMBOL, "]"} })) {
            root->SetSubType(TreeNodeSubTypeEnum_Type::Type_IntArray);
            return root;
        }
        /**********************************
         ��֧2
         "int"
        ************************************/
        else {
            root->SetSubType(TreeNodeSubTypeEnum_Type::Type_Int);
            return root;
        }
    }
    /**********************************
     ��֧3
     "boolean"
    ************************************/
    else if (_MatchTokenSequence({ {TokenTypeEnum::KEYWORD, "boolean"} })) {
        root->SetSubType(TreeNodeSubTypeEnum_Type::Type_boolean);
        return root;
    }
    /**********************************
     ��֧4
     �Զ�������
     Identifier
    ************************************/
    else if (temp = _MatchIdentifier()) {
        root->SetSubType(TreeNodeSubTypeEnum_Type::Type_Identifier);
        if (temp = _MatchIdentifier()) {
            root->SetChild(temp);
            return root;
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}