#ifndef _SAFE_H_
#define _SAFE_H_

#include "../controller/KeyController.h"
#include "../controller/DocumentController.h"
#include "../controller/ReportController.h"
#include "../model/Key.h"
#include "../persistence/PersistenceTypeEnum.h"
#include <string>

using namespace std;

class Safe
{
private:
  KeyController *keyController;
  DocumentController *documentController;
  ReportController *reportController;
  PersistenceType::types persistenceType;
  static Safe *safe;

  int readIntValue();
  char *readFile(string title);
  char *readFileNameToSave(string title);
  Key *readKey(string title);
  Safe(PersistenceType::types type);

protected:


public:
  static Safe *getInstance(PersistenceType::types type);
  static Safe *getInstance();
  void listOptions();
  void listKeys();
  void addKey();
  void removeKey();
  void listDocument();
  void addDocument();
  void addSignedDocument();
  void updateDocument();
  void removeDocument();
  void getDocument();
  void validateDocumentSignature();
  void report();
  PersistenceType::types getPersistenceType();
};

#endif