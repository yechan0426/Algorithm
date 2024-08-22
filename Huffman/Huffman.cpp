#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <cstdio>

using namespace std;

struct Node {
    char c = '\0';  //문자열
    int cnt;        //빈도수
    Node* left;     //왼쪽 노드
    Node* right;    //오른쪽 노드
};
Node* root_node;    //루트 노드

string s_input;                      //입력된 문자열 (string형)
vector<bool> compressed;             //압축된 문자열 (bool형)
unordered_map<char, int> frequency;  //문자의 빈도수

int main()
{
    int menu_num;
    string input_file_name, output_file_name;
    FILE* fin = nullptr;
    FILE* fout = nullptr;

    while (true) {
        cout << "1: 압축, 2: 압축 해제, 3: 종료\n";
        cin >> menu_num;
        if (menu_num == 1) {
            cout << "입력할 파일명 입력: ";
            cin >> input_file_name;
            cout << "출력할 파일명 입력: ";
            cin >> output_file_name;
            fin = fopen(input_file_name.c_str(), "rt");
            fout = fopen(output_file_name.c_str(), "")
        }
    }
}
/*
https://blockdmask.tistory.com/392
*/