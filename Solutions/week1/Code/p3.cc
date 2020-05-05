// author: BAO Jinge
// Student ID: A0214306U
// NUSNET ID: e0522065
// problem: P3 in assigment 1
// lecture: CS5330 randomized algorithms
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

const int MAXV = 100;

int _edge[MAXV][MAXV];
int fa[MAXV];

int getfa(int x) {
	if (fa[x] == x) {
		return x;
	} else{
		return fa[x] = getfa(fa[x]);
	}
}


int main(){
	srand(time(NULL));
	int nV = 50;
	int min_cut_size = 9999999;
	int iter = 0;
	for (int i = 0; i < nV; i++) {
		for (int j = 0; j < nV; j++) {
			cin >> _edge[i][j];
		}
	}

	while (true) {
		int edge[MAXV][MAXV];
		vector<int> v;
		v.clear();
		for (int i = 0; i < nV; i++) {
			for (int j = 0; j < nV; j++) {
				edge[i][j] = _edge[i][j];
			}
		}
		for (int i = 0; i < nV; i++) {
			fa[i] = i;
		}
		for (int i = 0; i < nV; i++) {
			v.push_back(i);
		}
		while(v.size() > 2) {
			int index_i = rand() % v.size();
			int index_j = rand() % v.size();
			int fa_i = getfa(v[index_i]);
			int fa_j = getfa(v[index_j]);
			if(fa_i != fa_j) {
				if (edge[fa_i][fa_j] >= 1) {
					if (fa_i != fa_j) {
						fa[fa_j] = fa_i;
						for (int k = 0; k < nV; k++) {
							fa[k] = getfa(fa[k]);
						}
						for (int k = 0; k < nV; k++) {
							edge[fa_i][k] = edge[k][fa_i] = edge[fa_i][k] + edge[fa_j][k];
						}
						edge[fa_i][fa_i] = 0;
						v.erase(v.begin() + index_j);
					}
				}
			}
		}	
//		cout << "the minimum cut size:" << edge[fa[v[0]]][fa[v[1]]] << endl;
//		cout << "iterations of the subroutine need to detect this answer" << ++iter << endl;
		min_cut_size = min(min_cut_size, edge[fa[v[0]]][fa[v[1]]]);
		iter++;
		if (min_cut_size == 3) {
			cout << "the minimum cut size:" << min_cut_size << ", after iteration" << iter <<endl;
			break;
		}
	}
	return 0;
}