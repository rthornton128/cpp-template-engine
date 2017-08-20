#include <iostream>
#include <sstream>

#include "assert.hpp"
#include "errors.hpp"

using namespace std;
using namespace Template;

int main() {
    /* Errors */
    string expect = "name:5:24: error message";
    Error err(Position("name", 5, 24), "error message");
    assert(err.String() == expect);

    stringstream ss;
    ss << err;
    assert(ss.str() == expect);

    /* ErrorList */
    string msgs[] = {
            "error one",
            "error two",
            "error three"
    };

    ErrorList errs0;
    for (int i = 0; i < 3; i++) {
        errs0.Append(Error(Position("", i, 0), msgs[i]));
    }
    assert_eq(errs0.NErrors(), 3);

    ErrorList errs1(2);
    for (int i = 0; i < 3; i++) {
        errs1.Append(Error(Position("", i, 0), msgs[i]));
    }
    assert_eq(errs1.NErrors(),2);

    expect = ":0:0: error one\n:1:0: error two\n";
    assert_eq(errs1.String(), expect);

    ss.str("");
    ss << errs1;
    assert_eq(ss.str(), expect);

    return 0;
}