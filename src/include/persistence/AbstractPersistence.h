#ifndef _ABSTRACTPERSISTENCE_H_
#define _ABSTRACTPERSISTENCE_H_

#include <bits/stdc++.h>
#include <string>

using namespace std;

template<class MODEL>
class AbstractPersistence {

    protected:
    string persistenceName;

    public:
    AbstractPersistence(string name);
    virtual void create(MODEL* object) = 0;
    virtual MODEL* update(MODEL* object) = 0;
    virtual void remove(int id) = 0;
    virtual MODEL* get(int key) = 0;
    virtual vector<MODEL*>* findAll() = 0;
    virtual vector<MODEL*>* findByParams(vector<string> keys, vector<string> values) = 0;
};

template<class MODEL>
AbstractPersistence<MODEL>::AbstractPersistence(string name) {
    this->persistenceName = name;
}

#endif