#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LZ77.h"

using namespace LZ77;

std::queue<wchar_t> search_buff, lookahead_buff;

void FileRead(vector<wchar_t>& v, ifstream& fin) { //파일을 읽고 벡터에 저장
    wchar_t c;
    while (true) {
        fin.get(c);
        if (fin.eof()) break;
		v.push_back(c);
    }
}

void LLDWrite(LLD& t, ofstream& fout) {
	fout.write((char*)&t.i, sizeof(uint8_t));
	fout.write((char*)&t.j, sizeof(uint8_t));
	fout.write((char*)&t.x, sizeof(wchar_t));
}

void LZ77::Compress(ifstream& fin, ofstream& fout) { //압축
	vector<wchar_t> s_input;
	int i, k, j;
	LLD tmpM, tmp;
    queue<wchar_t> tmpSB, tmpLB;

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
	fin.read((char*)&t.i, sizeof(uint8_t));
	fin.read((char*)&t.j, sizeof(uint8_t));
	fin.read((char*)&t.x, sizeof(wchar_t));
}

void LZ77::Release(ifstream& fin, ofstream& fout) { //압축 해제
    LLD tmp;
    queue<wchar_t> tmpSB;
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
                fout.write((char*)&tmpSB.front(), sizeof(wchar_t));
                tmpSB.pop();
            }
        }
        search_buff.push(tmp.x);
        if (search_buff.size() > SEARCH_BUFF_SIZE) { search_buff.pop(); }
        fout.write((char*)&tmp.x, sizeof(wchar_t));
    }
}

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