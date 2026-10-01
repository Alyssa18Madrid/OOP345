#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <iostream>
#include "event.h"

namespace seneca
{
    class Logger
    {
        Event* m_events{ nullptr };
        size_t m_size{ 0 };

    public:
        Logger() = default;

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        Logger(Logger&& other);
        Logger& operator=(Logger&& other);

        ~Logger();

        void addEvent(const Event& event);

        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
    };
}

#endif