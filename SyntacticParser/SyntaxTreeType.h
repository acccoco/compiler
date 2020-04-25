#pragma once
/*
 ���ڵ����͵Ķ���
*/
enum class TreeNodeMainTypeEnum {
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
enum class TreeNodeSubTypeEnum_Expression {
    Exp_Bracket,
    Exp_Not,
    Exp_NewIdentifier,
    Exp_NewIntArray,
    Exp_True,
    Exp_False,
    Exp_This,
    Exp_Identifier,
    Exp_IntegerLiteral,

    Exp_ArrayExpression,
    Exp_Length,
    Exp_FunctionCall,
    Exp_Operate,
};

/*
 �﷨��-Statement-��������
*/
enum class TreeNodeSubTypeEnum_Statement {
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
enum class TreeNodeSubTypeEnum_Type {
    Type_boolean,
    Type_Int,
    Type_IntArray,
    Type_Identifier,
};


///*
// �﷨���ڵ������
//*/
//class TreeNodeType {
//protected:
//    /*
//     ������޷�ʹ��
//    */
//    TreeNodeType() {
//        mainKind = TreeNodeMainTypeEnum::Default;
//    }
//public:
//    TreeNodeMainTypeEnum mainKind;
//};
///*
// Expression-���ڵ������
//*/
//class TreeNodeType_Expression :public TreeNodeType {
//public:
//    TreeNodeSubTypeEnum_Expression subKind;
//    TreeNodeType_Expression(TreeNodeSubTypeEnum_Expression subKind) {
//        mainKind = TreeNodeMainTypeEnum::Expression;
//        this->subKind = subKind;
//    }
//};
///*
// Statement-���ڵ������
//*/
//class TreeNodeType_Statement :public TreeNodeType {
//public:
//    TreeNodeSubTypeEnum_Statement subKind;
//    TreeNodeType_Statement(TreeNodeSubTypeEnum_Statement subKind) {
//        mainKind = TreeNodeMainTypeEnum::Statement;
//        this->subKind = subKind;
//    }
//};
///*
// Type-���ڵ������
//*/
//class TreeNodeType_Type :public TreeNodeType {
//public:
//    TreeNodeSubTypeEnum_Type subKind;
//    TreeNodeType_Type(TreeNodeSubTypeEnum_Type subKind) {
//        mainKind = TreeNodeMainTypeEnum::Type;
//        this->subKind = subKind;
//    }
//};
///*
// �﷨���ڵ������
// �ʺ�û�������͵Ľڵ�
//*/
//class TreeNodeType_Alone :public TreeNodeType {
//public:
//    TreeNodeType_Alone(TreeNodeMainTypeEnum mainKind) {
//        this->mainKind = mainKind;
//    }
//};