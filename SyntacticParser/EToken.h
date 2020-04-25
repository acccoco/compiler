#pragma once
#include "../LexicalAnalyzer/Token.h"

/*
 ��չ��Token
 ��Ҫ��������к�
*/
class EToken {
private:
    TokenTypeEnum _type;
    int _numValue;
    string _strValue;

    int _line;
    int _column;

public:
    EToken(TokenPtr token, int line, int column) {
        _line = line;
        _column = column;

        _type = token->type;
        _numValue = token->numValue;
        _strValue = token->strValue;
    }
    /*
     ȡ���к�
    */
    int GetLineNum() {
        return _line;
    }
    /*
     ȡ������
    */
    TokenTypeEnum GetTokenType() {
        return _type;
    }
    /*
     ȡ��ֵstrֵ
    */
    string GetStrValue() {
        return _strValue;
    }

    /*
     ȡ��numֵ
    */
    int GetNumValue() {
        return _numValue;
    }
};
/*
 EToken��ָ������
*/
typedef std::shared_ptr<EToken> ETokenPtr;