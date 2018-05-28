#include <iostream>
#include <malloc.h>
using namespace std;

void DFS(int num, int dim, int** matrix, int* isProceed) {
	isProceed[num] = 1;
	cout << num << endl;
	for(int i = num + 1; i < dim; i++)
		if(matrix[num][i] && !isProceed[i])
			DFS(i, dim, matrix, isProceed);
}

int main() {
  int dim;
  cin >> dim;
  
  int** matrix = (int**)malloc(dim*sizeof(int*));
  for(int i = 0; i < dim; i++) {
    matrix[i] = (int*)malloc(dim*sizeof(int));
    for(int j = 0; j < dim; j++) {
      matrix[i][j] = 0;
    }
  }
  
  int x,y;
  while(1) {
  	cin >> x;
  	if(x == -1) break;
  	cin >> y;
  	matrix[x][y] = 1;
  	matrix[y][x] = 1;
  }
  
  
  cout << endl << "Matrix: " << endl;
  for(int i = 0; i < dim; i++)  {
  	for(int j = 0; j < dim; j++) {
  		cout << matrix[i][j] << " ";
	}
	cout << endl;
  }
  
  int* isProceed = new int[dim];
  for(int i = 0; i < dim; i++)
  	isProceed[i] = 0;
  
  cout << endl << endl;	
  DFS(0, dim, matrix, isProceed);
}


