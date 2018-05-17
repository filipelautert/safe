#ifndef _SIGNATURESERVICE_H_
#define _SIGNATURESERVICE_H_

#include <openssl/evp.h>

#include "../model/Document.h"
#include "../model/Key.h"

class SignatureService
{
private:

public:
  SignatureService();
  bool validate(Document* document);
  char* sign(char* document, Key *key);
  EVP_PKEY* getPrivateKeyOpenSSL(char *key);
};

#endif