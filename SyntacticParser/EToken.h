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
    EToken(TokenPtr token, int line, int column)
        :_line(line),
        _column(column),
        _type(token->type),
        _numValue(token->numValue),
        _strValue(token->strValue) {}

    Property<int> LineNum = Property<int>(_line);
    ROProperty<int> NumValue = ROProperty<int>(_numValue);
    ROProperty<string> StrValue = ROProperty<string>(_strValue);
    ROProperty<TokenTypeEnum> TokenType = ROProperty<TokenTypeEnum>(_type);
};
/*
 EToken��ָ������
*/
typedef std::shared_ptr<EToken> ETokenPtr;