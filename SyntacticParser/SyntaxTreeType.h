#pragma once


class TreeType {
public:
#pragma region �ڵ�����ö��

    /*
     ���ڵ����͵Ķ���
    */
    enum class MainType {
        // �﷨�ڵ�
        Goal,
        MainClass,
        ClassDeclaration,
        VarDeclaration,
        MethodDeclaration,
        Type,
        Statement,
        Expression,
        // �ʷ��ڵ�
        Identifier,
        IntegerLeterial,
        // ����Ľڵ�
        Default,
    };



    /*
     �﷨��-Expression-��������
    */
    enum class SubType_Expression {
        Exp_Bracket,    // Expression -> "(" Expression ")"
        Exp_Not,    // Expression -> "!" Expression
        Exp_NewIdentifier,  // Expression -> "new" Identifier "(" ")"
        Exp_NewIntArray,    // Expression -> "new" "int" "[" Expression "]"
        Exp_True,   // Expression -> "true"
        Exp_False,  // Expression -> "false"
        Exp_This,   // Expression -> "this"
        Exp_Identifier, // Expression -> Identifier
        Exp_IntegerLiteral, // Expression -> IntegerLiteral

        Exp_ArrayExpression,    // Expression -> Expression "[" Expression "]"
        Exp_Length, // Expression -> Expression "." "length"
        Exp_FunctionCall,   // Expression "." Identifier "(" [ Expression { "," Expression } ] ")"
        Exp_Operate,    // Expression ->  Expression ( "&&" | "<" | "+" | "-" | "*" ) Expression
    };

    /*
     �﷨��-Statement-��������
    */
    enum class SubType_Statement {
        Statement_Sequence,
        Statement_if,
        Statement_while,
        Statement_println,
        Statement_assign,
        Statement_arrayAssign,
    };
    /*
     �﷨��-Type-��������
    */
    enum class SubType_Type {
        Type_boolean,
        Type_Int,
        Type_IntArray,
        Type_Identifier,
    };
#pragma endregion

    MainType GetMainType() { return _mainType; }
    SubType_Expression GetSubType_Expression() { return _subType_Expression; }
    SubType_Statement GetSubType_Statement() { return _subType_Statement; }
    SubType_Type GetSubType_Type() { return _subType_Type; }
    
    TreeType()
        : _mainType(MainType::Default) {}
    TreeType(MainType mainType)
        :_mainType(mainType) {}
    TreeType(SubType_Expression subType)
        : _mainType(MainType::Expression), _subType_Expression(subType) {}
    TreeType(SubType_Statement subType)
        : _mainType(MainType::Statement), _subType_Statement(subType) {}
    TreeType(SubType_Type subType)
        : _mainType(MainType::Type), _subType_Type(subType) {}

protected:
    MainType _mainType = MainType::Default;                         // �ڵ����Ҫ����
    SubType_Expression _subType_Expression = SubType_Expression::Exp_ArrayExpression;       /*************/
    SubType_Type _subType_Type = SubType_Type::Type_boolean;                                /* �����Ҫ���Ͳ���Default����ô������������ѡһ */
    SubType_Statement _subType_Statement = SubType_Statement::Statement_arrayAssign;        /************* */
};
typedef TreeType::MainType TreeMainType;
typedef TreeType::SubType_Expression TreeSubType_Expression;
typedef TreeType::SubType_Statement TreeSubType_Statement;
typedef TreeType::SubType_Type TreeSybType_Type;