#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>
#include "Perishable.h"

namespace aid {

	Perishable::Perishable() : Good::Good('P') { // passes in the Good base class no arugment constructor the P character.

		expireDate = Date(); // sets the current object to a safe empty state.
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {

		Good::store(file, false);

		file << "," << expireDate;

		if (newLine == true) {
			file << std::endl;
		}

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {

		Good::load(file);

		for (int i = 0; i < 8; i++) {
			file.ignore(2000, ',');
		}

		expireDate.read(file);

		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const {

		os << std::setfill(' ');

		if (Good::write(os, linear)) {

			if (Good::isClear()) {

				if (linear == true) {
					os << expireDate;
				}
				else {
					os << std::endl << " Expiry date: " << expireDate;
				}

			}
		}

		return os;

	}

	std::istream& Perishable::read(std::istream& is) {

		Date tempExp;

		if (Good::read(is)) {
			std::cout << " Expiry date (YYYY/MM/DD): ";

			is >> tempExp;

			if (tempExp.errCode() != 0) {

				is.setstate(std::ios::failbit);

				switch (tempExp.errCode()) {

				case CIN_FAILED:
					Good::message("Invalid Date Entry");
					break;
				case YEAR_ERROR:
					Good::message("Invalid Year in Date Entry");
					break;
				case MON_ERROR:
					Good::message("Invalid Month in Date Entry");
					break;
				case DAY_ERROR:
					Good::message("Invalid Day in Date Entry");
					break;
				case PAST_ERROR:
					Good::message("Invalid Expiry in Date Entry");
					break;
				default:
					break;
				}

			}

		}

		if (!is.fail()) {

			expireDate = tempExp;
		}


		return is;
	}

	const Date& Perishable::expiry() const {

		return expireDate;

	}

















}