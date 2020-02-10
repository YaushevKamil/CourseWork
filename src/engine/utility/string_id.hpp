#ifndef UTILITY_STRING_ID_HPP
#define UTILITY_STRING_ID_HPP

#include <string>

#define SID(string) custom_simple_hash(string)

inline unsigned int custom_simple_hash(const std::string &str) {
    unsigned int hash = 0;
    for (auto& it : str) {
        hash = 37 * hash + 17 * static_cast<char>(it);
    }
    return hash;
}

inline unsigned int custom_simple_hash(const char* cStr) {
    std::string str(cStr);
    return custom_simple_hash(str);
}

#endif //UTILITY_STRING_ID_HPP
