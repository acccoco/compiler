#pragma once
#include <string>
/***************************
 ����ģ�飺
   ö�٣��ַ�����
   �������ж��ַ�������
   �������ַ����Ƿ��ǹؼ���
 *************************/



/*
 �ַ�����ö��
 */
enum class CharTypeEnum {
	DIGIT,			    // ���֣� 0-9
	LETTER,			    // ��ĸ�� A-Za-z
	UNDERLINE,		    // �»��� '_'
	SYMBOL,			    // ���ţ�λ�ڷ��ż�����
	SPACE,			    // �հ��ַ����ո��Ʊ��
	INVILID,			// �Ƿ�����
};

/*
 �ж�һ���ַ������ͣ��»��ߣ��ַ������ţ�����
 */
CharTypeEnum JudgeCharType(const char c);

/*
 �ж�һ���ַ����ڲ��ڹؼ��ּ�������
 */
bool IsKeyword(const std::string tokenStr);