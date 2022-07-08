/**
 * @file elog.cpp
 * @author ahc (ahmethakan@pm.me)
 * @brief 
 * @version 0.2
 * @date 2022-07-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../inc/elog.h"

/**
 * @brief Set the Max File Size object
 * 
 * @param size 
 */
void elog::setMaxFileSize(uint32_t size)
{
    mMaxFileSize = size;
}

/**
 * @brief Get the Max File Size object
 * 
 * @return uint32_t 
 */
uint32_t elog::getMaxFileSize()
{
    return mMaxFileSize;
}

/**
 * @brief Set the Log Console Or File object
 * 
 * @param selection 
 */
void elog::setLogConsoleOrFile(bool selection)
{
    mLogConsoleOrFile = selection;
}

/**
 * @brief Get the Log Console Or File object
 * 
 * @return true File
 * @return false Console
 */
bool elog::getLogConsoleOrFile()
{
    return mLogConsoleOrFile;
}

/**
 * @brief Set the Max Log Level object
 * 
 * @param level 
 */
void elog::setMaxLogLevel(uint8_t level)
{
    mMaxLogLevel = level;
}

/**
 * @brief Get the Max Log Level object
 * 
 * @return uint8_t 
 */
uint8_t elog::getMaxLogLevel()
{
    return mMaxLogLevel;
}

/**
 * @brief Set the Max TID Size object
 * 
 * @param size 
 */
void elog::setMaxTIDSize(uint8_t size)
{
    mMaxTIDSize = size;
}

/**
 * @brief Get the Max TID Size object
 * 
 * @return uint8_t 
 */
uint8_t elog::getMaxTIDSize()
{
    return mMaxTIDSize;
}

/**
 * @brief Set the Max Line Size object
 * 
 * @param size 
 */
void elog::setMaxLineSize(uint8_t size)
{
    mMaxLineSize = size;
}

/**
 * @brief Get the Max Line Size object
 * 
 * @return uint8_t 
 */
uint8_t elog::getMaxLineSize()
{
    return mMaxLineSize;
}

/**
 * @brief Set the Max Level Size object
 * 
 * @param size 
 */
void elog::setMaxLevelSize(uint8_t size)
{
    mMaxLevelSize = size;
}

/**
 * @brief Get the Max Level Size object
 * 
 * @return uint8_t 
 */
uint8_t elog::getMaxLevelSize()
{
    return mMaxLevelSize;
}

/**
 * @brief Set the Max File Name Size object
 * 
 * @param size 
 */
void elog::setMaxFileNameSize(uint8_t size)
{
    mMaxFileNameSize = size;
}

/**
 * @brief Get the Max File Name Size object
 * 
 * @return uint8_t 
 */
uint8_t elog::getMaxFileNameSize()
{
    return mMaxFileNameSize;
}

/**
 * @brief Set the Max Func Name Size object
 * 
 * @param size 
 */
void elog::setMaxFuncNameSize(uint8_t size)
{
    mMaxFuncNameSize = size;
}

/**
 * @brief Get the Max Func Name Size object
 * 
 * @return uint8_t 
 */
uint8_t elog::getMaxFuncNameSize()
{
    return mMaxFuncNameSize;
}

/**
 * @brief Set the Max Message Length object
 * 
 * @param length 
 */
void elog::setMaxMessageLength(uint16_t length)
{
    mMaxMessageLength = length;
}

/**
 * @brief Get the Max Message Length object
 * 
 * @return uint16_t 
 */
uint16_t elog::getMaxMessageLength()
{
    return mMaxMessageLength;
}

/**
 * @brief Write a head to log file
 * 
 */
void elog::addLogHeadToFile()
{
    if (mLogFile.is_open())
    {
        mLogFile << "[" << "            Date / Time"<< "]";
        mLogFile << "[" << addSpacesToConstChar("TID", MAX_TID_SIZE) << "]";
        mLogFile << "[" << addSpacesToConstChar("File", MAX_FILE_NAME_SIZE)<< "]";
        mLogFile << "[" << addSpacesToConstChar("Function", MAX_FUNC_NAME_SIZE) << "]";
        mLogFile << "[" << addSpacesToConstChar("Line", MAX_LINE_SIZE) << "]";
        mLogFile << "[" << addSpacesToConstChar("Level", MAX_LEVEL_SIZE) << "]" << ": ";
        mLogFile << "[" << "Message" << "]" << std::endl;
        mLogFile.flush();
    }
}


/**
 * @brief Get current datetime
 * 
 * @return std::string 
 */
