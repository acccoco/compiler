#include "SyntaxParser.h"
#include <iostream>
#include <vector>
#include <string>

class ParserTest {
private:
    /*
     ��ӡ��ǰreader��״̬
    */
    void _PrintReaderState() {
        auto reader = parser->_reader;
        cout << "Reader״̬: " << endl;
        cout << "   index: " << reader->GetIndex() << endl;
        cout << "   lineNum: " << reader->GetCurLineNum() << endl;
        cout << "   token: " << reader->SeekToken()->GetStrValue() << ", " << reader->SeekToken()->GetNumValue() << endl;
    }
public:
    shared_ptr<SyntaxParser> parser;
    /*
     ��ʼ�����Զ���
    */
    void Init(vector<vector<shared_ptr<Token>>> tokens) {
        parser = shared_ptr<SyntaxParser>(new SyntaxParser(tokens));
    }

    /*
     ����MatchKeywordOrSymbol����
    */
    void MatchKeywordOrSymbol(TokenTypeEnum tokenType, string str) {
        cout << __FUNCTION__ << endl;
        _PrintReaderState();
        bool result = parser->_MatchKeywordOrSymbol(tokenType, str);
        cout << "match result: " << result << endl;
        _PrintReaderState();
    }
};