#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <list>
#include "TokenReader.h"
#include "TreeNode.h"
#include "SyntaxError.h"
#include "Goal.h"

/*
 �﷨��������ʵ��
 ���������token����������﷨�����õ��﷨����
 ����֮��ͨ����������ȡ�������
*/
class SyntaxParser {
protected:
    
    shared_ptr<TokenReader> _reader;                    // token�Ķ�ȡ��
    TreeNodePtr _root;                            // �������������
    list<shared_ptr<SyntaxError>> _errorList;          // �����������������

public:

    /* �﷨��������������б� */
    ROProperty<list<shared_ptr<SyntaxError>>> ErrorList = ROProperty<list<shared_ptr<SyntaxError>>>(_errorList);
    
    /* �﷨����������﷨�������� */
    ROProperty<TreeNodePtr> Root = ROProperty<TreeNodePtr>(_root);
#pragma region ���캯������������

    /*
     ͨ��reader����ʼ���﷨������
     �쳣�����readerΪ�գ����׳�string�쳣
    */
    SyntaxParser(shared_ptr<TokenReader> reader): _reader(reader) {
        if (reader = nullptr)
            throw string("readerΪ��");
    }
#pragma endregion

    /*
     ���еݹ��½��﷨��������
     �������ڶ����������
    */
    void Parse() {
        auto goal = RDCase_Goal(_reader);
        goal.Run();
        _root = goal.Root.Get();
        _errorList = goal.Errors.Get();
    }
};

