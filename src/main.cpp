#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../inc/elog.h"

using namespace std;

void foo()
{
    while (true)
    {
        E_LOG(DEBUG, "Name %d, %s \n", 15, "Ahmet");

        this_thread::sleep_for(221ms);
    }
}

void bar()
{
    while (true)
    {
        E_LOG(DEBUG, "Trying %d, %d, %.2f, %s \n", 15, 20, 10.65, "Hello, World!");

        this_thread::sleep_for(335ms);
    }
}

void inp()
{
    char a[2];
    while( true )
    {
        this_thread::sleep_for(250ms);
        std::cout << "Değer giriniz:";

        std::cin >> a;

        if ( *a == 'x' || *a == 'X' )
        {
            exit(0);
        }
    }
}


int main()
{
    thread th1(foo);
    thread th2(bar);
    thread th3(inp);

    th1.join();
    th2.join();
    th3.join();

    return 0;
}