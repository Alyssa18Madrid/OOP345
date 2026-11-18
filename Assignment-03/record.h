#ifndef SENECA_RECORD_H
#define SENECA_RECORD_H

#include <string>

namespace seneca
{
    inline std::string nextField(std::string& record, const char* error)
    {
        const auto comma = record.find(',');
        if (comma == std::string::npos)
            throw error;

        const auto field = record.substr(0, comma);
        record.erase(0, comma + 1);
        return field;
    }
}

#endif