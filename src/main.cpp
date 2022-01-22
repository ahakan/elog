#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../inc/elog.h"

void foo()
{
    while (true)
    {
        E_LOG(INFO, "Hello, %s", "world!");
        E_LOG(DEBUG, "Hello, %s", "world!");
        E_LOG(WARNING, "Hello, %s", "world!");
        E_LOG(ERROR, "Hello, %s", "world!");

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void bar()
{
    while (true)
    {
        E_LOG(DEBUG, "I'm trying this log library. This is awesome.");

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
            E_LOG(INFO, "Pressed X. Exiting...");

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
