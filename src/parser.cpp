//
// Created by rthornton on 04/06/17.
//

#include "parser.h"

#include <iostream>
#include <sstream>

using namespace Lex;
using namespace std;

Parser::Parser() : file(NULL), scanner(NULL) {
}

Node* Parser::Parse(File* f) {
    Node* root = new Document;
    file = f;
    scanner = new Scanner(*f);
    next();
    while (item.Tok() != TOK_EOF) {
        Node *n = NULL;
        switch (item.Tok()) {
            case TOK_HTML:
                n = parseHtml();
                break;
            default:
                n = parseExpression();
        }
        static_cast<Document*>(root)->Append(n);
    }
    return root;
}

int Parser::assert(Token t) {
    int pos = item.Pos();
    if (item.Tok() != t) {
        ostringstream ss;
        ss << "expected " << t << " got " << item.Tok();
        file->AddError(item.Pos(), ss.str());
    }
    next();
    return pos;
}

void Parser::next() {
    item = scanner->Scan();
}

Node* Parser::parseEnd(int open) {
    int end = assert(TOK_END);
    return new End(open, end, assert(TOK_CLOSE_EXPR));
}

Node* Parser::parseExpression() {
    int open = assert(TOK_OPEN_EXPR);
    switch (item.Tok()) {
        case TOK_END:
            return parseEnd(open);
        case TOK_IDENT:
            return parseQualifiedIdent();
        case TOK_FOR:
            return parseFor(open);
        case TOK_HTML:
            return parseHtml();
        default:
            return new Expression(open, assert(TOK_CLOSE_EXPR));
    }
}

Node* Parser::parseFor(int) {
    int forp = assert(TOK_FOR);
    Node* varIdent = parseQualifiedIdent();
    int in = assert(TOK_IN);
    Node* arrIdent = parseQualifiedIdent();
    // parse block
    std::vector<Node *> nodes;
    while (1) { // TODO this is kind of fugly
        Node *node = parseExpression();
        if (dynamic_cast<End *>(node) != NULL) {
            break;
        }
        nodes.push_back(node);
    }
    return new For(forp, varIdent, in, arrIdent, nodes);
}

Node* Parser::parseHtml() {
    std::string lit = item.Lit();
    return new Html(assert(TOK_HTML), lit);
}

Node* Parser::parseIdent() {
    std::string lit = item.Lit();
    return new Ident(assert(TOK_IDENT), lit);
}

Node* Parser::parseQualifiedIdent() {
    Ident *lhs = static_cast<Ident *>(parseIdent());
    if (item.Tok() != TOK_DOT) {
        return lhs;
    }
    int dot = assert(TOK_DOT);
    Ident *rhs = static_cast<Ident *>(parseIdent());
    return new QualifiedIdent(lhs, dot, rhs);
}