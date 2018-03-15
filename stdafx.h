#pragma once
#include <QtWidgets>
#include <iostream>
#include <math.h>
#include <qmessagebox.h>
#include <qfileinfo.h>
#include <qpushbutton.h>
#include <fstream>
#include <qline.h>

#define ZERO_SIGN '0'
#define LEFT_HIGH 1
#define HFMLEFT '0'
#define HFMRIGHT '1'
#define FILESEPE '/'
#define Zero_Sign "###"

#define UnitSize 44
#define SepaWidth 18
#define HeightAngle M_PI/3.75

class OutOfBounds {};
class NoMemory {};

using namespace std;
