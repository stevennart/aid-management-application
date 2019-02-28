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

#ifndef AMA_ERROR_H
#define AMA_ERROR_H
#include <iostream>
namespace aid {

    class Error {
    private:
        char* _message;
    public:
        void clear(); 
        virtual ~Error(); 
        bool isClear() const; 
        const char* message() const;   
        void message(const char* str); 
        Error(const Error& em) = delete; 
        Error& operator=(const Error& em) = delete; 
        explicit Error(const char* errorMessage = nullptr); 
    };

    std::ostream& operator<<(std::ostream& os, const Error& rhs);
}

#endif /*ERROR_H*/