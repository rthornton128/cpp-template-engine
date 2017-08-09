//
// Created by rthornton on 04/06/17.
//

#ifndef LEARN_CPP_POSITION_H
#define LEARN_CPP_POSITION_H

#include <ostream>
#include <string>

namespace Lex {
    class Position {
    public:
        Position(std::string, int, int);
        int Column() const;
        int Line() const;
        std::string Name() const;

    private:
        int col, line;
        std::string name;
    };
}

std::ostream& operator<<(std::ostream& os, const Lex::Position& p);

#endif //LEARN_CPP_POSITION_H
