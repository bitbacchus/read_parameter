#ifndef GETPARAMETER_H
#define GETPARAMETER_H

#include <QString>
#include <QFile>
#include <iostream>
#include <typeinfo>       // operator typeid
#include "csvParser/csv.h"



namespace getparameter {

// Open file and read parameter
int             readInt     (QString parameterName, QString fileName, int defaultVal = -1);
unsigned int    readUInt    (QString parameterName, QString fileName, unsigned int defaultVal = 0);
double          readDouble  (QString parameterName, QString fileName, double defaultVal = -1.0);
QString         readQString (QString parameterName, QString fileName, QString defaultVal = "NA");

// Get parameter from an already opened file
int             getInt      (QString parameterName, QFile &file, int defaultVal = -1);
unsigned int    getUInt     (QString parameterName, QFile &file, unsigned int defaultVal = 0);
double          getDouble   (QString parameterName, QFile &file, double defaultVal = -1.0);
QString         getQString  (QString parameterName, QFile &file, QString defaultVal = "NA");


// Possible delimiters between parameter name and value (comma, semi-colon, tab, one or more spaces)
static QString delimiters = "[,;\\t\\s+]";


// Little helper functions
template <typename T1, typename  T2>
bool isEqual(T1 val1, T2 val2, unsigned precision = 6)
{
    if (val1 == val2) {
        return true; // shortcut
    }

    // comparing QStrings to avoid floating point problems
    QString val1String = QString::number(val1, 'g', (int)precision);
    QString val2String = QString::number(val2, 'g', (int)precision);

    if (val1String == val2String) {
        return true;
    }

    return false;
}

template <typename T>
bool greaterThen(T i, T j)
{
    return (i > j);
}
template <typename T> unsigned indexOfLowestValue(std::vector<T> vector)
{
    auto tmp = vector;
    std::sort(tmp.begin(), tmp.end());
    for (unsigned i = 0; i < vector.size(); i++){
        if (vector[i] <= tmp[0]){
            return i;
        }
    }
    std::cerr << "Function indexOfLowestValue failed!";
    return 0;
}

template <typename T> unsigned indexOfHighestValue(std::vector<T> vector)
{
    auto tmp = vector;
    std::sort(tmp.begin(), tmp.end(), greaterThen<T>);
    for (unsigned i = 0; i < vector.size(); i++){
        if (vector[i] >= tmp[0]){
            return i;
        }
    }
    std::cerr << "Function indexOfLowestValue failed!";
    return 0;
}
}

#endif // GETPARAMETER_H
