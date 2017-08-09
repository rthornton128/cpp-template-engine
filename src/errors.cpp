//
// Created by rthornton on 04/06/17.
//

#include "errors.h"

#include <sstream>

using namespace Lex;

std::string Error::String() const {
    std::stringstream ss;
    ss << position << " " << message;
    return ss.str();
}

void ErrorList::Append(Error err) {
    errors.push_back(err);
}

unsigned int ErrorList::NErrors() {
    return static_cast<unsigned int>(errors.size());
}

std::string ErrorList::String() const {
    std::stringstream ss;
    for (unsigned int i = 0; i < errors.size() && i < max_errors; i++) {
        ss << errors.at(i) << std::endl;
    }
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Error& err) {
    os << err.String();
    return os;
}

std::ostream& operator<<(std::ostream& os, const ErrorList& el) {
    os << el.String();
    return os;
}