std::string elog::currentDateTime()
{
    const auto              p1 = std::chrono::system_clock::now();
    uint16_t                milliseconds = (std::chrono::duration_cast<std::chrono::milliseconds>(p1.time_since_epoch()).count())%1000;
    time_t                  now = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    struct tm               tstruct = *localtime(&now);
    char                    buf[30];

    strftime(buf, sizeof(buf), "%Y.%m.%d-%X", &tstruct);

    if (milliseconds < 10)
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".00%d", milliseconds);
    else if( 10 <= milliseconds && milliseconds < 100)
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".0%d", milliseconds);
    else
        snprintf(buf + strlen(buf), sizeof buf - strlen(buf), ".%d", milliseconds);

    return buf;
}


/**
 * @brief Return log file full name
 * 
 * @return std::string 
 */
std::string elog::getLogFileFullName()
{
    return mLogFilePath + mLogFileNamePrefix + mLogFileNameInfix + mLogFileNameSuffix;
}


/**
 * @brief Return log file size
 * 
 * @param fName 
 * @return std::ifstream::pos_type 
 */
std::ifstream::pos_type elog::fileSize(const char* fName)
{
    std::ifstream file(fName, std::ifstream::ate | std::ifstream::binary);

    return file.tellg();
}


/**
 * @brief Create a new log file
 * 
 */
void elog::changeFile()
{
    uint32_t _FileSize = fileSize((getLogFileFullName()).c_str());

    if (_FileSize >= MAX_FILE_SIZE)
    {
        mLogFile.close();

        mLogFileNameInfix = std::to_string(std::stoi(mLogFileNameInfix)+1);

        mLogFile.open(getLogFileFullName());

        addLogHeadToFile();
    }
}


/**
 * @brief Write a log message to log file
 * 
 * @param _FileName 
 * @param _TID 
 * @param _FunctionName 
 * @param _Line 
 * @param _LevelNames 
 * @param _Message 
 */
void elog::writeLogToFile(std::string _TID, std::string _FileName, std::string _FunctionName, std::string _Line, std::string _LevelNames, char* _Message)
{
    if (mLogFile.is_open())
    {
        mLogFile << "[" << currentDateTime() << "]";
        mLogFile << "[" << _TID << "]";
        mLogFile << "[" << _FileName << "]";
        mLogFile << "[" << _FunctionName << "]";
        mLogFile << "[" << _Line << "]";
        mLogFile << "[" << _LevelNames  << "]" << ": ";
        mLogFile << _Message << std::endl;
        mLogFile.flush();
    }
}


/**
 * @brief Write a log message to console
 * 
 * @param _FileName 
 * @param _TID 
 * @param _FunctionName 
 * @param _Line 
 * @param _LevelNames 
 * @param _Message 
 */
void elog::writeLogToConsole(std::string _TID, std::string _FileName, std::string _FunctionName, std::string _Line, std::string _LevelNames, char* _Message)
{
    LogConsole << "[" << currentDateTime() << "]";
    LogConsole << "[" << _TID << "]";
    LogConsole << "[" << _FileName << "]";
    LogConsole << "[" << _FunctionName << "]";
    LogConsole << "[" << _Line << "]";
    LogConsole << "[" << _LevelNames << "]" << ": ";
    LogConsole << _Message << std::endl;
}


/**
 * @brief Add spaces to const char*. It is used to change the function name and file name.
 *
 * @param getChar 
 * @param maxSize 
 * @return std::string 
 */
std::string elog::addSpacesToConstChar(const char* getChar, uint8_t maxSize)
{
    std::string     _StringWithSpace;

    if (strlen(getChar) < maxSize)
        for (size_t i = 0; i < maxSize - strlen(getChar); i++)
            _StringWithSpace = _StringWithSpace + " ";

    _StringWithSpace = _StringWithSpace + getChar;

    return _StringWithSpace;
}


/**
 * @brief Add spaces to unsigned int
 * 
 * @param getInt 
 * @param maxSize 
 * @return std::string 
 */
std::string elog::addSpacesToUnsignedInt(unsigned int getInt, uint8_t maxSize)
{
    std::string     _StringWithSpace;
    size_t          _IntLength = std::to_string(getInt).length();

    if (_IntLength < maxSize)
        for (size_t i = 0; i < maxSize - _IntLength; i++)
            _StringWithSpace = _StringWithSpace + " ";

    _StringWithSpace = _StringWithSpace + std::to_string(getInt);

    return _StringWithSpace;
}

elog _elog;