#pragma once
#include <string>
#include <memory>
#include "SyntaxTreeType.h"

using namespace std;




/*
 �﷨�������ڵ�
*/
class SyntaxTreeNode {
public:
    typedef std::shared_ptr<SyntaxTreeNode> Ptr;
private:
    Ptr _child;         // �ӽڵ�
    Ptr _subling;       // �ֵܽڵ�
    int _lineNum;       // �к�

    TreeNodeMainTypeEnum _mainType;
    union {
        TreeNodeSubTypeEnum_Expression _subType_Expression;
        TreeNodeSubTypeEnum_Statement _subType_Statement;
        TreeNodeSubTypeEnum_Type _subType_Type;
    };

    int _numValue;              // ����ֵ
    std::string _strValue;      // �ַ���ֵ

    /*
     ���ڸ������캯���ĳ�ʼ������
    */
    void _InitAssist(TreeNodeMainTypeEnum mainType, int lineNum, Ptr child, Ptr subling, int numValue, string strValue) {
        _mainType = mainType;
        _numValue = numValue;
        _strValue = strValue;
        _lineNum = lineNum;
        _child = child;
        _subling = subling;
    }
public:
    
    /*
     ���캯������ʼ��һ��Expression-���ڵ�
    */
    SyntaxTreeNode(TreeNodeSubTypeEnum_Expression subKind, int lineNum, Ptr child = NULL, Ptr subling = NULL) {
        _InitAssist(TreeNodeMainTypeEnum::Expression, lineNum, child, subling, 0, "");
        _subType_Expression = subKind;
    }
    /*
     ���캯������ʼ��һ��Statement-���ڵ�
    */
    SyntaxTreeNode(TreeNodeSubTypeEnum_Statement subKind, int lineNum, Ptr child = NULL, Ptr subling = NULL) {
        _InitAssist(TreeNodeMainTypeEnum::Statement, lineNum, child, subling, 0, "");
        _subType_Statement = subKind;
    }
    /*
     ���캯������ʼ��һ��Type-���ڵ�
    */
    SyntaxTreeNode(TreeNodeSubTypeEnum_Type subKind, int lineNum, Ptr child = NULL, Ptr subling = NULL) {
        _InitAssist(TreeNodeMainTypeEnum::Type, lineNum, child, subling, 0, "");
        _subType_Type = subKind;
    }
    /*
     ���캯������ʼ��һ��Identifier-���ڵ�
    */
    SyntaxTreeNode(string strValue, int lineNum, Ptr child = NULL, Ptr subling = NULL) {
        _InitAssist(TreeNodeMainTypeEnum::Identifier, lineNum, child, subling, 0, strValue);
    }
    /*
     ���캯������ʼ��һ��IntegerLiteral-���ڵ�
    */
    SyntaxTreeNode(int numValue, int lineNum, Ptr child = NULL, Ptr subling = NULL) {
        _InitAssist(TreeNodeMainTypeEnum::IntegerLeterial, lineNum, child, subling, numValue, "");
    }
    /*
     ���캯����ֻ����mainType
     Default��Goal, MainClass, ClassDeclaration, VarDeclaration, MethodDeclaration,
    */
    SyntaxTreeNode(TreeNodeMainTypeEnum mainKind, int lineNum, Ptr child = NULL, Ptr subling = NULL) {
        _InitAssist(mainKind, lineNum, child, subling, 0, "");
    }
    /*
     ��ýڵ��ֵ
    */
    string GetStrValue() {
        return _strValue;
    }
    /*
     ��ýڵ��ֵ
    */
    int GetNumValue() {
        return _numValue;
    }
    /*
     ��ýڵ���к�
    */
    int GetLineNum() {
        return _lineNum;
    }

    /*
     ���ú��ӽڵ�
    */
    void SetChild(Ptr child) {
        _child = child;
    }
    /*
     �����ֵܽڵ�
    */
    void SetSubling(Ptr subling) {
        _subling = subling;
    }
    /*
     ��ú��ӽڵ�
    */
    Ptr GetChild() {
        return _child;
    }
    /*
     ����ֵܽڵ�
    */
    Ptr GetSubling() {
        return _subling;
    }
    /*
     �������
    */
    TreeNodeMainTypeEnum GetMainType() {
        return _mainType;
    }
    /*
     ��������ͣ�Expression
    */
    TreeNodeSubTypeEnum_Expression GetSubType_Expression() {
        return _subType_Expression;
    }
    /*
     ��������ͣ�Statement
    */
    TreeNodeSubTypeEnum_Statement GetSubType_Statement() {
        return _subType_Statement;
    }
    /*
     ��������ͣ�Type
    */
    TreeNodeSubTypeEnum_Type GetSubType_Type() {
        return _subType_Type;
    }
    /*
     ���������ͣ�Expression
    */
    void SetSubType(TreeNodeSubTypeEnum_Expression subType) {
        this->_subType_Expression = subType;
    }
    /*
     ���������ͣ�Statement
    */
    void SetSubType(TreeNodeSubTypeEnum_Statement subType) {
        this->_subType_Statement = subType;
    }
    /*
     ���������ͣ�Type
    */
    void SetSubType(TreeNodeSubTypeEnum_Type subType) {
        this->_subType_Type = subType;
    }
};

