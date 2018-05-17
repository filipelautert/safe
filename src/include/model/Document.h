#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include "Key.h"
#include "BaseModel.h"
#include <string>

using namespace std;

class Document : public BaseModel
{
private:
  string hash;
  char *file, *signature;
  float size;
  Key *key;

public:
  Document();
  Document(int id, string hash, char *file, char *signature, Key *key);
  ~Document();
  string getHash();
  char *getFile();
  char *getSignature();
  float getSize();
  Key *getKey();
  void setFile(char *newFile, char *newSignature, Key *key);

  void populateFromCharArray(const char *r);
  char *toCharArray();

  string reportHeaders();
  string reportData();
};

#endif