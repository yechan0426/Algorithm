#include <iostream>
#include <string>
#include <fstream>
#include "LZ77.h"
#include "Huffman.h"

using namespace std;

int main(){
    int menu_num;
    string in_file, out_file;

    cout << "Deflate(1: 압축, 2: 압축 해제, 3:종료): ";
    cin >> menu_num;

    if (menu_num == 1) {
        cout << "압축할 파일 이름: ";
        cin >> in_file;
        cout << "출력할 파일 이름: ";
        cin >> out_file;

        ifstream fin;
        ofstream oftmp;
        ifstream iftmp;
        ofstream fout;

        fin.open(in_file.c_str(), ios::binary);
        oftmp.open("tmp.b", ios::binary);

        if (!fin) {
            cout << "입력 파일을 열지 못하였습니다.\n";
            return -1;
        }
        if (!oftmp) {
            cout << "tmp파일 생성 실패\n";
            return -1;
        }

        LZ77::Compress(fin, oftmp);

        fin.close();
        oftmp.close();


        iftmp.open("tmp.b", ios::binary);
        fout.open(out_file.c_str(), ios::binary);

        if (!iftmp) {
            cout << "tmp파일 로드 실패\n";
            return -1;
        }
        if (!fout) {
            cout << "출력 파일 생성을 실패하였습니다.\n";
            return -1;
        }

        Huffman::Compress(iftmp, fout);

        iftmp.close();
        fout.close();
    }
    else if (menu_num == 2) {
        cout << "압축 해제할 파일 이름: ";
        cin >> in_file;
        cout << "출력할 파일 이름: ";
        cin >> out_file;

        ifstream fin;
        ofstream oftmp;
        ifstream iftmp;
        ofstream fout;

        fin.open(in_file.c_str(), ios::binary);
        oftmp.open("tmp.b", ios::binary);

        if (!fin) {
            cout << "입력 파일을 열지 못하였습니다.\n";
            return -1;
        }
        if (!oftmp) {
            cout << "tmp파일 생성 실패\n";
            return -1;
        }

        Huffman::Release(fin, oftmp);

        fin.close();
        oftmp.close();


        iftmp.open("tmp.b", ios::binary);
        fout.open(out_file.c_str(), ios::binary);

        if (!iftmp) {
            cout << "tmp파일 로드 실패\n";
            return -1;
        }
        if (!fout) {
            cout << "출력 파일 생성을 실패하였습니다.\n";
            return -1;
        }

        LZ77::Release(iftmp, fout);

        iftmp.close();
        fout.close();
    }
    else {
        cout << "종료";
        return 0;
    }

    return 0;
}