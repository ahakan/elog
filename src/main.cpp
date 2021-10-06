#include <iostream>
#include <string>

#include "../inc/elog.h"

using namespace std;


int main()
{
    string a = "Ahmet";

    E_LOG(DEBUG, "Name %d, %s \n", 15, a.c_str());

    E_LOG(DEBUG, "Trying %d, %d, %.2f, %s \n", 15, 20, 10.65, "Hello, World!");


    return 0;
}