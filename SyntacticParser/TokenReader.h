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
 ���ڶ�ȡ�ʷ�����tokens����
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

    Property<int> Index = Property<int>(_curIndex);     // reader��ǰ��ָ��λ��
    Property<int> TokenCount = Property<int>(_tokenCount);      // reader����token������

    /*
     �ж��Ƿ������
     ��������ˣ���ôָ��ֵӦ����tokenCount
     �쳣����
    */
    bool IsEnd() const noexcept {
        return _curIndex == _tokenCount;
    }

    /*
     ��ȡ��ǰָ��ָ���token����Ȼ��ָ�����
     ���ָ��Խ�磬�ͷ���null
     �쳣����
    */
    ETokenPtr GetToken() noexcept {
        if (_curIndex >= _tokenCount) {
            return NULL;
        }
        return _tokens[_curIndex++];
    }

    /*
     ��ȡ��ǰָ��ָ���Token������ı�ָ���ֵ
     ���û�пɶ��ģ��ͷ��ؿ�ָ��
     �쳣����
    */
    ETokenPtr SeekToken() const noexcept {
        return _curIndex < _tokenCount ? _tokens[_curIndex] : NULL;
    }

    /*
     ��ǰָ��ָ���tokne���к�
     ���û�У��ͷ���-1
     �쳣����
    */
    int GetCurLineNum() const noexcept {
        if (_curIndex < _tokenCount) {
            return _tokens[_curIndex]->LineNum.Get();
        }
        else {
            return -1;
        }
    }
    /*
     ��һ��ָ��ָ���tokne���к�
     ���û�У��ͷ���-1
     �쳣����
    */
    int GetLastLineNum() const  noexcept {
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
 ���ڶ�ȡ�ʷ�����tokens����
*/
typedef std::shared_ptr<TokenReader> ReaderPtr;