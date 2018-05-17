#ifndef _ASKPASSFUNCTION_H_
#define _ASKPASSFUNCTION_H_

#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <iostream>

static int my_ask_pass_function(char *buf, int size, int rwflag, void *u)
{
    std::string tmp;
    printf("Enter pass phrase for \"%s\"\n", (char *)u);

    //FIXME should not use CIN, use something better.
    std::cin >> tmp;
    if (tmp.length() <= 0)
        return 0;

    memcpy(buf, tmp.c_str(), tmp.length());
    return tmp.length();
}

void print_openssl_error(std::string msg)
{
    char *buf = new char[200];
    ERR_error_string(ERR_get_error(), buf);
    std::cout << msg << buf << std::endl;
    delete[] buf;
}

#endif