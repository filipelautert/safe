#ifndef _DOCUMENTCONTROLLER_H_
#define _DOCUMENTCONTROLLER_H_

#include "../model/Document.h"
#include "../dao/DocumentDao.h"
#include "../service/SignatureService.h"
#include "../persistence/PersistenceTypeEnum.h"
#include <string>

using namespace std;

class DocumentController
{
private:
  DocumentDao* documentDao;
  SignatureService* signatureService;

public:
  DocumentController(PersistenceType::types type);
  void create(int id, char* file, char* signature, Key *key);
  void create(int id, char *file, Key *key);
  void create(Document* document);
  Document* update(Document* document, char* docContent, Key* key);
  void remove(int id);
  Document* get(int id);
  vector<Document*>* findAll();
  void validate(int id);
  string hash(const char* file);

};

#endif