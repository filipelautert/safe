#include "../include/view/Safe.h"
#include "../include/model/Document.h"
#include "../include/model/Key.h"

#include <iostream>

using namespace std;

Safe *Safe::safe = NULL;

Safe::Safe(PersistenceType::types type)
{
    persistenceType = type;
    this->keyController = new KeyController(type);
    this->documentController = new DocumentController(type);
    this->reportController = new ReportController(type);
}

Safe *Safe::getInstance(PersistenceType::types type)
{
    if (NULL != safe)
    {
        if (safe->persistenceType != type)
        {
            throw std::domain_error("Invalid state - there is another instance of safe instantiated using a different Persistence Type.");
        }
        else
        {
            return safe;
        }
    }
    safe = new Safe(type);
    return safe;
}

Safe *Safe::getInstance()
{
    if (NULL != safe)
    {
        return safe;
    }
    else
    {
        throw std::domain_error("Invalid state - safe should be initialized using getInstance(type)");
    }
}

void Safe::listOptions()
{
    cout << "Options:" << endl;
    cout << " 1. List Keys" << endl;
    cout << " 2. Add a new key" << endl;
    cout << " 3. Remove a key" << endl;
    cout << " 4. List Documents" << endl;
    cout << " 5. Get a document" << endl;
    cout << " 6. Add and sign a document" << endl;
    cout << " 7. Add a signed document" << endl;
    cout << " 8. Remove a document" << endl;
    cout << " 9. Validate signature of a document" << endl;
    cout << "10. Update a document" << endl;
    cout << "20. Generate report" << endl;
    cout << "99. Exit" << endl;
    cout << ">>> Enter your option: ";

    int option = readIntValue();
    cout << endl;

    switch (option)
    {
    case 1:
        this->listKeys();
        break;

    case 2:
        this->addKey();
        break;

    case 3:
        this->removeKey();
        break;

    case 4:
        this->listDocument();
        break;
    case 5:
        this->getDocument();
        break;
    case 6:
        this->addDocument();
        break;
    case 7:
        this->addSignedDocument();
        break;
    case 8:
        this->removeDocument();
        break;
    case 9:
        this->validateDocumentSignature();
        break;
    case 10:
        this->updateDocument();
        break;
    case 20:
        this->report();
        break;
    case 99:
        exit(0);

    default:
        cout << "Unknow option " << option << ". Try again." << endl
             << endl;
    }

    this->listOptions();
}

void Safe::listKeys()
{
    vector<Key *> *keys = this->keyController->findAll();
    cout << " ---------------------------------------------------------------------------------------------" << endl;
    cout << "| ID   |   Type    |     Key        |       Created At           |         Updated At         |" << endl;
    cout << "|------+-----------+----------------+----------------------------+----------------------------|" << endl;
    for (Key *key : *keys)
    {
        printf("|%5d |  %.8s  | %.10s...  |  %s  |  %s  |\n",
               key->getId(), key->getType().c_str(), key->getKey(), key->getCreatedAt(), key->getUpdatedAt());
        delete key;
    }
    delete keys;

    cout << " ---------------------------------------------------------------------------------------------" << endl;
}

void Safe::addKey()
{
    //FIXME get next id, not ask for it
    cout << "Type the new Key id: ";
    int id = readIntValue();

    //FIXME read file from user
    char *keyContent = this->readFile("Choose your key");
    if (NULL == keyContent)
    {
        return;
    }
    Key *key = new Key(id, "PRIVATE", keyContent);
    try
    {
        this->keyController->create(key);
    }
    catch (std::exception &e)
    {
        cout << "Error adding key: " << e.what() << endl;
    }
    delete[] keyContent;
    delete key;
}

void Safe::removeKey()
{
    this->listKeys();
    cout << "Enter the id of the key to be removed: ";
    int id = readIntValue();
    this->keyController->remove(id);
}

