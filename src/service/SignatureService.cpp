#include <openssl/pem.h>
//glib used to decode base64
#include <glib.h>
#include <glib/gi18n.h>

#include <iostream>
#include <string.h>

#include "../include/service/SignatureService.h"
#include "../include/service/SignatureFunctions.h"

#define SHA1_SIGNATURE_SIZE 256

using namespace std;

SignatureService::SignatureService() {}

bool SignatureService::validate(Document *document)
{
  EVP_MD_CTX *ctx = EVP_MD_CTX_create();
  const EVP_MD *md = EVP_get_digestbyname("SHA1");

  if (!md)
  {
    cout << "Error creating md to validate the signature." << endl;
    return false;
  }

  //convert private key to openssl object
  EVP_PKEY *openSslKey = this->getPrivateKeyOpenSSL(document->getKey()->getKey());

  if (NULL == openSslKey)
  {
    return false;
  }

  //convert signature from base64 to binary and validate it against the document
  size_t originalSigSize = strlen(document->getSignature());
  guchar *signature = g_base64_decode(document->getSignature(), &originalSigSize);

  EVP_VerifyInit_ex(ctx, md, NULL);
  EVP_VerifyUpdate(ctx, document->getFile(), strlen(document->getFile()));
  int ret = EVP_VerifyFinal(ctx, signature, SHA1_SIGNATURE_SIZE, openSslKey);

  g_free(signature);

   RSA *rsakey = EVP_PKEY_get1_RSA(openSslKey);
   cout << "key details: " <<endl;
   RSA_print_fp(stdout, rsakey, 3);
   cout << "End key. " <<endl;

  EVP_PKEY_free(openSslKey);
  // handle validation return code
  if (1 == ret)
  {
    return true;
  }
  if (-1 == ret)
  {
    print_openssl_error("Error validating signature. Description: ");
  }

  return false;
}

char *SignatureService::sign(char *document, Key *key)
{
  EVP_MD_CTX *ctx = EVP_MD_CTX_create();
  const EVP_MD *md = EVP_get_digestbyname("SHA1");

  if (!md)
  {
    cout << "Error creating md to validate the signature." << endl;
    return NULL;
  }
  EVP_PKEY *openSslKey = this->getPrivateKeyOpenSSL(key->getKey());

  if (NULL == openSslKey)
  {
    return NULL;
  }

  if (!EVP_SignInit(ctx, md))
  {
    cout << "EVP_SignInit: failed";
    EVP_PKEY_free(openSslKey);
    return NULL;
  }
  int data_len = strlen(document);
  if (!EVP_SignUpdate(ctx, document, data_len))
  {
    print_openssl_error("EVP_SignUpdate: failed:");
    EVP_PKEY_free(openSslKey);
    return NULL;
  }
  unsigned char *sig = new unsigned char[(EVP_PKEY_size(openSslKey))];
  unsigned int sig_len;
  int ret = EVP_SignFinal(ctx, sig, &sig_len, openSslKey);

  gchar *sigBase64 = g_base64_encode(sig, sig_len);

  delete []sig;
  EVP_PKEY_free(openSslKey);
  if (1 == ret)
  {
    return (char *)sigBase64;
  }
  if (-1 == ret)
  {
    print_openssl_error("Error signing. Description: ");
  }

  return NULL;
}

EVP_PKEY *SignatureService::getPrivateKeyOpenSSL(char *key)
{
  FILE *fp = fmemopen(key, strlen(key), "r");
  string keyLabel = "My key "; //TODO should get the key id here, change method to receive it
  EVP_PKEY *openSslKey = PEM_read_PrivateKey(fp, NULL, my_ask_pass_function, (void *)keyLabel.c_str());
  fclose(fp);

  if (openSslKey == NULL)
  {
    print_openssl_error("Error loading SHA1 private key: ");
    return NULL;
  }
  return openSslKey;
}