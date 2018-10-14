#include <iostream>
#include <algorithm>
#include <search.h> // for the qsort()
using namespace std;

#define N 15
struct student_t {
	int id;
	string name;
	float score;

	bool operator<(const student_t& b) const {
		return score < b.score;
	}
} students[N];

int stl_sort_main(int argc, char *argv[]) {
	int a[7] = { 23, 1, 33, -20, 6, 6, 9 };
	sort(a, a + 7);
	for (int i = 0; i < 7; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	///
	for (int i = 0; i < N; i++) {
		students[i].score = N - i;
	}
	cout << "Unsorted: ";
	for (int i = 0; i < N; i++) {
		cout << students[i].score << " ";
	}
	cout << endl;
	sort(students, students + N);
	cout << "Sorted: ";
	for (int i = 0; i < N; i++) {
		cout << students[i].score << " ";
	}
	cout << endl;

	return 0;
}
