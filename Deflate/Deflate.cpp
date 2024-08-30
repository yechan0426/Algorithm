#include <iostream>
#include <string>
#include <fstream>
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

        ifstream fin;
        ofstream oftmp;
        ifstream iftmp;
        ofstream fout;

        fin.open(in_file.c_str(), ios::binary);
        oftmp.open("tmp.b", ios::binary);

        if (!fin) {
            cout << "�Է� ������ ���� ���Ͽ����ϴ�.\n";
            return -1;
        }
        if (!oftmp) {
            cout << "tmp���� ���� ����\n";
            return -1;
        }

        LZ77::Compress(fin, oftmp);

        fin.close();
        oftmp.close();


        iftmp.open("tmp.b", ios::binary);
        fout.open(out_file.c_str(), ios::binary);

        if (!iftmp) {
            cout << "tmp���� �ε� ����\n";
            return -1;
        }
        if (!fout) {
            cout << "��� ���� ������ �����Ͽ����ϴ�.\n";
            return -1;
        }

        Huffman::Compress(iftmp, fout);

        iftmp.close();
        fout.close();
    }
    else if (menu_num == 2) {
        cout << "���� ������ ���� �̸�: ";
        cin >> in_file;
        cout << "����� ���� �̸�: ";
        cin >> out_file;

        ifstream fin;
        ofstream oftmp;
        ifstream iftmp;
        ofstream fout;

        fin.open(in_file.c_str(), ios::binary);
        oftmp.open("tmp.b", ios::binary);

        if (!fin) {
            cout << "�Է� ������ ���� ���Ͽ����ϴ�.\n";
            return -1;
        }
        if (!oftmp) {
            cout << "tmp���� ���� ����\n";
            return -1;
        }

        Huffman::Release(fin, oftmp);

        fin.close();
        oftmp.close();


        iftmp.open("tmp.b", ios::binary);
        fout.open(out_file.c_str(), ios::binary);

        if (!iftmp) {
            cout << "tmp���� �ε� ����\n";
            return -1;
        }
        if (!fout) {
            cout << "��� ���� ������ �����Ͽ����ϴ�.\n";
            return -1;
        }

        LZ77::Release(iftmp, fout);

        iftmp.close();
        fout.close();
    }
    else {
        cout << "����";
        return 0;
    }

    return 0;
}