#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;
bool q[200];
int p[200];
const int NNodes = 128;

int main() {
	long long total_round = 0;
	int times = 1000000;
	int Ntimes= 1000000;
	while (times--) {
		srand(time(NULL));
		int round = 0;
		memset(q, false , sizeof(q));
		q[0] = true;
		int cnt = 1;
		while (cnt < NNodes) {
			for (int i = 0; i < NNodes; i++) {
				p[i] = rand() % NNodes;
				while (p[i] == i) p[i] = rand() % NNodes;
			}
			int tmp_q[200];
			for (int i = 0; i < NNodes; i++) {
				tmp_q[i] = q[i];
			}

			for (int i = 0; i < NNodes; i++) {
				if (tmp_q[i]) {
					if (!q[p[i]]) cnt++;
					q[p[i]] = q[p[i]] + true;
				}
			}
			round++;
//			cout << "round = " << round << ", cnt = " << cnt <<endl; 
		}
		cout << round << endl;
		total_round = total_round + round;
	}

	cout << total_round << endl;
	cout << "# of avg_round = " << total_round * 1.0 / Ntimes << endl;
	return 0;
}
