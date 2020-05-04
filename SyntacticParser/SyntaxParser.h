#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <list>
#include "TokenReader.h"
#include "SyntaxTreeNode.h"
#include "SyntaxError.h"
#include "Goal.h"

/*
 �﷨��������ʵ��
 ���������token����������﷨��������﷨����
*/
class SyntaxParser {
protected:
    typedef SyntaxTreeNode::Ptr SyntaxTreeNodePtr;
    shared_ptr<TokenReader> _reader;                    // token�Ķ�ȡ��
    SyntaxTreeNodePtr _root;                            // �������������
    list<shared_ptr<SyntaxError>> _errorList;          // �����������������

public:

    ROProperty<list<shared_ptr<SyntaxError>>> ErrorList = ROProperty<list<shared_ptr<SyntaxError>>>(_errorList);
    ROProperty<SyntaxTreeNodePtr> Root = ROProperty<SyntaxTreeNodePtr>(_root);
#pragma region ���캯������������
    /*
     ͨ��reader����ʼ��
    */
    SyntaxParser(shared_ptr<TokenReader> reader): _reader(reader) {
        if (reader = nullptr)
            throw string("readerΪ��");
    }
#pragma endregion

    /*
     ���еݹ��½��﷨����
     �������ڶ����������
    */
    void Parse() {
        auto goal = RDCase_Goal(_reader);
        goal.Run();
        _root = goal.Root.Get();
        _errorList = goal.Errors.Get();
    }
};

