#pragma once
#include "Common.h"

//每一个函数都对应encode里的那个
void readByte(char & ch, string & str) {

	char c[8];
	for (int i = 7; i >= 0; i--) {
		if (ch % 2) c[i] = '1';
		else c[i] = '0';
		ch >>= 1;
	}
	int len = int(str.length());
	char *temp = new char[len + 9];
	const char * t = str.c_str();
	for (int i = 0; i < len; i++)
		temp[i] = t[i];
	for (int i = 0; i < 8; i++)
		temp[i + len] = c[i];
	temp[len + 8] = '\0';
	str = string(temp);
	delete[] temp;
}

string readBinaryFrom(const string & path, long & length) {
	if (path.empty())
		return string();
	ifstream input(path, ios::binary | ios::in);
	if (!input.is_open()) {
		showErrorMessage(QString("5"));
		return string();
	}
	length = 0;
	char c[1]; string str;
	while (input.read(c, 1)) {
		readByte(c[0], str);
		length += 8;
	}
	length -= rest;
	return str;
}

void decode(const string & filePath) {
	long length = -1;
	string result = readBinaryFrom(filePath, length);
	if (length == -1) return;
	if (!length || result.empty()) {
		showErrorMessage(QString("读取结果为空6"));
		return;
	}

	Dictionary<string, char> reversedDict;

	dict.reverseTo(reversedDict);
	string text, temp;	char c;

	const char * arr = result.c_str();
	for (long i = 0; i < length; i++) {
		char aa = arr[i];
		append(temp, aa);

		if (reversedDict.objectForKey(temp, c)) {
			append(text, c);
			temp.clear();
		}
	}
	///NOW WE GOT THE FINAL STRING!!!:text
	
	string path0;
	append(path0, file_dir);
	append(path0, file_nam);
	append(path0, formalPost);
	fileExists(path0, formalPost.length()-1);
 
	ofstream f_out(path0);
	f_out << text;
	f_out.close();

}
