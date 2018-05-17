
#include "../../include/service/report/AbstractReport.h"
#include "../../include/service/report/XmlReport.h"
#include <sstream>
#include <algorithm>

using namespace std;

XmlReport::XmlReport(vector<Document *> *reportData) : AbstractReport(reportData)
{
}

XmlReport::~XmlReport() {}

void XmlReport::generateReport(string fileName)
{
    if (NULL == this->reportData || this->reportData->size() == 0)
    {
        return;
    }
    ofstream outputFile;
    outputFile.open(fileName.c_str());

    string headers = this->reportData->at(0)->reportHeaders();
    outputFile << "<documents>" << endl;

    for (Document *doc : *this->reportData)
    {
        outputFile << " <document>" << endl;
        stringstream headerTags(headers);

        string s = doc->reportData();
        replace(s.begin(), s.end(), '\n', ' ');
        stringstream content(s);

        string hl, cc;
        while (getline(headerTags, hl, '|') && getline(content, cc, '|'))
        {

            std::replace( hl.begin(), hl.end(), ' ', '_');
            outputFile << "       <" << hl << ">";
            outputFile << cc;
            outputFile << "</" << hl << ">" << endl;
        }

        outputFile << " </document>" << endl;
    }

    outputFile << "</documents>" << endl;

    outputFile.close();
}
