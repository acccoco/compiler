#pragma once
#include <string>
#include "TreeType.h"
#include "TokenReader.h"
#include <sstream>

/*
 �﷨����Ķ���
*/
class SyntaxError {
protected:
    size_t _curLineNum;     // ������ʱ����һ��
    size_t _preLineNum;     // ������ʱ�ĵ�ǰ��
    size_t _curIndex;       // ������ʱreader��ָ��λ��
    size_t _columnNum;      // �����������ڵĵڼ���token
    string _tokenValue;    // ������ʱ token������
    string _message;             // �������ʾ��Ϣ
    TreeType _treeType;         // ��������ʱ�����ڵ�����


public:

    ROProperty<size_t> curLineNum = ROProperty<size_t>(_curLineNum);         // ������ʱ����һ��
    ROProperty<size_t> preLineNum = ROProperty<size_t>(_preLineNum);         // ������ʱ�ĵ�ǰ��
    ROProperty<size_t> columnNum = ROProperty<size_t>(_columnNum);          // ������ʱtoken�����ڵ�λ��
    ROProperty<size_t> curIndex = ROProperty<size_t>(_curIndex);        // ������ʱreader��ָ��λ��
    ROProperty<string> tokenValue = ROProperty<string>(_tokenValue);        // ������ʱ token������
    ROProperty<string> message = ROProperty<string>(_message);                    // �������ʾ��Ϣ
    ROProperty<TreeType> treeType = ROProperty<TreeType>(_treeType);             // ��������ʱ�����ڵ�����

    /*
     ����һ���﷨�������
     ������reader�����ڵõ�������������Ϣ�����������кŵ�
     ������message���������ʾ��Ϣ
     ������treeType�����������﷨��λ��
    */
    SyntaxError(shared_ptr<const TokenReader> reader, std::string message, TreeType treeType)
        : _curLineNum(reader->GetCurLineNum()),
        _preLineNum(reader->GetLastLineNum()),
        _curIndex(reader->Index.Get()),
        _message(message), 
        _treeType(treeType) {
    
        /* ��ȡtoken���� */
        auto token = reader->SeekToken();
        if (token) {
            if (token->TokenType.Get() == TokenTypeEnum::INTEGER) {
                char temp[256];
                _itoa_s(token->NumValue.Get(), temp, 10);
                _tokenValue = temp;
            }
            else {
                _tokenValue = token->StrValue.Get();
            }
        }
        else {
            _tokenValue = "";
        }
        

        /* ��ȡ�к����� */
        if (token) {
            _columnNum = token->ColumnNum.Get();
        }
        else {
            _columnNum = 0;
        }
    }

    /* 
     ���﷨�����Ĵ������ת��Ϊ�ַ���
     �쳣����
    */
    string toString() noexcept {
        
        char buffer[256];
        _itoa_s((int)_preLineNum, buffer, 10);
        string preLineNumStr = buffer;
        _itoa_s((int)_curLineNum, buffer, 10);
        string curLineNumStr = buffer;
        string lineNumStr = (_curLineNum == 0) ? preLineNumStr : curLineNumStr;
        _itoa_s((int)_columnNum, buffer, 10);
        string columnNumStr = buffer;

        stringstream strBuilder;

        /* AST(Expression), at line(1, 2), token(static): ʶ��xx���� */
        strBuilder << "AST(" << _treeType.toString() << "), ";
        strBuilder << "at line(" << lineNumStr << ", " << columnNumStr << "), ";
        strBuilder << "token(" << _tokenValue << "): ";
        strBuilder << _message;

        return strBuilder.str();
    }

};

/* �﷨������� */
typedef shared_ptr<SyntaxError> SyntaxErrorPtr;