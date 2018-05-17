#include "../include/dao/DocumentDao.h"
#include <string>

using namespace std;

DocumentDao::DocumentDao(PersistenceType::types type)
{
  switch (type)
  {
  case PersistenceType::types::TXT:
    this->entityManager = new TxtPersistence<Document>("Document");
    break;
  case PersistenceType::types::XML:
    //TODO implement
    throw std::invalid_argument("Not implemented yet.");
    break;

  case PersistenceType::types::NoSQL:
  default:
    this->entityManager = new NoSqlPersistence<Document>("Document");
  }
}

void DocumentDao::create(Document *document)
{
  this->entityManager->create(document);
}

Document *DocumentDao::update(Document *document)
{
  return this->entityManager->update(document);
}

void DocumentDao::remove(int id)
{
  this->entityManager->remove(id);
}

Document *DocumentDao::get(int id)
{
  return this->entityManager->get(id);
}

vector<Document *> *DocumentDao::findAll()
{
  return this->entityManager->findAll();
}