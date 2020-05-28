#include "logic.h"

vector<vector<string>> matrix;
vector<vector<string>> regionMatrix;
int loadFlag = 0;

vector<string> readCSV(string filepath)
{
    ifstream file(filepath);
    string tmp;
    vector<string> sArray;
    int count = 0;
    for (int i = 0; getline(file, tmp); i++)
    {
        sArray.push_back(tmp);
        count++;
    }
    for (int i = 0; i  < count; i++)
    {
        qDebug() << QString::fromStdString(sArray[i]);
    }

    return sArray;
}

vector<string> splitString(string str, string sep)
{
    vector<string> arr;
    size_t prev = 0;
    size_t next;
    size_t delta = 1;
    while ((next = str.find(sep, prev)) != string::npos)
    {
        arr.push_back(str.substr(prev, next - prev));
        prev = next + delta;
    }
    arr.push_back(str.substr(prev));
    return arr;
}

void getStringMatrix(vector<string> array)
{
    vector<vector<string>> tempMatrix;
    vector<string> tempArray;
    for (int i = 0; i < array.size(); i++)
    {
        tempArray = splitString(array[i], ",");
        tempMatrix.push_back(tempArray);
    }
    matrix = tempMatrix;
}

vector<vector<string>> getRegionMatrix(string region, int year)
{
    vector<vector<string>> tempMatrix;
    if (!matrix.empty() && !region.empty())
    for (int i = 0; i < matrix.size()-1; i++)
    {
        if (matrix[i][1] == region && stod(matrix[i][0]) >= year)
            tempMatrix.push_back(matrix[i]);
    }
    regionMatrix = tempMatrix;
    loadFlag = 1;
    return tempMatrix;
}

vector<double> getMinMaxValueFromMatrix(int column)
{
    if (!regionMatrix.empty() && loadFlag==1)
    {
        vector<double> values = {0, 0};
        values[0], values[1] = stod(regionMatrix[0][column]);
        for (int i = 0; i < regionMatrix.size(); i++)
        {
            double value = stod(regionMatrix[i][column]);
            if (value > values[0])
                values[0] = value;
            else if (value < values[1])
                values[1] = value;
        }
        return values;
    }
}

double getMedianFromMatrix(int column)
{
    if (!regionMatrix.empty() && loadFlag==1)
    {
        vector<double> array;
        for (int i = 0; i < regionMatrix.size(); i++)
            array.push_back(stod(regionMatrix[i][column]));
        sort(array.begin(), array.end());
        return array[ round((regionMatrix.size()-1)/2) ];
    }
}

string checkFilepath(string filepath)
{
    if (!filepath.empty() && filepath.substr(filepath.length()-3, 3) == "csv")
        return filepath;
    else
        return ERROR;
}
