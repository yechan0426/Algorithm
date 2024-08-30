#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Huffman.h"

using namespace Huffman;

Node *root_node = nullptr;    //루트 노드

unordered_map<char, uint32_t> huffman_code; //[문자] = 이진코드
unordered_map<char, uint8_t> h_c_len;       //이진코드의 길이
unordered_map<char, uint32_t> frequency;    //문자의 빈도수

struct comp { // 우선순위 큐를 위한 연산자 오버로딩
    bool operator() (Node* x, Node* y) {
        return x->cnt > y->cnt;
    }
};

priority_queue<Node*, vector<Node*>, comp> node_queue; //cnt가 낮으면 top에 위치


void FileRead(vector<char>& v, ifstream& fin, long long& len) { //파일을 읽고 벡터에 저장
    char c;
    while (true) {
        fin.get(c);
        if (fin.eof()) break;
		v.push_back(c);
        len++;
    }
}

void DeleteTree(Node* pNode) { //동적할당 해제
    if (pNode == nullptr) { return; }

    DeleteTree(pNode->left);
    DeleteTree(pNode->right);

    free(pNode);
}

void GetFrequency(vector<char>& v) { //문자의 빈도 수 구하고 저장
    for (char i : v) {
        frequency[i]++;
    }
}

void MakeHuffmanTree() { //허프먼 트리 생성
    Node *top1, *top2;
    for (auto i : frequency) {
        Node* tmp_node = (Node*)malloc(sizeof(Node));

        tmp_node->c = i.first;
        tmp_node->cnt = i.second;
        tmp_node->left = nullptr;
        tmp_node->right = nullptr;

        node_queue.push(tmp_node);
    }

    
    while (node_queue.size() > 1) {
        top1 = node_queue.top();
        node_queue.pop();
        top2 = node_queue.top();
        node_queue.pop();

        Node* tmp_node = (Node*)malloc(sizeof(Node));

        tmp_node->c = '\0';
        tmp_node->cnt = top1->cnt + top2->cnt;
        tmp_node->left = top1;
        tmp_node->right = top2;

        node_queue.push(tmp_node);
    }

    root_node = node_queue.top();
}

void MakeHuffmanCode(Node *node, uint32_t num, uint8_t len) { // 문자열에 이진수 할당
    if (node->left == nullptr && node->right == nullptr) {
        huffman_code[node->c] = num;
        h_c_len[node->c] = len;
        return;
    }

    num = num << 1;
    MakeHuffmanCode(node->left, num, len+1u);
    num += 1u;
    MakeHuffmanCode(node->right, num, len+1u);
}

void WriteByte(ofstream& fout, uint32_t b_code, uint8_t b_len, bool flush) {
    static uint32_t bit = 0;
    static int empty_bit = 32;
    if (flush == true)
    {
        bit = bit << empty_bit;
        fout.write((char*)&bit, 4);
        return;
    }

    if (b_len > empty_bit) {
        bit = bit << empty_bit;
        int tmp = b_code >> (b_len - empty_bit);
        b_code = b_code | (tmp << (b_len - empty_bit));
        b_len -= empty_bit;
        bit = bit | tmp;
        fout.write((char*)&bit, 4);
        bit = 0;
        empty_bit = 32;
    }

    empty_bit -= b_len;
    bit = (bit << b_len) | b_code;
}

void Huffman::Compress(ifstream& fin, ofstream& fout) {
    vector<char> s_input;                   //입력된 문자열 (string형)
    uint32_t size;
    long long s_len = 0;

    for(char i:s_input){printf("%d ",i);}

    FileRead(s_input, fin, s_len);
    GetFrequency(s_input);
    MakeHuffmanTree();
    MakeHuffmanCode(root_node, 0u, 0);

    //허프만 코드 기록
    size = huffman_code.size();
    fout.write((char*)&s_len, sizeof(long long));
    fout.write((char*)&size, sizeof(uint32_t));
    for (auto i : huffman_code) {
        fout.write((char*)&i.first, sizeof(char));
        fout.write((char*)&i.second, sizeof(uint32_t));
        fout.write((char*)&h_c_len[i.first], sizeof(uint8_t));
    }

    //압축된 내용저장
    for (char c : s_input) {
        WriteByte(fout, huffman_code[c], h_c_len[c], false);
    }
    WriteByte(fout, 0, 0, true);// 마지막 비트32개 모이지 않아도 저장

    DeleteTree(root_node);
}

