#include "SyntaxParser.h"
using namespace std;

#if false

/*
 MainClass -> "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}"
*/
shared_ptr<TreeNode> SyntaxParser::MainClass(list<shared_ptr<SyntaxError>>& errorList) {

    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeMainTypeEnum::MainClass);
    /******************
     "class"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "class", curTreeType, "ʶ��classʧ��");
    /******************
     Identifier
     ********************/
    tempTreeNode = _MatchIdentifier();
    SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ������Identifierʧ��");
    /******************
     "{" "public" "static" "void" "main" "(" "String" "[" "]"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "{", curTreeType, "ʶ��{ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "public", curTreeType, "ʶ��publicʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "static", curTreeType, "ʶ��staticʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "void", curTreeType, "ʶ��voidʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "main", curTreeType, "ʶ��mainʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "(", curTreeType, "ʶ��(ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "String", curTreeType, "ʶ��Stringʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "[", curTreeType, "ʶ��[ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "]", curTreeType, "ʶ��]ʧ��");
    /******************
     Identifier
     ********************/
    tempTreeNode = _MatchIdentifier();
    SET_SUBTREE_SUBLING_RETURN(tempTreeNode, root->Child.Get(), curTreeType, "ʶ�������Identifierʧ��");
    /******************
     ")" "{"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ")", curTreeType, "ʶ��)ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "{", curTreeType, "ʶ��{ʧ��");
    /******************
     Statement
     ********************/
    tempTreeNode = Statement(tempErrorList);
    SET_SUBTREE_SUBLING_RETURN(tempTreeNode, root->Child.Get()->Subling.Get(), curTreeType, "ʶ��Statementʧ��");
    /******************
     "}" "}"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "}", curTreeType, "ʶ��}ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "}", curTreeType, "ʶ��}ʧ��");

    return root;
}

#endif