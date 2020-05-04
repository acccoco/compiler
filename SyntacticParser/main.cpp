#include "../LexicalAnalyzer/Token.h"
#include "../LexicalAnalyzer/LexicalAnalyzer.h"
#include "../LexicalAnalyzer/fileReader.h"
#include "SyntaxWriter.h"
#include <vector>
#include <iostream>
using namespace std;

#if false
int main(int argc, char** argv) {
	// ��ȡ�����в���
	if (argc != 3) {
		cout << "�����������" << endl;
		return 0;
	}
	string fileInPath, fileOutPath;
	fileInPath = argv[1];
	fileOutPath = argv[2];

	// ��ȡ�ļ�
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
	vector<string> rawStrs = FileReader().readFile(fileIn);

	// �ʷ�����
	LexialAnalyzer analyzer;
	analyzer.LexicalAnlyze(rawStrs);
	auto tokens = analyzer.GetResultTokens();
	auto tokenErrors = analyzer.GetResultErrors();

	// �ر��ļ�
	fileIn.close();
	fileOut.close();

	// �﷨����


	// д����


	return 0;
}

#endif
