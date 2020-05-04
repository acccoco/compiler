#pragma once
#include <string>
#include <memory>
#include "TreeType.h"

using namespace std;


/*
 �﷨�������ڵ�
 ���ֵܽڵ�Ķ�������
 node �� subling
   ��
 child
 
*/
class TreeNode {
public:

    /* �﷨�������ڵ� */
    typedef std::shared_ptr<TreeNode> Ptr;
private:

    int _lineNum;               // ���ڵ��Ӧ���к�
    TreeType _treeType;         // ���ڵ������
    int _numValue;              // ����ֵ�����ַ���ֵ��ѡһ
    std::string _strValue;      // �ַ���ֵ��������ֵ��ѡһ

    Ptr _child;                     // �ӽڵ�
    Ptr _subling;                   // �ֵܽڵ�

public:

#pragma region ����

    Property<string> StrValue = Property<string>(_strValue);    // ���ڵ���ַ���ֵ
    Property<int> NumValue = Property<int>(_numValue);          // ���ڵ������ֵ
    Property<int> LineNum = Property<int>(_lineNum);            // ���ڵ��Ӧ���к�
    Property<TreeType> Type = Property<TreeType>(_treeType);    // ���ڵ������

    Property<Ptr> Child = Property<Ptr>(_child);                // ���ڵ�ĺ���
    Property<Ptr> Subling = Property<Ptr>(_subling);            // ���ڵ���ֵܽڵ�

#pragma endregion

#pragma region ���캯��

    /*
     ����һ�����ڵ�
     �ֵܽڵ���ӽڵ�Ϊ��
     �ַ���ֵĬ��Ϊ�մ�������ֵĬ��Ϊ0
    */
    TreeNode(TreeType treeType, int lineNum, string strValue = "", int numValue = 0) noexcept
        : _treeType(treeType), _lineNum(lineNum), _strValue(strValue), _numValue(numValue) {}

    /* 
     ����һ�����ڵ�
     ֻ��ʹ��Identifer��IntegerLiteral��token����˶���
     �����������ͣ����׳�string���͵��쳣
     */
    TreeNode(ETokenPtr token)
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

/* �﷨�����������ڵ� */
typedef shared_ptr<TreeNode> TreeNodePtr;