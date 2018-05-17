#ifndef _CSVREPORT_H_
#define _CSVREPORT_H_

#include "AbstractReport.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class CsvReport : public AbstractReport
{
  public:
    CsvReport(vector<Document *> *reportData);
    void generateReport(string fileName);
    ~CsvReport();
};

#endif