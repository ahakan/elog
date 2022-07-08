/**
 * @file elog.h
 * @author ahc (ahmethakan@pm.me)
 * @brief 
 * @version 0.2
 * @date 2022-07-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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

#define  ERROR                      __FILE__ , __LINE__ , __FUNCTION__ , 0
#define  WARNING                    __FILE__ , __LINE__ , __FUNCTION__ , 1
#define  DEBUG                      __FILE__ , __LINE__ , __FUNCTION__ , 2
#define  INFO                       __FILE__ , __LINE__ , __FUNCTION__ , 3


#define  __FILENAME__               (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)


#define  LOG_CONSOLE_OR_FILE        1                   // 0 = Console, 
                                                        // 1 = File

#define  MAX_LEVEL                  4                   // 1 = Error, 
                                                        // 2 = Error, Warning, 
                                                        // 3 = Error, Warning, Debug, 
                                                        // 4 = Error, Warning, Debug, Info
#define  MAX_FILE_SIZE              10485760            // 10MB

#define  MAX_TID_SIZE               6
#define  MAX_LINE_SIZE              5
#define  MAX_LEVEL_SIZE             7
#define  MAX_FILE_NAME_SIZE         14
#define  MAX_FUNC_NAME_SIZE         22
#define  MAX_MESSAGE_LENGTH         2048           

#define  ELOG                       getLog

#define  LogConsole                 std::cout

class elog
{
    private:

        /**
         * @brief The log file object
         * 
         */
        std::ofstream               mLogFile;

        /**
         * @brief The log file path
         * 
         */
        std::string                 mLogFilePath = "";

        /**
         * @brief The log file prefix
         * 
         */
        std::string                 mLogFileNamePrefix = "00";

        /**
         * @brief The log file infix
         *        Must be defined as an integer
         * 
         */
        std::string                 mLogFileNameInfix = "1";

        /**
         * @brief The log file suffix
         * 
         */
        std::string                 mLogFileNameSuffix = ".log";

        /**
         * @brief The log file max size
         * 
         */
        uint32_t                    mMaxFileSize;

        /**
         * @brief false => Console, true => File
         * 
         */
        bool                        mLogConsoleOrFile;

        /**
         * @brief 1 = Error, 
         *        2 = Error, Warning, 
         *        3 = Error, Warning, Debug, 
         *        4 = Error, Warning, Debug, Info
         * 
         */
        uint8_t                     mMaxLogLevel;

        /**
         * @brief TID column max size
         * 
         */
        uint8_t                     mMaxTIDSize;

        /**
         * @brief Line column max size
         * 
         */
        uint8_t                     mMaxLineSize;

        /**
         * @brief Level column max size
         * 
         */
        uint8_t                     mMaxLevelSize;

        /**
         * @brief File name column max size
         * 
         */
        uint8_t                     mMaxFileNameSize;

        /**
         * @brief Function name column max size
         * 
         */
        uint8_t                     mMaxFuncNameSize;

        /**
         * @brief Message column max length
         * 
         */
        uint16_t                    mMaxMessageLength;


        /**
         * @brief Set the Max File Size object
         * 
         * @param size 
         */
        void                        setMaxFileSize(uint32_t size);

        /**
         * @brief Get the Max File Size object
         * 
         * @return uint32_t 
         */
        uint32_t                    getMaxFileSize();

        /**
         * @brief Set the Log Console Or File object
         * 
         * @param selection 
         */
        void                        setLogConsoleOrFile(bool selection);

        /**
         * @brief Get the Log Console Or File object
         * 
         * @return bool 
         */
        bool                        getLogConsoleOrFile();

        /**
         * @brief Set the Max Log Level object
         * 
         * @param level 
         */
        void                        setMaxLogLevel(uint8_t level);

        /**
         * @brief Get the Max Log Level object
         * 
         * @return uint8_t 
         */
        uint8_t                     getMaxLogLevel();

        /**
         * @brief Set the Max TID Size object
         * 
         * @param size 
         */
        void                        setMaxTIDSize(uint8_t size);

        /**
         * @brief Get the Max TID Size object
         * 
         * @return uint8_t 
         */
        uint8_t                     getMaxTIDSize();

        /**
         * @brief Set the Max Line Size object
         * 
         * @param size 
         */
        void                        setMaxLineSize(uint8_t size);

        /**
         * @brief Get the Max Line Size object
         * 
         * @return uint8_t 
         */
        uint8_t                     getMaxLineSize();

        /**
         * @brief Set the Max Level Size object
         * 
         * @param size 
         */
        void                        setMaxLevelSize(uint8_t size);

        /**
         * @brief Get the Max Level Size object
         * 
         * @return uint8_t 
         */
        uint8_t                     getMaxLevelSize();

        /**
         * @brief Set the Max File Name Size object
         * 
         * @param size 
         */
        void                        setMaxFileNameSize(uint8_t size);

        /**
         * @brief Get the Max File Name Size object
         * 
         * @return uint8_t 
         */
        uint8_t                     getMaxFileNameSize();

        /**
         * @brief Set the Max Func Name Size object
         * 
         * @param size 
         */
        void                        setMaxFuncNameSize(uint8_t size);

        /**
         * @brief Get the Max Func Name Size object
         * 
         * @return uint8_t 
         */
        uint8_t                     getMaxFuncNameSize();

        /**
         * @brief Set the Max Message Length object
         * 
         * @param length 
         */
        void                        setMaxMessageLength(uint16_t length);

        /**
         * @brief Get the Max Message Length object
         * 
         * @return uint16_t 
         */
        uint16_t                    getMaxMessageLength();


        void                        addLogHeadToFile();
        std::string                 currentDateTime();
        std::string                 getLogFileFullName();
        std::ifstream::pos_type     fileSize(const char* fName);

    public:
        std::mutex                  MutexLock;
        char const*                 LevelNames[ 4 ] = { "ERROR", "WARNING", "DEBUG", "INFO" };


        inline                      elog();
        inline                      ~elog();

        void                        changeFile();
        void                        writeLogToFile(std::string _FileName, std::string _TID, std::string _FunctionName, std::string _Line, std::string _LevelNames, char* _Message);
        void                        writeLogToConsole(std::string _FileName, std::string _TID, std::string _FunctionName, std::string _Line, std::string _LevelNames, char* _Message);
        std::string                 addSpacesToConstChar(const char* getChar, uint8_t maxSize);
        std::string                 addSpacesToUnsignedInt(unsigned int getInt, uint8_t maxSize);
};


