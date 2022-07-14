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
        ELOG(ERROR, "Hello, world!");

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void bar()
{
    while (true)
    {
        ELOG(DEBUG, "I'm trying this log library. This is awesome.");

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void inp()
{
    char a[2];
    while (true)
    {
        std::cin >> a;

        if ( *a == 'x' || *a == 'X' )
        {
            ELOG(INFO, "Pressed X. Exiting...");

            exit(0);
        }
    }
}


int main()
{
    ELOG_LEVEL(Elog::LogLevel::Info);
    ELOG_OUTPUT(Elog::LogOutput::File);
    ELOG_FILESIZE(Elog::ByteSize::MB1);
    ELOG_FILEPREFIX("app");
    ELOG_FILESUFFIX(".log");
    ELOG_TIDCOLSIZE(Elog::Size::Six);
    ELOG_LINECOLSIZE(Elog::Size::Five);
    ELOG_LEVELCOLSIZE(Elog::Size::Eight);
    ELOG_FILENAMECOLSIZE(Elog::Size::Ten);
    ELOG_FUNCNAMECOLSIZE(Elog::Size::Ten);

    ELOG_MESSAGELENGTH(Elog::ByteSize::KB1);

    std::thread th1 = std::thread(foo);
    std::thread th2 = std::thread(bar);
    std::thread th3 = std::thread(inp);

    th1.join();
    th2.join();
    th3.join();

    return 0;
}
