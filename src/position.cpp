//
// Created by rthornton on 04/06/17.
//

#include "position.hpp"

using namespace Template;
using namespace std;

Position::Position(string name, int line, int col) :
    name(name),
    line(line),
    col(col) {}

int Position::Column() const { return this->col; }
int Position::Line() const { return this->line; }
string Position::Name() const { return this->name; }

std::ostream& operator<<(std::ostream& os, const Position& p) {
    os << p.Name() << ":" << p.Line() << ":" << p.Column() << ": ";
    return os;
}
