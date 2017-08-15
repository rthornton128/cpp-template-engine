#include "parser.hpp"

#include <iostream>
#include <sstream>

using namespace Template;
using namespace std;

Parser::Parser() : file(NULL), scanner(NULL) {
}

Node* Parser::Parse(File* f) {
    Document* root = new Document();
    file = f;
    scanner = new Scanner(*f);
    next();
    while (item.Tok() != TOK_EOF) {
        Node *n = parseExpression();
        root->Append(n);
    }
    delete scanner;
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
    //cout << "item: " << item << endl;
}

Node* Parser::parseEnd(int open) {
    int end = assert(TOK_END);
    return new End(open, end, 0);
}

Node* Parser::parseExpression() {
    if (item.Tok() == TOK_HTML) {
        return parseHtml();
    }

    int open = assert(TOK_OPEN_EXPR);
    Node* node = NULL;
    switch (item.Tok()) {
        case TOK_END:
            node = parseEnd(open); break;
        case TOK_DOT:
        case TOK_IDENT:
            node = parseQualifiedIdent(); break;
        case TOK_FOR:
            return parseFor(open);
        case TOK_IF:
            return parseIf();
        default:
            break;
    }
    assert(TOK_CLOSE_EXPR);
    return node;
}

Node* Parser::parseFor(int) {
    int forp = assert(TOK_FOR);
    Node* varIdent = parseQualifiedIdent();
    int in = assert(TOK_IN);
    Node* arrIdent = parseQualifiedIdent();
    assert(TOK_CLOSE_EXPR);

    std::vector<Node *> nodes;
    parseInner(nodes);
    return new For(forp, varIdent, in, arrIdent, nodes);
}

Node* Parser::parseHtml() {
    std::string lit = item.Lit();
    return new Html(assert(TOK_HTML), lit);
}

Node* Parser::parseIdent() {
    std::string lit = item.Lit();
    if (item.Tok() == TOK_DOT) {
         return new Ident(assert(TOK_DOT), lit);
    }
    return new Ident(assert(TOK_IDENT), lit);
}

Node* Parser::parseIf() {
    int posIf = assert(TOK_IF);
    Node* predicate = parseQualifiedIdent();
    assert(TOK_CLOSE_EXPR);

    std::vector<Node *> nodes;
    parseInner(nodes);
    return new If(posIf, predicate, nodes);
}

Node* Parser::parseQualifiedIdent() {
    Ident* lhs = dynamic_cast<Ident*>(parseIdent());
    if (item.Tok() != TOK_DOT) {
        return lhs;
    }
    int dot = assert(TOK_DOT);
    Ident* rhs = dynamic_cast<Ident*>(parseIdent());
    return new QualifiedIdent(lhs, dot, rhs);
}

void Parser::parseInner(std::vector<Node*>& nodes) {
    Node *node = NULL;
    while (dynamic_cast<End *>(node) == NULL) {
        node = parseExpression();
        nodes.push_back(node);
    }
}
