#include "../include/model/Key.h"
#include <string.h>
#include <sstream>
#include <iostream>

Key::Key() : BaseModel(){};

Key::Key(int id, string type, char *key)
{
    this->id = id;
    this->type = type;
    if (NULL == key)
    {
        throw std::invalid_argument("Key cannot be null.");
    }
    this->key = new char[strlen(key) + 1];
    strcpy(this->key, key);
    this->setCreatedAt();
    this->setUpdatedAt();
}

Key::~Key()
{
    cerr << "Key with id " << this->id << " is being destructed." << endl;
    if (NULL != this->key)
    {
        delete []this->key;
    }
}

void Key::populateFromCharArray(const char *r)
{
    stringstream ss;
    ss << r;
    string id;
    getline(ss, id, '|');
    this->id = std::stoi(id);
    getline(ss, type, '|');
    string key;
    getline(ss, key, '|');
    this->key = new char[key.size() + 1];
    strcpy(this->key, key.c_str());
    string ca;
    getline(ss, ca, '|');
    this->createdAt = new char[ca.size() + 1];
    strcpy(this->createdAt, ca.c_str());
    string ua;
    getline(ss, ua, '|');
    this->updatedAt = new char[ua.size() + 1];
    strcpy(this->updatedAt, ua.c_str());
}

char *Key::toCharArray()
{
    std::stringstream ret;
    ret << this->id << '|'
        << type << '|'
        << key << '|'
        << this->createdAt << '|'
        << this->updatedAt << '|';
    string str = ret.str();
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());

    return cstr;
}

string Key::getType()
{
    return this->type;
}

char *Key::getKey()
{
    char *ret = new char[strlen(this->key) + 1];
    strcpy(ret, this->key);
    return ret;
}

void Key::setKey(char *newKey)
{
    if (NULL != this->key)
    {
        delete (this->key);
    }
    this->key = new char[strlen(key) + 1];
    strcpy(this->key, key);
    this->setUpdatedAt();
}