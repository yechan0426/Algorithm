#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define LOOKAHEAD_BUFF_SIZE 64
#define WINDOW_BUFF_SIZE    32

using namespace std;

struct LLD{
	int i;
	int j;
	char x;
};

int main()
{
    int menu_num;
    string input_file_name, output_file_name;
    ifstream fin;
    ofstream fout;

    cout << "LZ77(1: 압축, 2: 압축 해제, 3: 종료): ";
    cin >> menu_num;
    if (menu_num == 1) {
        cout << "입력할 파일명 입력: ";
        cin >> input_file_name;
        cout << "출력할 파일명 입력: ";
        cin >> output_file_name;

        fin.open(input_file_name.c_str(), ios::binary);
        fout.open(output_file_name.c_str(), ios::binary);

        if (!fin) {
            cout << "파일이 존재하지 않습니다.";
            return -1;
        }
        if (!fout) {
            cout << "파일 생성을 실패했습니다.";
            return -1;
        }

        Compress(fin, fout);

        fin.close();
        fout.close();
    }
    else if (menu_num == 2) {
        cout << "입력할 파일명 입력: ";
        cin >> input_file_name;
        cout << "출력할 파일명 입력: ";
        cin >> output_file_name;
		
        fin.open(input_file_name.c_str(), ios::binary);
        fout.open(output_file_name.c_str(), ios::binary);

        if (!fin) {
            cout << "파일이 존재하지 않습니다.";
            return -1;
        }
        if (!fout) {
            cout << "파일 생성을 실패했습니다.";
            return -1;
        }

        Release(fin, fout);

        fin.close();
        fout.close();
    }
    else {
        cout << "종료합니다.";
        return 0;
    }
    return 0;
}