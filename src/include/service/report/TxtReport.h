#ifndef _TXTREPORT_H_
#define _TXTREPORT_H_

#include "AbstractReport.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class TxtReport : public AbstractReport
{
  public:
    TxtReport(vector<Document *> *reportData);
    void generateReport(string fileName);
    ~TxtReport();
};

#endif