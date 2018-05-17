#include "../include/model/BaseModel.h"
#include <ctime>
#include <string.h>
#include <iostream>

using namespace std;

BaseModel::BaseModel()
{
  // default constructor used by persistence
  this->updatedAt = NULL;
}

BaseModel::~BaseModel()
{
  cerr << "Base model with id " << this->id << " is being destructed." << endl;
  if (NULL != this->createdAt)
  {
    delete []this->createdAt;
  }
  if (NULL != this->updatedAt)
  {
    delete []this->updatedAt;
  }
}

int BaseModel::getId()
{
  return this->id;
}

char *BaseModel::now()
{
  time_t now = time(0);
  char *t = ctime(&now);
  t[strlen(t) - 1] = '\0'; // removes \n from the end
  char *ret = new char[strlen(t) + 1];
  strcpy(ret, t);
  return ret;
}

void BaseModel::setUpdatedAt()
{
  if (NULL != this->updatedAt)
  {
    delete (this->updatedAt);
  }
  this->updatedAt = now();
}
void BaseModel::setCreatedAt()
{
  this->createdAt = now();
}

char *BaseModel::getCreatedAt()
{
  return this->createdAt;
}

char *BaseModel::getUpdatedAt()
{
  return this->updatedAt;
}