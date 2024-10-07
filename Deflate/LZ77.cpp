#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LZ77.h"

using namespace LZ77;

long long search_buff, lookahead_buff;

void FileRead(vector<char>& v, ifstream& fin) { //파일을 읽고 벡터에 저장
    char c;
    while (true) {
        fin.get(c);
        if (fin.eof()) break;
		v.push_back(c);
    }
}

void LLDWrite(LLD& t, ofstream& fout) {
	fout.write((char*)&t.i, sizeof(uint16_t));
	fout.write((char*)&t.j, sizeof(uint8_t));
	fout.write((char*)&t.x, sizeof(char));
}

void LZ77::Compress(ifstream& fin, ofstream& fout) { //압축
	vector<char> s_input;
    long long size;
	long long i, j, k;
	LLD tmpM, tmp;

	FileRead(s_input, fin);

    size = s_input.size();

    tmpM.i = 0;
    tmpM.j = 0;
    tmpM.x = '\0';
    for (i = 0; i < size;) {
        search_buff = i - SEARCH_BUFF_SIZE;
        if(search_buff < 0){ search_buff = 0; }

        lookahead_buff = i + LOOKAHEAD_BUFF_SIZE;
        if(lookahead_buff >= size){ lookahead_buff = size; }

        tmp = tmpM;

        k = 0;
        for(j = search_buff; j < i; j++){
            tmp.x = s_input[i+k];
            if(i+k >= lookahead_buff){
                tmpM = tmp;
                break;
            }
            if(s_input[j] != s_input[i+k]){
                if(tmpM.j < tmp.j){ tmpM = tmp; }

                tmp.i = 0;
                tmp.j = 0;
                tmp.x = '\0';
                k = 0;
                continue;
            }
            if(tmp.i == 0){ tmp.i = i-j; }
            tmp.j++;
            k++;
        }

        LLDWrite(tmpM, fout);
    }
}

void LLDRead(LLD& t, ifstream& fin) {
	fin.read((char*)&t.i, sizeof(uint16_t));
    fin.read((char*)&t.j, sizeof(uint8_t));
	fin.read((char*)&t.x, sizeof(char));
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
                fout.write((char*)&tmpSB.front(), sizeof(char));
                tmpSB.pop();
            }
        }
        search_buff.push(tmp.x);
        if (search_buff.size() > SEARCH_BUFF_SIZE) { search_buff.pop(); }
        fout.write((char*)&tmp.x, sizeof(char));
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
