#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <stack>
#include <list>
#include "TokenReader.h"
#include "SyntaxTreeNode.h"
#include "SyntaxError.h"

/*
 �﷨��������ʵ��
 ���������token����������﷨��������﷨����
*/
class SyntaxParser
{
private:
    typedef SyntaxTreeNode::Ptr SyntaxTreeNodePtr;
    shared_ptr<TokenReader> _reader;                    // token�Ķ�ȡ��

    /*
     ʶ��ؼ��ֻ��߷���
     �������Ĳ��� keyword �� symbol ����ʶ��ʧ��
     �����ƥ�䣬reader �� index �����
    */
    bool _MatchKeywordOrSymbol(TokenTypeEnum tokenType, string str) {
        // �ж������Ƿ�ϸ�
        if (tokenType != TokenTypeEnum::KEYWORD && tokenType != TokenTypeEnum::SYMBOL) {
            return false;
        }
        // ����ƥ��
        ETokenPtr token = _reader->SeekToken();
        if (token->GetTokenType() == tokenType && token->GetStrValue() == str) {
            _reader->GetToken();
        }
        else {
            return false;
        }
    }

    /*
     ʶ��һ��Token
     ֻ����ʶ��keywords��symbol���͵ģ�������ʶ��Identifier����IntegerLiteral
     �����ƥ�䣬_reader�����
    */
    bool _MatchTokenSequence(vector<pair<TokenTypeEnum, string>> tokens) {
        int step = 0;       // �Ѿ�ʶ���˵Ĳ��������ڻ���
        int tokensCount = tokens.size();

        // ���Խ���ƥ��
        ETokenPtr curToken;
        for (int i = 0; i < tokensCount; ++i) {
            if (tokens[i].first != TokenTypeEnum::KEYWORD && tokens[i].first != TokenTypeEnum::SYMBOL)
                break;
            curToken = _reader->GetToken();
            if (curToken
                && curToken->GetTokenType() == tokens[i].first
                && curToken->GetStrValue() == tokens[i].second) {
                ++step;
            }
            else {
                break;
            }
        }

        // �Ƿ���ȫƥ�䣬����ȫƥ��ͻ���
        if (step == tokensCount) {
            return true;
        }
        else {
            _reader->GoBack(step);
            return false;
        }
    }
    /*
     ʶ��Identifier
     ���ʧ�ܣ�����ˣ����ҷ���NULL
     �ɹ��������ڵ�
    */
    SyntaxTreeNodePtr _MatchIdentifier() {
        ETokenPtr token;
        if ((token = _reader->SeekToken()) && token->GetTokenType() == TokenTypeEnum::IDENTIFIER) {
            token = _reader->GetToken();
            return SyntaxTreeNodePtr(new SyntaxTreeNode(token->GetStrValue(), token->GetLineNum()));
        }
        else {
            return NULL;
        }
    }
    /*
     ʶ��IntgetLiteral
     ���ʧ�ܣ�����ˣ����ҷ���NULL
     �ɹ��������ڵ�
    */
    SyntaxTreeNodePtr _MatchIntegetLiteral() {
        ETokenPtr token;
        if ((token = _reader->GetToken()) && token->GetTokenType() == TokenTypeEnum::INTEGER) {
            token = _reader->GetToken();
            return SyntaxTreeNodePtr(new SyntaxTreeNode(token->GetNumValue(), token->GetLineNum()));
        }
        else {
            return NULL;
        }
    }

public:
#pragma region ���캯������������
    /*
     ֱ��ͨ��tokens�Ķ�ά��������ʼ��
    */
    SyntaxParser(vector<vector<shared_ptr<Token>>> tokens) {
        _reader = shared_ptr<TokenReader>(new TokenReader(tokens));
        if (_reader == NULL) {
            throw("Error: SyntaxParser Construction fail.");
        }
    }
    /*
     ͨ��reader����ʼ��
    */
    SyntaxParser(shared_ptr<TokenReader> reader) {
        if (!reader) {
            throw("Error: SyntaxParser Construction fail.");
        }
        else {
            _reader = reader;
        }
    }
#pragma endregion




