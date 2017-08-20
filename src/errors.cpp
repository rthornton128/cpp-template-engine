#include "errors.hpp"

#include <sstream>

using namespace Template;
using namespace std;

/** Error */

Error::Error(Position p, string m) : position(p), message(m) {}

string Error::String() const {
    std::stringstream ss;
    ss << position << message;
    return ss.str();
}

/** ErrorList */

ErrorList::ErrorList(int max_errors) : max_errors(max_errors) {}

void ErrorList::Append(const Error& err) {
    if (max_errors == 0 || errors.size() < max_errors) {
        errors.push_back(err);
    }
}

unsigned int ErrorList::NErrors() {
    return static_cast<unsigned int>(errors.size());
}

string ErrorList::String() const {
    stringstream ss;
    if (max_errors > 0) {
        for (unsigned int i = 0; i < errors.size() && i < max_errors; i++) {
            ss << errors.at(i) << endl;
        }
    } else {
        for (unsigned int i = 0; i < errors.size(); i++) {
            ss << errors.at(i) << endl;
        }
    }
    return ss.str();
}

/** Globals */

ostream& operator<<(ostream& os, const Error& err) {
    os << err.String();
    return os;
}

ostream& operator<<(ostream& os, const ErrorList& el) {
    os << el.String();
    return os;
}
