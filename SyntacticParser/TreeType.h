#pragma once
#include <map>
#include <string>
using namespace std;

#pragma region ���ڵ����͵�ö��

/* �﷨�������ڵ�������� */
enum class TreeMainType {

    /*--------�﷨�ڵ�-------*/
    Goal,
    MainClass,
    ClassDeclaration,
    VarDeclaration,
    MethodDeclaration,
    Type,
    Statement,
    Expression,

    /*----------�ʷ��ڵ�----------*/
    Identifier,         // ��ʶ���������������
    IntegerLeterial,    // ����

    /*-----------����ڵ�--------------*/
    Default,        // ������϶���ڵ�
};

/* Expression���������׵������� */
enum class TreeSubType_Expression {
    Default,        // û�������ͣ�ֻ��������

    /*------��Ӧ���ս����ͷ�Ĳ���ʽ-----*/
    Exp_Bracket,    // Expression -> "(" Expression ")"
    Exp_Not,    // Expression -> "!" Expression
    Exp_NewIdentifier,  // Expression -> "new" Identifier "(" ")"
    Exp_NewIntArray,    // Expression -> "new" "int" "[" Expression "]"
    Exp_True,   // Expression -> "true"
    Exp_False,  // Expression -> "false"
    Exp_This,   // Expression -> "this"
    Exp_Identifier, // Expression -> Identifier
    Exp_IntegerLiteral, // Expression -> IntegerLiteral

    /*------��Ӧ�Է��ս����ͷ�Ĳ���ʽ-----*/
    Exp_ArrayExpression,    // Expression -> Expression "[" Expression "]"
    Exp_Length, // Expression -> Expression "." "length"
    Exp_FunctionCall,   // Expression "." Identifier "(" [ Expression { "," Expression } ] ")"
    Exp_Operate,    // Expression ->  Expression ( "&&" | "<" | "+" | "-" | "*" ) Expression
};

/* Statement���������׵������� */
enum class TreeSubType_Statement {
    Default,    // û�������ͣ�ֻ��������

    /*------��Ӧ��Ӧ�Ĳ���ʽ-----*/
    Statement_Sequence,
    Statement_if,
    Statement_while,
    Statement_println,
    Statement_assign,
    Statement_arrayAssign,
};

/* Type���������׵������� */
enum class TreeSubType_Type {
    Default,        // û�������ͣ�ֻ��������
    /*------��Ӧ��Ӧ�Ĳ���ʽ-----*/
    Type_boolean,
    Type_Int,
    Type_IntArray,
    Type_Identifier,
};
#pragma endregion



/*
 �����͵�ö�ٳ���˵���ַ���
*/
class TreeTypeConst {
public:

    /* MainType�ĳ����ַ�������������κ����� */
    const map<TreeMainType, string> mainTypeStr = {
        {TreeMainType::Goal, "Goal"},
        {TreeMainType::MainClass, "MainClass"},
        {TreeMainType::ClassDeclaration, "ClassDeclaration"},
        {TreeMainType::VarDeclaration, "VarDeclaration"},
        {TreeMainType::MethodDeclaration, "MethodDeclaration"},
        {TreeMainType::Type, "Type"},
        {TreeMainType::Statement, "Statement"},
        {TreeMainType::Expression, "Expression"},

        {TreeMainType::Identifier, "Identifier"},
        {TreeMainType::IntegerLeterial, "integerLiterial"},

        {TreeMainType::Default, "Default"},
    };

    /* subType_Expression�ĳ����ַ�������������κ����� */
    const map<TreeSubType_Expression, string> subType_ExpressionStr = {
        {TreeSubType_Expression::Default, "Expression-Default"},

        {TreeSubType_Expression::Exp_Bracket, "Expression-Bracket"},
        {TreeSubType_Expression::Exp_Not, "Expression-Not"},
        {TreeSubType_Expression::Exp_NewIdentifier, "Expression-NewIdentifier"},
        {TreeSubType_Expression::Exp_NewIntArray, "Expression-NewIntArray"},
        {TreeSubType_Expression::Exp_True, "Expression-True"},
        {TreeSubType_Expression::Exp_False, "Expression-False"},
        {TreeSubType_Expression::Exp_This, "Expression-This"},
        {TreeSubType_Expression::Exp_Identifier, "Expression-Identifier"},
        {TreeSubType_Expression::Exp_IntegerLiteral, "Expression-IntegerLiteral"},

        {TreeSubType_Expression::Exp_ArrayExpression, "Expression-ArrayExpression"},
        {TreeSubType_Expression::Exp_Length, "Expression-Length"},
        {TreeSubType_Expression::Exp_FunctionCall, "Expression-FunctionCall"},
        {TreeSubType_Expression::Exp_Operate, "Expression-Operate"},
    };

