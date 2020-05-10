#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <list>
using namespace std;



/* ������д���ļ��ĸ����� */
class FileWriter {
public:

    /* ������ļ�����д���ַ������� */
    void write2File(ofstream& of, vector<string> strs) {
        for (string str : strs) {
            of << str << endl;
        }
    }

    /* ������ļ�����д���ַ������� */
    void write2File(ofstream& of, list<string> strs) {
        for (string str : strs) {
            of << str << endl;
        }
    }
};