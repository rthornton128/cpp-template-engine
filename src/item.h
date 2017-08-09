//
// Created by rthornton on 04/06/17.
//

#ifndef LEARN_CPP_NAMESPACE_H
#define LEARN_CPP_NAMESPACE_H

#include "token.h"

#include <ostream>

namespace Lex {


    class Item {
    public:
        Item();
        Item(Token, std::string, int);
        Token Tok();
        std::string Lit();
        int Pos();
    private:
        Token tok;
        std::string lit;
        int pos;
    };

}

std::ostream& operator<<(std::ostream&, Lex::Item&);

#endif //LEARN_CPP_NAMESPACE_H
