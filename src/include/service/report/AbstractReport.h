#ifndef _IREPORT_H_
#define _IREPORT_H_

#include "../../model/Document.h"
#include <vector>

using namespace std;

enum ReportType
{
    CSV,
    TXT,
    XML
};

class AbstractReport
{

  protected:
    vector<Document *> *reportData;

  public:
    AbstractReport(vector<Document *> *reportData)
    {
        this->reportData = reportData;
    }
    ~AbstractReport() {}

    virtual void generateReport(string fileName) = 0;
};

#endif