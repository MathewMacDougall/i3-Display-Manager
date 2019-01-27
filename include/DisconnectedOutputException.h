#pragma once

#include <exception>
#include <stdexcept>

class DisconnectedOutputException : public std::exception {

    virtual inline const char* what() const throw() {
        return "Encountered a disconnected output";
    }
};
