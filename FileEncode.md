```cpp
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

//Функция для перевода в двоичную систему
unsigned integerToBinary(unsigned k) {
    if (k == 0) return 0;
    if (k == 1) return 1;                       
    return (k % 2) + 10 * integerToBinary(k / 2);
}

//Функция для создания строки из 8 битов
string BinaryIntToString (int a) {
    ostringstream temp;
    temp << a;
    string res = temp.str();
    int zeros = 8-res.length();
   	for(int i = 0; i < zeros; i++) 
   		res = "0" + res;	
    return res;
}


//Найденная в интернете функция split
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



int main() {
	setlocale(LC_ALL, "rus");
	
		//Открываем файл
		FILE* file = fopen("C:\\fileForEncode.txt","r");
		if(!file) {
			cerr << "File not found!";
			exit(1);
		}
		
		//Находим размер файла
		fseek(file , 0 , SEEK_END);                         
  		long size = ftell(file);                            
  		rewind(file); 
		
		//Выделяем память под содержимое файла
		char* buffer = new char[size];
		if(!buffer) {
			cerr << "Memory error!";
			exit(2);
		}
		
		//Читаем содержимое
		fread(buffer, 1, size, file); 
		
		cout << "Secret word: " << buffer << "\n";
		
		//Получаем битовую последовательность
		string bitSeq = "";
		for(int i = 0; i < size; i++){
			bitSeq += BinaryIntToString(integerToBinary(buffer[i]));
		}
		
		cout << "Bit sequence: " << bitSeq << "\n";
		
		fclose(file);
		
		//Открываем файл
		FILE* file2read = fopen("C:\\fileToPast.txt","r");
	
		if(!file2read) {
			cerr << "File2 not found!";
			exit(1);
		}
		
		char* str = new char[50];
		string res = "";
		
		//Считываем содержимое большого файла
		while (fgets (str, 50, file2read) != NULL) {
			res+=str;
		}
		fclose(file2read);
		
		
		//Разбиваем содержимое файла на строки
		vector<string> splittedStrings = split(res, "\n");
		
		res = "";
		//Дописываем пробелы в тех местах, где в битовой последовательности встречается единица
		for(int i = 0; i < splittedStrings.size(); i++) {
			if(i < bitSeq.length())
			splittedStrings[i] += bitSeq[i] == '1' ? " " : "";
			res += splittedStrings[i] + "\n";
		}
		
		//Открываем поток и пишем в файл
		ofstream out("C:\\fileToPast.txt");
   		out << res;
    	
		
		out.close();	
		free(buffer);	
	}
```
