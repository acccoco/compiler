#include <iostream>
#include <fstream>
using namespace std;
#include "LexicalAnalyzer.h"
#include "fileReader.h"
#include "TokenWriter.h"


/**
 �ʷ������������������в�����
   ����1�������ļ�
   ����2������ļ�
*/
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
	// ���д���ļ�
	TokenWriter().Write2File(tokens, tokenErrors, fileOut);

	// �ر��ļ�
	fileIn.close();
	fileOut.close();
	return 0;
}

