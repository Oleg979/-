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
	int* res = new int[n];
	res[0] = arr[0];
	int num = 1;
	int buf = num;
	
	while(num < n) {
		res[num] = arr[num];
		buf = num;
		while(res[buf] > res[(buf-1)/2] && (buf-1)/2 >= 0 && buf >= 0) {
			swap(res, buf, (buf-1)/2);
			buf = (buf-1)/2;
		}
		num++;
	}
	return res;
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
	if(arr[0] > arr[1]) swap(arr, 0, 1);
	return arr;
}

int main() {
	
	int arr[] = {10,5,6,2,-6,-3,0,1,4,2,3,-11,5,13};
	int n = sizeof(arr)/sizeof(arr[0]);
	
	int* pyramid = toPyramid(arr, n);
	int* sorted = toSorted(pyramid, n);
	
	for(int i = 0; i < n; i++)
		cout << sorted[i] << " " << endl;
}
