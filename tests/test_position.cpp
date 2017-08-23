#include <iostream>
#include <sstream>

#include "assert.hpp"
#include "position.hpp"

using namespace std;
using namespace Template;

int main() {
    Position p = Position("name", 1, 42);
    assert_eq(p.Column(), 42);
    assert_eq(p.Line(), 1);
    assert_eq(p.Name(), "name");

    string expect = "name:1:42: ";
    ostringstream out;
    out << p;
    assert_eq(out.str(), expect);
}
