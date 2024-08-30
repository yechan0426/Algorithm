#ifndef __LZ77_H__
#define __LZ77_H__

#define SEARCH_BUFF_SIZE    64 // ~ 256
#define LOOKAHEAD_BUFF_SIZE 32 // ~ 256

#include <queue>
#include <string>

using namespace std;

namespace LZ77{
	struct LLD{
		uint8_t i;
		uint8_t j;
		wchar_t x;
	};

	void Compress(ifstream& fin, ofstream& fout);
	void Release(ifstream& fin, ofstream& fout);
}

#endif