void Safe::listDocument()
{
    vector<Document *> *documents = this->documentController->findAll();
    cout << " ----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "| ID   |                   Hash                    | Key Id  |       Created At           |         Updated At         |" << endl;
    cout << "|------+-------------------------------------------+---------+----------------------------+----------------------------|" << endl;
    for (Document *document : *documents)
    {
        printf("|%5d |  %.40s |  %.4d   |  %s  |  %s  |\n",
               document->getId(), document->getHash().c_str(), (NULL != document->getKey() ? document->getKey()->getId() : 0), document->getCreatedAt(), document->getUpdatedAt());
        delete document;
    }
    delete documents;

    cout << " ----------------------------------------------------------------------------------------------------------------------" << endl;
}

void Safe::addSignedDocument()
{
    //FIXME get next id, not ask for it
    cout << "Type the new document id: ";
    int id = readIntValue();

    char *docContent = this->readFile("Select your document");
    if (NULL == docContent)
    {
        return;
    }
    char *signature = this->readFile("Select the SHA1 signature file in BASE64 format");
    if (NULL == signature)
    {
        return;
    }

    Key *key = this->readKey("Type the key id or 0 so it's not associated to a key: ");

    try
    {
        this->documentController->create(id, docContent, signature, key);
    }
    catch (std::exception &e)
    {
        cout << "Error adding document: " << e.what() << endl;
    }
    delete[] docContent;
    delete[] signature;
    if (NULL != key)
    {
        delete key;
    }
}

void Safe::addDocument()
{
    //FIXME get next id, not ask for it
    cout << "Type the new document id: ";
    int id = readIntValue();

    char *docContent = this->readFile("Select your document");
    if (NULL == docContent)
    {
        return;
    }

    Key *key = this->readKey("Type the key id to be used to sign the document: ");

    if (NULL == key)
    {
        cout << "Invalid key..." << endl;
        return;
    }

    try
    {
        this->documentController->create(id, docContent, key);
    }
    catch (std::exception &e)
    {
        cout << "Error adding document: " << e.what() << endl;
    }
    delete[] docContent;
    if (NULL != key)
    {
        delete key;
    }
}
void Safe::updateDocument()
{
    cout << "Enter the id of the document to update: ";
    int id = readIntValue();
    Document *document = this->documentController->get(id);

    if (NULL == document)
    {
        cout << "There is no document with this id." << endl;
        return;
    }

    char *docContent = this->readFile("Select your new document");
    if (NULL == docContent)
    {
        return;
    }

    Key *key = this->readKey("Type the key id to be used to sign the document: ");

    if (NULL == key)
    {
        cout << "There is no key with this id." << endl;
        return;
    }

    try
    {
        this->documentController->update(document, docContent, key);
    }
    catch (std::exception &e)
    {
        cout << "Error adding document: " << e.what() << endl;
    }
    delete[] docContent;
    delete document;
}

void Safe::removeDocument()
{
    cout << "Enter the id of the document to be removed: ";
    int id = readIntValue();
    this->documentController->remove(id);
}
void Safe::getDocument()
{
    cout << "Enter the id of the document to retrieve: ";
    int id = readIntValue();
    Document *doc = this->documentController->get(id);

    if (NULL == doc)
    {
        cout << "Invalid id..." << endl;
        return;
    }

    char *fileName = this->readFileNameToSave("In the dialog, select the place to save it. ");
    ofstream stream;
    stream.open(fileName, ios::out | ios::binary);
    if (!stream)
        cout << "Opening file failed" << endl;
    char *file = doc->getFile();
    stream.write(file, strlen(file));

    if (!stream)
        cout << "Write failed" << endl;

    stream.close();
    cerr << "[DEBUG] Wrote " << strlen(file) << " bytes to " << fileName << endl;
    delete file;
    delete doc;
}

void Safe::validateDocumentSignature()
{
    cout << "Enter the id of the document to validate: ";
    int id = readIntValue();

    try
    {
        this->documentController->validate(id);
        cout << "The signature is ***VALID***" << endl;
    }
    catch (std::exception &e)
    {
        cout << e.what() << endl;
    }
}

