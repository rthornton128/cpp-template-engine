#ifndef CPP_TEMPLATE_ENGINE_SCANNER_H
#define CPP_TEMPLATE_ENGINE_SCANNER_H

#include "file.hpp"
#include "item.hpp"

#include <string>

namespace Template {
    enum State {
        State_Html,
        State_Expr,
    };

    class Scanner {
    public:
        explicit Scanner(File f);
        bool Done();
        Item Scan();

    private:
        void next();
        void skipWhitespace();
        Token scanExpr();
        Token scanHtml();
        Token scanIdent();
        Token scanString();

        char ch;
        unsigned int off, roff, state, start;
        std::string src;
        File file;
    };
}
#endif //CPP_TEMPLATE_ENGINE_SCANNER_H
