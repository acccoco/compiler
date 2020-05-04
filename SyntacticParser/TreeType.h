#pragma once

/*
 ���ڵ������
 ����Expresison��Statement��Type���������ͣ���Ҫ����Ӧ�������Ͳ�����
*/
class TreeType {
public:
#pragma region �ڵ�����ö��

    /* �﷨�������ڵ�������� */
    enum class MainType {

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
    enum class SubType_Expression {
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
    enum class SubType_Statement {
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
    enum class SubType_Type {
        Default,        // û�������ͣ�ֻ��������
        /*------��Ӧ��Ӧ�Ĳ���ʽ-----*/
        Type_boolean,
        Type_Int,
        Type_IntArray,
        Type_Identifier,
    };
#pragma endregion

#pragma region ��ȡ�ڵ���Ϣ�ķ���

    /* ��ýڵ����Ҫ����  */
    MainType GetMainType() { return _mainType; }

    /* ����Expression���͵Ľڵ㣬����������� */
    SubType_Expression GetSubType_Expression() { return _subType_Expression; }

    /* ����Statement���͵Ľڵ㣬����������� */
    SubType_Statement GetSubType_Statement() { return _subType_Statement; }

    /* ����Type���͵Ľڵ㣬����������� */
    SubType_Type GetSubType_Type() { return _subType_Type; }

#pragma endregion

#pragma region ���캯��

    /* ������ΪĬ������(Default)�����Ͷ���������ȫĬ�� */
    TreeType()
        : _mainType(MainType::Default) {}

    /* ������Ϊָ�����͵����Ͷ���������ȫĬ�� */
    TreeType(MainType mainType)
        :_mainType(mainType) {}

    /* ������Ϊ Expression ���ͣ�������ָ�� */
    TreeType(SubType_Expression subType)
        : _mainType(MainType::Expression), _subType_Expression(subType) {}

    /* ������Ϊ Statement ���ͣ�������ָ�� */
    TreeType(SubType_Statement subType)
        : _mainType(MainType::Statement), _subType_Statement(subType) {}

    /* ������Ϊ Type ���ͣ�������ָ�� */
    TreeType(SubType_Type subType)
        : _mainType(MainType::Type), _subType_Type(subType) {}

#pragma endregion

protected:
    MainType _mainType = MainType::Default;                         // �ڵ��������
    SubType_Expression _subType_Expression = SubType_Expression::Default;   // Expression���������׵�������
    SubType_Type _subType_Type = SubType_Type::Default;         // Type���������׵�������
    SubType_Statement _subType_Statement = SubType_Statement::Default;      // Statement���������׵�������
};

/* ��Ҫ���� */
typedef TreeType::MainType TreeMainType;

/* Expression ��Ҫ���͵ģ����׵������� */
typedef TreeType::SubType_Expression TreeSubType_Expression;

/* Statement ��Ҫ���͵ģ����׵������� */
typedef TreeType::SubType_Statement TreeSubType_Statement;

/* Type ��Ҫ���͵ģ����׵������� */
typedef TreeType::SubType_Type TreeSybType_Type;