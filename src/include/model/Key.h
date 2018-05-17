#ifndef _KEY_H_
#define _KEY_H_
#include <string>

#include "BaseModel.h"
using namespace std;

class Key:public BaseModel {
  private:
    string type;
    char* key;

  public:
    Key();
    Key(int id, string type, char* key);
    ~Key();
    string getType();
    char* getKey();
    void setKey(char* newKey);
    void populateFromCharArray(const char *r);
    char *toCharArray();

};

#endif