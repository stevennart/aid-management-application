// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name    STEVEN TRAN           Date    October 30th, 2018             Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H

#define NO_ERROR 0
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5

namespace aid {

    const int min_year = 2018;
    const int max_year = 2038;
    const int min_date = 751098;

    class Date {
    private:
        int year; // in yyyy format
        int month; // in mm format
        int day; // in dd format
        int errorState; // error int # value
        int compareValue;

        int mdays(int _month, int _year) const;
        void errCode(int errorCode);
    public:
        Date();
        Date(int _year, int _month, int _day);

        bool operator==(const Date& rhs) const;
        bool operator!=(const Date& rhs) const;
        bool operator<(const Date& rhs) const;
        bool operator>(const Date& rhs) const;
        bool operator<=(const Date& rhs) const;
        bool operator>=(const Date& rhs) const;

        int errCode() const;
        bool bad() const;

        std::istream& read(std::istream& istr); // modifier
        std::ostream& write(std::ostream& ostr) const; // query 
    };

    std::ostream& operator<<(std::ostream& os, const Date& rhs);
    std::istream& operator>>(std::istream& is, Date& rhs);

}

#endif