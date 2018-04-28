#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int find(int n) {
	int buf;
	int* digits = new int[10];
	int counter = 0;
	for(int i = 2; n != 1; i++) {
		if (i >= 10) return -1;	
		buf = 1;
		while (!(n%i)) {
			buf*=i;
			if(buf >=10) {
				buf/=i;
				digits[counter++] = buf;
					buf = i;
			}
			n/=i;
		}	
		if(buf > 1) {
			digits[counter++] = buf;
		} 
		
	}
	int temp, i, j;
	for(i=0; i<(counter-1); i++)
		for(j=0; j<(counter-i-1); j++)
			if(digits[j]>digits[j+1]) {
				temp=digits[j];
				digits[j]=digits[j+1];
				digits[j+1]=temp;
			}	
	for(int i = 0; i < counter; i++) {
		cout << digits[i];
	}
	return 0;
}

int main() {
	int n;
	cin >> n;
	find(n);
}
