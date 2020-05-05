//Author: Bao Jinge
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

const int N = 500000;
const int MOD_NUM = 1000;

int arr[N];

// one pivot QuickSort
int QSPartition(int a[], int l, int r){
    int temp = a[l];
    while(l < r){
        while(l < r && a[r] > temp) r--;
        a[l] = a[r];
        while(l < r && a[l] <= temp) l++;
        a[r] = a[l];
    }
    a[l] = temp;
    return l;
} 

void QuickSort(int a[], int l, int r){
    if(l < r) {
        int pos = QSPartition(a,l,r);
        QuickSort(a,l,pos-1);
        QuickSort(a,pos+1,r);
    }
} 

// One Pivot Random Quick Sort
int RQSPartition(int a[], int l, int r){
    int p = round(1.0*rand()/RAND_MAX*(r-l)+l);
    swap(a[p],a[l]);

    int temp = a[l];
    while(l < r){
        while(l < r && a[r] > temp) r--;
        a[l] = a[r];
        while(l < r && a[l] <= temp) l++;
        a[r] = a[l];
    }
    a[l] = temp;
    return l;
} 

void RandomQuickSort(int a[], int l, int r){
    if(l < r) {
        int pos = RQSPartition(a,l,r);
        QuickSort(a,l,pos-1);
        QuickSort(a,pos+1,r);
    }
} 
  
