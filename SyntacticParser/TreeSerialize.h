#pragma once
#include "TreeNode.h"
#include "TreeType.h"
#include <list>
#include <string>
#include <map>
using namespace std;

/*
 �������л������Ϊ�ַ�������
*/
class TreeSerialize {
public:

    /*
     ��AST���л�
     �쳣�������׳��쳣
    */
    static list<string> Serialize(TreeNodePtr root)noexcept {
        
        const string rootPrefix = "    ";       // ���ڵ��ǰ׺�ǿո�

        return _PreTravelSerialize(rootPrefix, root);

    }

protected:

    /*
     ��ASTǰ��������õ��ַ�������
     ��ʽ�涨���ӽڵ�����4λ
    */
    static list<string> _PreTravelSerialize(string prefix, TreeNodePtr root) {

        /* ���ڿ�����ʾ��ʽ�ĳ���ֵ */
        const size_t replaceLength = 4;          // �滻�ַ��ĳ���
        const string replaceLast = "    ";      // �滻����ʱ���ýڵ�û��subling
        const string replaceNotLast = " |  ";   // �滻����ʱ���ýڵ���subling
        const string childPrefixAdd = " +- ";   // Ϊ�ӽڵ����ӵ�ǰ׺

        list<string> result;

        /* ��Ӹ��ڵ� */
        if (root == nullptr) return result;
        result.push_back(prefix + _NodeToString(root));

        /* �����ӽڵ��ǰ׺ */
        string childPrefix = prefix;
        childPrefix.erase(prefix.size() - replaceLength, replaceLength);    // �滻��nλ
        childPrefix += (root->Subling.Get() == nullptr) ? replaceLast : replaceNotLast;
        childPrefix += childPrefixAdd;

        /* ����ӽڵ� */
        TreeNodePtr child = root->Child.Get();
        while (child != nullptr) {
            auto childResult = _PreTravelSerialize(childPrefix, child);
            result.insert(result.end(), childResult.begin(), childResult.end());
            child = child->Subling.Get();
        }

        return result;
    }

    /*
     ��ͬ�ڵ����ݵĳ���ֵ���ڵ����Ͳ�ͬ��ֵ��ͬ
    */
    class NodeStrConst {
    public:

        /* �����ͽڵ��˵��ֵ */
        const map<TreeMainType, string> nodeStr_MainType = {

            /* Default��Ϊ���� */
            {TreeMainType::Default, "Sequence"},

            /* �﷨�ڵ� */
            {TreeMainType::Goal, "Goal"},
            {TreeMainType::ClassDeclaration, "ClassDeclaration"},
            {TreeMainType::MainClass, "MainClass"},
            {TreeMainType::MethodDeclaration, "MethodDeclaration"},
            {TreeMainType::VarDeclaration, "VarDeclaration"},
        };

        /* Type���ͽڵ��˵��ֵ */
        const map<TreeSubType_Type, string> nodeStr_Type = {
            
            /* Type������ */
            {TreeSubType_Type::Type_boolean, "type: boolean"},
            {TreeSubType_Type::Type_Identifier, "type: "},
            {TreeSubType_Type::Type_Int, "type: int"},
            {TreeSubType_Type::Type_IntArray, "type: int[]"},

            /* Type������ */
            {TreeSubType_Type::Default, "type"},
        };

        /* Statement���ͽڵ��˵��ֵ */
        const map<TreeSubType_Statement, string> nodeStr_Statement = {

            /* Statement������ */
            {TreeSubType_Statement::Statement_arrayAssign, "statement: array assign"},
            {TreeSubType_Statement::Statement_assign, "statement: assign"},
            {TreeSubType_Statement::Statement_if, "statement: if"},
            {TreeSubType_Statement::Statement_println, "statement: println"},
            {TreeSubType_Statement::Statement_Sequence, "statement sequence: "},
            {TreeSubType_Statement::Statement_while, "statement: while"},

            /* Statement������ */
            {TreeSubType_Statement::Default, "statement: "},
        };

