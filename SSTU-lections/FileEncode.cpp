#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

unsigned integerToBinary(unsigned k) {
    if (k == 0) return 0;
    if (k == 1) return 1;                       
    return (k % 2) + 10 * integerToBinary(k / 2);
}

string BinaryIntToString (int a) {
    ostringstream temp;
    temp << a;
    string res = temp.str();
    int zeros = 8-res.length();
   	for(int i = 0; i < zeros; i++) 
   		res = "0" + res;	
    return res;
}

vector<string> split(string stringToBeSplitted, string delimeter) {
	vector<string> splittedString;
	int startIndex = 0;
	int  endIndex = 0;
	while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
	{
 
		string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + delimeter.size();
 
	}
	if(startIndex < stringToBeSplitted.size())
	{
		string val = stringToBeSplitted.substr(startIndex);
		splittedString.push_back(val);
	}
	return splittedString;
}


bool hasEnding (string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


int main() {
		setlocale(LC_ALL, "rus");
	
		
		FILE* file = fopen("C:\\fileForEncode.txt","r");
		if(!file) {
			cerr << "File not found!";
			exit(1);
		}
		
		
		fseek(file , 0 , SEEK_END);                         
  		long size = ftell(file);                            
  		rewind(file); 
		
		
		char* buffer = new char[size];
		if(!buffer) {
			cerr << "Memory error!";
			exit(2);
		}
		
		
		fread(buffer, 1, size, file); 
		
		cout << "Secret word: " << buffer << "\n";
		
		
		string bitSeq = "";
		for(int i = 0; i < size; i++){
			bitSeq += BinaryIntToString(integerToBinary(buffer[i]));
		}
		
		cout << "Bit sequence: " << bitSeq << "\n";
		
		fclose(file);
		
		
		FILE* file2read = fopen("C:\\fileToPast.txt","r");
	
		if(!file2read) {
			cerr << "File2 not found!";
			exit(1);
		}
		
		char* str = new char[50];
		string res = "";
		
		
		while (fgets (str, 50, file2read) != NULL) {
			res+=str;
		}
		fclose(file2read);
		
		
		
		vector<string> splittedStrings = split(res, "\n");
		
		res = "";
		
		for(int i = 0; i < splittedStrings.size(); i++) {
			if(i < bitSeq.length())
			splittedStrings[i] += bitSeq[i] == '1' ? " " : "";
			res += splittedStrings[i] + "\n";
		}
		
		
		ofstream out("C:\\fileToPast.txt");
   		out << res;
    	
		
		out.close();	
		free(buffer);
		
		
		
		
		FILE* file2 = fopen("C:\\fileToPast.txt","r");
	
		if(!file2) {
			cerr << "File2 not found!";
			exit(1);
		}
		
		str = new char[50];
		res = "";
		
		
		while (fgets (str, 50, file2) != NULL) {
			res+=str;
		}

			
		fclose(file2);
	
	
		vector<string>Strings = split(res, "\n");
		
		
		cout << Strings.size() << endl;
		
		string bits = "";
		
	
		for(int i = 0; i < Strings.size(); i++) {
			bits += hasEnding(Strings[i], " ") ? "1" : "0";
		}
		
		
		int count = 0;
		int* chars = new int[bits.length()/8];
		
		cout << bits;
		
		file2 = fopen("C:\\fileToDecode.txt","w");
		
		for(int i = 0; count < bits.length()/8; i = i+8, count++) {
			int buf =  strtol(bits.substr(i,8).c_str(), NULL, 2);
			cout << buf << endl;
			putc(buf, file2);
		}
		
		
		fclose(file2);
			
	}