    /* subType_Statement�ĳ����ַ�������������κ����� */
    const map<TreeSubType_Statement, string> subType_StatementStr{
        {TreeSubType_Statement::Default, "Statement-Default"},

        {TreeSubType_Statement::Statement_Sequence, "Statement-Sequence"},
        {TreeSubType_Statement::Statement_if, "Statement-if"},
        {TreeSubType_Statement::Statement_while, "Statement-while"},
        {TreeSubType_Statement::Statement_println, "Statement-println"},
        {TreeSubType_Statement::Statement_assign, "Statement-assign"},
        {TreeSubType_Statement::Statement_arrayAssign, "Statement-arrayAssign"},
    };

    /* SubType_Type�ĳ����ַ�������������κ����� */
    const map<TreeSubType_Type, string> subType_TypeStr = {
        {TreeSubType_Type::Default, "Type-Default"},

        {TreeSubType_Type::Type_boolean, "Type-boolean"},
        {TreeSubType_Type::Type_Int, "Type-Int"},
        {TreeSubType_Type::Type_IntArray, "Type-IntArray"},
        {TreeSubType_Type::Type_Identifier, "Type-Identifier"},
    };
};

/*
 ���ڵ������
 ����Expresison��Statement��Type���������ͣ���Ҫ����Ӧ�������Ͳ�����
*/
class TreeType {
public:

    /*
     ���ö������Ϣ���ַ�������ʽ���ֳ���
     �쳣����
    */
    string toString() noexcept {

        TreeTypeConst treeTypeConst;

        switch (_mainType) {
        case TreeMainType::Expression:
            return treeTypeConst.subType_ExpressionStr.at(_subType_Expression);
            break;
        case TreeMainType::Statement:
            return treeTypeConst.subType_StatementStr.at(_subType_Statement);
            break;
        case TreeMainType::Type:
            return treeTypeConst.subType_TypeStr.at(_subType_Type);
            break;
        default:
            return treeTypeConst.mainTypeStr.at(_mainType);
            break;
        }
    }

#pragma region ��ȡ�ڵ���Ϣ�ķ���

    /* ��ýڵ����Ҫ����  */
    TreeMainType GetMainType() const { return _mainType; }

    /* ����Expression���͵Ľڵ㣬����������� */
    TreeSubType_Expression GetSubType_Expression() const { return _subType_Expression; }

    /* ����Statement���͵Ľڵ㣬����������� */
    TreeSubType_Statement GetSubType_Statement() const { return _subType_Statement; }

    /* ����Type���͵Ľڵ㣬����������� */
    TreeSubType_Type GetSubType_Type() const { return _subType_Type; }

#pragma endregion

#pragma region ���캯��

    /* ������ΪĬ������(Default)�����Ͷ���������ȫĬ�� */
    TreeType()
        : _mainType(TreeMainType::Default) {}

    /* ������Ϊָ�����͵����Ͷ���������ȫĬ�� */
    TreeType(TreeMainType mainType)
        :_mainType(mainType) {}

    /* ������Ϊ Expression ���ͣ�������ָ�� */
    TreeType(TreeSubType_Expression subType)
        : _mainType(TreeMainType::Expression), _subType_Expression(subType) {}

    /* ������Ϊ Statement ���ͣ�������ָ�� */
    TreeType(TreeSubType_Statement subType)
        : _mainType(TreeMainType::Statement), _subType_Statement(subType) {}

    /* ������Ϊ Type ���ͣ�������ָ�� */
    TreeType(TreeSubType_Type subType)
        : _mainType(TreeMainType::Type), _subType_Type(subType) {}

#pragma endregion

protected:
    TreeMainType _mainType = TreeMainType::Default;                         // �ڵ��������
    TreeSubType_Expression _subType_Expression = TreeSubType_Expression::Default;   // Expression���������׵�������
    TreeSubType_Type _subType_Type = TreeSubType_Type::Default;         // Type���������׵�������
    TreeSubType_Statement _subType_Statement = TreeSubType_Statement::Default;      // Statement���������׵�������
};
