#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>

#include "Good.h"

namespace aid {

	// protected methods


	void Good::name(const char* name) {

		if (good_name != nullptr) {

			delete[] good_name;
			good_name = nullptr;
		}

		if (name != nullptr) {
			if (strlen(name) > max_name_length) {
				good_name = new char[max_name_length + 1];
				strncpy(good_name, name, max_name_length);

				if (good_name[strlen(name)] != '\0') {
					good_name[strlen(name)] = '\0';
				}

			}
			else {
				good_name = new char[strlen(name) + 1];
				strcpy(good_name, name);

				if (good_name[strlen(name)] != '\0') {
					good_name[strlen(name)] = '\0';
				}

			}
		}

	}

	const char* Good::name() const {

		return (good_name == nullptr || good_name[0] == '\0') ? nullptr : good_name;
	}

	const char* Good::sku() const {

		return sku_no;
	}

	const char* Good::unit() const {

		return unit_name;
	}

	bool Good::taxed() const {

		return tax_status;
	}

	double Good::itemPrice() const {

		return good_price;
	}

	double Good::itemCost() const {

		return (tax_status) ? good_price + (good_price * tax_rate) : good_price;
	}

	void Good::message(const char* eMessage) {

		good_error_state.message(eMessage);
	}
	bool Good::isClear() const {

		return good_error_state.isClear();
	}




	// public methods

	Good::Good(char goodType) {

		good_type = goodType;
		sku_no[0] = '\0';
		unit_name[0] = '\0';
		good_name = nullptr;
		qty_on_hand = 0;
		qty_needed = 0;
		good_price = 0;
		tax_status = true;
	}

	Good::Good(const char* _sku, const char* gName, const char* gUnit, int qoh, bool tStatus, double gPrice, int qNeeded) {

		good_name = nullptr;
		*this = Good();

		strncpy(sku_no, _sku, max_sku_length);

		if (sku_no[max_sku_length] != '\0') {
			sku_no[max_sku_length] = '\0';
		}

		name(gName);
		strncpy(unit_name, gUnit, max_unit_length);

		if (unit_name[max_unit_length] != '\0') {
			unit_name[max_unit_length] = '\0';
		}

		qty_on_hand = qoh;
		qty_needed = qNeeded;
		tax_status = tStatus;
		good_price = gPrice;
	}

	Good::Good(const Good& copyGood) {

		if (!copyGood.isEmpty()) {

			good_name = nullptr;
			*this = copyGood;
		}
	}

	Good& Good::operator=(const Good& copyGood) {

		if (this == &copyGood) {

			return *this;
		}
		else {

			good_type = copyGood.good_type;

			strcpy(sku_no, copyGood.sku_no);

			name(copyGood.good_name);

			strcpy(unit_name, copyGood.unit_name);

			qty_on_hand = copyGood.qty_on_hand;

			qty_needed = copyGood.qty_needed;

			tax_status = copyGood.tax_status;

			good_price = copyGood.good_price;

			good_error_state.message(copyGood.good_error_state.message());

			return *this;
		}
	}

	Good::~Good() {

		delete[] good_name;
		good_name = nullptr;
	}

	std::fstream& Good::store(std::fstream& file, bool newLine) const {

		file << good_type << "," << sku_no << "," << good_name << "," << unit_name << ","
			<< tax_status << "," << good_price << "," << qty_on_hand << "," << qty_needed;

		if (newLine == true) {
			file << std::endl;
		}

		return file;
	}

