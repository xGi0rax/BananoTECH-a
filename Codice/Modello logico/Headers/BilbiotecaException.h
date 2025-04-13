#ifndef BIBLIOTECA_EXCEPTION_H
#define BIBLIOTECA_EXCEPTION_H

#include <stdexcept>
#include <string>

class BibliotecaException : public std::runtime_error {
public:
    explicit BibliotecaException(const std::string& message): std::runtime_error(message) {}
};

#endif // BIBLIOTECA_EXCEPTION_H