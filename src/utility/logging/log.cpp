#include "log.hpp"

#include <iostream>
#include <iomanip>

static std::string LOG_TYPE_NAME[] = {
        "DEFAULT",
        "DEBUG",
        "INIT",
        "WARNING",
        "ERROR"
};

int nrLogTypes = LOG_ERROR - LOG_DEFAULT + 1;
std::vector<std::vector<std::string>> Log::m_LogEntries = std::vector<std::vector<std::string>>(nrLogTypes);

unsigned int Log::m_Filter = LOG_TYPE::LOG_DEFAULT |
                             LOG_TYPE::LOG_DEBUG   |
                             LOG_TYPE::LOG_INIT    |
                             LOG_TYPE::LOG_WARNING |
                             LOG_TYPE::LOG_ERROR;

void Log::Message(const std::string& message, const LOG_TYPE type) {
    m_LogEntries[type].push_back(message);
    if ((type == LOG_TYPE::LOG_DEFAULT && m_Filter & LOG_TYPE::LOG_DEFAULT) ||
        (type == LOG_TYPE::LOG_DEBUG   && m_Filter & LOG_TYPE::LOG_DEBUG)   ||
        (type == LOG_TYPE::LOG_INIT    && m_Filter & LOG_TYPE::LOG_INIT)    ||
        (type == LOG_TYPE::LOG_WARNING && m_Filter & LOG_TYPE::LOG_WARNING) ||
        (type == LOG_TYPE::LOG_ERROR   && m_Filter & LOG_TYPE::LOG_ERROR)) {
        Log::printMessage(message, type);
    }
}

void Log::SetFilter(unsigned int filter) {
    m_Filter = filter;
}

void Log::Clear() {
    for (auto& entry : m_LogEntries) {
        entry.clear();
    }
}

void Log::Display(const LOG_TYPE type) {
    const std::string divider = "=========================================================";
    const bool filter = type != LOG_DEFAULT;
    for (std::size_t i = 0; i < m_LogEntries.size(); ++i) {
        if (m_LogEntries.at(i).size() > 0) {
            if (!filter || (i == type)) {
                /*   std::cout << divider << std::endl;
                   std::cout << LOG_TYPE_NAME[i] << std::endl;
                   std::cout << divider << std::endl;*/
                for (std::size_t j = 0; j < m_LogEntries.at(i).size(); ++j) {
                    std::cout << std::setw(7) << LOG_TYPE_NAME[i] << ": " << m_LogEntries.at(i).at(j) << std::endl;
                    //std::cout << " - "  << m_LogEntries[i][j] << std::endl;
                }
                std::cout << std::endl;
                //std::cout << divider << std::endl << std::endl;
            }
        }
    }
}

void Log::printMessage(const std::string& message, const LOG_TYPE type) {
    std::string typeName;
    switch (type) {
        case LOG_DEBUG:
            typeName = "DEBUG";
            break;
        case LOG_INIT:
            typeName = "INIT";
            break;
        case LOG_WARNING:
            typeName = "WARNING";
            break;
        case LOG_ERROR:
            typeName = "ERROR";
            break;
        default:
            typeName = "DEFAULT";
    }
    std::cout << std::setw(7) << typeName << ":  " << message << std::endl;
}