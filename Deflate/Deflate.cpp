#include <iostream>
#include <string>
#include "LZ77.h"
#include "Huffman.h"

using namespace std;

int main(){
    int menu_num;
    string in_file, out_file;

    cout << "Deflate(1: ����, 2: ���� ����, 3:����): ";
    cin >> menu_num;

    if (menu_num == 1) {
        cout << "������ ���� �̸�: ";
        cin >> in_file;
        cout << "����� ���� �̸�: ";
        cin >> out_file;

        LZ77::InputAndCompress(in_file, "tmp.b");
        Huffman::InputAndCompress("tmp.b", out_file);
    }
    else if (menu_num == 2) {
        cout << "���� ������ ���� �̸�: ";
        cin >> in_file;
        cout << "����� ���� �̸�: ";
        cin >> out_file;

        Huffman::OutputAndRelease(in_file, "tmp.b");
        LZ77::OutputAndRelease("tmp.b", out_file);
    }
    else {
        cout << "����";
        return 0;
    }

    return 0;
}