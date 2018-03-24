#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

char* arrOp = (char*) malloc(200);
double* arrNum = (double*) malloc(200*sizeof(double));

int opLen = 0;
int numLen = 0;

void pushNum(double n) {
	arrNum[numLen++] = n;
}

void pushOp(char c) {
	arrOp[opLen++] = c;
}

char popOp() {
	return arrOp[--opLen];
}

double popNum() {
	return arrNum[--numLen];
}

char peekOp() {
	return arrOp[opLen-1];
}

double peekNum() {
	return arrNum[numLen-1];
}
int isEmptyOp() {
	return opLen == 0;
}

int isSingleNum() {
	return numLen == 1;
}

double calc(double n1, double n2, char sign) {
	double res = 0.0;
	switch(sign) {
		case '+':
			res = n1+n2;
			break;
		case '-':
			res = n1-n2;
			break;
		case '*':
			res = n1*n2;
			break;
		case '/':
			res = n1/n2;
			break;
	}
	return res;
}



char** parse (char* str) {
	
	int length;
	for(length = 0; str[length] != '\0'; length++);
	
	char** res = (char**)malloc(length*sizeof(char*));
	char* buf = (char*)malloc(10*sizeof(char));
	
	int i, len = 0, count = 0;
	for(i = 0; str[i] != '\0'; i++) {
		switch(str[i]) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '.':
				buf[len++] = str[i];
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
				buf[len] = '\0';
				res[count] = (char*)malloc(len);
				strcpy(res[count++], buf);  
				len = 0;
								
				res[count] = (char*)malloc(1); 
				res[count][0] = str[i];  
				res[count++][1] = '\0'; 
				break; 
		}
	}
	
	buf[len] = '\0';  
	res[count] = (char*)malloc(len);
	strcpy(res[count++], buf);  
	res[count] = (char*)malloc(1);  
	res[count] = "end";
			
	return res;
	
}

double compute(char** res) {
	char op;
	double n1,n2,n;
    for(int i = 0; res[i]!="end"; i++) {
    	switch(res[i][0]) {
	    	case '1':
	    	case '2':
	    	case '3':
	    	case '4':
	    	case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				pushNum(atof(res[i]));	
		    	printf("Operand: %lf\n", atof(res[i])); 
				break;
			case '/':
			case '*':
			case '(':
				pushOp(res[i][0]);
				printf("Operation: %c\n",res[i][0]);
				break;
			case '+':
			case '-':
				printf("Operation: %c\n",res[i][0]);
				op = popOp();
				printf("%c",op);
				while(!isEmptyOp() && (op=='+' ||  op=='/' || op=='*' || op=='-') && op!='(' &&  op!=')') {
					n2 = popNum();
					n1 = popNum();
					n = calc(n1,n2,op);
					pushNum(n);
					op = popOp();
					printf("Calc: %lf\n", n);
				}
				if(op == '(' || op == ')') pushOp(op);
				pushOp(res[i][0]);
				
				break;
			case ')':
				printf("Operation: %c\n",res[i][0]);
				op = popOp();
				while(!isEmptyOp() && op!='(') {
					n2 = popNum();
					n1 = popNum();
					n = calc(n1,n2,op);
					pushNum(n);
					op = popOp();
					printf("Calc: %lf\n", n);
				}
				break;
		}
		 
			/*n2 = popNum();
			n1 = popNum();
			op = popOp();
			n = calc(n1,n2,op);
			pushNum(n);*/
		
  	
	}
	 return popNum();	
}

int main() {
	
	char* str = "25*80+(124/2)-1";
	char** res = parse(str);
	for(int i = 0; res[i] != "end"; i++) 
		printf("%s\n", res[i]);
		
	double acc = compute(res);
	printf("\nThe result of the expression: %lf\n", acc);
			
}
