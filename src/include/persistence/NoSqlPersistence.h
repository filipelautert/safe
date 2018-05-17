#ifndef _NOSQLPERSISTENCE_H_
#define _NOSQLPERSISTENCE_H_

#include <bits/stdc++.h>
#include <string>
#include <db_cxx.h>

#include "AbstractPersistence.h"

using namespace std;

template <class MODEL>
class NoSqlPersistence : public AbstractPersistence<MODEL>
{

  private:
    DbEnv *env;
    Db *pdb;

  public:
    NoSqlPersistence(string name) : AbstractPersistence<MODEL>(name)
    {
        this->persistenceName = name;
        this->persistenceName.append(".db");
        env = new DbEnv(0);
        env->set_error_stream(&cerr);
        env->open("./db", DB_CREATE | DB_INIT_MPOOL, 0);
        pdb = new Db(env, 0);
        pdb->open(NULL, this->persistenceName.c_str(), NULL, DB_BTREE, DB_CREATE, 0); // | DB_TRUNCATE
    }

    void create(MODEL *object)
    {
        cerr << "Persisting model with id " << object->getId() << endl;
        char *representation = object->toCharArray();
        string my_key = std::to_string(object->getId());
        Dbt key(const_cast<char *>(my_key.data()), my_key.size() + 1);
        Dbt value(representation, strlen(representation) + 1 );
        pdb->put(NULL, &key, &value, 0);
    }

    MODEL *update(MODEL *object)
    {
        MODEL *exists = this->get(object->getId());
        if (NULL != exists)
        {
            this->create(object);
            return object;
        } else {
            throw std::invalid_argument("Object doesn't exist in database in order to be updated. Did you want to create it?");
        }
    }

    void remove(int id)
    {
        string my_key = std::to_string(id);
        Dbt key(const_cast<char *>(my_key.data()), my_key.size() + 1);
        if (pdb->del(NULL, &key, 0) == 0)
        {
            cerr << "db: " <<  std::to_string(id) << " key removed." << endl;
        }
        else
        {
            cout << "error removing object with key " << std::to_string(id) << endl;
        }
    }

    MODEL *get(int key)
    {
        string my_key = std::to_string(key);
        Dbt bdbKey(const_cast<char *>(my_key.data()), my_key.size() + 1);
        Dbt data;
        if (pdb->get(NULL, &bdbKey, &data, 0) == DB_NOTFOUND)
        {
            cerr << "Object with key " <<  (char *)bdbKey.get_data() << " not found." << endl;
            return NULL;
        }
        else
        {
            cerr << "[DEBUG] Model Found: " << (char *)bdbKey.get_data() << endl;
            MODEL *r = new MODEL();
            r->populateFromCharArray((char *)data.get_data());

            cerr << "[DEBUG] Loaded object with ID: " << r->getId() << endl;
            return r;
        }
    }

    vector<MODEL *> *findAll()
    {
        vector<MODEL *> *models = new vector<MODEL *>();
        Dbt data;
        Dbc *cursorp;
        pdb->cursor(NULL, &cursorp, 0);
        Dbt bdbKey;
        int ret;

        // Iterate over the database, retrieving each record in turn.
        while ((ret = cursorp->get(&bdbKey, &data, DB_NEXT)) == 0)
        {
            cerr << "[DEBUG] Model Found: " << (char *)bdbKey.get_data() << endl;
            MODEL *r = new MODEL();
            r->populateFromCharArray((char *)data.get_data());
            models->push_back(r);
        }
        return models;
    }

    vector<MODEL *>* findByParams(vector<string> keys, vector<string> values)
    {
        return  new vector<MODEL *>();
    }

    ~NoSqlPersistence()
    {
        cerr << "Ending BDB persistence... ";
        if (pdb != NULL)
        {
            pdb->close(0);
            delete pdb;
        }
        env->close(0);
        delete env;
        cerr << "done." << endl;
    }
};

#endif