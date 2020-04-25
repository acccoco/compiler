#include "LexicalDFA.h"
#include "utils.h"
using namespace std;

shared_ptr<LexicalDFA> LexicalDFA::_instance = NULL;


TokenErrorType LexicalDFA::Parse(string rawStr, int& curIndex) {
    // �����Ϣ
    _token = NULL;
    _errStr = "";

    // ��ʼ��
    int strLen = rawStr.length();
    StateEnum curState = StateEnum::START;
    string curTokenStr = "";

    // Lambda��״̬��ת�Ĺ���
    auto stateTurn = [&curIndex, &curState, &curTokenStr](char curChar, StateEnum state) {
        ++curIndex;
        curTokenStr += curChar;
        curState = state;
    };

    while (curIndex != strLen) {
        char curChar = rawStr[curIndex];
        CharTypeEnum curCharType = JudgeCharType(curChar);

        // ����ͳһ�ų�INVILID����
        if (curCharType == CharTypeEnum::INVILID) {
            _errStr = curTokenStr + curChar;
            return TokenErrorType::INVILID_CHAR;
        }

        // ״̬������
        switch (curState)
        {

            /********************  ״̬START  *****************************/
        case LexicalDFA::StateEnum::START:
            switch (curCharType)
            {
            case CharTypeEnum::DIGIT:   // ʶ������
                stateTurn(curChar, StateEnum::NUMBER_1);
                break;
            case CharTypeEnum::LETTER:  // ʶ��identifier
                stateTurn(curChar, StateEnum::IDENTIFIER_1);
                break;
            case CharTypeEnum::UNDERLINE:   // ����Ŀ�ʼ�ַ�
                _errStr = "_";
                return TokenErrorType::UNEXPECTED_CHAR_BEGIN;
            case CharTypeEnum::SYMBOL:  // ʶ��symbol����Ҫ��ϸ�ж��ַ�����
                if (curChar == '&')
                    stateTurn(curChar, StateEnum::SYMBOL_1);
                else if (curChar == '.')
                    stateTurn(curChar, StateEnum::SYMBOL_3);
                else
                    stateTurn(curChar, StateEnum::SYMBOL_2);
                break;
            case CharTypeEnum::SPACE:   // ��ת
                ++curIndex;
                break;
            }
            break;

            /*********************  ״̬SYMBOL_1  *****************************/
        case LexicalDFA::StateEnum::SYMBOL_1:
            if (curChar == '&') {
                stateTurn(curChar, StateEnum::SYMBOL_2);
            }
            else {
                _errStr = curTokenStr + curChar;
                return TokenErrorType::UNEXPECTED_CHAR_SYMB_1;
            }
            break;

            /*********************  ״̬SYMBOL_2  *****************************/
        case LexicalDFA::StateEnum::SYMBOL_2:
            _token = shared_ptr<Token>(new Token(TokenTypeEnum::SYMBOL, curTokenStr));
            return TokenErrorType::OK;

            /*********************  ״̬SYMBOL_3  *****************************/
        case LexicalDFA::StateEnum::SYMBOL_3:
            if (curCharType == CharTypeEnum::DIGIT) {   // �������
                _errStr = curTokenStr + curChar;
                return TokenErrorType::FLOAT_ERROR_SYMB_3;
            }
            else {      // ����
                _token = shared_ptr<Token>(new Token(TokenTypeEnum::SYMBOL, curTokenStr));
                return TokenErrorType::OK;
            }
            break;

            /*********************  ״̬IDENTIFIER_1  *****************************/
        case LexicalDFA::StateEnum::IDENTIFIER_1:
            switch (curCharType)
            {
            case CharTypeEnum::DIGIT:       // ״̬����
            case CharTypeEnum::LETTER:
                stateTurn(curChar, StateEnum::IDENTIFIER_1);
                break;
            case CharTypeEnum::UNDERLINE:   // ״̬��ת
                stateTurn(curChar, StateEnum::IDENTIFIER_2);
                break;
            case CharTypeEnum::SYMBOL:      // ���ر�ʶ��
            case CharTypeEnum::SPACE:
                _token = shared_ptr<Token>(new Token(TokenTypeEnum::IDENTIFIER, curTokenStr));
                return TokenErrorType::OK;
            }
            break;

            /*********************  ״̬IDENTIFIER_2  *****************************/
        case LexicalDFA::StateEnum::IDENTIFIER_2:
            switch (curCharType)
            {
            case CharTypeEnum::DIGIT:       // ״̬��ת
            case CharTypeEnum::LETTER:
                stateTurn(curChar, StateEnum::IDENTIFIER_1);
                break;
            case CharTypeEnum::UNDERLINE:   // �����ַ�
            case CharTypeEnum::SYMBOL:
            case CharTypeEnum::SPACE:
                _errStr = curTokenStr + curChar;
                return TokenErrorType::UNEXPECTED_CHAR_IDEN_2;
            }
            break;

            /*********************  ״̬NUMBER_1  *****************************/
        case LexicalDFA::StateEnum::NUMBER_1:
            switch (curCharType)
            {
            case CharTypeEnum::DIGIT:   // ״̬����
                stateTurn(curChar, StateEnum::NUMBER_1);
                break;
            case CharTypeEnum::LETTER:      // ������ַ�
            case CharTypeEnum::UNDERLINE:
                _errStr = curTokenStr + curChar;
                return TokenErrorType::UNEXPECTED_CHAR_NUM1;
            case CharTypeEnum::SYMBOL:
                if (curChar == '.') {     // �������
                    _errStr = curTokenStr + curChar;
                    return TokenErrorType::FLOAT_ERROR_NUM1;
                }
                else {
                    _token = shared_ptr<Token>(new Token(TokenTypeEnum::INTEGER, stoi(curTokenStr)));
                    return TokenErrorType::OK;
                }
            case CharTypeEnum::SPACE:   // ʶ�����
                _token = shared_ptr<Token>(new Token(TokenTypeEnum::INTEGER, stoi(curTokenStr)));
                return TokenErrorType::OK;
            }
            break;
        }
    }


    // �������ַ�����ĩβ
    switch (curState) { // ����״̬����_token��_errStr��������״̬��
    case StateEnum::START:
        return TokenErrorType::SPACE;
    case StateEnum::NUMBER_1:
        _token = shared_ptr<Token>(new Token(TokenTypeEnum::INTEGER, stoi(curTokenStr)));
        return TokenErrorType::OK;
    case StateEnum::IDENTIFIER_1:
        _token = shared_ptr<Token>(new Token(TokenTypeEnum::IDENTIFIER, curTokenStr));
        return TokenErrorType::OK;
    case StateEnum::IDENTIFIER_2:
        _errStr = curTokenStr + "[endl]";
        return TokenErrorType::UNEXPECTED_CHAR_IDEN_2;
    case StateEnum::SYMBOL_1:
        return TokenErrorType::UNEXPECTED_CHAR_SYMB_1;
    case StateEnum::SYMBOL_2:
    case StateEnum::SYMBOL_3:
        _token = shared_ptr<Token>(new Token(TokenTypeEnum::SYMBOL, curTokenStr));
        return TokenErrorType::OK;
    }
}




