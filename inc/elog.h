#ifndef ELOG_H
#define ELOG_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <mutex>

#include <chrono>
#include <time.h>

#define  DEBUG              __FILE__ , __LINE__ , __FUNCTION__ , 0
#define  INFO               __FILE__ , __LINE__ , __FUNCTION__ , 1
#define  WARNING            __FILE__ , __LINE__ , __FUNCTION__ , 2
#define  ERROR              __FILE__ , __LINE__ , __FUNCTION__ , 3

#define __FILENAME__        (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define  MAX_LEVEL          4
#define  MAX_FILE_SIZE      25600   // 25MB

#define  E_LOG              logging::writeLog

std::ofstream               _LogFile;
std::mutex                  _MutexLock;

std::string                 LogFileNamePrefix = "0000";
std::string                 LogFileName = "1";
std::string                 LogFileNameSuffix = ".log";

class eLog
{
    public:
        eLog()
        {
            if( !_LogFile.is_open() )
            {
                _LogFile.open(LogFileNamePrefix+LogFileName+LogFileNameSuffix);

                _LogFile << "[" << currentDateTime() << "]";
                _LogFile << "[" << __FILENAME__ << "]";
                _LogFile << "[" << gettid() << "]";
                _LogFile << "[" << __FUNCTION__ << "]";
                _LogFile << "[" << __LINE__ << "]";
                _LogFile << "[" << "INFO" << "]" << ": ";
                _LogFile << "Logging has been successfully started. " << "Max log file size: " << MAX_FILE_SIZE << "KB" << std::endl;
                _LogFile.flush();
            }
        }

        ~eLog()
        {
            if( _LogFile.is_open() )
            {
                _LogFile << "[" << currentDateTime() << "]";
                _LogFile << "[" << __FILENAME__ << "]";
                _LogFile << "[" << gettid() << "]";
                _LogFile << "[" << __FUNCTION__ << "]";
                _LogFile << "[" << __LINE__ << "]";
                _LogFile << "[" << "INFO" << "]" << ": ";
                _LogFile << "Logging has been successfully terminated. " << "Total log file: " << LogFileName << std::endl;
                _LogFile.flush();

                _LogFile.close();
            }
        }

        const std::string currentDateTime();

        std::ifstream::pos_type fileSize(const char* filename);

        void changeFile();
};

const std::string eLog::currentDateTime()
{
    const auto p1 = std::chrono::system_clock::now();

    uint16_t milliseconds = (std::chrono::duration_cast<std::chrono::milliseconds>(
        p1.time_since_epoch()).count())%1000;

    time_t     now = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    char       buf[30];
    struct tm  tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y.%m.%d-%X", &tstruct);

    if( milliseconds < 10 )
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".00%d", milliseconds);
    else if( 10 <= milliseconds && milliseconds < 100)
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".0%d", milliseconds);
    else
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".%d", milliseconds);

    return buf;
}

std::ifstream::pos_type eLog::fileSize(const char* filename)
{
    std::ifstream file(filename, std::ifstream::ate | std::ifstream::binary);

    return file.tellg();
}

void eLog::changeFile()
{
    uint32_t _FileSize = fileSize((LogFileNamePrefix+LogFileName+LogFileNameSuffix).c_str());

    if( _FileSize >= MAX_FILE_SIZE )
    {
        _LogFile.close();

        LogFileName = std::to_string(stoi(LogFileName)+1);

        _LogFile.open(LogFileNamePrefix+LogFileName+LogFileNameSuffix);
    }
}


namespace logging
{
    eLog _eLog;

    template<typename... Args>
    void writeLog(char const *file, unsigned int line, char const * function, unsigned char lvl, const char * f, Args... args)
    {
        char const *LevelNames[ MAX_LEVEL ] = { "DEBUG", "INFO" , "WARNING" ,"ERROR" };

        _MutexLock.lock();

        char buffer[256];
        snprintf (buffer, 255, f, args...);

        // /full/path/to/file.c to file.c
        file = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);

        if( _LogFile.is_open() )
        {
            _LogFile << "[" << _eLog.currentDateTime() << "]";
            _LogFile << "[" << file << "]";
            _LogFile << "[" << gettid() << "]";
            _LogFile << "[" << function << "]";
            _LogFile << "[" << line << "]";
            _LogFile << "[" << LevelNames[ lvl ] << "]" << ": ";
            _LogFile << buffer;
            _LogFile.flush();
        }

        _eLog.changeFile();

        _MutexLock.unlock();
    }
}

#endif

