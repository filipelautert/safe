#include "../include/service/ReportService.h"
#include "../include/service/report/AbstractReport.h"
#include "../include/service/report/CsvReport.h"
#include "../include/service/report/TxtReport.h"
#include "../include/service/report/XmlReport.h"

ReportService::ReportService() {}
void ReportService::generateReport(vector<Document *> *reportData, ReportType type, string fileName)
{
    AbstractReport *report;
    switch (type)
    {
    case CSV:
        report = new CsvReport(reportData);
        break;
    case TXT:
        report = new TxtReport(reportData);
        break;
    case XML:
        report = new XmlReport(reportData);
        break;
    default:
        throw std::invalid_argument("Format not yet supported");
        break;
    }
    report->generateReport(fileName);
}