#ifndef LT_UTILS_HPP
#define LT_UTILS_HPP

#include <sstream>
#include <iostream>

namespace lt
{

struct Logger
{
    template<typename... Args> void
    operator()(const Args&... args)
    {
        std::ostringstream msg;
        msg << "[" << m_name << "]  ";
        log_recursive(msg, args...);
    }

    explicit Logger(const char *name) : m_name(name) {}
private:
    const char *m_name;

    // Terminator
    void log_recursive(std::ostringstream& msg)
    {
        std::cout << msg.str() << std::endl;
    }

    // "Recursive" variadic function
    template<typename T, typename... Args>
    void log_recursive(std::ostringstream& msg,
                       T value, const Args&... args)
    {
        msg << value;
        log_recursive(msg, args...);
    }

};

}

#endif
