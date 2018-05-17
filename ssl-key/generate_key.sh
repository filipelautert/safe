#openssl genrsa -des3 -out sigsso_private.key 2048 - chave com senha 123456
#openssl rsa -pubout -in sigsso_private.key -out public.key


openssl req -newkey rsa:2048 -nodes -keyout key.pem -x509 -days 365 -out certificate.pem
openssl pkcs12 -inkey key.pem -in certificate.pem -export -out certificate.p12
openssl rsa -pubout -in key.pem -out public.key



# assina com sha1
openssl dgst -sha1 -sign key.pem -out testes.txt.sha1 testes.txt 
openssl base64 -in testes.txt.sha1 -out testes.txt.sha1.base64

