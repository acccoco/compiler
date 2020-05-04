#pragma once
#include <string>
#include "TreeType.h"
#include "TokenReader.h"

/*
 �﷨����Ķ���
*/
class SyntaxError {
protected:
    shared_ptr<const TokenReader> _reader;      // TODO����Ӧ�����������reader����ȡһ�㶫�������ͺ���
    std::string _message;             // �������ʾ��Ϣ
    TreeType _treeType;         // ��������ʱ�����ڵ�����


public:

    /*
     ����һ���﷨�������
     ������reader�����ڵõ�������������Ϣ�����������кŵ�
     ������message���������ʾ��Ϣ
     ������treeType�����������﷨��λ��
    */
    SyntaxError(shared_ptr<const TokenReader> reader, std::string message, TreeType treeType)
        : _reader(reader), _message(message), _treeType(treeType) {}

};

/* �﷨������� */
typedef shared_ptr<SyntaxError> SyntaxErrorPtr;