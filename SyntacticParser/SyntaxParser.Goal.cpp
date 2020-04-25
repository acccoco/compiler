#include "SyntaxParser.h"
using namespace std;

/*
 �ݹ��½���Goal
 ���ʶ��ʧ�ܣ�reader��ָ������
*/
shared_ptr<SyntaxTreeNode> SyntaxParser::Goal(list<shared_ptr<SyntaxError>>& errorList) {

    errorList.clear();                              // ��մ����б�
    const int curIndex = _reader->GetIndex();       // reader��ǰ��λ��
    SyntaxTreeNodePtr tempTreeNode;                 // �ռ��������ʱ�ڵ�
    list<shared_ptr<SyntaxError>> tempErrorList;    // �ռ��������ʱ����
    auto curTreeType = TreeNodeMainTypeEnum::Goal;  // ��ǰ���ڵ�����

    /**********************************
     �������ڵ�
     �жϵ�һ��token�Ƿ����
    ************************************/
    ETokenPtr firstToken = _reader->SeekToken();
    if (firstToken == NULL) {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��ʼtokenʧ��", curTreeType));
        return NULL;
    }
    SyntaxTreeNodePtr root(new SyntaxTreeNode(curTreeType, firstToken->GetLineNum()));


    /**********************************
     ��ȡMainClass��������һ��
    ************************************/
    SyntaxTreeNodePtr mainClass = MainClass(tempErrorList);
    if (mainClass == NULL) {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��MainClassʧ��", curTreeType));
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());
        _reader->SetIndex(curIndex);
        return NULL;
    }
    else {
        root->SetChild(mainClass);
    }
    /**********************************
     ��ȡ�ඨ��ClassDeclaration��0������
    ************************************/
    SyntaxTreeNodePtr preNode = mainClass;
    SyntaxTreeNodePtr classDeclaration;
    while (classDeclaration = ClassDeclaration(tempErrorList)) {
        preNode->SetSubling(classDeclaration);
        preNode = classDeclaration;
    }
    /**********************************
     ��EOF����
    ************************************/
    if (_reader->IsEnd() == false) {
        errorList.emplace_back(new SyntaxError(_reader, "���õ����ļ���β", curTreeType));
        _reader->SetIndex(curIndex);
        return NULL;
    }

    return root;
}