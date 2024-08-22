#include <iostream>
#include <string>
#include <vector>

#define LOOKAHEAD_BUFF_SIZE 64
#define WINDOW_BUFF_SIZE    32

using namespace std;

int main()
{
	string INPUT, OUTPUT, tmp;
	int literal, length;
	char distance;
	int cnt;

	while (true) {
		getline(cin, tmp);
		if (tmp == "!STOP") { break; }
		INPUT += tmp;
	}

	OUTPUT = "LB";
	OUTPUT += to_string(LOOKAHEAD_BUFF_SIZE);
	OUTPUT += "WB";
	OUTPUT += to_string(WINDOW_BUFF_SIZE);

	int i, k;
	for (i = 0; i < INPUT.size(); i++) {
		literal = 0;
		length = 0;
		k = i - LOOKAHEAD_BUFF_SIZE;
		distance = INPUT[i];
		if (k < 0) {
			k = 0;
		}
		for (k; k < i; k++) {
			cnt = 0;
			while (i + cnt + 1 < INPUT.size() && k < i && INPUT[k] == INPUT[i + cnt]) {
				cnt++;
				k++;
			}if (cnt == 0) {
				continue;
			}
			if (cnt >= length) {
				length = cnt;
				literal = i - k + cnt;
				distance = INPUT[i + cnt];
			}
		}
		i += length;
		OUTPUT += "(";
		OUTPUT += to_string(literal);
		OUTPUT += ",";
		OUTPUT += to_string(length);
		OUTPUT += ",";
		OUTPUT += distance;
		OUTPUT += ")";
	}

	cout << OUTPUT;

	return 0;
}