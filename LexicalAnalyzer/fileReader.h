#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*
 ��ȡ�ļ�Ϊ�ַ�������
*/

class FileReader {
public:
    /* һ���Զ�ȡ�ļ� */
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