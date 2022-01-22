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

#define  INFO                   __FILE__ , __LINE__ , __FUNCTION__ , 0
#define  DEBUG                  __FILE__ , __LINE__ , __FUNCTION__ , 1
#define  WARNING                __FILE__ , __LINE__ , __FUNCTION__ , 2
#define  ERROR                  __FILE__ , __LINE__ , __FUNCTION__ , 3

#define  __FILENAME__           (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define  LOG_CONSOLE_OR_FILE    1                               // 0=Console , 1=File
#define  MAX_LEVEL              2                               // 1 = Info, 2 = Info, Debug, 3 = Info, Debug, Warning, 4 = Info, Debug, Warning, Error
#define  MAX_FILE_SIZE          26214400                        // 25MB

#define  MAX_LINE_SIZE          5
#define  MAX_TID_SIZE           6
#define  MAX_LEVEL_SIZE         7
#define  MAX_FILE_NAME_SIZE     14
#define  MAX_FUNC_NAME_SIZE     12

#define  E_LOG                  logging::getLog

#define  LogConsole             std::cout

#if LOG_CONSOLE_OR_FILE == 0
    char const*                 LevelNames[ 4 ] = { "\033[1;34mINFO\033[0m" , "\033[1;32mDEBUG\033[0m", "\033[1;33mWARNING\033[0m" ,"\033[1;31mERROR\033[0m" };
#else
    char const*                 LevelNames[ 4 ] = { "INFO", "DEBUG", "WARNING", "ERROR" };
#endif

std::mutex                      MutexLock;

class eLog
{
    private:
        std::ofstream           LogFile;
        std::string             LogFilePath = "";
        std::string             LogFileNamePrefix = "0000";
        std::string             LogFileNameInfix = "1";         // Must be defined as an integer
        std::string             LogFileNameSuffix = ".log";

    public:
        eLog();
        ~eLog();
        void                        writeLogToFile(std::string _FileName, std::string _TID, std::string _FunctionName, std::string _Line, std::string _LevelNames, char* _Message);
        void                        writeLogToConsole(std::string _FileName, std::string _TID, std::string _FunctionName, std::string _Line, std::string _LevelNames, char* _Message);
        void                        addLogHeadToFile();
        void                        changeFile();
        std::string                 currentDateTime();
        std::string                 getLogFileFullName();
        std::ifstream::pos_type     fileSize(const char* fName);
        std::string                 addSpacesToConstChar(const char* getChar, uint8_t maxSize);
        std::string                 addSpacesToUnsignedInt(unsigned int getInt, uint8_t maxSize);

};

// Constructor
eLog::eLog()
{
    char            _Message[256];
    const char*     _FileName       = __FILENAME__;
    const char*     _FunctionName   = __FUNCTION__;

    #if LOG_CONSOLE_OR_FILE == 0

        snprintf (_Message, 255, "Logging has been successfully started.");

        writeLogToConsole(_FileName,
                                std::to_string(gettid()),
                                _FunctionName,
                                std::to_string(__LINE__),
                                LevelNames[ 0 ],
                                _Message);

    #else

        if( !LogFile.is_open() )
        {
            LogFile.open(getLogFileFullName());

            addLogHeadToFile();

            snprintf (_Message, 255, "Logging has been successfully started. Max log file size: %dKB", MAX_FILE_SIZE);

            writeLogToFile(addSpacesToConstChar(_FileName, MAX_FILE_NAME_SIZE),
                            addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE),
                            addSpacesToConstChar(_FunctionName, MAX_FUNC_NAME_SIZE),
                            addSpacesToUnsignedInt(__LINE__, MAX_LINE_SIZE),
                            addSpacesToConstChar(LevelNames[ 0 ], MAX_LEVEL_SIZE),
                            _Message);
        }

    #endif
}

// Destructor
eLog::~eLog()
{
    char            _Message[256];
    const char*     _FileName       = __FILENAME__;
    const char*     _FunctionName   = __FUNCTION__;

    #if LOG_CONSOLE_OR_FILE == 0
        snprintf (_Message, 255, "Logging has been successfully terminated.");

        writeLogToConsole(_FileName,
                                std::to_string(gettid()),
                                _FunctionName,
                                std::to_string(__LINE__),
                                LevelNames[ 0 ],
                                _Message);
    #else
        snprintf (_Message, 255, "Logging has been successfully terminated. Total log file: %s", LogFileNameInfix.c_str());

        writeLogToFile(addSpacesToConstChar(_FileName, MAX_FILE_NAME_SIZE),
                        addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE),
                        addSpacesToConstChar(_FunctionName, MAX_FUNC_NAME_SIZE),
                        addSpacesToUnsignedInt(__LINE__, MAX_LINE_SIZE),
                        addSpacesToConstChar(LevelNames[ 0 ], MAX_LEVEL_SIZE),
                        _Message);

        LogFile.close();
    #endif
}

// Write a log message to log file
void eLog::writeLogToFile(std::string _FileName, std::string _TID, std::string _FunctionName, std::string _Line, std::string _LevelNames, char* _Message)
{
    if( LogFile.is_open() )
    {
        LogFile << "[" << currentDateTime() << "]";
        LogFile << "[" << _FileName << "]";
        LogFile << "[" << _TID << "]";
        LogFile << "[" << _FunctionName << "]";
        LogFile << "[" << _Line << "]";
        LogFile << "[" << _LevelNames  << "]" << ": ";
        LogFile << _Message << std::endl;
        LogFile.flush();
    }
}

// Write a log message to console
void eLog::writeLogToConsole(std::string _FileName, std::string _TID, std::string _FunctionName, std::string _Line, std::string _LevelNames, char* _Message)
{
    LogConsole << "[" << currentDateTime() << "]";
    LogConsole << "[" << _FileName << "]";
    LogConsole << "[" << _TID << "]";
    LogConsole << "[" << _FunctionName << "]";
    LogConsole << "[" << _Line << "]";
    LogConsole << "[" << _LevelNames << "]" << ": ";
    LogConsole << _Message << std::endl;
}

// Write a head to log file
void eLog::addLogHeadToFile()
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

        addLogHeadToFile();
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
    void getLog(char const *file, unsigned int line, char const * function, unsigned char lvl, const char * f, Args... args)
    {

        if( static_cast<int>(lvl) < MAX_LEVEL )
        {
            char    _Message[256];

            MutexLock.lock();

            // /full/path/to/file.c to file.c
            file = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);

            // get all args
            snprintf (_Message, 255, f, args...);


            #if LOG_CONSOLE_OR_FILE == 0
                _eLog.writeLogToConsole(file,
                                    std::to_string(gettid()),
                                    function,
                                    std::to_string(line),
                                    LevelNames[ lvl ],
                                    _Message);
            #else
                _eLog.writeLogToFile(_eLog.addSpacesToConstChar(file, MAX_FILE_NAME_SIZE),
                                    _eLog.addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE),
                                    _eLog.addSpacesToConstChar(function, MAX_FUNC_NAME_SIZE),
                                    _eLog.addSpacesToUnsignedInt(line, MAX_LINE_SIZE),
                                    _eLog.addSpacesToConstChar(LevelNames[ lvl ], MAX_LEVEL_SIZE),
                                    _Message);

                _eLog.changeFile();
            #endif

            MutexLock.unlock();
        }
    }
}

#endif

