#include <iostream>
#include <malloc.h>
using namespace std;


int** findMinor(int** matrix, int x, int y, int dim) {
	
	int** minor = (int**)malloc((dim-1) * sizeof(int*));
	for(int i = 0; i < dim; i++) 
		minor[i] = (int*)malloc((dim-1) *sizeof(int));

	int curX = 0, curY = 0;
	for(int i = 0; i < dim; i++) 	
		for(int j = 0; j < dim; j++)  
			if(i != x && j != y) {
				
				minor[curX][curY++] = matrix[i][j];
				if(curY == dim-1) {
					curX++;
					curY = 0;
				}
				
			}
			
	return minor;
}


int calc(int** matrix, int dim, int res = 0) {
	
	int** minor;
	int buf = 0;
	int minorVal = 0;
	
	for(int i = 0; i < dim; i++) {
		
		buf = matrix[0][i];
		buf *= (1+i) % 2 != 0 ? 1 : -1;
		cout << buf << " * ";
		
		minor = findMinor(matrix, 0, i, dim);
		
		if(dim - 1 == 2) 
			minorVal = minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0]; 
		else 
			minorVal = calc(minor, dim-1);
		
		free(minor);
		cout << minorVal << " + ";
		buf *= minorVal;
		res += buf;
	}
	
	return res;
}

int main() {
	
	cout << "Enter dimension: ";
	int dim;
	cin >> dim;
	
	int** matrix = (int**)malloc(dim*sizeof(int*));
	
	for(int i = 0; i < dim; i++) {
		matrix[i] = (int*)malloc(dim*sizeof(int));
			for(int j = 0; j < dim; j++) {
			cout << "Enter matrix[" << i << "][" << j <<"]: " << endl;
			cin >> matrix[i][j];
		}
	}
	
	cout << "Result: " << calc(matrix, dim);
	free(matrix);
}

