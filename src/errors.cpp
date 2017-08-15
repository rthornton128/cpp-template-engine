#include "errors.hpp"

#include <sstream>
#include <iostream> // temp

using namespace Template;
using namespace std;

string Error::String() const {
    std::stringstream ss;
    ss << position << " " << message;
    return ss.str();
}

void ErrorList::Append(Error err) {
    cout << "new error: " << err << endl;
    errors.push_back(err);
}

unsigned int ErrorList::NErrors() {
    cout << "error count:" << errors.size() << endl;
    return static_cast<unsigned int>(errors.size());
}

string ErrorList::String() const {
    stringstream ss;
    for (unsigned int i = 0; i < errors.size() && i < max_errors; i++) {
        ss << errors.at(i) << endl;
    }
    return ss.str();
}

ostream& operator<<(ostream& os, const Error& err) {
    os << err.String();
    return os;
}

ostream& operator<<(ostream& os, const ErrorList& el) {
    os << el.String();
    return os;
}
