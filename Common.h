//
//  xcept.h
//  3.1
//
//  Created by Eric on 07/11/2017.
//  Copyright © 2017 INGStudio. All rights reserved.
//
#pragma once
 
#include "Dictionary.hpp"

static short rest = 0;
static int treeHeight = 0;
static string file_dir = ".";
static string file_nam = "";
static string formalPost = "";
static string final_dir = "";
static Dictionary<char, string> dict;

///alert. most simple
void showErrorMessage(QString & msg) {
	QMessageBox::critical(0, "ALERT", msg, QMessageBox::Ok, 0);
}

///question with yes, no, cancel. select result returned as int 
int showQuestionMsg(QString & msg) {
	return QMessageBox::question(0, "CHOOSE", msg, QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
}

///info. most simple
void showInfoMessage(QString & msg) {
	QMessageBox::information(0, "INFO", msg, QMessageBox::Ok);
}

///reference to the str. postLength doesnt contain '.' //If file exsits, rename it by inserting (1),(2)...
void fileExists(string & str, int postLength) {
	int c = 1;
	while (true) {
		const char * strcstr = str.c_str();
		QFileInfo fileInfo(QString(str.c_str()));
		if (fileInfo.isFile()) {
			int len = str.length(), i = 0;
			if (c == 1) {
				char * arr = new char[len + 4];
				strncpy(arr, strcstr, len - postLength - 1); arr[len - postLength - 1] = '\0';
				//int b = 3, d = c; while (d /= 10) { b++; }
				//char * temp = new char[b]; 
				char temp[3];
				sprintf(temp, "(%d)", c);
				strcat(arr, temp);
				strcat(arr, str.substr(len - postLength - 1).c_str());
				arr[len + 3] = '\0';
				str = string(arr);
				delete[] arr;
				
			} else {
				char temp[1]; sprintf(temp, "%d", c);
				str.replace(len - 6, 1, temp);
			}
			c++;
		} else {
			break;
		}
	}
}

///str append a char. I think it's more efficient
void append(string & str, char c) {
    long l = str.length();
    const char *s = str.c_str();
    char * chs = new char[l+2];
    for (long i = 0; i < l; i++) {
        chs[i] = s[i];
    }
    chs[l] = c;
	chs[l + 1] = '\0';
    str = string(chs);
    delete [] chs;
}

///str1 append str2
void append(string & str1, const string & str2) {
    long l1 = str1.length(), l2 = str2.length();
    long l = l1+l2, i = 0;
    char * str = new char[l+1];
    const char * str11 = str1.c_str();
    const char * str22 = str2.c_str();
    for (; i < l1; i++) {
        str[i] = str11[i];
    }
    for (long j = 0; j < l2; j++, i++) {
        str[i] = str22[j];
    }
	str[l] = '\0';
    str1 = string(str);
    delete [] str;
}

///适用于树的button,x, y为正常xy
QPushButton * getRegularButton(QWidget * parent, int xx, int yy, string & key) {
	QPushButton * but = new QPushButton(parent);
	but->setGeometry(xx, yy, UnitSize, UnitSize);
	//but->setStyle();
	but->setFont(QFont("Times", 26, QFont::Bold));
	 
	const char * title = key.c_str();
	if (strcmp(title, Zero_Sign) == 0) {
		but->setText(" ");
		but->setEnabled(0);
	}
	else
		but->setText(QString(title));
	return but;
}

///reset static members
void resetProj() {
	rest = 0;
	treeHeight = 0;
	dict.reset(0);
	formalPost = "";
	file_dir = ".";
	file_nam = "";
	final_dir = "";
}

 