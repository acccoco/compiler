#include "SyntaxParser.h"
using namespace std;

#if false

/*
 Statement -> ...
*/
shared_ptr<TreeNode> SyntaxParser::Statement(list<shared_ptr<SyntaxError>>& errorList) {
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeMainTypeEnum::Statement);
    if (!(tempTreeNode = Statement_Sequence(tempErrorList))
        && !(tempTreeNode = Statement_If(tempErrorList))
        && !(tempTreeNode = Statement_while(tempErrorList))
        && !(tempTreeNode = Statement_Assign(tempErrorList))
        && !(tempTreeNode = Statement_ArrayAssign(tempErrorList))
        && !(tempTreeNode = Statement_Println(tempErrorList))) {

        return NULL;
    }
    return tempTreeNode;
}

/*
 Statement -> "{" { Statement } "}"
*/
shared_ptr<TreeNode> SyntaxParser::Statement_Sequence(list<shared_ptr<SyntaxError>>& errorList) {
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeSubTypeEnum_Statement::Statement_Sequence);
    /******************
     "{"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "{", curTreeType, "ʶ��{ʧ��");
    /******************
     { Statement }
     ********************/
    if (tempTreeNode = Statement(tempErrorList)) {
        root->Child.Set(tempTreeNode);
        TreeNodePtr preNode = tempTreeNode;
        while (tempTreeNode = Statement(tempErrorList)) {
            preNode->Subling.Set(tempTreeNode);
            preNode = tempTreeNode;
        }
    }
    /******************
     "}"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "}", curTreeType, "ʶ��}ʧ��");
    return root;
}
/*
 Statement -> "while" "(" Expression ")" Statement
*/
shared_ptr<TreeNode> SyntaxParser::Statement_while(list<shared_ptr<SyntaxError>>& errorList) {
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeSubTypeEnum_Statement::Statement_while);
    /******************
     "while" "("
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "while", curTreeType, "ʶ��whileʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "(", curTreeType, "ʶ��(ʧ��");
    /******************
     Expression
     ********************/
    tempTreeNode = Expression(tempErrorList);
    SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ��Expressionʧ��");
    /******************
     ")"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ")", curTreeType, "ʶ��)ʧ��");
    /******************
      Statement
      ********************/
    tempTreeNode = Statement(tempErrorList);
    SET_IDEN_OR_INT_SUBLING_RETURN(tempTreeNode, root->Child.Get(), curTreeType, "ʶ��Statementʧ��");
    return root;
}
/*
 Statement -> "if" "(" Expression ")" Statement "else" Statement
*/
shared_ptr<TreeNode> SyntaxParser::Statement_If(list<shared_ptr<SyntaxError>>& errorList) {
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeSubTypeEnum_Statement::Statement_if);
    /******************
     "if" "("
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "if", curTreeType, "ʶ��ifʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "(", curTreeType, "ʶ��(ʧ��");
    /******************
     Expression
     ********************/
    tempTreeNode = Expression(tempErrorList);
    SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ��Expressionʧ��");
    /******************
     ")"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ")", curTreeType, "ʶ��)ʧ��");
    /******************
      Statement
      ********************/
    tempTreeNode = Statement(tempErrorList);
    SET_IDEN_OR_INT_SUBLING_RETURN(tempTreeNode, root->Child.Get(), curTreeType, "ʶ��Statementʧ��");
    /******************
     "else"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "else", curTreeType, "ʶ��elseʧ��");
    /******************
      Statement
      ********************/
    tempTreeNode = Statement(tempErrorList);
    SET_IDEN_OR_INT_SUBLING_RETURN(tempTreeNode, root->Child.Get()->Subling.Get(), curTreeType, "ʶ��Statementʧ��");
    return root;
}
/*
 Statement -> "System.out.println" "(" Expression ")" ";"
*/
shared_ptr<TreeNode> SyntaxParser::Statement_Println(list<shared_ptr<SyntaxError>>& errorList) {
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeSubTypeEnum_Statement::Statement_println);
    /******************
     "System.out.println" "("
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::KEYWORD, "System.out.println", curTreeType, "ʶ��System.out.printlnʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "(", curTreeType, "ʶ��(ʧ��");
    /******************
     Expression
     ********************/
    tempTreeNode = Expression(tempErrorList);
    SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ��Expressionʧ��");
    /******************
     ")" ";"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ")", curTreeType, "ʶ��)ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ";", curTreeType, "ʶ��;ʧ��");
    return root;
}
/*
 Statement -> Identifier "=" Expression ";"
*/
shared_ptr<TreeNode> SyntaxParser::Statement_Assign(list<shared_ptr<SyntaxError>>& errorList) {
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeSubTypeEnum_Statement::Statement_assign);
    /******************
     Identifier
     ********************/
    tempTreeNode = _MatchIdentifier();
    SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ��identifierʧ��");
    /******************
     "="
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "=", curTreeType, "ʶ��=ʧ��");
    /******************
     Expression
     ********************/
    tempTreeNode = Expression(tempErrorList);
    SET_IDEN_OR_INT_SUBLING_RETURN(tempTreeNode, root->Child.Get(), curTreeType, "ʶ��Expressionʧ��");
    /******************
     ";"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ";", curTreeType, "ʶ��;ʧ��");
    return root;
}
/*
 Statement -> Identifier "[" Expression "]" "=" Expression ";"
*/
shared_ptr<TreeNode> SyntaxParser::Statement_ArrayAssign(list<shared_ptr<SyntaxError>>& errorList) {
    RECURSIVE_DESCENT_INIT_RETURN(TreeNodeSubTypeEnum_Statement::Statement_arrayAssign);
    /******************
     Identifier
     ********************/
    tempTreeNode = _MatchIdentifier();
    SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, "ʶ��identifierʧ��");
    /******************
     "["
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "[", curTreeType, "ʶ��[ʧ��");
    /******************
     Expression
     ********************/
    tempTreeNode = Expression(tempErrorList);
    SET_IDEN_OR_INT_SUBLING_RETURN(tempTreeNode, root->Child.Get(), curTreeType, "ʶ��Expressionʧ��");
    /******************
     "]" "="
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "]", curTreeType, "ʶ��]ʧ��");
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, "=", curTreeType, "ʶ��=ʧ��");
    /******************
     Expression
     ********************/
    tempTreeNode = Expression(tempErrorList);
    SET_IDEN_OR_INT_SUBLING_RETURN(tempTreeNode, root->Child.Get()->Subling.Get(), curTreeType, "ʶ��Expressionʧ��");
    /******************
     ";"
     ********************/
    PROCESS_STR_RETURN(TokenTypeEnum::SYMBOL, ";", curTreeType, "ʶ��;ʧ��");

    return root;
}

#endif