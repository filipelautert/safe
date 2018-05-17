#ifndef DOCUMENTDAO_H_
#define DOCUMENTDAO_H_

#include "../model/Document.h"
#include "../persistence/NoSqlPersistence.h"
#include "../persistence/TxtPersistence.h"
#include "../persistence/PersistenceTypeEnum.h"
#include <string>

using namespace std;

class DocumentDao
{
private:
  AbstractPersistence<Document>* entityManager;

public:
  DocumentDao(PersistenceType::types type);
  void create(Document* document);
  Document* update(Document* document);
  void remove(int id);
  Document* get(int id);
  vector<Document*>* findAll();

};

#endif