#include "../include/model/Document.h"
#include "../include/dao/KeyDao.h"
#include "../include/view/Safe.h"
#include <string.h>
#include <sstream>
#include <iostream>

Document::Document() : BaseModel(){};

Document::Document(int id, string hash, char *file, char *signature, Key *key)
{
  this->id = id;
  this->hash = hash;
  this->setFile(file, signature, key);
  this->setCreatedAt();
}

Document::~Document()
{
  cerr << "Document with id " << this->id << " is being destructed." << endl;
  if (NULL != this->file)
  {
    delete[] this->file;
  }
  if (NULL != this->signature)
  {
    delete[] this->signature;
  }
  if (NULL != this->key)
  {
    delete this->key;
  }
}

void Document::populateFromCharArray(const char *r)
{
  stringstream ss;
  ss << r;
  string id;
  getline(ss, id, '|');
  this->id = std::stoi(id);
  getline(ss, hash, '|');
  string file;
  getline(ss, file, '|');
  this->file = new char[file.size() + 1];
  strcpy(this->file, file.c_str());
  string signature;
  getline(ss, signature, '|');
  this->signature = new char[signature.size() + 1];
  strcpy(this->signature, signature.c_str());
  string ca;
  getline(ss, ca, '|');
  this->createdAt = new char[ca.size() + 1];
  strcpy(this->createdAt, ca.c_str());
  string ua;
  getline(ss, ua, '|');
  this->updatedAt = new char[ua.size() + 1];
  strcpy(this->updatedAt, ua.c_str());
  string keyIdS;
  getline(ss, keyIdS, '|');
  int keyId = std::stoi(keyIdS);
  if (keyId != 0)
  {
    KeyDao *keyDao = new KeyDao(Safe::getInstance()->getPersistenceType());
    this->key = keyDao->get(keyId);
    delete keyDao;
  }
  else
  {
    this->key = NULL;
  }
}

char *Document::toCharArray()
{
  std::stringstream ret;
  ret << this->id << '|'
      << hash << '|'
      << file << '|'
      << signature << '|'
      << this->createdAt << '|'
      << this->updatedAt << '|'
      << (NULL != this->key ? this->key->getId() : 0) << '|'; // only key id is serialized for reference
  string str = ret.str();
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());

  cerr << "Doc as string: " << cstr << endl;
  return cstr;
}

void Document::setFile(char *newFile, char *newSignature, Key *key)
{
  this->file = new char[strlen(newFile) + 1];
  strcpy(this->file, newFile);
  this->signature = new char[strlen(newSignature) + 1];
  strcpy(this->signature, newSignature);
  this->key = key;
  this->setUpdatedAt();
}

string Document::getHash()
{
  return this->hash;
}

char *Document::getFile()
{
  char *ret = new char[strlen(this->file) + 1];
  strcpy(ret, this->file);
  return ret;
}

char *Document::getSignature()
{
  char *ret = new char[strlen(this->signature) + 1];
  strcpy(ret, this->signature);
  return ret;
}

float Document::getSize()
{
  return this->size;
}

Key *Document::getKey()
{
  return this->key;
}

string Document::reportHeaders() {
  return "ID|HASH|SIGNATURE|CREATED AT|UPDATED AT|KEY ID";
}

string Document::reportData()
{
  std::stringstream ret;
  ret << this->id << '|'
      << hash << '|'
      << signature << '|'
      << this->createdAt << '|'
      << this->updatedAt << '|'
      << (NULL != this->key ? this->key->getId() : 0);

  return ret.str();
}
