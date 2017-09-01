#include "parser.hpp"

#include <iostream>
#include <sstream>

using namespace Template;
using namespace std;

Parser::Parser() : file(NULL), scanner(NULL) {}

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

Node* Parser::parseEnd() {
    return new End(assert(TOK_END));
}

Node* Parser::parseExpression() {
    if (item.Tok() == TOK_HTML) {
        return parseHtml();
    }

    assert(TOK_OPEN_EXPR);
    Node* node = NULL;
    switch (item.Tok()) {
        case TOK_END:
            node = parseEnd(); break;
        case TOK_DOT:
        case TOK_IDENT:
            node = parseQualifiedIdent(); break;
        case TOK_FOR:
            return parseFor();
        case TOK_IF:
            return parseIf();
        default:
            break;
    }
    assert(TOK_CLOSE_EXPR);
    return node;
}

Node* Parser::parseFilters(Ident* ident) {
    while (item.Tok() == TOK_PIPE) {
        assert(TOK_PIPE);
        ident->AddFilter(parseIdent());
    }
    return ident;
}

Node* Parser::parseFor() {
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
        return parseFilters(lhs);
    }
    int dot = assert(TOK_DOT);
    Ident* rhs = dynamic_cast<Ident*>(parseIdent());
    return new QualifiedIdent(lhs, dot,
      dynamic_cast<Ident*>(parseFilters(rhs)));
}

void Parser::parseInner(std::vector<Node*>& nodes) {
    Node *node = NULL;
    while (dynamic_cast<End *>(node) == NULL) {
        node = parseExpression();
        nodes.push_back(node);
    }
}
