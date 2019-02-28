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
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "Date.h"

namespace aid {

    // number of days in month mon and year year
    //
    int Date::mdays(int mon, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = mon >= 1 && mon <= 12 ? mon : 13;
        month--;
        return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    void Date::errCode(int errorCode) {

        errorState = errorCode;   // sets error code into instance variable 
    }

    int Date::errCode() const {

        return errorState;
    }

    bool Date::bad() const {

        return (errorState != NO_ERROR) ? true : false; // true if errorstate isn't no_error
    }

    Date::Date() {
        // safe empty state
        year = 0000;
        month = 00;
        day = 00;
        errCode(NO_ERROR);
        compareValue = 0;
    }

    Date::Date(int year_, int month_, int day_) {

        int _compareValue = year_ * 372 + month_ * 31 + day_; // calculated comparator value from received parameters, these parameters are not validated yet.
        // sets the following appropriate error codes for each failed validation. 
        if (year_ == 0 && month_ == 0 && day_ == 0) {
            errCode(CIN_FAILED);
        }
        else if (year_ < min_year || year_ > max_year) {
            errCode(YEAR_ERROR);
        }
        else if (month_ < 1 || month_ > 12) {
            errCode(MON_ERROR);
        }
        else if (day_ < 1 || day_ > mdays(month_, year_)) {
            errCode(DAY_ERROR);
        }
        else if (_compareValue < min_date) { // date received isn't valid if the comparator value isn't >= to min_date.
            errCode(PAST_ERROR);
        }
        else { // if everything passes, then it will set the received parameters into the instance variables. And set the error state to NO_ERROR.
            errCode(NO_ERROR);
            year = year_;
            month = month_;
            day = day_;
            compareValue = _compareValue;
        }

        if (bad() == true) { // if the error state != NO_ERROR (when validiation fails) it will set everything to an empty state. 
            year = 0000;
            month = 00;
            day = 00;
            compareValue = 0;
        }

    }

    bool Date::operator==(const Date& rhs) const {

        if (compareValue != 0 || rhs.compareValue != 0) { // checks if one or both object is empty, if not it will return result of comparison.
            return (compareValue == rhs.compareValue) ? true : false;
        }
        else {
            return false;
        }

    }

    bool Date::operator!=(const Date& rhs) const {

        if (compareValue != 0 || rhs.compareValue != 0) {
            return (compareValue != rhs.compareValue) ? true : false;
        }
        else {
            return false;
        }

    }

    bool Date::operator<(const Date& rhs) const {

        if (compareValue != 0 || rhs.compareValue != 0) {
            return (compareValue < rhs.compareValue) ? true : false;
        }
        else {
            return false;
        }

    }

    bool Date::operator>(const Date& rhs) const {


        if (compareValue != 0 || rhs.compareValue != 0) {
            return (compareValue > rhs.compareValue) ? true : false;
        }
        else {
            return false;
        }
    }

    bool Date::operator<=(const Date& rhs) const {

        if (compareValue != 0 || rhs.compareValue != 0) {
            return (compareValue <= rhs.compareValue) ? true : false;
        }
        else {
            return false;
        }

    }

    bool Date::operator>=(const Date& rhs) const {


        if (compareValue != 0 || rhs.compareValue != 0) {
            return (compareValue >= rhs.compareValue) ? true : false;
        }
        else {
            return false;
        }


    }

    std::ostream& operator<<(std::ostream& os, const Date& rhs) { // calls the write function on the rhs object and passes in a reference to a ostream object and then returns it.

        return rhs.write(os);
    }

    std::ostream& Date::write(std::ostream& ostr) const { // returns the year, month, and day in the '/' format with 0's filled in to any empty spaces.

        return ostr << year << "/" << std::setfill('0') << std::setw(2) << month << "/" << std::setfill('0') << std::setw(2) << day;
    }

    std::istream& operator>>(std::istream& is, Date& rhs) { // calls the read function on the rhs object and passes in a reference to a istream object and then returns it.

        return rhs.read(is);
    }

    std::istream& Date::read(std::istream& istr) { // accepts user string input, separates the year, month, day and converts it to an int. Then stores it into the object.

        int i;
        char dateInput[30]; // statically allocated string user input for the YYYY/MM/DD date format.
        int date[3]; // an int array to hold the year, month, day.

        istr >> dateInput;

        char* tok = strtok(dateInput, "/-"); // strtok function is called, and passes in the dateInput along with specified delimiters. It is then stored into a char pointer token.

        if (istr.fail()) { // empty state if istr fails, and sets appropriate error code.
            *this = Date();
            errCode(CIN_FAILED);
        }
        else {

            for (i = 0; i < 3; i++) { // loops through the year, month, day and converts each token to an int and stores into the date array.
                if (tok == nullptr) { //  loop breaks if one of the tokens are nullptr.
                    break;
                }

                date[i] = atoi(tok); // atoi function converts the string token to an int and stores into date array.

                tok = strtok(nullptr, "/-"); // sets the string token of year to month to day with each iteration so it can be converted to int. 
            }

            if (i == 3) {
                *this = Date(date[0], date[1], date[2]); // year, month, day goes through validation through the constructor and sets the current object variables.
            }
            else {
                *this = Date();
                errCode(CIN_FAILED);
                istr.clear();
            }

        }

        return istr;
    }

}
