# safe
An academic C++ application using OpenSSL and Berkeley DB to store files and it's signatures

## Directory structure

* UML - contains the class and use case diagrams for the aplication
* src - C++ source
* db - sample berkeley DB with test data
* ssl-key - it contains:
  * 2 auto generated ssl keys (key.pem and sigsso_private.key - the second one with password 123456) that can be used to test the application 
  * simple file named "teste.txt" - currently there is a limitation that the system does not accept files with a pipe character ("|") - so to test it try to load only text files without a pipe
  * file testes.txt.sha1.base64 that holds the base64 signature for teste.txt file
* Makefile tested under Debian GNU/Linux 9.4

Diagrams were built using http://draw.io  .
