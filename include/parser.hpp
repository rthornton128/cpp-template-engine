#ifndef CPP_TEMPLATE_ENGINE_PARSER_H
#define CPP_TEMPLATE_ENGINE_PARSER_H

#include "ast.hpp"
#include "scanner.hpp"
#include "token.hpp"

namespace Template {
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
        Node* parseIf();
        Node* parseQualifiedIdent();

        void parseInner(std::vector<Node*>& nodes);

        Scanner* scanner;
        File* file;
        Item item;
    };
}

#endif //CPP_TEMPLATE_ENGINE_PARSER_H
