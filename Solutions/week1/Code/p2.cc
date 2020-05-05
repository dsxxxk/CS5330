// author: BAO Jinge
// Student ID: A0214306U
// NUSNET ID: e0522065
// problem: P2 in assigment 1
// lecture: CS5330 randomized algorithms
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int randbit() {
	int random = rand() % 2;
	return random;
}

int a[1000005];


int main() {
	srand(time(NULL));
	int iter = 1000000;
	int n = 8;
	for (int i = 0; i < iter; i++) {
		int x = randbit() * 4 + randbit() * 2 + randbit() * 1;
		a[i] = x;
	}
	int len[10];
	memset(len, 0 , sizeof(len));
	int p = a[0];
	int lencnt = 1;
	for (int i = 1; i < iter; i++) {
		if (a[i] == p) {
			lencnt++;
		} else {
			len[p] = max(len[p],lencnt);
			lencnt = 0;
			p = a[i];
		}
	}

	int answer = -1;
	for (int i = 0; i < n; i++) {
		cout << i << ":" << len[i] << endl;
		answer = max(answer, len[i]);
	}

	cout << "the length of the longest streak in array a:" << answer << endl;

	return 0;
}