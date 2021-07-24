#include "xorImpl.h"
#include <algorithm>
#include <iostream>

std::string details::XORImpl::encode(const std::string& text, const std::string& key)
{
    std::string result = text;

    std::transform(text.cbegin(), text.cend(), key.cbegin(), result.begin(), [](const char& lhs, const char& rhs)
    {
        return static_cast<char>(lhs^rhs);
    });

    return result;
}

std::string details::XORImpl::decode(const std::string&, const std::string&)
{
    return std::string();
}
