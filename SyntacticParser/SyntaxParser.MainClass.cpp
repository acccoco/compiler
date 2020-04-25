#include "SyntaxParser.h"
using namespace std;



/*
 �ݹ��½�
 MainClass
*/
shared_ptr<SyntaxTreeNode> SyntaxParser::MainClass(list<shared_ptr<SyntaxError>>& errorList) {

    errorList.clear();                                      // ��մ����б�    
    const int curIndex = _reader->GetIndex();               // reader��ǰ��λ��    
    SyntaxTreeNodePtr tempTreeNode;                         // �ռ��������ʱ�ڵ�          
    list<shared_ptr<SyntaxError>> tempErrorList;            // �ռ��������ʱ����
    auto curTreeType = TreeNodeMainTypeEnum::MainClass;     // ��ǰ���ڵ�����              


    // �жϵ�һ��Token�Ƿ����
    ETokenPtr firstToken = _reader->SeekToken();
    if (firstToken == NULL) {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ���һ��tokenʧ��", curTreeType));
        return NULL;
    }
    // �������ڵ�
    SyntaxTreeNodePtr root(new SyntaxTreeNode(curTreeType, firstToken->GetLineNum()));
    


    /******************
     "class"
     ********************/
    if (_MatchTokenSequence({ {TokenTypeEnum::KEYWORD, "class"} }) == false) {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��ؼ���classʧ��", curTreeType));
        _reader->SetIndex(curIndex);
        return NULL;
    }
    /******************
     ����
     Identifier
     ********************/
    if (tempTreeNode = _MatchIdentifier()) {
        root->SetChild(tempTreeNode);
    }
    else {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ������ʧ��", curTreeType));
        _reader->SetIndex(curIndex);
        return NULL;
    }
    /******************
     "{ public static void main ( String [ ]"
     ********************/
    vector<pair<TokenTypeEnum, string>> tokenSequence_1 = {
        {TokenTypeEnum::SYMBOL, "{"},
        {TokenTypeEnum::KEYWORD, "public"},
        {TokenTypeEnum::KEYWORD, "static"},
        {TokenTypeEnum::KEYWORD, "void"},
        {TokenTypeEnum::KEYWORD, "main"},
        {TokenTypeEnum::SYMBOL, "("},
        {TokenTypeEnum::KEYWORD, "String"},
        {TokenTypeEnum::SYMBOL, "["},
        {TokenTypeEnum::SYMBOL, "]"},
    };
    if (_MatchTokenSequence(tokenSequence_1) == false) {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��{public static void main(String[]ʧ��", curTreeType));
        _reader->SetIndex(curIndex);
        return NULL;
    }
    /******************
     ������
     Identifier
     ********************/
    tempTreeNode = _MatchIdentifier();
    if (tempTreeNode = _MatchIdentifier()) {
        root->GetChild()->SetSubling(tempTreeNode);
    }
    else {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��������������ʧ��", curTreeType));
        _reader->SetIndex(curIndex);
        return NULL;
    }
    /******************
     ") {"
     ********************/
    vector<pair<TokenTypeEnum, string>> tokenSequence_2 = {
        {TokenTypeEnum::SYMBOL, ")"},
        {TokenTypeEnum::SYMBOL, "{"},
    };
    if (_MatchTokenSequence(tokenSequence_1) == false) {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��){ʧ��", curTreeType));
        _reader->SetIndex(curIndex);
        return NULL;
    }
    /******************
     ʶ��Statement
     ********************/
    if (tempTreeNode = Statement(tempErrorList)) {
        root->GetChild()->GetSubling()->SetSubling(tempTreeNode);
    }
    else {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��Statementʧ��", curTreeType));
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());
        _reader->SetIndex(curIndex);
        return NULL;
    }
    /******************
     "} }"
     ********************/
    vector<pair<TokenTypeEnum, string>> tokenSequence_3 = {
        {TokenTypeEnum::SYMBOL, "}"},
        {TokenTypeEnum::SYMBOL, "}"},
    };
    if (_MatchTokenSequence(tokenSequence_1) == false) {
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��}}ʧ��", curTreeType));
        _reader->SetIndex(curIndex);
        return NULL;
    }

    return root;
}