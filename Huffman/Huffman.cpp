#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

struct Node {
    char c = '\0';  //문자열
    int cnt;        //빈도수
    Node *left;     //왼쪽 노드
    Node *right;    //오른쪽 노드
};
Node *root_node;    //루트 노드

unordered_map<char, uint32_t> huffman_code; //[문자] = 이진코드
unordered_map<char, uint8_t> h_c_len;       //이진코드의 길이
unordered_map<char, uint32_t> frequency;    //문자의 빈도수

struct comp { // 우선순위 큐를 위한 연산자 오버로딩
    bool operator() (Node* x, Node* y) {
        return x->cnt > y->cnt;
    }
};

priority_queue<Node*, vector<Node*>, comp> node_queue; //cnt가 크면 top에 위치

void FileRead(vector<string>& v, ifstream& fin) { //파일을 읽고 벡터에 저장
    string line;
    while (true) {
        getline(fin, line);
        v.push_back(line);
        cout << line << endl;
        if (fin.eof()) break;
    }
}

void GetFrequency(vector<string>& v) { //문자의 빈도 수 구하고 저장
    for (string i : v) {
        for (char c : i) {
            frequency[c]++;
        }
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
        printf("%c %d\n", i.first, i.second);

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
    if (node->c != '\0') {
        huffman_code[node->c] = num;
        h_c_len[node->c] = len;
        return;
    }

    num = num << 1;
    MakeHuffmanCode(node->left, num, len+1u);
    num += 1u;
    MakeHuffmanCode(node->right, num, len+1u);
}

void WriteByte(ofstream& fout, uint32_t b_code, bool flush) {
    static uint32_t bit = 0;
    static int empty_bit = 32;
    if (flush == true)
    {
        bit << empty_bit;
        fout << bit;
        return;
    }
}

void Compress(ifstream& fin, ofstream& fout) {
    vector<string> s_input;                   //입력된 문자열 (string형)
    vector<uint8_t> compressed;               //압축된 문자열 (8bit형)

    FileRead(s_input, fin);
    GetFrequency(s_input);
    MakeHuffmanTree();
    MakeHuffmanCode(root_node, 0u, 1);

    //압축된 내용저장
    for (string s : s_input) {
        for (char c : s) {
            WriteByte(fout, huffman_code[c], false);
        }
    }
    WriteByte(fout, 0, true);// 마지막 비트8개 모이지 않아도 저장
}

void DeleteTree(Node* pNode) { //동적할당 해제
    if (pNode == nullptr) { return; }

    DeleteTree(pNode->left);
    DeleteTree(pNode->right);

    free(pNode);
}

int main()
{
    int menu_num;
    string input_file_name, output_file_name;
    ifstream fin;
    ofstream fout;
    

    cout << "1: 압축, 2: 압축 해제, 3: 종료\n";
    cin >> menu_num;
    if (menu_num == 1) {
        cout << "입력할 파일명 입력: ";
        cin >> input_file_name;
        cout << "출력할 파일명 입력: ";
        cin >> output_file_name;
        
        input_file_name += ".txt";
        output_file_name += ".txt";
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
        DeleteTree(root_node);
    }
}
/*
https://blockdmask.tistory.com/392
*/