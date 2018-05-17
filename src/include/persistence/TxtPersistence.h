#ifndef _TXTPERSISTENCE_H_
#define _TXTPERSISTENCE_H_

#include "AbstractPersistence.h"

#include <bits/stdc++.h>
#include <string>

using namespace std;

template<class MODEL>
class TxtPersistence : public AbstractPersistence<MODEL> {

    protected:

    public:
    TxtPersistence(string name)  : AbstractPersistence<MODEL>(name) {
        //FIXME implement
        //initialize Txt persistence object
    }

    void create(MODEL* object) {
        //FIXME implement
    }
    MODEL *update(MODEL* object) {
        //FIXME implement
        return object;
    }
    void remove(int id) {
        //FIXME implement
    }
    MODEL *get(int key) {
        return new MODEL();
    }
    
    vector<MODEL*>* findAll() {
        return new vector<MODEL*>();
    }

    vector<MODEL*>* findByParams(vector<string> keys, vector<string> values) {
        return new vector<MODEL*>();
    }
};


#endif