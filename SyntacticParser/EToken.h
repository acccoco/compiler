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

    int _lineNum;      // Token���к�
    int _column;        // Token������������λ��

public:

    /* ͨ��һ��token����������Etoken������Ҫ�ṩ�кź��к� */
    EToken(TokenPtr token, int line, int column):
        _lineNum(line),
        _column(column),
        _type(token->type),
        _numValue(token->numValue),
        _strValue(token->strValue) {}

    Property<int> LineNum = Property<int>(_lineNum);    // Token���к�
    ROProperty<int> NumValue = ROProperty<int>(_numValue);  // token������ֵ�����ַ�����ֵ��ѡһ
    ROProperty<string> StrValue = ROProperty<string>(_strValue);    // token���ַ���ֵ��������ֵ��ѡһ
    ROProperty<TokenTypeEnum> TokenType = ROProperty<TokenTypeEnum>(_type); // token������
};

/* ��չ�Ĵʷ�token���� */
typedef std::shared_ptr<EToken> ETokenPtr;