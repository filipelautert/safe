#ifndef _KEYDAO_H_
#define _KEYDAO_H_

#include "../model/Key.h"
#include "../persistence/NoSqlPersistence.h"
#include "../persistence/TxtPersistence.h"
#include "../persistence/PersistenceTypeEnum.h"
#include <string>

using namespace std;

class KeyDao
{
private:
  AbstractPersistence<Key>* entityManager;

public:
  KeyDao(PersistenceType::types type);
  void create(Key* key);
  void remove(int id);
  Key* get(int id);
  vector<Key*>* findAll();

};

#endif