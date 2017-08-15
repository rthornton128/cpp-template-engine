//
// Created by rthornton on 05/06/17.
//
#include "token.hpp"

using namespace std;
using namespace Template;

string tokens[] = {
    "EOF",
    "error",
    "HTML",
    "identifier",
    "", // keywords_start
    "for",
    "end",
    "in",
    "if",
    "", // keywords_end
    "", // operators_start
    "{#",
    "#}",
    ".",
    "{{",
    "}}",
};

Token Template::GetToken(string lit) {
    if (lit == "end") return TOK_END;
    if (lit == "for") return TOK_FOR;
    if (lit == "in") return TOK_IN;
    if (lit == "if") return TOK_IF;
    return TOK_IDENT;
}

bool IsKeyword(Token t) {
    return t > keywords_start && t < keywords_end;
}

bool IsOperator(Token t) {
    return t > operators_start && t < operators_end;
}

std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << tokens[t];
    return os;
}
