
#include "../include/service/ReportService.h"
#include "../include/controller/ReportController.h"
#include "../include/controller/DocumentController.h"
#include "../include/view/Safe.h"
#include <string>

ReportController::ReportController(PersistenceType::types type)
{
  this->documentController = new DocumentController(type);
}

void ReportController::findAll(vector<string> *keys, vector<string> *values, ReportType type, string fileName)
{
  //TODO should filter by keys and values
  vector<Document *> *documents = this->documentController->findAll();
  ReportService rs;
  rs.generateReport(documents, type, fileName);
  delete documents;
}