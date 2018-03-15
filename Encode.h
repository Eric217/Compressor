#pragma once
#include <fstream>
#include "HuffmanTree.hpp"

///从path路径里读取出内容返回到char数组，并把字符数写到length里。!!!请手动delete
char * readFileFrom(const string & path, long & length) {

	if (path.empty())
		return 0;
	ifstream input(path);

	if (!input.is_open()) {
		showErrorMessage(QString("Fail To Read"));
		return 0;
	}
	long size = 80;
	length = 0;
	char c, *arr = new char[size];
	while (input.get(c)) {
		if (length == size) {
			size *= 2;
			char * temp = new char[size];
			for (int i = 0; i < length; temp[i] = arr[i], i++);
			delete[] arr;
			arr = temp;
		}
		arr[length++] = c;
	}
	arr[length] = '\0';
	return arr;
}

///参数：完整路径，转成.hfm 过程中给几个全局变量赋值
string convertPath(const string & filePath) {

	const char * path = filePath.c_str();
	int len = strlen(path);
	while (len-- && path[len] != FILESEPE);
	if (len == -1) {
		showErrorMessage(QString("File Not Exsit (3)"));
		return string();
	}
	string name = filePath.substr(len + 1); //name: 文件全名

	char * dir = new char[len + 2];
	strncpy(dir, path, len + 1);
	dir[len + 1] = '\0';
	int len1 = (int)name.length(); len = len1;
	const char * pureName = name.c_str();
	while (len-- && pureName[len] != '.');
	formalPost = "";
	if (len != -1) {
		char * temp = new char[len + 1];
		strncpy(temp, pureName, len);
		formalPost = name.substr(len);
		temp[len] = '\0';
		name = string(temp);
		len1 = len;
		delete[] temp;
	}
	file_nam = name;
	//For Now: 无后缀的文件名 name, 无后缀长度 len1
	name.append(string(".hfm")); //拼接后缀后的文件名

	string strDir(dir); //所在文件夹
	file_dir = strDir;
	append(strDir, name); //最终路径

	delete[] dir;
	return strDir;
}

///写入8位char。str为8位01字符串（压缩的关键算法）
void writeByte(ofstream & f_out, string & str) {
	const char * arr = str.c_str();
	char c[1] = { 0 };
	if (arr[0] == HFMRIGHT)
		c[0] |= 128;
	if (arr[1] == HFMRIGHT)
		c[0] |= 64;
	if (arr[2] == HFMRIGHT)
		c[0] |= 32;
	if (arr[3] == HFMRIGHT)
		c[0] |= 16;
	if (arr[4] == HFMRIGHT)
		c[0] |= 8;
	if (arr[5] == HFMRIGHT)
		c[0] |= 4;
	if (arr[6] == HFMRIGHT)
		c[0] |= 2;
	if (arr[7] == HFMRIGHT)
		c[0] |= 1;

	f_out.write(c, 1);
}

///arr是文件内原字符串
short writeBinaryTo(string & path, char * arr, long & length) {

	ofstream f_out(path, ios::app | ios::binary | ios::out);
	if (!f_out.is_open()) {
		showErrorMessage(QString("No Right To Access (2)"));
		return 0;
	}

	string str, restStr;
	short rest = 0;
	for (long i = 0; i < length;) {
		if (rest >= 8) {
			writeByte(f_out, restStr);
			restStr = restStr.substr(8);
			rest -= 8;
		}
		else {
			dict.objectForKey(arr[i++], str);
			rest += str.length();
			append(restStr, str);
			if (rest >= 8) {
				writeByte(f_out, restStr);
				restStr = restStr.substr(8);
				rest -= 8;
			}
		}
	}
	if (rest > 0) { //补 8-rest个0
		for (int i = 0; i < 8 - rest; i++)
			append(restStr, HFMLEFT);
		writeByte(f_out, restStr);
	}
	f_out.close();
	if (rest)
		return 8 - rest;
	return 0;
}

///选择文件开始压缩！
bool encode(const string & filePath) {
	long length = -1;
	///raw data
	char * arr = readFileFrom(filePath, length);
	if (length == -1) 
		return 0;
	if (!length || !arr) {
		showErrorMessage(QString("Nothing Read (4)"));
		return 0;
	}
	char * charSet = new char[length];
	int * weights = new int[length], charSetSize = 0;
	bool add;
	for (long i = 0; i < length; i++) {
		add = 0; char c = arr[i];
		for (u_int j = 0; j < charSetSize; j++)
			if (charSet[j] == c) {
				weights[j]++;
				add = 1; break;
			}
		if (!add) {
			charSet[charSetSize] = c;
			weights[charSetSize++] = 1;
		}
	}
	charSet[charSetSize] = '\0';
	weights[charSetSize] = '\0';

	dict.reset(charSetSize);
	BinaryTree<char> tree = HuffmanTree(charSet, weights, charSetSize);
	tree.allPath();
	treeHeight = tree.height();

	//dict.output();

	string des = convertPath(filePath);
	if (des.empty()) {
		QString getDir1 = QFileDialog::getExistingDirectory(0, QString("Choose Directory"), QString(file_dir.c_str()), QFileDialog::Option::ShowDirsOnly);
		if (getDir1.isEmpty()) {
			resetProj(); tree.Delete(); delete[] charSet;
			delete[] weights; delete[] arr; return 0;
		}
		file_dir = getDir1.append("/").toStdString();
		des = getDir1.append(file_nam.c_str()).append(".hfm").toStdString();
	}
	else {
		string msg = "Save to default ";
		append(msg, des);
		int sqm = showQuestionMsg(QString(msg.c_str()));
		if (QMessageBox::No == sqm) {
			QString getDir1 = QFileDialog::getExistingDirectory(0, QString("Choose Directory"), QString(file_dir.c_str()), QFileDialog::Option::ShowDirsOnly);
			if (getDir1.isEmpty()) {
				resetProj(); tree.Delete(); delete[] charSet;
				delete[] weights; delete[] arr; return 0;
			}
			file_dir = getDir1.append("/").toStdString();
			des = getDir1.append(file_nam.c_str()).append(".hfm").toStdString();
		}
		else if (sqm == QMessageBox::Cancel) {
			resetProj(); tree.Delete(); delete[] charSet;
			delete[] weights; delete[] arr; return 0;
		}
	}

	fileExists(des, 3);
	final_dir = des;
	///write. Now des = ./././.hfm 
	rest = writeBinaryTo(des, arr, length);
	dict.localize(des);

	tree.Delete();
	delete[] charSet;
	delete[] weights;
	delete[] arr;
	return 1;
}