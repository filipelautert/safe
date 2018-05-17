#ifndef _REPORTSERVICE_H_
#define _REPORTSERVICE_H_

#include "../model/Document.h"
#include "report/AbstractReport.h"

class ReportService
{
private:
public:
  ReportService();
  void generateReport(vector<Document *> *reportData, ReportType type, string fileName);
};

#endif