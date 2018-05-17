#include "../include/dao/KeyDao.h"
#include <string>

using namespace std;

KeyDao::KeyDao(PersistenceType::types type)
{
  switch (type)
  {
  case PersistenceType::types::TXT:
    this->entityManager = new TxtPersistence<Key>("Key");
    break;
  case PersistenceType::types::XML:
  //TODO implement
    throw std::invalid_argument("Not implemented yet.");
    break;

  case PersistenceType::types::NoSQL:
  default:
    this->entityManager = new NoSqlPersistence<Key>("Key");
  }
}

void KeyDao::create(Key *key)
{
  this->entityManager->create(key);
}

void KeyDao::remove(int id)
{
  this->entityManager->remove(id);
}

Key *KeyDao::get(int id)
{
  return this->entityManager->get(id);
}

vector<Key *> *KeyDao::findAll()
{
  return this->entityManager->findAll();
}