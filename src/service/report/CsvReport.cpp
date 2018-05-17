
#include "../../include/service/report/AbstractReport.h"
#include "../../include/service/report/CsvReport.h"


using namespace std;

CsvReport::CsvReport(vector<Document *> *reportData) : AbstractReport(reportData)
{
}

CsvReport::~CsvReport() {}

void CsvReport::generateReport(string fileName)
{
    if (NULL == this->reportData || this->reportData->size() == 0)
    {
        return;
    }
    ofstream outputFile;
    outputFile.open(fileName.c_str());

    string headers = this->reportData->at(0)->reportHeaders();
    replace(headers.begin(), headers.end(), '|', ';');
    outputFile << headers << endl;

    for (Document *doc : *this->reportData)
    {
        string s = doc->reportData();
        replace(s.begin(), s.end(), '|', ';');
        replace(s.begin(), s.end(), '\n', ' ');
        outputFile << s << endl;
    }

    outputFile.close();
}