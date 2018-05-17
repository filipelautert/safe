#ifndef _XMLREPORT_H_
#define _XMLREPORT_H_

#include "AbstractReport.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class XmlReport : public AbstractReport
{
  public:
    XmlReport(vector<Document *> *reportData);
    void generateReport(string fileName);
    ~XmlReport();
};

#endif