//
// Created by rthornton on 04/06/17.
//

#include "scanner.hpp"

#include <iostream>

using namespace Template;
using namespace std;

/* Utility functions */

// isDigit returns true for any digit
static bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

// isLetter returns true for any upper or lowercase English character
static bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');
}

// isWhitespace returns true if the character is a space, tab,
// carriage return or new line
static bool isWhitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

Scanner::Scanner(File f) : ch(0), file(f), off(0), roff(0), state(State_Html), start(0) {
    src = f.Source();
    next();
}

bool Scanner::Done() { return off >= src.length(); }

Item Scanner::Scan() {
    start = off;
    Token tok = TOK_EOF;
    if (state == State_Html) {
        tok = scanHtml();
    }

    if (start == off) {
        state = State_Expr;
    }

    if (state == State_Expr)  {
        tok = scanExpr();
    }
    std::string lit;
    if (tok != TOK_EOF) {
        lit = src.substr(start, off - start);
    }
    Item item = Item(tok, lit, start);
    start = off;
    return item;
}

void Scanner::next() {
    off = roff;
    if (off >= src.length()) {
        ch = 0;
        return;
    }

    ch = src[off];
    if (ch == '\n') {
        file.AddLine(off);
    }
    roff++;
}

Token Scanner::scanExpr() {
    skipWhitespace();
    if (isLetter(ch)) {
        return scanIdent();
    }

    char ch = this->ch;
    next();
    switch (ch) {
        case '.':
            return TOK_DOT;
        case '{':
            if (this->ch == '{') {
                state = State_Expr;
                next();
                return TOK_OPEN_EXPR;
            }
            next();
            return scanHtml();
        case '}':
            if (this->ch == '}') {
                state = State_Html;
                next();
                return TOK_CLOSE_EXPR;
            }
            break;
        case '"':
            next();
            return scanString();
        case 0:
            return TOK_EOF;
        default:
            if (state == State_Html) {
                return scanHtml();
            }
            break;
    }
    return TOK_ERR;
};

Token Scanner::scanHtml() {
    while (ch != '{' && !Done()) {
        next();
    }
    return TOK_HTML;
}

Token Scanner::scanIdent() {
    while (isDigit(ch) || isLetter(ch)) {
        next();
    }
    return GetToken(src.substr(start, off - start));
}

Token Scanner::scanString() {
    while (ch != '"' && ch != 0) {
        next();
    }
    next();
    return TOK_STRING;
}

void Scanner::skipWhitespace() {
    while (isWhitespace(ch)) {
        next();
    }
    start = off;
}