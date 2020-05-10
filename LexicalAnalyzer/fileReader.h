#pragma once
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*
 ���ļ���������
*/
class FileReader {
public:
    /*
     ��ȡһ���ļ�
     ���أ��ַ������飬һ��Ԫ�ر�ʾһ��
    */
    vector<string> readFile(ifstream& ifs) {
        vector<string> rawStrs;
        string lineStr;
        do {
            getline(ifs, lineStr, '\n');
            rawStrs.push_back(lineStr);
        } while (ifs.good());
        return rawStrs;
    }
};