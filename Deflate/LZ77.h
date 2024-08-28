#ifndef __LZ77_H__
#define __LZ77_H__

#define SEARCH_BUFF_SIZE    64
#define LOOKAHEAD_BUFF_SIZE 32

#include <queue>
#include <string>

using namespace std;

namespace LZ77{
	struct LLD{
		int i;
		int j;
		char x;
	};

	void Compress(ifstream& fin, ofstream& fout);
	void Release(ifstream& fin, ofstream& fout);

	void InputAndCompress(string input_file_name, string output_file_name);
	void OutputAndRelease(string input_file_name, string output_file_name);
}

#endif