// Dual Pivot Quick Sort
pair<int,int> DPQSPartition(int a[], int l, int r) 
{ 
    if (a[l] > a[r]) 
        swap(a[l], a[r]); 
    int j = l + 1; 
    int g = r - 1, k = l + 1, p = a[l], q = a[r]; 
    while (k <= g) { 
        if (a[k] < p) { 
            swap(a[k], a[j]); 
            j++; 
        } 
        else if (a[k] >= q) { 
            while (a[g] > q && k < g) 
                g--; 
            swap(a[k], a[g]); 
            g--; 
            if (a[k] < p) { 
                swap(a[k], a[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    swap(a[l], a[j]); 
    swap(a[r], a[g]); 


    return make_pair(j, g); 
}
void DualPivotQuickSort(int a[], int l, int r) 
{ 
    if (l < r) { 
        int lp, rp;  
        pair<int,int> p = DPQSPartition(a, l, r); 
        lp = p.first;
        rp = p.second;
        DualPivotQuickSort(a, l, lp - 1); 
        DualPivotQuickSort(a, lp + 1, rp - 1); 
        DualPivotQuickSort(a, rp + 1, r); 
    } 
} 

// Random Dual Pivot Quick Sort
pair<int,int> RDPQSPartition(int a[], int l, int r) 
{ 
	int rand_x = round(1.0*rand()/RAND_MAX*(r-l)+l);
	int rand_y = round(1.0*rand()/RAND_MAX*(r-l)+l);
	while(rand_y == rand_x) {
		rand_y = round(1.0*rand()/RAND_MAX*(r-l)+l);
	}
	swap(a[l],a[rand_x]);
	swap(a[r],a[rand_y]);
    if (a[l] > a[r]) 
        swap(a[l], a[r]); 
    int j = l + 1; 
    int g = r - 1, k = l + 1, p = a[l], q = a[r]; 
    while (k <= g) { 
        if (a[k] < p) { 
            swap(a[k], a[j]); 
            j++; 
        } 
        else if (a[k] >= q) { 
            while (a[g] > q && k < g) 
                g--; 
            swap(a[k], a[g]); 
            g--; 
            if (a[k] < p) { 
                swap(a[k], a[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    swap(a[l], a[j]); 
    swap(a[r], a[g]); 


    return make_pair(j, g); 
}
void RandomDualPivotQuickSort(int a[], int l, int r) 
{ 
    if (l < r) { 
        int lp, rp;  
        pair<int,int> p = DPQSPartition(a, l, r); 
        lp = p.first;
        rp = p.second;
        DualPivotQuickSort(a, l, lp - 1); 
        DualPivotQuickSort(a, lp + 1, rp - 1); 
        DualPivotQuickSort(a, rp + 1, r); 
    } 
} 


int main(){
	// configuration
	bool FLAG_QS = true;
	bool FLAG_RQS = true;
	bool FLAG_DPQS = true;
	bool FLAG_RDPQS = true;
	bool FLAG_stdQS = true;
	int times_per_data = 10; // get average running time of sorting time
	int data_num = 2000; // the number of experiments
	int stride = 10; // array size increasing number
	int data_len_array[5000]; // array to sort
	int data_repeat = 20; // numbers of test to get average running time for ecch array size

	clock_t start_time, end_time;
	srand(time(NULL));
	cout<<setiosflags(ios::fixed)<<setprecision(8);

	fstream fout("./result.txt", ios::in | ios::out);
	fout<<setiosflags(ios::fixed)<<setprecision(8);

	for (int i = 0; i < data_num; i++) {
		data_len_array[i] = (i + 1) * stride;
	}

	for (int i = 0; i < data_num; i++) {
		cout << "Experiment " << i << ": over data length " << data_len_array[i] << endl;
		clock_t QS_time_count = 0;
		clock_t RQS_time_count = 0;
		clock_t DPQS_time_count = 0;
		clock_t RDPQS_time_count = 0;
		clock_t std_QS_time_count = 0;
		for (int repeat = 0; repeat < data_repeat; repeat++) {
//			cout << "repeat " << repeat << endl;
			for (int j = 0; j < data_len_array[i]; j++) {
					arr[j] = rand()%MOD_NUM;
			}
			int tmp_arr[N];
			for (int j = 0; j < data_len_array[i]; j++) {
				tmp_arr[j] = arr[j];
			}

	//		for (int j = 0; j < data_len_array[i]; j++) {
	//			cout << arr[j] << " ";
	//		}
	//		cout << endl;

			// experiment		
			if (FLAG_QS) { // QuickSort
				for (int k = 0; k < times_per_data; k++) {
					start_time = clock();
					QuickSort(arr, 0, data_len_array[i]-1);
	//				for (int j = 0; j < data_len_array[i]; j++) {
	//					cout << arr[j] << " ";
	//				}
	//				cout << endl;
					end_time = clock();
					QS_time_count += end_time - start_time;
					for (int j = 0; j < data_len_array[i]; j++){
						arr[j] = tmp_arr[j];
					}
				}
			}

			if (FLAG_RQS) { // Radnom QuickSort
				for (int k = 0; k < times_per_data; k++) {
					start_time = clock();
					RandomQuickSort(arr, 0, data_len_array[i]-1);
	//				for (int j = 0; j < data_len_array[i]; j++) {
	//					cout << arr[j] << " ";
	//				}
	//				cout << endl;
					end_time = clock();
					RQS_time_count += end_time - start_time;
					for (int j = 0; j < data_len_array[i]; j++){
						arr[j] = tmp_arr[j];
					}
				}
			}

			if (FLAG_DPQS) { // Dual-Pivot QuickSort
				for (int k = 0; k < times_per_data; k++) {
					start_time = clock();
					DualPivotQuickSort(arr, 0, data_len_array[i]-1);
	//				for (int j = 0; j < data_len_array[i]; j++) {
	//					cout << arr[j] << " ";
	//				}
	//				cout << endl;
					end_time = clock();
					DPQS_time_count += end_time - start_time;
					for (int j = 0; j < data_len_array[i]; j++){
						arr[j] = tmp_arr[j];
					}
				}
			}

			if (FLAG_RDPQS) { // Random Dual-Pivot QuickSort
				for (int k = 0; k < times_per_data; k++) {
					start_time = clock();
					RandomDualPivotQuickSort(arr, 0, data_len_array[i]-1);
	//				for (int j = 0; j < data_len_array[i]; j++) {
	//					cout << arr[j] << " ";
	//				}
	//				cout << endl;
					end_time = clock();
					RDPQS_time_count += end_time - start_time;
					for (int j = 0; j < data_len_array[i]; j++){
						arr[j] = tmp_arr[j];
					}
				}

			}
			if (FLAG_stdQS) {
				for (int k = 0; k < times_per_data; k++) {
					start_time = clock();
					sort(arr, arr+data_len_array[i]);
					end_time = clock();
					std_QS_time_count += end_time - start_time;
					for (int j = 0; j < data_len_array[i]; j++){
						arr[j] = tmp_arr[j];
					}
				}
			}

		}
		cout << "QucikSort running time: " << (double)((double)(QS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << "s" << endl;
		fout << (double)((double)(QS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << " ";
		cout << "Random QucikSort running time: " << (double)((double)(RQS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << "s" << endl;
		fout << (double)((double)(RQS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << " ";
		cout << "Dual-Pivot QucikSort running time: " << (double)((double)(DPQS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << "s" << endl;
		fout << (double)((double)(DPQS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << " ";
		cout << "Random Dual-Pivot QucikSort running time: " << (double)((double)(RDPQS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << "s" << endl;
		fout << (double)((double)(RDPQS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << " ";
		cout << "std QucikSort running time: " << (double)((double)(std_QS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << "s" << endl;
		fout << (double)((double)(std_QS_time_count)/times_per_data/data_repeat)/CLOCKS_PER_SEC << " ";
		fout << endl;
	}	

	return 0;
}