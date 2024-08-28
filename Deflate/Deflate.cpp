#include <iostream>
#include <string>
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

        LZ77::InputAndCompress(in_file, "tmp.b");
        Huffman::InputAndCompress("tmp.b", out_file);
    }
    else if (menu_num == 2) {
        cout << "압축 해제할 파일 이름: ";
        cin >> in_file;
        cout << "출력할 파일 이름: ";
        cin >> out_file;

        Huffman::OutputAndRelease(in_file, "tmp.b");
        LZ77::OutputAndRelease("tmp.b", out_file);
    }
    else {
        cout << "종료";
        return 0;
    }

    return 0;
}