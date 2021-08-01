#pragma once
#include <string>
namespace details {

class XORImpl
{
public:
    std::string encode(const std::string& text, const std::string& key);
    std::string decode(const std::string& text, const std::string& key);
};

}
