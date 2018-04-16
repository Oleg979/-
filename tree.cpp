#include <stdio.h>
#include <malloc.h>

typedef struct Node {
	int val;
	Node* left;
	Node* right;
} Node; 


int addInTree(Node* root, int n) {
	int c = root->val;
	Node* newNode;
	Node* where = n>=c ? root->right : root->left;
		if(where == NULL) {
			newNode = (Node*)calloc(sizeof(Node),1);
			if(newNode == NULL) return -1;
			newNode->val = n;
			where = newNode;
			return 0;	
		}
		return addInTree(where, n);	
}

void printTree(Node* root) {
	if(root == NULL) return;
	printTree(root->left);
	printf("%d ", root->val);
	printTree(root->right);
}

void freeTree(Node* root) {
	if(root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

int main() {
	Node* root = (Node*)calloc(sizeof(Node),1);
	int arr[] = {2,6,4,7,9};
	int size = (sizeof(arr)/sizeof(arr[0]))-1;
	root->val = arr[0];
	
	for(int i=1; i<size; i++) {
		if(addInTree(root,arr[i]))
			break;
	}
	
	printTree(root);
	freeTree(root);
}
