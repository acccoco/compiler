#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Token.h"
#include "TokenError.h"

/*
 �ʷ����������Զ�����
*/
class LexicalDFA
{
    /*
     ״̬��������ö��
    */
    enum class StateEnum {
        START,                  // ��ʼ״̬
        END,                    // ��ֹ״̬

        SYMBOL_1,               // ʶ��symbol��symbol_1�����˴���
        SYMBOL_2,               // ʶ��symbol��symbol_2�����˴���
        SYMBOL_3,               // ʶ��symbol��symbol_3�����˴���

        IDENTIFIER_1,           // ʶ��identifier��identifier_1�����˴���
        IDENTIFIER_2,           // ʶ��identifier��identifier_2�����˴���

        NUMBER_1,               // ʶ��integerLiteral��״̬�����˴���
    };

public:
    shared_ptr<Token> GetToken() {
        return _token;
    }
    /*
     ���صĴ�����Ϣ����indexָ����Ǹ��ַ�
     */
    std::string GetError() {
        return _errStr;
    }
    /*
     ��õ���ʵ��
     */
    static shared_ptr<LexicalDFA> GetInstance() {
        if (_instance == NULL)
            _instance = shared_ptr<LexicalDFA>(new LexicalDFA());
        return _instance;
    }
    /*
     ���ٵ���ʵ��
     */
    static void DestroyInstance() {
        if (_instance != NULL) _instance = NULL;
    }
    /*
     ����һ���ַ�������curIndex����ʼ����
     ������һ���ͷ���
     ���ò���������д�curIndexָ�����λ�ã����û�д���curIndexָ����һ�����������λ��
     ���أ����ؾ���Ĵ������
    */
    TokenErrorType Parse(std::string rawStr, int& curIndex);

private:
    static shared_ptr<LexicalDFA> _instance;       // ����ʵ��
    shared_ptr<Token> _token;           // ʶ����� Token
    std::string _errStr;                // �����������

protected:
    LexicalDFA(): _token(NULL), _errStr("") {}  // ��������ù��캯��
};

