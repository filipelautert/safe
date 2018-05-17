#ifndef _KEYCONTROLLER_H_
#define _KEYCONTROLLER_H_

#include "../model/Key.h"
#include "../dao/KeyDao.h"
#include "../persistence/PersistenceTypeEnum.h"
#include <string>

using namespace std;

class KeyController
{
private:
  KeyDao* keyDao;

public:
  KeyController(PersistenceType::types type);
  void create(Key* key);
  void remove(int id);
  Key* get(int id);
  vector<Key*>* findAll();

};

#endif