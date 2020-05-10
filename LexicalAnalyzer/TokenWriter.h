#pragma once
#include "Token.h"
#include "TokenError.h"
#include <vector>
#include <fstream>
#include <memory>
using namespace std;

/*
 ���ʷ������õ���һϵ��tokenд���ļ�
*/
class TokenWriter {
public:
    /*
     ��token�ʹ���д��ָ���ļ���
    */
    void Write2File(const vector<vector<shared_ptr<Token>>>& tokens,
        const vector<shared_ptr<TokenError>> tokenErrors, ofstream& fileOut) {
        /*
         д�����
         #Errors: 1
         xxxxx
        */
        fileOut << "#Errors: " << tokenErrors.size() << endl;
        for (auto tokenError : tokenErrors) {
            fileOut << tokenError->errMsg << endl;
        }
        /*
         д��Token
         #Token:
         #line 1
         KEYWORD int
         IDENTIFIER acc
         SYMBOL ;
         #line 2
         */
        fileOut << "#Token: " << endl;
        for (size_t lineNum = 1; lineNum <= tokens.size(); ++lineNum) {
            fileOut << "#line " << lineNum << endl;
            for (auto token : tokens[lineNum - 1]) {
                switch (token->type)
                {
                case TokenTypeEnum::IDENTIFIER:
                    fileOut << "IDENTIFIER " << token->strValue << endl;
                    break;
                case TokenTypeEnum::SYMBOL:
                    fileOut << "SYMBOL " << token->strValue << endl;
                    break;
                case TokenTypeEnum::KEYWORD:
                    fileOut << "KEYWORD " << token->strValue << endl;
                    break;
                case TokenTypeEnum::INTEGER:
                    fileOut << "INTEGER " << token->numValue << endl;
                    break;
                }
            }
        }
    }
};