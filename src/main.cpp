#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../inc/elog.h"

void foo()
{
    while (true)
    {
        ELOG(INFO, "Hello, %s", "world!");
        ELOG(DEBUG, "Hello, %s", "world!");
        ELOG(WARNING, "Hello, %s", "world!");
        ELOG(ERROR, "Hello, %s", "world!");

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void bar()
{
    while (true)
    {
        // ELOG(DEBUG, "I'm trying this log library. This is awesome.");

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void inp()
{
    char a[2];
    while( true )
    {
        // std::cout << "Değer giriniz(Quit=x|X): \n";

        std::cin >> a;

        if ( *a == 'x' || *a == 'X' )
        {
            // ELOG(INFO, "Pressed X. Exiting...");

            exit(0);
        }
    }
}


int main()
{
    std::thread th1 = std::thread(foo);
    std::thread th2 = std::thread(bar);
    std::thread th3 = std::thread(inp);

    th1.join();
    th2.join();
    th3.join();

    return 0;
}