	std::fstream& Good::load(std::fstream& file) {

		std::string tempStr[7];
		std::string line;
		std::getline(file, line);
		std::stringstream ss(line);

		int i = 0;

		while (std::getline(ss, tempStr[i], ',')) {
			if (i == 6) {
				break;
			}
			i++;
		}

		Good _tempGood = Good(tempStr[0].c_str(), tempStr[1].c_str(), tempStr[2].c_str(), std::stoi(tempStr[5]),
			std::stoi(tempStr[3]), std::stof(tempStr[4]), std::stoi(tempStr[6]));

		*this = _tempGood;

		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const {
		if (good_error_state.isClear()) {

			if (linear) {

				os << std::left << std::setw(max_sku_length) << sku_no << "|";
				os << std::left << std::setw(20) << good_name << "|";
				os << std::fixed << std::setprecision(2) << std::right << std::setw(7) << itemCost() << "|";
				os << std::right << std::setw(4) << qty_on_hand << "|";
				os << std::left << std::setw(10) << unit_name << "|";
				os << std::right << std::setw(4) << qty_needed << "|";
			}
			else {

				os << " Sku: " << sku_no << std::endl;
				os << " Name (no spaces): " << good_name << std::endl;
				os << " Price: " << itemPrice() << std::endl;
				os << " Price after tax: ";

				if (taxed()) {
					os << itemCost() << std::endl;
				}
				else {
					os << " N/A" << std::endl;
				}

				os << " Quantity on Hand: " << qty_on_hand << " " << unit_name << std::endl;
				os << " Quantity needed: " << qty_needed;
			}
		}
		else {
			os << good_error_state;
		}
		return os;
	}

	std::istream& Good::read(std::istream& is) {

		char* _sku = new char[max_sku_length + 1];
		char* _name = new char[max_name_length + 1];
		char* _unit = new char[max_unit_length + 1];

		int quanOnHand;
		int quantityNeeded;
		double price;
		char taxed;
		bool _tax_status;

		std::cout << " Sku: ";
		is >> _sku;
		std::cout << " Name (no spaces): ";
		is >> _name;
		std::cout << " Unit: ";
		is >> _unit;
		std::cout << " Taxed? (y/n): ";
		is >> taxed;

		if ((taxed != 'y' && taxed != 'Y') && (taxed != 'n' && taxed != 'N')) {

			is.setstate(std::ios::failbit);
			good_error_state.message("Only (Y)es or (N)o are acceptable");
		}
		else {
			(taxed == 'y' || taxed == 'Y') ? _tax_status = true : _tax_status = false;
		}

		if (!is.fail()) {
			std::cout << " Price: ";
			is >> price;
			if (is.fail()) {
				good_error_state.message("Invalid Price Entry");
			}
		}

		if (!is.fail()) {
			std::cout << " Quantity on hand: ";
			is >> quanOnHand;
			if (is.fail()) {
				good_error_state.message("Invalid Quantity Entry");
			}
		}

		if (!is.fail()) {
			std::cout << " Quantity needed: ";
			is >> quantityNeeded;
			if (is.fail()) {
				good_error_state.message("Invalid Quantity Needed Entry");
			}
		}

		if (!is.fail()) {

			Good temp = Good(good_type);

			delete[] temp.good_name;
			temp.good_name = new char[strlen(_name) + 1];

			strcpy(temp.sku_no, _sku);
			strcpy(temp.good_name, _name);
			strcpy(temp.unit_name, _unit);

			temp.qty_on_hand = quanOnHand;
			temp.tax_status = _tax_status;
			temp.good_price = price;
			temp.qty_needed = quantityNeeded;

			*this = temp;
		}

		delete[] _sku;
		_sku = nullptr;

		delete[] _name;
		_name = nullptr;

		delete[] _unit;
		_unit = nullptr;

		is.get();

		return is;
	}

	bool Good::operator==(const char* sku) const {

		return (strcmp(sku_no, sku) == 0);
	}

	double Good::total_cost() const {

		return itemCost() * qty_on_hand;
	}

	void Good::quantity(int numOfUnits) {

		qty_on_hand = numOfUnits;
	}

	bool Good::isEmpty() const {

		return (good_type == 'N' && sku_no[0] == '\0' && unit_name[0] && '\0' && qty_on_hand == 0 && qty_needed == 0 &&
			good_price == 0 && tax_status == true && good_name == nullptr) ? true : false;
	}

	int Good::qtyNeeded() const {

		return qty_needed;
	}

	int Good::quantity() const {

		return qty_on_hand;
	}

	bool Good::operator>(const char* sku) const {

		return (sku_no > sku);
	}

	bool Good::operator>(const iGood& good) const {

		return (good_name > good.name());
	}

	int Good::operator+=(int numOfUnits) {

		qty_on_hand += numOfUnits;
		return qty_on_hand;
	}

	std::ostream& operator<<(std::ostream& os, const iGood& good) {

		good.write(os, true);
		return os;
	}

	std::istream& operator>>(std::istream& is, iGood& good) {

		good.read(is);
		return is;
	}

	double operator+=(double& add, const iGood& good) {

		add += good.total_cost();
		return add;
	}



}
