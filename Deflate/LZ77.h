#ifndef __LZ77_H__
#define __LZ77_H__

#define SEARCH_BUFF_SIZE    (1024*32) // 1KIB * 32 = 2^15
#define LOOKAHEAD_BUFF_SIZE (255) // 2^8 - 1

#include <queue>
#include <string>

using namespace std;

namespace LZ77{
	struct LLD{
		uint16_t i;
		uint8_t j;
		char x;
	};

	void Compress(ifstream& fin, ofstream& fout);
	void Release(ifstream& fin, ofstream& fout);
}

#endif