void ReMakeHuffTree(char c)
{
    if (root_node == nullptr){
        root_node = (Node*)malloc(sizeof(Node));
        root_node->left = nullptr;
        root_node->right = nullptr;
    }
    // HuffCode와nLength를 이용해서 허프만 트리 구성하기
    Node* node = nullptr;
    Node* Temp = nullptr;
    node = Temp = root_node;

    int nLength = h_c_len[c];
    unsigned int HuffCode = huffman_code[c];

    while (nLength > 0)
    {
        int nBit = (HuffCode >> (nLength - 1)) & 1;
        if (nBit == 0)
        {
            Temp = Temp->left;
            if (Temp == nullptr)
            {
                Temp = (Node*)malloc(sizeof(Node));
                Temp->left = nullptr;
                Temp->right = nullptr;
                node->left = Temp;
            }
        }
        else
        {
            Temp = Temp->right;
            if (Temp == nullptr)
            {
                Temp = (Node*)malloc(sizeof(Node));
                Temp->left = nullptr;
                Temp->right = nullptr;
                node->right = Temp;
            }
        }
        node = Temp;
        nLength--;
    }
    Temp->c = c;
}

bool ReadBit(ifstream& fin)
{
    static unsigned int Cur = 0;
    static int Bit = -1;
    if (Bit < 0)
    {
        fin.read((char*)&Cur, 4);
        Bit = 31;
    }

    if (fin.eof())
        return 0;

    bool HuffBit = 0;
    HuffBit = (Cur >> Bit) & 1;
    Bit--;

    return HuffBit;
}
void Huffman::Release(ifstream& fin, ofstream& fout) {
    uint32_t size;
    char c;
    uint32_t num;
    uint8_t len;
    long long s_len;

    fin.read((char*)&s_len, sizeof(long long));
    fin.read((char*)&size, sizeof(uint32_t));
    while(size--) {
        fin.read((char*)&c, sizeof(char));
        fin.read((char*)&num, sizeof(uint32_t));
        fin.read((char*)&len, sizeof(uint8_t));
        huffman_code[c] = num;
        h_c_len[c] = len;
        ReMakeHuffTree(c);
    }

    Node* node = root_node;
    bool bit = ReadBit(fin);
    long long w_len = 0;

    while (w_len < s_len) {
        while (node->left && node->right) //자식 노드가없는 단말 노드일때까지
        {
            if (bit == 0)                 //읽어온 비트가 0이면
                node = node->left;
            else                           //읽어온 비트가 1이면
                node = node->right;

            bit = ReadBit(fin);
        }
        fout.write((char*)&node->c, sizeof(char));//단말 노드의 문자를 파일에쓴다.
        node = root_node;
        w_len++;
    }

    DeleteTree(root_node);
}
/*
int main() {
    int m;
    cin >> m;
    string in, out;

    ifstream fin;
    ofstream fout;

    if(m==1){
        cin >> in;
        cin >> out;

        fin.open(in.c_str(), ios::binary);
        fout.open(out.c_str(), ios::binary);

        Compress(fin, fout);

        fin.close();
        fout.close();
    }
    else if(m==2){
        cin >> in;
        cin >> out;

        fin.open(in.c_str(), ios::binary);
        fout.open(out.c_str(), ios::binary);

        Release(fin, fout);

        fin.close();
        fout.close();
    }
}
*/