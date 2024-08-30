#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <iostream>
#include <stdint.h>
#include <queue>
#include <unordered_map>

using namespace std; 

namespace Huffman{
    struct Node {
        char c;          //문자열
        uint32_t cnt;    //빈도수
        Node *left = nullptr;      //왼쪽 노드
        Node *right = nullptr;     //오른쪽 노드
    };

    void Compress(ifstream& fin, ofstream& fout);
    void Release(ifstream& fin, ofstream& fout);
}

#endif