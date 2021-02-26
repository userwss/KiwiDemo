#pragma once

#define IMPLEMENT_KIWI_H
#define IMPLEMENT_SCHEMA_H

#include "testv1.h"
#include "kiwi.h"

#include <QDebug>
#include <QTime>
#include <QApplication>
#include <QXmlStreamReader>
#include <QFile>
#include <QColor>
//#include <fstream>
//#include <iostream>
using namespace std;

#define PRE_DEFINE_H

#include "PreDefineTest.h"

class Main {
public:
    int serialize();
    int deserialize();
    int xmlSave();
    int xmlParse();
};

struct Colors {
    uint8_t  m_color[4];

    void toString() {
        for (uint8_t color: m_color) {
            qDebug() << color;
        }
    }
};

class BasicInfo
{
public:
    qreal    m_clientID;
    uint     m_type;
    vector<Colors> m_clrs;
    QString  m_name;
};
