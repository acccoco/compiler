/*************************************************
  Token��صĶ��壺
    enum class TokenTypeEnum ������Token������
    class Token ������Token�ĸ�ʽ
***********************************************/
#pragma once
#include <string>
#include <memory>
#include <iostream>
using namespace std;





/*
 Token����ö��
 */
enum class TokenTypeEnum {
    KEYWORD,
    SYMBOL,
    IDENTIFIER,
    INTEGER,
};

/*
 Token����
 */
struct Token {

    TokenTypeEnum type;
    int numValue = 0;
    string strValue = "";


    Token(TokenTypeEnum type, int numValue)
        : type(type), numValue(numValue) {}
    Token(TokenTypeEnum type, string strValue)
        : type(type), strValue(strValue) {}
    Token(const Token& token)
        :type(token.type), numValue(token.numValue), strValue(token.strValue) {}
    ~Token() {}
};
typedef std::shared_ptr<Token> TokenPtr;
