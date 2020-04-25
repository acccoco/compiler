/**********************************
 �ʷ�������
   - ����1����һ���ַ������дʷ�������������� Token �� ������Ϣ
   - ����2����һ���ļ����дʷ��������� ������Ϣ �� Token��Ϣ�����ָ���ļ�
***********************************/
#pragma once
#include <fstream>
#include "TokenError.h"
#include "utils.h"
#include "LexicalDFA.h"

class LexialAnalyzer {
private:
    vector<vector<shared_ptr<Token>>> _tokens;          // �ʷ������Ľ��
    vector<shared_ptr<TokenError>> _tokenErrors;                    // ������

public:
    /**
     �ʷ�����
     �������ļ��������ݽ��дʷ���������Token�ʹ�����Ϣд������ļ���
    */
    void LexicalAnlyze(const vector<string> rawStrs) {

        _tokens.clear();
        _tokenErrors.clear();
        shared_ptr<LexicalDFA> DFA = LexicalDFA::GetInstance();

        // һ��һ�еؽ��дʷ�����
        for (int lineNum = 1; lineNum <= rawStrs.size(); ++lineNum) {
            vector<shared_ptr<Token>> lineTokens;
            lexicalAnlyzeOneLine(DFA, lineTokens, _tokenErrors, rawStrs[lineNum - 1], lineNum);
            _tokens.push_back(lineTokens);
        }

        // �ͷ���Դ
        LexicalDFA::DestroyInstance();
    }

    /*
     ���شʷ������Ľ��
    */
    vector<vector<shared_ptr<Token>>> GetResultTokens() {
        return _tokens;
    }
    /*
     ���شʷ������Ĵ���
    */
    vector<shared_ptr<TokenError>> GetResultErrors() {
        return _tokenErrors;
    }



    /**
     ��һ���ַ������дʷ�����
     ����token�ʹ�����Ϣ
    */
    void lexicalAnlyzeOneLine(shared_ptr<LexicalDFA> DFA, vector<shared_ptr<Token>>& tokens,
        vector<shared_ptr<TokenError>>& tokenErrors, const string rawStr, int lineNum) {

        int index = 0;
        int lineLength = rawStr.length();
        while (index < lineLength) {
            TokenErrorType tokenError = DFA->Parse(rawStr, index);
            shared_ptr<Token> token = DFA->GetToken();
            string errStr = DFA->GetError();

            // ����ʶ���Լ�������
            errorHandling(lineNum, rawStr, index, DFA, tokenError, tokens, tokenErrors);
        }
    }
private:

    /*
     ��identifier���ҳ�keyword
     ��Ҫ��IDENTIFIER����
     */
    void findKeyword(string rawStr, int& index, shared_ptr<Token> token) {
        if (token->type != TokenTypeEnum::IDENTIFIER)
            return;
        if (IsKeyword(token->strValue)) {   // ʶ��һ��ؼ���
            token->type = TokenTypeEnum::KEYWORD;
            return;
        }
        /*
         System.out.println
               |index      |index+12
         */
        if (token->strValue == "System" 			// ����System.out.println����Ҫ����println֮����ַ�
            && index + 11 < rawStr.length()
            && rawStr.substr(index, 12) == ".out.println") {
            if (index + 12 < rawStr.length()
                && JudgeCharType(rawStr[index + 12]) != CharTypeEnum::SPACE
                && JudgeCharType(rawStr[index + 12]) != CharTypeEnum::SYMBOL) {
                return;
            }
            else {
                token->type = TokenTypeEnum::KEYWORD;
                token->strValue = "System.out.println";
                index += 12;
                return;
            }
        }
    }

    /*
     ������
     �ƶ�indexָ��
     ���ҽ���֮����ַ����뵽������Ϣ��
     */
    void errorHandling(int lineNum, string rawStr, int& index, shared_ptr<LexicalDFA> dfa, TokenErrorType tokenError,
        vector<shared_ptr<Token>>& tokens, vector<shared_ptr<TokenError>>& tokenErrors) {

        // lambda���ߵ���һ��space��symbol�ĵط�
        auto toNextSplit = [&index, &rawStr]() {
            string addedErrStr = "";    // ֮�󸽼ӵĴ�����Ϣ
            // ������Ҫ�жϵ�һ�������ַ��Ƿ����ŷָ������
            CharTypeEnum curCharType = JudgeCharType(rawStr[index]);
            if (curCharType == CharTypeEnum::SPACE || curCharType == CharTypeEnum::SYMBOL) {
                ++index;
                return addedErrStr;
            }
            // ��һ�������ַ������зָ����ã���������������
            ++index;
            while (index < rawStr.size()) {
                curCharType = JudgeCharType(rawStr[index]);
                if (curCharType == CharTypeEnum::SPACE || curCharType == CharTypeEnum::SYMBOL) {
                    break;
                }
                else {
                    addedErrStr += rawStr[index];
                    ++index;
                }
            }
            return addedErrStr;
        };

        shared_ptr<Token> token = dfa->GetToken();
        string errStr = dfa->GetError();

        // ������
        if (tokenError == TokenErrorType::OK) {     // û�д���
            if (token->type == TokenTypeEnum::IDENTIFIER)
                findKeyword(rawStr, index, token);
            tokens.push_back(token);
            return;
        }
        else if (tokenError == TokenErrorType::SPACE) { // ȫ�ǿո�
            return;
        }
        else {      // �д���
            // �ƶ�index��ֱ����һ��space��symbol�����ҽ����ݼӵ�������Ϣ��
            errStr += toNextSplit();
            tokenErrors.emplace_back(new TokenError(lineNum, index + 1, tokenError, errStr));
            return;
        }
    }

};