/**
 * @brief Construct a new elog::elog object
 * 
 */
inline elog::elog()
{
    char            *_Message       = (char *)malloc(MAX_MESSAGE_LENGTH);
    const char*     _FileName       = __FILENAME__;
    const char*     _FunctionName   = __FUNCTION__;

    if (_Message)
    {
        #if LOG_CONSOLE_OR_FILE == 0

            snprintf (_Message, 255, "Logging has been successfully started.");

            writeLogToConsole(  std::to_string(gettid()),
                                _FileName,
                                _FunctionName,
                                std::to_string(__LINE__),
                                LevelNames[ 0 ],
                                _Message);

        #else

            if (!mLogFile.is_open())
            {
                mLogFile.open(getLogFileFullName());

                addLogHeadToFile();

                snprintf (_Message, MAX_MESSAGE_LENGTH-1, "Logging has been successfully started. Max log file size: %dKB", MAX_FILE_SIZE);

                writeLogToFile( addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE),
                                addSpacesToConstChar(_FileName, MAX_FILE_NAME_SIZE),
                                addSpacesToConstChar(_FunctionName, MAX_FUNC_NAME_SIZE),
                                addSpacesToUnsignedInt(__LINE__, MAX_LINE_SIZE),
                                addSpacesToConstChar(LevelNames[ 3 ], MAX_LEVEL_SIZE),
                                _Message);
            }

        #endif

        free(_Message);
    }
}


/**
 * @brief Destroy the elog::elog object
 * 
 */
inline elog::~elog()
{
    char            *_Message       = (char *)malloc(MAX_MESSAGE_LENGTH);
    const char*     _FileName       = __FILENAME__;
    const char*     _FunctionName   = __FUNCTION__;

    if (_Message)
    {
        #if LOG_CONSOLE_OR_FILE == 0
            snprintf (_Message, 255, "Logging has been successfully terminated.");

            writeLogToConsole(  std::to_string(gettid()),
                                _FileName,
                                _FunctionName,
                                std::to_string(__LINE__),
                                LevelNames[ 0 ],
                                _Message);
        #else
            snprintf (_Message, MAX_MESSAGE_LENGTH-1, "Logging has been successfully terminated. Total log file: %s", mLogFileNameInfix.c_str());

            writeLogToFile( addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE),
                            addSpacesToConstChar(_FileName, MAX_FILE_NAME_SIZE),
                            addSpacesToConstChar(_FunctionName, MAX_FUNC_NAME_SIZE),
                            addSpacesToUnsignedInt(__LINE__, MAX_LINE_SIZE),
                            addSpacesToConstChar(LevelNames[ 3 ], MAX_LEVEL_SIZE),
                            _Message);

            mLogFile.close();
        #endif

        free(_Message);
    }
}
  

extern elog _elog;


/**
 * @brief Get the Log object
 * 
 * @tparam Args 
 * @param file 
 * @param line 
 * @param function 
 * @param lvl 
 * @param f 
 * @param args 
 */
template<typename... Args>
void getLog(char const *file, unsigned int line, char const * function, unsigned char lvl, const char * f, Args... args)
{
    
    if( static_cast<int>(lvl) < MAX_LEVEL )
    {
        char    *_Message = (char *)malloc(MAX_MESSAGE_LENGTH);

        if (_Message)
        {
            _elog.MutexLock.lock();

            // /full/path/to/file.c to file.c
            file = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);

            // get all args
            snprintf (_Message, MAX_MESSAGE_LENGTH-1, f, args...);

            #if LOG_CONSOLE_OR_FILE == 0
                _elog.writeLogToConsole(file,
                                        std::to_string(gettid()),
                                        function,
                                        std::to_string(line),
                                        _elog.LevelNames[ lvl ],
                                        _Message);
            #else
                _elog.writeLogToFile(_elog.addSpacesToUnsignedInt(gettid(), MAX_TID_SIZE),
                                     _elog.addSpacesToConstChar(file, MAX_FILE_NAME_SIZE),
                                     _elog.addSpacesToConstChar(function, MAX_FUNC_NAME_SIZE),
                                     _elog.addSpacesToUnsignedInt(line, MAX_LINE_SIZE),
                                     _elog.addSpacesToConstChar(_elog.LevelNames[ lvl ], MAX_LEVEL_SIZE),
                                     _Message);

                _elog.changeFile();
            #endif

            _elog.MutexLock.unlock();

            free(_Message);
        }
    }
}


#endif