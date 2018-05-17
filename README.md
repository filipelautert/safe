# safe
An academic C++ application using OpenSSL and Berkeley DB to store files and it's signatures

## Directory structure
* UML - contains the class and use case diagrams for the aplication
* src - C++ source
* db - sample berkeley DB with test data
* ssl-key - it contains:
  * 2 auto generated ssl keys (key.pem and sigsso_private.key - the second one with password 123456) that can be used to test the application 
  * simple txt file named "teste.txt" - c
  * file testes.txt.sha1.base64 that holds the base64 signature for teste.txt file
* Makefile - simple and built/tested on Debian GNU/Linux 9.4 

## Limitations
* The system does not accept files with a pipe character ("|") - so to test it try to load only text files without a pipe
* The TXT and XML storages are not implemented yet, just mocks - so segfaults will occur if they are selected
* it's a command line application but uses the external gui tool zenity to select files - so it may fail if executed over ssh without X forwarding (ex: ssh -XYC)

## Info

Diagrams were built using http://draw.io  .
