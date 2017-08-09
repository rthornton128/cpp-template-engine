//
// Created by rthornton on 08/06/17.
//

#ifndef LEARN_CPP_TEMPLATE_H
#define LEARN_CPP_TEMPLATE_H

#include "errors.h"
#include "parser.h"
#include "value.hpp"

#include <ostream>

namespace Lex {
    class Template {
    public:
        Template(std::string, std::string);
        ~Template();

        void Execute(std::ostream&, std::string, Value data);

    private:
        ErrorList errors;
        std::string name;
        Node *tree;
        std::vector<Template> templates;
    };
}

#endif //LEARN_CPP_TEMPLATE_H
