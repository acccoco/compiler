/*************************************
 ���������
 TODO��������
 TODO���ϲ���������
*******************************************/
#include "../LexicalAnalyzer/Token.h"
#include "../LexicalAnalyzer/LexicalAnalyzer.h"
#include "../LexicalAnalyzer/fileReader.h"
#include "ParserTest.h"
#include "SyntaxWriter.h"
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	// �жϲ����Ƿ�Ϸ�
	if (argc != 3) {
		cout << "�����������" << endl;
		return 0;
	}
	// ��ȡ����
	string fileInPath, fileOutPath;
	fileInPath = argv[1];
	fileOutPath = argv[2];
	// ���ļ�
	ifstream fileIn;
	ofstream fileOut;
	fileIn.open(fileInPath, ios::in);
	fileOut.open(fileOutPath, ios::out | ios::trunc);
	if (!fileIn.is_open()) {
		cout << "�������ļ�ʧ��" << endl;
		return 0;
	}
	if (!fileOut.is_open()) {
		cout << "������ļ�ʧ��" << endl;
		return 0;
	}

	// ��ȡ�ļ�
	auto rawStrs = FileReader().readFile(fileIn);
	// ���дʷ�����
	LexialAnalyzer analyzer;
	analyzer.LexicalAnlyze(rawStrs);
	// ��ý��
	auto tokens = analyzer.GetResultTokens();
	auto tokenErrors = analyzer.GetResultErrors();
	// �ر��ļ�
	fileIn.close();
	fileOut.close();

	// �ʷ�����
	SyntaxParser parser(tokens);
	parser.Parse();
	auto root = parser.GetRoot();
	auto syntaxErrors = parser.GetErrorList();

	SyntaxWriter writer;
	auto result = writer.Serialize(writer.PreOrderTraval(root, 0));
	for (auto data : result) {
		cout << data << endl;
	}

	return 0;
}