    SyntaxTreeNodePtr Goal(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr MainClass(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr ClassDeclaration(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr VarDeclaration(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr MethodDeclaration(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr Type(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr Statement(list<shared_ptr<SyntaxError>>& errorList);
    SyntaxTreeNodePtr Expression(list<shared_ptr<SyntaxError>>& errorList);

#pragma region ʶ��Expression���ӹ���
    shared_ptr<SyntaxTreeNode> Expression_Identifier(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_IntegerLiteral(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_this(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_true(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_false(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_not(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_bracket(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_newIntArray(list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_newIdentifier(list<shared_ptr<SyntaxError>>& errorList);

    shared_ptr<SyntaxTreeNode> Expression_operate(shared_ptr<SyntaxTreeNode> firstNode, list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_length(shared_ptr<SyntaxTreeNode> firstNode, list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_arrayExpression(shared_ptr<SyntaxTreeNode> firstNode, list<shared_ptr<SyntaxError>>& errorList);
    shared_ptr<SyntaxTreeNode> Expression_functionCall(shared_ptr<SyntaxTreeNode> firstNode, list<shared_ptr<SyntaxError>>& errorList);
#pragma endregion


};

#pragma region �ظ�����ĺ궨��
/*
 �ݹ��½�������ʼ���Ĺ��̣�
 - ��� errorList
 - ���� curIndex����������_reader��λ��
 - ���� tempTreeNode
 - ���� tempErrorList
 - ���� curTreeType
 - �ж��Ƿ���ڵ�һ�� token����������ڣ��ͷ���
 - �������ڵ� root
*/
#define RECURSIVE_DESCENT_INIT_RETURN(treeType)\
    errorList.clear();\
    const int curIndex = _reader->GetIndex();\
    SyntaxTreeNodePtr tempTreeNode;\
    list<shared_ptr<SyntaxError>> tempErrorList;\
    auto curTreeType = treeType;\
    ETokenPtr firstToken = _reader->SeekToken(); \
    if (firstToken == NULL) {\
        errorList.emplace_back(new SyntaxError(_reader, "ʶ��ʼtokenʧ��", treeType)); \
        return NULL; \
    }\
    shared_ptr<SyntaxTreeNode> root(new SyntaxTreeNode(treeType, firstToken->GetLineNum()));

/*
 �ݹ��½���ʶ�� Identifier �� IntegerLiteral
 ���ʶ��ɹ���
 - �����ڵ���Ϊָ���ڵ��child
 ���ʶ��ʧ�ܣ�
 - �� errorList ��׷�Ӵ���
 - ָ�����
 - ����
*/
#define SET_IDEN_OR_INT_CHILD_RETURN(tempTreeNode, root, curTreeType, message)\
    if (tempTreeNode) {\
        root->SetChild(tempTreeNode);\
    }\
    else {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }

/*
 �ݹ��½���ʶ�� Identifier �� IntegerLiteral
 ���ʶ��ɹ���
 - �����ڵ���Ϊָ���ڵ��subling
 ���ʶ��ʧ�ܣ�
 - �� errorList ��׷�Ӵ���
 - ָ�����
 - ����
*/
#define SET_IDEN_OR_INT_SUBLING_RETURN(tempTreeNode, root, curTreeType, message)\
    if (tempTreeNode) {\
        root->SetSubling(tempTreeNode);\
    }\
    else {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }

/*
 �ݹ��½���ʶ�� ����
 ���ʶ��ɹ���
 - �������ڵ���Ϊָ���ڵ��subling
 ���ʶ��ʧ�ܣ�
 - �� errorList ��׷�Ӵ���
 - ��errorList��׷�������Ĵ���
 - ָ�����
 - ����
*/
#define SET_SUBTREE_SUBLING_RETURN(tempTreeNode, root, curTreeType, message)\
    if (tempTreeNode) {\
        root->SetSubling(tempTreeNode);\
    }\
    else {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }

/*
 �ݹ��½���ʶ�� ����
 ���ʶ��ɹ���
 - �������ڵ���Ϊָ���ڵ��child
 ���ʶ��ʧ�ܣ�
 - �� errorList ��׷�Ӵ���
 - ��errorList��׷�������Ĵ���
 - ָ�����
 - ����
*/
#define SET_SUBTREE_CHILD_RETURN(tempTreeNode, root, curTreeType, message)\
    if (tempTreeNode) {\
        root->SetChild(tempTreeNode);\
    }\
    else {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        errorList.insert(errorList.end(), tempErrorList.begin(), tempErrorList.end());\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }

/*
 �ݹ��½�����ʶ�� keyword �� symbol �Ĺ��̣�����޷�ʶ�𣬾ͣ�
 -  ��errorList ��׷�Ӵ���
 - ָ�����
 - ����
*/
#define PROCESS_STR_RETURN(tokenType, tokenStr, curTreeType, message)\
    if (_MatchKeywordOrSymbol(tokenType, tokenStr) == false) {\
        errorList.emplace_back(new SyntaxError(_reader, message, curTreeType));\
        _reader->SetIndex(curIndex);\
        return NULL;\
    }
#pragma endregion