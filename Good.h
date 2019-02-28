#ifndef AMA_GOOD_H
#define AMA_GOOD_H

#include "Error.h"
#include "iGood.h"
#include <iostream>

namespace aid {

    // pre-defined constants:
    const int max_sku_length = 7;
    const int max_unit_length = 10;
    const int max_name_length = 75;
    const double tax_rate = 0.13;

    class Good : public iGood {

    private:
        char good_type;
        char sku_no[max_sku_length + 1];
        char unit_name[max_unit_length + 1];
        char* good_name;
        int qty_on_hand;
        int qty_needed;
        double good_price;
        bool tax_status;
        Error good_error_state;
    protected:
        void name(const char*);
        const char* name() const;
        const char* sku() const;
        const char* unit() const;
        bool taxed() const;
        double itemPrice() const;
        double itemCost() const;
        void message(const char*);
        bool isClear() const;
    public:
        Good(char goodType = 'N');
        Good(const char* _sku, const char* gName, const char* gUnit, int qoh = 0, bool tStatus = true, double gPrice = 0, int qNeeded = 0);
        Good(const Good&);
        Good& operator=(const Good&);
        ~Good();
        std::fstream& store(std::fstream& file, bool newLine = true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std::istream& read(std::istream& is);
        bool operator==(const char*) const;
        double total_cost() const;
        void quantity(int);
        bool isEmpty() const;
        int qtyNeeded() const;
        int quantity() const;
        bool operator>(const char*) const;
        bool operator>(const iGood&) const;
        int operator+=(int);
    };
    // helper functions
    std::ostream& operator<<(std::ostream&, const iGood&);
    std::istream& operator>>(std::istream&, iGood&);
    double operator+=(double&, const iGood&);
}

#endif  /* GOOD_H */
