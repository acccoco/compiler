#include "../LexicalAnalyzer/Token.h"
#include "../LexicalAnalyzer/LexicalAnalyzer.h"
#include "../LexicalAnalyzer/fileReader.h"
#include "SyntaxWriter.h"
#include "../LexicalAnalyzer/FileWriter.h"
#include <vector>
#include <iostream>
using namespace std;

#if true
int main(int argc, char** argv) {

	bool flagPrintConsole = true;		// �Ƿ񽫽����ӡ������̨
	bool flagWrite2File = true;		// �Ƿ񽫽��������ļ�

	/* ��ȡ�����в��� */
	if (argc != 3) {
		cout << "�����������" << endl;
		return 0;
	}

	/* ���ļ�����ȡ�ļ� */
	string filePathIn, filePathOut;
	filePathIn = argv[1];
	filePathOut = argv[2];
	ifstream fileIn;
	ofstream fileOut;
	fileIn.open(filePathIn, ios::in);
	fileOut.open(filePathOut, ios::out | ios::trunc);
	if (!fileIn.is_open()) {
		cout << "�������ļ�ʧ��" << endl;
		return 0;
	}
	if (!fileOut.is_open()) {
		cout << "������ļ�ʧ��" << endl;
		return 0;
	}
	vector<string> rawStrs = FileReader().readFile(fileIn);

	/* �ʷ����� */
	LexialAnalyzer lexicalAnalyzer;
	lexicalAnalyzer.LexicalAnlyze(rawStrs);
	auto tokens = lexicalAnalyzer.GetResultTokens();
	auto lexicalErrors = lexicalAnalyzer.GetResultErrors();

	/* �жϴʷ������Ľ�� */
	if (lexicalErrors.size() != 0) {
		cout << "�ʷ������д����޷������﷨����" << endl;
		return 0;
	}

	/* �����﷨���� */
	auto reader = ReaderPtr(new TokenReader(tokens));
	auto syntaxParser = SyntaxParser(reader);
	syntaxParser.Parse();
	auto syntaxTreeStrs = syntaxParser.getSerialTree();
	auto syntaxTreeRoot = syntaxParser.Root.Get();
	auto syntaxErrors = syntaxParser.ErrorList.Get();
	auto syntaxErrorStrs = syntaxParser.getErrorStrs();
	
	/* ��ӡ�﷨�����Ľ�� */
	if (flagPrintConsole) {

		/* ��ӡ���󵽿���̨ */
		cout << endl << "Syntax Errors: " << endl;
		for (string syntaxErrorStr : syntaxErrorStrs) {
			cout << syntaxErrorStr << endl;
		}
		cout << endl;

		/* ��ӡ���ڵ㵽����̨ */
		cout << "Syntax Tree: " << endl;
		for (string str : syntaxTreeStrs) {
			cout << str << endl;
		}
		cout << endl;
	}

	/* ���������ļ� */
	if (flagWrite2File) {
		FileWriter fileWriter;

		/* ��������ļ� */
		fileWriter.write2File(fileOut, vector<string>{"Syntax Errors:"});
		fileWriter.write2File(fileOut, syntaxErrorStrs);

		/* ������ڵ㵽�ļ� */
		fileWriter.write2File(fileOut, vector<string>{"Syntax Tree"});
		fileWriter.write2File(fileOut, syntaxTreeStrs);
	}

	/* �ر��ļ� */
	fileIn.close();
	fileOut.close();

	return 0;
}

#endif
