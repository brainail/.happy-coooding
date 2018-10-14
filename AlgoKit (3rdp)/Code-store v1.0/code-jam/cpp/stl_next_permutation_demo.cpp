#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/* http://marknelson.us/2002/03/01/next-permutation */

void swap(char* first, char* second) {
	char ch = *second;
	*second = *first;
	*first = ch;
}

int permute(char* set, int begin, int end) {
	int i;
	int range = end - begin;
	if (range == 1) {
		cout << set << endl;
	} else {
		for (i = 0; i < range; i++) {
			swap(&set[begin], &set[begin + i]); //initial swap
			permute(set, begin + 1, end); //recursion
			swap(&set[begin], &set[begin + i]); //swap back
		}
	}
	return 0;
}

int stl_perm_main(int argc, char *argv[]) {
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int count = 0;
	do {
		if ((a[0] + a[1] + a[2]) == 17 && (a[0] + a[3] + a[6]) == 17
				&& (a[2] + a[5] + a[8]) == 17 && (a[2] + a[4] + a[6]) == 17
				&& (a[6] + a[7] + a[8]) == 17) {
			cout << count << " : ";
			for (int i = 0; i < 9; i++)
				cout << a[i] << " ";
			cout << endl;
		}
		count++;
	} while (next_permutation(a, a + 9));
	cout << count << " permutations were tested\n";

	string s = "12345";
//	char *str = strdup(s.c_str());	// POSIX
	char* str = new char[s.size() + 1];
	copy(s.begin(), s.end(), str);
	str[s.size()] = '\0'; // don't forget the terminating 0

	permute(str, 0, strlen(str));

	// don't forget to free the string after finished using it
	delete[] str;

	return 0;
}