int Safe::readIntValue()
{
    string value;
    int myNumber = 0;
    while (true)
    {
        getline(cin, value);
        stringstream myStream(value);
        if (myStream >> myNumber)
        {
            int number = strtof((value).c_str(), 0);
            if (number > 0)
            {
                return number;
            }
        }
        cout << "Invalid value, try again..." << endl;
    }
}

char *Safe::readFile(string title)
{
    char fileName[1024];
    FILE *f = popen(("zenity --file-selection  --filename=./ssl-key/key.pem --title=\"" + title + "\" 2>/dev/null").c_str(), "r");
    fgets(fileName, 1024, f);
    fclose(f);
    strtok(fileName, "\n");
    cerr << "Reading " << fileName << endl;
    ifstream file(fileName, ios::in | ios::binary | ios::ate);
    if (file.is_open())
    {
        streampos size = file.tellg();
        char *memblock = new char[((int)size) + 1];
        memblock[(int)size] = '\0';
        file.seekg(0, ios::beg);
        file.read(memblock, size);
        file.close();
        return memblock;
    }
    else
    {
        cout << "Unable to open file";
        return NULL;
    }
}

char *Safe::readFileNameToSave(string description)
{
    cout << description << endl;
    FILE *f = popen(("zenity --file-selection --save  --filename=/home/filipe/tmp/output.pdf --title=\"Save as...\" 2>/dev/null"), "r");
    char *fileName = new char[1024];
    fgets(fileName, 1024, f);
    strtok(fileName, "\n");
    cerr << "[DEBUG] Writing to " << fileName << endl;
    return fileName;
}

Key *Safe::readKey(string title)
{
    Key *key = NULL;
    while (NULL == key)
    {
        cout << title;
        int keyId = readIntValue();
        if (0 != keyId)
        {
            key = this->keyController->get(keyId);
            if (NULL == key)
            {
                cout << "Invalid key. Try again..." << endl;
            }
        }
        else
        {
            break;
        }
    }
    return key;
}

void Safe::report()
{
    cout << "Select the report format below: " << endl;
    cout << "1. CSV" << endl;
    cout << "2. TXT" << endl;
    cout << "3. XML" << endl;
    int i = this->readIntValue();

    char *fileName = this->readFileNameToSave("Select the export file name in the dialog.");

    switch (i)
    {
    case 1:
        this->reportController->findAll(NULL, NULL, CSV, string(fileName));
        cout << "CSV report generated" << endl << endl;
        break;
    case 2:
        this->reportController->findAll(NULL, NULL, TXT, string(fileName));
        cout << "TXT report generated" << endl << endl;
        break;
    case 3:
        this->reportController->findAll(NULL, NULL, XML, string(fileName));
        cout << "XML report generated" << endl << endl;
        break;
    default:
        cout << "Invalid option..." << endl << endl;
        break;
    }

    delete fileName;
}

PersistenceType::types Safe::getPersistenceType()
{
    return persistenceType;
}

int main(int argc, char **argv)
{
    cout << "Starting up..." << endl;

    Safe *safe;
    if (argc > 1)
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            cout << "You can switch the persistence type by using the parameters [TXT|NoSQL|XML]. Default is NoSQL" << endl;
            exit(0);
        }
        else if (strcmp(argv[1], "TXT") == 0)
        {
            safe = Safe::getInstance(PersistenceType::types::TXT);
        }
        else if (strcmp(argv[1], "XML") == 0)
        {
            safe = Safe::getInstance(PersistenceType::types::XML);
        }
        else if (strcmp(argv[1], "NoSQL") == 0)
        {
            safe = Safe::getInstance(PersistenceType::types::NoSQL);
        }
        else
        {
            cout << "Invalid option. Try --help for available options." << endl;
            exit(1);
        }
    }
    else
    {
        safe = Safe::getInstance(PersistenceType::types::NoSQL);
    }
    OpenSSL_add_all_algorithms();
    safe->listOptions();
    EVP_cleanup();
}
