#pragma once
#include <string>
#include "SyntaxTreeType.h"
#include "TokenReader.h"

/*
 �﷨����Ķ���
*/
class SyntaxError {
private:
    int _index;                             // �����token��reader�е�λ�á����ִ���ʱ��ʹ��GetIndex()���ݸò���
    std::string _message;                   // �������Ϣ
    TreeNodeMainTypeEnum _treeMainType;     // ��λ���ĸ��﷨����
    union {
        TreeNodeSubTypeEnum_Expression _treeSubType_Expression;
        TreeNodeSubTypeEnum_Statement _treeSubType_Statement;
        TreeNodeSubTypeEnum_Type _treeSubType_Type;
    };
    void _InitAssist(shared_ptr<const TokenReader> reader, std::string message, TreeNodeMainTypeEnum treeMainType) {
        _index = reader->GetIndex();
        _message = message;
        _treeMainType = treeMainType;
    }

public:
    /*
     ���캯��
     �����ó��ִ�����﷨����������
    */
    SyntaxError(shared_ptr<const TokenReader> reader, std::string message, TreeNodeMainTypeEnum treeMainType) {
        _InitAssist(reader, message, treeMainType);
    }
    /*
     ���캯��
     ���ó��ִ�����﷨���������ͺ�������
    */
    SyntaxError(shared_ptr<const TokenReader> reader, std::string message, TreeNodeSubTypeEnum_Expression treeSubType_Expression) {
        _InitAssist(reader, message, TreeNodeMainTypeEnum::Expression);
        _treeSubType_Expression = treeSubType_Expression;
    }
    /*
     ���캯��
     ���ó��ִ�����﷨���������ͺ�������
    */
    SyntaxError(shared_ptr<const TokenReader> reader, std::string message, TreeNodeSubTypeEnum_Statement treeSubType_Statement) {
        _InitAssist(reader, message, TreeNodeMainTypeEnum::Statement);
        _treeSubType_Statement = treeSubType_Statement;
    }
    /*
     ���캯��
     ���ó��ִ�����﷨���������ͺ�������
    */
    SyntaxError(shared_ptr<const TokenReader> reader, std::string message, TreeNodeSubTypeEnum_Type treeSubType_Type) {
        _InitAssist(reader, message, TreeNodeMainTypeEnum::Type);
        _treeSubType_Type = treeSubType_Type;
    }
};