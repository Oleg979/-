#include <iostream>
using namespace std;

int* swap(int* arr, int x, int y) {
	int tmp;
	tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
	cout << "swap " << arr[x] << " " << arr[y] << endl;
	return arr;
}

int* toPyramid(int* arr, int n) {
	int len = --n;
	int num = n;
	while(num > 1) {
		cout << num << endl;
		if(arr[num] < arr[num/2]) {
			num = --len;
			continue;
		}
		while(arr[num] > arr[num/2] && num > 0 &&  num/2 > 0) {
			swap(arr, num, num/2);
			num = num/2;
		}
		num = len;
	}

	if(arr[n] < arr[n-1]) swap(arr, n, n-1);
	
	return arr;
}

int* toSorted(int* arr, int n) {
	int num;
	while(n > 1) {
		num = 0;
		swap(arr, num, n-1);
		n--;
		
		while(n > 2 && (arr[num] < arr[num+1] || arr[num] < arr[num+2])) {
			int buf = arr[num+1] > arr[num+2] ? num+1 : num+2;
			swap(arr, num, buf);
			if(buf + 1 < n && buf + 2 < n) num = buf;
		}	
	}
	
	return arr;
}

int main() {
	int arr[] = {-100,3,-1,2,5,4};
	int n = sizeof(arr)/sizeof(arr[0]);
	
//	int* pyramid = toPyramid(arr, n);
	//for(int i = 1; i < n; i++)
	//	cout << endl << pyramid[i] << " ";
	
	int pyramid[] = {5,4,2,-1,3};
	 n = sizeof(pyramid)/sizeof(pyramid[0]);
	 
	int* sorted = toSorted(pyramid, n);
	for(int i = 1; i < n; i++)
		cout << endl << sorted[i] << " ";
}
