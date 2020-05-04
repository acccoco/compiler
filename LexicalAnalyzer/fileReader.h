#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*
 �����ļ��������
*/
class FileReader {
public:
    /*
     ��ȡָ���ļ�������һ���ַ������飬ÿһ��Ԫ�ش���һ���ַ���
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