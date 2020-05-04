#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
#include "Property.h"
#include "../LexicalAnalyzer/Token.h"
#include "EToken.h"


/*
 ���ڶ�ȡtokens����
 �����ֻ��������ȡtoken�ģ���Ӧ�ò��ִ�����
*/
class TokenReader {
private:
    vector<ETokenPtr> _tokens;          // tokens����
    int _tokenCount;                    // tokens���ܸ���
    int _curIndex;                      // ��ǰtoken�������±꣬������ʶ��GetToken()��SeekToken()������õľ������token
public:
    /*
     ���캯����
     ͨ��Token*[][]����Reader
     ͨ�������±��ƶ��к�
    */
    TokenReader(const vector<vector<TokenPtr>>& tokens):
        _curIndex(0) {
        _tokenCount = 0;
        for (int i = 0; i < tokens.size(); ++i) {
            for (int j = 0; j < tokens[i].size(); ++j) {
                _tokens.push_back(ETokenPtr(new EToken(tokens[i][j], i + 1, j + 1)));
                ++_tokenCount;
            }
        }
    }

    Property<int> Index = Property<int>(_curIndex);
    Property<int> TokenCount = Property<int>(_tokenCount);

    /*
     �ж��Ƿ������
     ��ǰ�±��Ƿ�Խ��
    */
    bool IsEnd() const {
        return _curIndex == _tokenCount;
    }

    /*
     ��ȡһ��token��Ȼ��ָ�����
     ���Խ�磬�򷵻�NULL
    */
    ETokenPtr GetToken() {
        if (_curIndex >= _tokenCount) {
            return NULL;
        }
        return _tokens[_curIndex++];
    }

    /*
     ��һ�۵�ǰ��Token
     ���û�пɶ��ģ��ͷ��ؿ�ָ��
    */
    ETokenPtr SeekToken() const {
        return _curIndex < _tokenCount ? _tokens[_curIndex] : NULL;
    }

    /*
     ��Ҫ��ȡ��token���к�
     ���û�У��ͷ���-1
    */
    int GetCurLineNum() const {
        if (_curIndex < _tokenCount) {
            return _tokens[_curIndex]->LineNum.Get();
        }
        else {
            return -1;
        }
    }
    /*
     ��һ����ȡ���token���к�
     ���û�У��ͷ���-1
    */
    int GetLastLineNum() const {
        auto lastIndex = _curIndex - 1;
        if (0 <= lastIndex && lastIndex < _tokenCount) {
            return _tokens[lastIndex]->LineNum.Get();
        }
        else {
            return -1;
        }
    }
};
/*
 Reader���ָ������
*/
typedef std::shared_ptr<TokenReader> ReaderPtr;