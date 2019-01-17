#include "getparameter.h"
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QRegularExpression>
#include <sstream>
#include <iostream>


template <typename T> T readParameter(QString parameterName, QString fileName, T defaultVal = -1.0)
{
    T parameterVal = defaultVal;
    bool success = false; // not successful, yet

    // Open file
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "could not open " << fileName.toStdString() <<
                     ", using default value " <<
                     parameterName.toStdString()<< ": " << defaultVal;
        return parameterVal;
    }

    // Read line-by-line
    QTextStream stream(&file);
    QString line;

    while (stream.readLineInto(&line)) {
        QStringList lineSegments = line.split(QRegularExpression(getparameter::delimiters), QString::SkipEmptyParts);
        if (lineSegments.size() > 1)
            if (lineSegments[0] == parameterName) {
                QString parameterValStr = lineSegments[1];
                std::string str = parameterValStr.toStdString();
                std::istringstream stringStream(str);
                stringStream >> parameterVal;
                success = true;
                if (stringStream.fail())
                {
                    std::clog << "Could not read " << parameterName.toStdString()
                              << " in " << fileName.toStdString()
                              << ", using default value "
                              << parameterName.toStdString() << defaultVal;
                    parameterVal = defaultVal;
                    success = false;
                }
                break;
            }
    }

    // If EOF && first line segment != parameterName, parameterValue = defaultVal
    if (!success) {
        std::clog << "Could not read " << parameterName.toStdString()
                  << " in " << fileName.toStdString()
                  << ", using default value "
                  << parameterName.toStdString() << defaultVal;
        parameterVal = defaultVal;
    }

    file.close();
    return parameterVal;
}

template <typename T> T getParameter(QString parameterName, QFile &file, T defaultVal = -1.0)
{
    T parameterVal = defaultVal;
    bool success = false; // not successful, yet

    // Read line-by-line
    QTextStream stream(&file);
    QString line;

    while (stream.readLineInto(&line)) {
        QStringList lineSegments = line.split(QRegularExpression(getparameter::delimiters), QString::SkipEmptyParts);
        if (lineSegments.size() > 1)
            if (lineSegments[0] == parameterName) {
                QString parameterValStr = lineSegments[1];
                std::string str = parameterValStr.toStdString();
                std::istringstream stringStream(str);
                stringStream >> parameterVal;
                success = true;
                if (stringStream.fail())
                {
                    std::clog << "Could not read " << parameterName.toStdString()
                              << " in " << file.fileName().toStdString()
                              << ", using default value " << parameterName.toStdString()
                              << defaultVal;
                    parameterVal = defaultVal;
                    success = false;
                }
                break;
            }
    }

    // If EOF && first line segment != parameterName, parameterValue = defaultVal
    if (!success) {
        std::clog << "Could not read " << parameterName.toStdString()
                  << " in " << file.fileName().toStdString()
                  << ", using default value " << parameterName.toStdString()
                  << defaultVal;
        parameterVal = defaultVal;
    }

    return parameterVal;
}

int getparameter::readInt(QString parameterName, QString fileName, int defaultVal)
{
    return readParameter(parameterName, fileName, defaultVal);
}

double getparameter::readDouble(QString parameterName, QString fileName, double defaultVal)
{
    return readParameter(parameterName, fileName, defaultVal);
}

unsigned int getparameter::readUInt(QString parameterName, QString fileName, unsigned int defaultVal)
{
    return readParameter(parameterName, fileName, defaultVal);
}


int getparameter::getInt(QString parameterName, QFile &file, int defaultVal)
{
    return getParameter(parameterName, file, defaultVal);
}

unsigned int getparameter::getUInt(QString parameterName, QFile &file, unsigned int defaultVal)
{
    return getParameter(parameterName, file, defaultVal);
}

double getparameter::getDouble(QString parameterName, QFile &file, double defaultVal)
{
    return getParameter(parameterName, file, defaultVal);
}


QString getparameter::readQString(QString parameterName, QString fileName, QString defaultVal)
{
    QString parameterVal = defaultVal;

    // Open file
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::clog << "could not open " << fileName.toStdString() << ", using default value "
                  << parameterName.toStdString() << defaultVal.toStdString();
        return parameterVal;
    }

    // Read line-by-line
    QTextStream stream(&file);
    QString line;

    while (stream.readLineInto(&line)) {
        QStringList lineSegments = line.split(QRegularExpression(getparameter::delimiters), QString::SkipEmptyParts);
        if (lineSegments.size() > 1)
            if (lineSegments[0] == parameterName) {
                parameterVal = lineSegments[1];
                break;
            }
    }
    return parameterVal;
}

QString getparameter::getQString(QString parameterName, QFile &file, QString defaultVal)
{
    QString parameterVal = defaultVal;

    // Read line-by-line
    QTextStream stream(&file);
    QString line;

    while (stream.readLineInto(&line)) {
        QStringList lineSegments = line.split(QRegularExpression(getparameter::delimiters), QString::SkipEmptyParts);
        if (lineSegments.size() > 1)
            if (lineSegments[0] == parameterName) {
                parameterVal = lineSegments[1];
                break;
            }
    }
    return parameterVal;
}
