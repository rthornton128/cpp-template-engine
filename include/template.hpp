#ifndef CPP_TEMPLATE_ENGINE_TEMPLATE_H
#define CPP_TEMPLATE_ENGINE_TEMPLATE_H

#include "errors.hpp"
#include "parser.hpp"
#include "value.hpp"

#include <ostream>

namespace Template {
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

#endif //CPP_TEMPLATE_ENGINE_TEMPLATE_H
