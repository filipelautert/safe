#include "../include/controller/DocumentController.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <string.h>
#include <string>

using namespace std;

DocumentController::DocumentController(PersistenceType::types type)
{
  this->documentDao = new DocumentDao(type);
  this->signatureService = new SignatureService();
}

void DocumentController::create(int id, char *file, char *signature, Key *key)
{
  Document *document = new Document(id, this->hash(file), file, signature, key);
  this->documentDao->create(document);
}

void DocumentController::create(int id, char *file, Key *key)
{
  char *signature = this->signatureService->sign(file, key);
  if (NULL == signature)
  {
    throw std::domain_error("Unable to sign the document.");
  }
  Document *document = new Document(id, this->hash(file), file, signature, key);
  this->documentDao->create(document);
}

void DocumentController::create(Document *document)
{
  this->documentDao->create(document);
}

Document *DocumentController::update(Document *document, char *docContent, Key *key)
{
  char *signature = this->signatureService->sign(docContent, key);
  if (NULL == signature)
  {
    throw std::domain_error("Unable to sign the document.");
  }

  document->setFile(docContent, signature, key);
  return this->documentDao->update(document);
}

void DocumentController::remove(int id)
{
  this->documentDao->remove(id);
}

Document *DocumentController::get(int id)
{
  return this->documentDao->get(id);
}

vector<Document *> *DocumentController::findAll()
{
  return this->documentDao->findAll();
}

void DocumentController::validate(int id)
{
  Document *doc = this->get(id);

  if (NULL == doc)
  {
    throw std::invalid_argument("No document found with the provided id.");
  }

  bool isValid = this->signatureService->validate(doc);
  delete doc;
  if (!isValid)
  {
    throw std::domain_error("Invalid signature.");
  }
}

string DocumentController::hash(const char *file)
{
  unsigned char hash[SHA_DIGEST_LENGTH]; // == 20
  SHA1((const unsigned char *)file, strlen(file), hash);

  std::ostringstream os;
  os.fill('0');
  os << std::hex;
  for (const unsigned char *ptr = hash; ptr < hash + SHA_DIGEST_LENGTH; ptr++)
  {
    os << std::setw(2) << (unsigned int)*ptr;
  }
  return os.str();
}
