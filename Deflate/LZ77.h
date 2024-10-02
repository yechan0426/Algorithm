#ifndef __LZ77_H__
#define __LZ77_H__

#define SEARCH_BUFF_SIZE    31 // 2^5 - 1
#define LOOKAHEAD_BUFF_SIZE 7 // 2^3 - 1

#include <queue>
#include <string>

using namespace std;

namespace LZ77{
	struct LLD{
		uint8_t i;
		uint8_t j;
		char x;
	};

	void Compress(ifstream& fin, ofstream& fout);
	void Release(ifstream& fin, ofstream& fout);
}

#endif