#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LZ77.h"

using namespace LZ77;

std::queue<char> search_buff, lookahead_buff;

void FileRead(string& v, ifstream& fin) { //파일을 읽고 벡터에 저장
    string line;
    while (true) {
        getline(fin, line);
		v += line;
        if (fin.eof()) break;
    }
}

void LLDWrite(LLD& t, ofstream& fout) {
	fout.write((char*)&t.i, sizeof(int));
	fout.write((char*)&t.j, sizeof(int));
	fout.write(&t.x, sizeof(char));
}

void LZ77::Compress(ifstream& fin, ofstream& fout) { //압축
	string s_input;
	int i, k, j;
	LLD tmpM, tmp;
    queue<char> tmpSB, tmpLB;

	FileRead(s_input, fin);
	for (i = 0; i < s_input.size();) {
        if (i >= LOOKAHEAD_BUFF_SIZE) { break; }
        lookahead_buff.push(s_input[i++]);
    }printf("\n");

    j = i;
    tmpM.i = 0;
    tmpM.j = 0;
    tmpM.x = '\0';
    for (i = 0; i < s_input.size();) {
        if (lookahead_buff.empty()) { break; }
        tmpSB = search_buff;
        tmpLB = lookahead_buff;

        tmpM.i = 0;
        tmpM.j = 0;
        tmpM.x = tmpLB.front();

        tmp = tmpM;

        while (!tmpSB.empty()) {
            tmp.x = tmpLB.front();
            if (tmpLB.size() <= 1 || tmpSB.front() != tmpLB.front()) {
                tmpSB.pop();
                if (tmp.j >= tmpM.j) {
                    tmpM = tmp;
                }
                tmpLB = lookahead_buff;
                tmp.i = 0;
                tmp.j = 0;
                continue;
            }
            if (!tmp.i) { tmp.i = tmpSB.size(); }
            tmp.j++;
            tmpSB.pop();
            tmpLB.pop();
        }
        if (tmp.j >= tmpM.j) {
            tmpM = tmp;
        }

        LLDWrite(tmpM, fout);

        for (k = 0; k <= tmpM.j; k++) {
            if (lookahead_buff.empty()) { break; }
            search_buff.push(lookahead_buff.front());
            if (search_buff.size() > SEARCH_BUFF_SIZE) { search_buff.pop(); }
            lookahead_buff.pop();
            i++;
            if (j >= s_input.size()) { continue; }
            lookahead_buff.push(s_input[j++]);
        }
    }
}

void LLDRead(LLD& t, ifstream& fin) {
	fin.read((char*)&t.i, sizeof(int));
	fin.read((char*)&t.j, sizeof(int));
	fin.read(&t.x, sizeof(char));
}

void LZ77::Release(ifstream& fin, ofstream& fout) { //압축 해제
    LLD tmp;
    queue<char> tmpSB;
    int i, k;

    while (true) {
        LLDRead(tmp, fin);
        if (fin.eof()) break;

        if (tmp.i != 0) {
            tmpSB = search_buff;
            while (tmpSB.size() > tmp.i) { tmpSB.pop(); }
            for (int i = 0; i < tmp.j; i++) {
                search_buff.push(tmpSB.front());
                if (search_buff.size() > SEARCH_BUFF_SIZE) { search_buff.pop(); }
                fout.write(&tmpSB.front(), sizeof(char));
                tmpSB.pop();
            }
        }
        search_buff.push(tmp.x);
        if (search_buff.size() > SEARCH_BUFF_SIZE) { search_buff.pop(); }
        fout.write(&tmp.x, sizeof(char));
    }
}