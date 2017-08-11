#include "item.hpp"

using namespace Template;

std::ostream& operator<<(std::ostream& os, Item& i) {
    os << "[" << i.Tok();
    os << ",\"" << i.Lit() << "\"";
    os << "," << i.Pos() << "]";
    return os;
}

Item::Item() : tok(TOK_EOF), lit(""), pos(0) {}

Item::Item(Token tok, std::string lit, int pos) {
    this->tok = tok;
    this->lit = lit;
    this->pos = pos;
}

Token Item::Tok() { return tok; }
std::string Item::Lit() { return lit; }
int Item::Pos() { return pos; }