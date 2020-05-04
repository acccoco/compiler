#pragma once
#include <string>
#include "SyntaxTreeType.h"
#include "TokenReader.h"

/*
 �﷨����Ķ���
*/
class SyntaxError {
private:
    shared_ptr<const TokenReader> _reader;
    std::string _message;                       // �������Ϣ
    TreeType _treeType;


public:
#pragma region ���캯��
    SyntaxError(shared_ptr<const TokenReader> reader, std::string message, TreeType treeType)
        : _reader(reader), _message(message), _treeType(treeType) {}
#pragma endregion

    
};
typedef shared_ptr<SyntaxError> SyntaxErrorPtr;