        /* Expression���ͽڵ��˵��ֵ */
        const map<TreeSubType_Expression, string> nodeStr_Expression = {

            /* ����ݹ����ʽ */
            {TreeSubType_Expression::Exp_Bracket, "expression: (expression)"},
            {TreeSubType_Expression::Exp_False, "expression: false"},
            {TreeSubType_Expression::Exp_Identifier, "expression: Identifier"},
            {TreeSubType_Expression::Exp_IntegerLiteral, "expression: IntegerLiteral"},
            {TreeSubType_Expression::Exp_NewIdentifier, "expression: new class"},
            {TreeSubType_Expression::Exp_NewIntArray, "expression: new int[]"},
            {TreeSubType_Expression::Exp_Not, "expression: !expression"},
            {TreeSubType_Expression::Exp_This, "expression: this"},
            {TreeSubType_Expression::Exp_True, "expression: true"},

            /* ��ݹ����ʽ */
            {TreeSubType_Expression::Exp_ArrayExpression, "expression: expression[expression]"},
            {TreeSubType_Expression::Exp_Length, "expression: expression.length"},
            {TreeSubType_Expression::Exp_FunctionCall, "expression: functioncall"},
            {TreeSubType_Expression::Exp_Operate, "expression: operate "},

            /* Ĭ������ */
            {TreeSubType_Expression::Default, "expression: "},
        };

        /* �ڵ�Ϊ�յ����� */
        const string nodeStr_Null = "";

        /* �ʷ��ڵ�IntegerLiteral��˵��ֵ */
        string nodeStr_Integer(int numValue) {
            char temp[256];
            string str = "IntegerLiteral<";
            _itoa_s(numValue, temp, 10);
            str += temp;
            str += ">";
            return str;
        }

        /* �ʷ��ڵ�Identifier��˵��ֵ */
        string nodeStr_Identifier(string strValue) {
            return "Ientifier<" + strValue + ">";
        }
    };

    /*
     ���ݽڵ����ͣ����ڵ�ת��Ϊ�ַ���
    */
    static string _NodeToString(TreeNodePtr node) {

        NodeStrConst nodeStrConst;      // �ڵ�˵��ֵ�����������
        const auto treeType = node->Type.Get();     // �ڵ������
        const auto mainType = treeType.GetMainType();   // ������
        const auto subType_Expression = treeType.GetSubType_Expression();
        const auto subType_Statement = treeType.GetSubType_Statement();
        const auto subType_Type = treeType.GetSubType_Type();

        /* ���ڵ��Ƿ���� */
        if (node == nullptr) return nodeStrConst.nodeStr_Null;

        string str = "";

        /* ��ͬ�Ľڵ����ͣ����в�ͬ��ֵ */
        switch (node->Type.Get().GetMainType()) {

            /* û�������͵��﷨�ڵ� */
        case TreeMainType::Goal:
        case TreeMainType::ClassDeclaration:
        case TreeMainType::MainClass:
        case TreeMainType::MethodDeclaration:
        case TreeMainType::VarDeclaration:
            str = nodeStrConst.nodeStr_MainType.at(mainType);
            break;

            /* Default�ڵ㣨�������ϣ� */
        case TreeMainType::Default:
            str = nodeStrConst.nodeStr_MainType.at(mainType);
            break;

            /* �ʷ��ڵ� */
        case TreeMainType::IntegerLeterial:
            str = nodeStrConst.nodeStr_Integer(node->NumValue.Get());
            break;
        case TreeMainType::Identifier:
            str = nodeStrConst.nodeStr_Identifier(node->StrValue.Get());
            break;

            /* ���������͵Ľڵ� Type */
        case TreeMainType::Type:
            str = nodeStrConst.nodeStr_Type.at(subType_Type);
            break;

            /* ���������͵Ľڵ� Statement */
        case TreeMainType::Statement:
            str = nodeStrConst.nodeStr_Statement.at(subType_Statement);
            break;

            /* ���������͵Ľڵ� Expression */
        case TreeMainType::Expression:
            if (subType_Expression == TreeSubType_Expression::Exp_Operate) {
                str = nodeStrConst.nodeStr_Expression.at(TreeSubType_Expression::Exp_Operate) + node->StrValue.Get();
            }
            else {
                str = nodeStrConst.nodeStr_Expression.at(subType_Expression);
            }
            break;

        default:;/* never */
        }
        return str;
    }

};
