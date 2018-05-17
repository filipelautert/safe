#include "../include/controller/KeyController.h"
#include <string>

using namespace std;

KeyController::KeyController(PersistenceType::types type) {
  this->keyDao = new KeyDao(type);
}

void KeyController::create(Key* key) {
  this->keyDao->create(key);
}

void KeyController::remove(int id){
  this->keyDao->remove(id);
}

Key* KeyController::get(int id) {
  return this->keyDao->get(id);
}

vector<Key*>* KeyController::findAll() {
  return this->keyDao->findAll();
}