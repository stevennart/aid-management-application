// Final Project Milestone 2
//
// Version 1.0
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name    STEVEN TRAN           Date    November 4th, 2018             Reason
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include "Error.h"

namespace aid {

    Error::Error(const char* errorMessage) {

        _message = nullptr;

        if (errorMessage == nullptr) {
            message('\0');
        }
        else {
            message(errorMessage);
        }
    }

    std::ostream& operator<<(std::ostream& os, const Error& rhs) {

        if (!rhs.isClear()) {
            os << rhs.message();
        }

        return os;
    }

    Error::~Error() {

        delete[] _message;
        _message = nullptr;
    }

    void Error::clear() {

        _message[0] = '\0';
    }

    bool Error::isClear() const {

        return (_message[0] == '\0');
    }

    void Error::message(const char* str) {

        if (str != nullptr) {

            if (_message != nullptr) {

                delete[] _message;
                _message = nullptr;
            }

            _message = new char[strlen(str) + 1];

            strncpy(_message, str, strlen(str));

            if (_message[strlen(str)] != '\0') {

                _message[strlen(str)] = '\0';
            }
        }
        else {
            _message = new char[1];
            _message[0] = '\0';
        }
    }

    const char* Error::message() const {

        return (!this->isClear()) ? _message : nullptr;
    }

}



