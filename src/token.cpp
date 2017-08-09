//
// Created by rthornton on 05/06/17.
//
#include "token.h"

using namespace Lex;

std::string tokens[] = {
    "EOF",
    "error",
    "HTML",
    "identifier",
    "", // keywords_start
    "for",
    "end",
    "in",
    "", // keywords_end
    "", // operators_start
    "{#",
    "#}",
    ".",
    "{{",
    "}}",
};

Token Lex::GetToken(std::string lit) {
    if (lit == "end") return TOK_END;
    if (lit == "for") return TOK_FOR;
    if (lit == "in") return TOK_IN;
    return TOK_IDENT;
}

bool Lex::IsKeyword(Token t) {
    return t > keywords_start && t < keywords_end;
}

bool Lex::IsOperator(Token t) {
    return t > operators_start && t < operators_end;
}

std::ostream& operator<<(std::ostream& os, const Lex::Token& t) {
    os << tokens[t];
    return os;
}
