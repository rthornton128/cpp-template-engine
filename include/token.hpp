#ifndef CPP_TEMPLATE_ENGINE_TOKEN_H
#define CPP_TEMPLATE_ENGINE_TOKEN_H

#include <string>
#include <vector>

namespace Template {
    enum Token {
        TOK_EOF,
        TOK_ERR,
        TOK_HTML,
        TOK_IDENT,
        keywords_start,
        TOK_FOR,
        TOK_END,
        TOK_IN,
        TOK_IF,
        keywords_end,
        operators_start,
        TOK_OPEN_COMMENT,
        TOK_CLOSE_COMMENT,
        TOK_DOT,
        TOK_OPEN_EXPR,
        TOK_CLOSE_EXPR,
        operators_end
    };

    Token GetToken(std::string);
    bool IsKeyword(Token);
    bool IsOperator(Token);
}

std::ostream& operator<<(std::ostream& os, const Template::Token& t);

#endif //CPP_TEMPLATE_ENGINE_TOKEN_H
