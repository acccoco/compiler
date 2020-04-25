#include <set>
#include "utils.h"
using namespace std;

/*
 �ؼ��ּ��ϡ��ر�ע�⣺��û�а���"System.out.println"
 */
const set<string> keywords = { "class", "public", "static", "void", "main", "String", "extends",
						"return", "int", "boolean",  "if", "else", "while" ,
						"length", "true", "false", "this", "new" };
/*
 �ж�һ���ַ����ڲ��ڹؼ��ּ�������
 */
bool IsKeyword(const string tokenStr) {
	return keywords.find(tokenStr) != keywords.end();
}



/*
 ���ż���
 ��û�а���&&�����ǰ�����&
*/
const set<char> symbols = { '[', ']', '(', ')', '{', '}', ',', ';', '=', '&', '<', '+', '-', '*', '.', '!' };

/*
 �ж�һ���ַ������ͣ��»��ߣ��ַ������ţ�����
 */
CharTypeEnum JudgeCharType(const char c) {
	if (c == '_')
		return CharTypeEnum::UNDERLINE;
	if (c == ' ' || c == '\t')
		return CharTypeEnum::SPACE;
	if ('0' <= c && c <= '9')
		return CharTypeEnum::DIGIT;
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return CharTypeEnum::LETTER;
	if (symbols.find(c) != symbols.end())
		return CharTypeEnum::SYMBOL;
	return CharTypeEnum::INVILID;
}