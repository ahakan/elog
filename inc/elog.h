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

#define  DEBUG                  __FILE__ , __LINE__ , __FUNCTION__ , 0
#define  INFO                   __FILE__ , __LINE__ , __FUNCTION__ , 1
#define  WARNING                __FILE__ , __LINE__ , __FUNCTION__ , 2
#define  ERROR                  __FILE__ , __LINE__ , __FUNCTION__ , 3

#define  __FILENAME__           (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define  MAX_LEVEL              4
#define  MAX_FILE_SIZE          25600   // 25MB

#define  MAX_LINE_SIZE          5
#define  MAX_FILE_NAME_SIZE     16
#define  MAX_FUNC_NAME_SIZE     10

#define  E_LOG                  logging::writeLog

std::ofstream                   _LogFile;
std::mutex                      _MutexLock;

std::string                     LogFileNamePrefix = "0000";
std::string                     LogFileName = "1";
std::string                     LogFileNameSuffix = ".log";
char const*                     LevelNames[ MAX_LEVEL ] = { "  DEBUG", "   INFO" , "WARNING" ,"  ERROR" };

class eLog
{
    private:
        const char*             _FileName = __FILENAME__;

    public:
        eLog()
        {
            if( !_LogFile.is_open() )
            {
                const char*     _FunctionName   = __FUNCTION__;
                unsigned int    _Line           = __LINE__;

                _LogFile.open(LogFileNamePrefix+LogFileName+LogFileNameSuffix);

                _LogFile << "[" << currentDateTime() << "]";
                _LogFile << "[" << addSpacesToConstChar(_FileName, MAX_FILE_NAME_SIZE) << "]";
                _LogFile << "[" << gettid() << "]";
                _LogFile << "[" << addSpacesToConstChar(_FunctionName, MAX_FUNC_NAME_SIZE) << "]";
                _LogFile << "[" << addSpacesToUnsignedInt(_Line, MAX_LINE_SIZE) << "]";
                _LogFile << "[" << LevelNames[1] << "]" << ": ";
                _LogFile << "Logging has been successfully started. " << "Max log file size: " << MAX_FILE_SIZE << "KB" << std::endl;
                _LogFile.flush();
            }
        }

        ~eLog()
        {
            if( _LogFile.is_open() )
            {
                const char*     _FunctionName   = __FUNCTION__;
                unsigned int    _Line           = __LINE__;

                _LogFile << "[" << currentDateTime() << "]";
                _LogFile << "[" << addSpacesToConstChar(_FileName, MAX_FILE_NAME_SIZE) << "]";
                _LogFile << "[" << gettid() << "]";
                _LogFile << "[" << addSpacesToConstChar(_FunctionName, MAX_FUNC_NAME_SIZE) << "]";
                _LogFile << "[" << addSpacesToUnsignedInt(_Line, MAX_LINE_SIZE) << "]";
                _LogFile << "[" << LevelNames[1] << "]" << ": ";
                _LogFile << "Logging has been successfully terminated. " << "Total log file: " << LogFileName << std::endl;
                _LogFile.flush();

                _LogFile.close();
            }
        }

        void                        changeFile();
        std::string                 currentDateTime();
        std::ifstream::pos_type     fileSize(const char* fName);
        std::string                 addSpacesToConstChar(const char* getChar, uint8_t maxSize);
        std::string                 addSpacesToUnsignedInt(unsigned int getInt, uint8_t maxSize);

};

std::string eLog::currentDateTime()
{
    const auto              p1 = std::chrono::system_clock::now();
    uint16_t                milliseconds = (std::chrono::duration_cast<std::chrono::milliseconds>(p1.time_since_epoch()).count())%1000;
    time_t                  now = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    struct tm               tstruct = *localtime(&now);
    char                    buf[30];

    strftime(buf, sizeof(buf), "%Y.%m.%d-%X", &tstruct);

    if( milliseconds < 10 )
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".00%d", milliseconds);
    else if( 10 <= milliseconds && milliseconds < 100)
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".0%d", milliseconds);
    else
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".%d", milliseconds);

    return buf;
}

std::ifstream::pos_type eLog::fileSize(const char* fName)
{
    std::ifstream file(fName, std::ifstream::ate | std::ifstream::binary);

    return file.tellg();
}

// Create a new log file
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

// Add spaces to const char*
// It is used to change the function name and file name.
std::string eLog::addSpacesToConstChar(const char* getChar, uint8_t maxSize)
{
    std::string _StringWithSpace;

    if( strlen(getChar) < maxSize )
        for (size_t i = 0; i < maxSize - strlen(getChar); i++)
            _StringWithSpace = _StringWithSpace + " ";

    _StringWithSpace = _StringWithSpace + getChar;

    return _StringWithSpace;
}

// Add spaces to unsigned int
std::string eLog::addSpacesToUnsignedInt(unsigned int getInt, uint8_t maxSize)
{
    std::string _StringWithSpace;
    size_t     _IntLength = std::to_string(getInt).length();
    if( _IntLength < maxSize )
        for (size_t i = 0; i < maxSize - _IntLength; i++)
            _StringWithSpace = _StringWithSpace + " ";

    _StringWithSpace = _StringWithSpace + std::to_string(getInt);

    return _StringWithSpace;
}


namespace logging
{
    eLog _eLog;

    template<typename... Args>
    void writeLog(char const *file, unsigned int line, char const * function, unsigned char lvl, const char * f, Args... args)
    {
        char            buffer[256];

        _MutexLock.lock();

        // get all args
        snprintf (buffer, 255, f, args...);

        // /full/path/to/file.c to file.c
        file = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);

        if( _LogFile.is_open() )
        {
            _LogFile << "[" << _eLog.currentDateTime() << "]";
            _LogFile << "[" << _eLog.addSpacesToConstChar(file, MAX_FILE_NAME_SIZE) << "]";
            _LogFile << "[" << gettid() << "]";
            _LogFile << "[" << _eLog.addSpacesToConstChar(function, MAX_FUNC_NAME_SIZE) << "]";
            _LogFile << "[" << _eLog.addSpacesToUnsignedInt(line, MAX_LINE_SIZE) << "]";
            _LogFile << "[" << LevelNames[ lvl ] << "]" << ": ";
            _LogFile << buffer;
            _LogFile.flush();
        }

        _eLog.changeFile();

        _MutexLock.unlock();
    }
}

#endif

