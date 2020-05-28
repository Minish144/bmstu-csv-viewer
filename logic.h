#ifndef LOGIC_H
#define LOGIC_H

#define ERROR "ERROR"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QDebug>

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<string> readCSV(string filepath);

vector<string> splitString(string str, string sep);

void getStringMatrix(vector<string> array);

vector<vector<string>> getRegionMatrix(string region, int year);

vector<double> getMinMaxValueFromMatrix(int column);

double getMedianFromMatrix(int column);

string checkFilepath(string filepath);

#endif // LOGIC_H
