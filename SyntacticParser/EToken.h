#pragma once
#include "../LexicalAnalyzer/Token.h"

/*
 �ʷ�token���ͣ���ԭ Token �������չ��������кź��кŵ��ֶ�
*/
class EToken {
private:

    TokenTypeEnum _type;    // Token ������
    int _numValue;          // Token ������ֵ�����ַ���ֵ��ѡһ
    string _strValue;       // Token ���ַ���ֵ��������ֵ��ѡһ

    size_t _lineNum;      // Token���к�
    size_t _column;        // Token������������λ��

public:

    /* ͨ��һ��token����������Etoken������Ҫ�ṩ�кź��к� */
    EToken(TokenPtr token, size_t line, size_t column):
        _lineNum(line),
        _column(column),
        _type(token->type),
        _numValue(token->numValue),
        _strValue(token->strValue) {}

    Property<size_t> LineNum = Property<size_t>(_lineNum);    // Token���к�
    Property<size_t> ColumnNum = Property<size_t>(_column);     // token���к�
    ROProperty<int> NumValue = ROProperty<int>(_numValue);  // token������ֵ�����ַ�����ֵ��ѡһ
    ROProperty<string> StrValue = ROProperty<string>(_strValue);    // token���ַ���ֵ��������ֵ��ѡһ
    ROProperty<TokenTypeEnum> TokenType = ROProperty<TokenTypeEnum>(_type); // token������
};

/* ��չ�Ĵʷ�token���� */
typedef std::shared_ptr<EToken> ETokenPtr;