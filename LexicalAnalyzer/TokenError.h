#pragma once
#include <string>
#include <sstream>
using namespace std;


/*
 �ʷ������������Ͷ���
*/
enum class TokenErrorType {
	OK,							// �������
	SPACE,						// ȫ�ǿո�

	INVILID_CHAR,				// �Ƿ��ַ�
	FLOAT_ERROR_SYMB_3,			// �������   .23
	UNEXPECTED_CHAR_SYMB_1,		// ���Ŵ���   &x
	UNEXPECTED_CHAR_IDEN_2,		// ��ʶ������ acc_x
	FLOAT_ERROR_NUM1,			// �������  23.
	UNEXPECTED_CHAR_NUM1,		// ���ִ���  23x
	UNEXPECTED_CHAR_BEGIN,		// ��ʼ����  _
};


/*
 �ʷ������������
*/
struct TokenError {
	int lineNum;				// ������ֵ��к�
	int column;					// ������ֵ�λ��
	TokenErrorType tokenType;	// ��������
	string errMsg;				// ������Ϣ

	TokenError(int lineNum, int column, TokenErrorType errType, string errContex) {
		this->lineNum = lineNum;
		this->column = column;
		this->tokenType = errType;


		/*
		 �����������
		 at line 23, column : xxx.
		 */
		ostringstream oss;
		oss << "at line " << lineNum << ", " << "column " << column << ": ";
		switch (errType)
		{
		case TokenErrorType::INVILID_CHAR:
			oss << "�Ƿ��ַ� ";
			break;
		case TokenErrorType::FLOAT_ERROR_NUM1:
		case TokenErrorType::FLOAT_ERROR_SYMB_3:
			oss << "��֧�ָ����� ";
			break;
		case TokenErrorType::UNEXPECTED_CHAR_SYMB_1:
			oss << "����ķ��� ";
			break;
		case TokenErrorType::UNEXPECTED_CHAR_IDEN_2:
			oss << "����ı�ʶ�� ";
			break;
		case TokenErrorType::UNEXPECTED_CHAR_NUM1:
			oss << "��������� ";
			break;
		case TokenErrorType::UNEXPECTED_CHAR_BEGIN:
			oss << "����Ŀ�ʼ�ַ� ";
			break;
		}
		oss << "\"" << errContex << "\"";
		errMsg = oss.str();
	}
};