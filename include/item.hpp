#ifndef CPP_TEMPLATE_ENGINE_ITEM_H
#define CPP_TEMPLATE_ENGINE_ITEM_H

#include "token.hpp"

#include <ostream>

namespace Template {
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

std::ostream& operator<<(std::ostream&, Template::Item&);

#endif //CPP_TEMPLATE_ENGINE_ITEM_H
