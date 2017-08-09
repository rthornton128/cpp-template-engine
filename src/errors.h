//
// Created by rthornton on 04/06/17.
//

#ifndef LEARN_CPP_ERRORS_H
#define LEARN_CPP_ERRORS_H

#include <ostream>
#include <string>
#include <vector>

#include "position.h"

namespace Lex {
    class Error {
    public:
        Error(Position p, std::string m) : position(p), message(m) {}
        std::string String() const;

    private:
        Position position;
        std::string message;
    };

    class ErrorList {
    public:
        ErrorList(int max_errors = 10) : max_errors(max_errors) {}
        void Append(Error err);
        unsigned int NErrors();
        std::string String() const;

    private:
        std::vector<Error> errors;
        int max_errors;
    };
}

std::ostream& operator<<(std::ostream&, const Lex::Error&);
std::ostream& operator<<(std::ostream&, const Lex::ErrorList&);

#endif //LEARN_CPP_ERRORS_H
