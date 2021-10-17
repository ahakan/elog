#ifndef ELOG_H
#define ELOG_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <mutex>
#include <unistd.h>
#include <sys/types.h>

#include <chrono>
#include <time.h>

#define  DEBUG                  __FILE__ , __LINE__ , __FUNCTION__ , 0
#define  INFO                   __FILE__ , __LINE__ , __FUNCTION__ , 1
#define  WARNING                __FILE__ , __LINE__ , __FUNCTION__ , 2
#define  ERROR                  __FILE__ , __LINE__ , __FUNCTION__ , 3

#define  __FILENAME__           (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define  MAX_LEVEL              4
// #define  MAX_FILE_SIZE          26214400                        // 25MB
#define  MAX_FILE_SIZE          2621                        // 25MB

#define  MAX_LINE_SIZE          5
#define  MAX_TID_SIZE           6
#define  MAX_LEVEL_SIZE         7
#define  MAX_FILE_NAME_SIZE     14
#define  MAX_FUNC_NAME_SIZE     12

#define  E_LOG                  logging::writeLog

std::ofstream                   LogFile;
std::string                     LogFilePath = "";
std::string                     LogFileNamePrefix = "0000";
std::string                     LogFileNameInfix = "1";         // Must be defined as an integer
std::string                     LogFileNameSuffix = ".log";
char const*                     LevelNames[ MAX_LEVEL ] = { "DEBUG", "INFO" , "WARNING" ,"ERROR" };

std::mutex                      MutexLock;

class eLog
{
    private:
        const char*             _FileName = __FILENAME__;

    public:
        eLog()
        {
            if( !LogFile.is_open() )
            {
                const char*     _FunctionName   = __FUNCTION__;
                unsigned int    _Line           = __LINE__;

                LogFile.open(getLogFileFullName());

                addLogFileHeader();

                LogFile << "[" << currentDateTime() << "]";
                LogFile << "[" << addSpacesToConstChar(_FileName, MAX_FILE_NAME_SIZE) << "]";
                LogFile << "[" << addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE) << "]";
                LogFile << "[" << addSpacesToConstChar(_FunctionName, MAX_FUNC_NAME_SIZE) << "]";
                LogFile << "[" << addSpacesToUnsignedInt(_Line, MAX_LINE_SIZE) << "]";
                LogFile << "[" << addSpacesToConstChar(LevelNames[ 1 ], MAX_LEVEL_SIZE)  << "]" << ": ";
                LogFile << "Logging has been successfully started. " << "Max log file size: " << MAX_FILE_SIZE << "KB" << std::endl;
                LogFile.flush();
            }
        }

        ~eLog()
        {
            if( LogFile.is_open() )
            {
                const char*     _FunctionName   = __FUNCTION__;
                unsigned int    _Line           = __LINE__;

                LogFile << "[" << currentDateTime() << "]";
                LogFile << "[" << addSpacesToConstChar(_FileName, MAX_FILE_NAME_SIZE) << "]";
                LogFile << "[" << addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE) << "]";
                LogFile << "[" << addSpacesToConstChar(_FunctionName, MAX_FUNC_NAME_SIZE) << "]";
                LogFile << "[" << addSpacesToUnsignedInt(_Line, MAX_LINE_SIZE) << "]";
                LogFile << "[" << addSpacesToConstChar(LevelNames[ 1 ], MAX_LEVEL_SIZE) << "]" << ": ";
                LogFile << "Logging has been successfully terminated. " << "Total log file: " << LogFileNameInfix << std::endl;
                LogFile.flush();

                LogFile.close();
            }
        }

        void                        addLogFileHeader();
        void                        changeFile();
        std::string                 currentDateTime();
        std::string                 getLogFileFullName();
        std::ifstream::pos_type     fileSize(const char* fName);
        std::string                 addSpacesToConstChar(const char* getChar, uint8_t maxSize);
        std::string                 addSpacesToUnsignedInt(unsigned int getInt, uint8_t maxSize);

};

void eLog::addLogFileHeader()
{
    if( LogFile.is_open() )
    {
        LogFile << "[" << "            Date / Time"<< "]";
        LogFile << "[" << addSpacesToConstChar("File", MAX_FILE_NAME_SIZE)<< "]";
        LogFile << "[" << addSpacesToConstChar("TID", MAX_TID_SIZE) << "]";
        LogFile << "[" << addSpacesToConstChar("Function", MAX_FUNC_NAME_SIZE) << "]";
        LogFile << "[" << addSpacesToConstChar("Line", MAX_LINE_SIZE) << "]";
        LogFile << "[" << addSpacesToConstChar("Level", MAX_LEVEL_SIZE) << "]" << ": ";
        LogFile << "[" << "Message" << "]" << std::endl;
        LogFile.flush();
    }
}

// Create a new log file
void eLog::changeFile()
{
    uint32_t _FileSize = fileSize((getLogFileFullName()).c_str());

    if( _FileSize >= MAX_FILE_SIZE )
    {
        LogFile.close();

        LogFileNameInfix = std::to_string(std::stoi(LogFileNameInfix)+1);

        LogFile.open(getLogFileFullName());

        addLogFileHeader();
    }
}

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

std::string eLog::getLogFileFullName()
{
    return LogFilePath + LogFileNamePrefix + LogFileNameInfix + LogFileNameSuffix;
}

std::ifstream::pos_type eLog::fileSize(const char* fName)
{
    std::ifstream file(fName, std::ifstream::ate | std::ifstream::binary);

    return file.tellg();
}

// Add spaces to const char*
// It is used to change the function name and file name.
std::string eLog::addSpacesToConstChar(const char* getChar, uint8_t maxSize)
{
    std::string     _StringWithSpace;

    if( strlen(getChar) < maxSize )
        for (size_t i = 0; i < maxSize - strlen(getChar); i++)
            _StringWithSpace = _StringWithSpace + " ";

    _StringWithSpace = _StringWithSpace + getChar;

    return _StringWithSpace;
}

// Add spaces to unsigned int
std::string eLog::addSpacesToUnsignedInt(unsigned int getInt, uint8_t maxSize)
{
    std::string     _StringWithSpace;
    size_t          _IntLength = std::to_string(getInt).length();

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

        MutexLock.lock();

        // get all args
        snprintf (buffer, 255, f, args...);

        // /full/path/to/file.c to file.c
        file = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);

        if( LogFile.is_open() )
        {
            LogFile << "[" << _eLog.currentDateTime() << "]";
            LogFile << "[" << _eLog.addSpacesToConstChar(file, MAX_FILE_NAME_SIZE) << "]";
            LogFile << "[" << _eLog.addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE) << "]";
            LogFile << "[" << _eLog.addSpacesToConstChar(function, MAX_FUNC_NAME_SIZE) << "]";
            LogFile << "[" << _eLog.addSpacesToUnsignedInt(line, MAX_LINE_SIZE) << "]";
            LogFile << "[" << _eLog.addSpacesToConstChar(LevelNames[ lvl ], MAX_LEVEL_SIZE) << "]" << ": ";
            LogFile << buffer;
            LogFile.flush();
        }

        _eLog.changeFile();

        MutexLock.unlock();
    }
}

#endif

