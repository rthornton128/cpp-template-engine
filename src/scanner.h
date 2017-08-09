//
// Created by rthornton on 04/06/17.
//

#ifndef LEARN_CPP_SCANNER_H
#define LEARN_CPP_SCANNER_H

#include "file.h"
#include "item.h"

#include <string>

namespace Lex {
    enum State {
        State_Html,
        State_Expr,
    };

    class Scanner {
    public:
        Scanner(File f);
        bool Done();
        Item Scan();

    private:
        void next();
        void skipWhitespace();
        Token scanExpr();
        Token scanHtml();
        Token scanIdent();

        char ch;
        unsigned int off, roff, state, start;
        std::string src;
        File file;
    };
}
#endif //LEARN_CPP_SCANNER_H
