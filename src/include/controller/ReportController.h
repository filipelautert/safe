#ifndef _REPORTCONTROLLER_H_
#define _REPORTCONTROLLER_H_

#include "../service/ReportService.h"
#include "../service/report/AbstractReport.h"
#include "../controller/DocumentController.h"
#include "../persistence/PersistenceTypeEnum.h"
#include <string>

using namespace std;

class ReportController
{
private:
  DocumentController *documentController;

public:
  ReportController(PersistenceType::types type);
  void findAll(vector<string> *keys, vector<string> *values, ReportType type, string fileName);
};

#endif