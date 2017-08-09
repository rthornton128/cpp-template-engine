//
// Created by rthornton on 04/06/17.
//

#ifndef LEARN_CPP_PARSER_H
#define LEARN_CPP_PARSER_H

#include "ast.h"
#include "scanner.h"
#include "token.h"

namespace Lex {
    class Parser {
    public:
        Parser();
        Node* Parse(File*);

    private:
        int assert(Token);
        void next();
        Node* parseEnd(int);
        Node* parseExpression();
        Node* parseFor(int);
        Node* parseHtml();
        Node* parseIdent();
        Node* parseQualifiedIdent();

        Scanner* scanner;
        File* file;
        Item item;
    };
}

#endif //LEARN_CPP_PARSER_H
