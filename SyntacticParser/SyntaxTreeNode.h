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
    Ptr _child;                     // �ӽڵ�
    Ptr _subling;                   // �ֵܽڵ�
    int _lineNum;                   // �к�
    TreeType _treeType;
    int _numValue;                  // ����ֵ
    std::string _strValue;          // �ַ���ֵ

public:

#pragma region ����
    Property<string> StrValue = Property<string>(_strValue);
    Property<int> NumValue = Property<int>(_numValue);
    Property<int> LineNum = Property<int>(_lineNum);
    Property<Ptr> Child = Property<Ptr>(_child);
    Property<Ptr> Subling = Property<Ptr>(_subling);
    Property<TreeType> Type = Property<TreeType>(_treeType);

#pragma endregion

#pragma region ���캯��

    /* һ�㹹�캯�� */
    SyntaxTreeNode(TreeType treeType, int lineNum, string strValue = "", int numValue = 0)
        : _treeType(treeType), _lineNum(lineNum), _strValue(strValue), _numValue(numValue) {}

    /* ʹ��token���죬ֻ��ʹ��Identifer��IntegerLiteral��token����˶��� */
    SyntaxTreeNode(ETokenPtr token)
        : _lineNum(token->LineNum.Get()), _strValue(token->StrValue.Get()), _numValue(token->NumValue.Get()) {
        if (token->TokenType.Get() == TokenTypeEnum::IDENTIFIER)
            _treeType = TreeType(TreeMainType::Identifier);
        else if (token->TokenType.Get() == TokenTypeEnum::INTEGER)
            _treeType = TreeType(TreeMainType::IntegerLeterial);
        else
            throw string("����ʹ��Identifer��IntegerLiteral��token����˶���");
    }
#pragma endregion

};

typedef shared_ptr<SyntaxTreeNode> SyntaxTreeNodePtr;