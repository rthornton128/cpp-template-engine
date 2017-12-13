#ifndef CPP_TEMPLATE_ENGINE_TEMPLATE_H
#define CPP_TEMPLATE_ENGINE_TEMPLATE_H

#include "errors.hpp"
#include "parser.hpp"
#include "value.hpp"

#include <ostream>

namespace Template {
    class Template {
    public:
        Template();
        Template(std::string, std::string);
        ~Template();

        ErrorList& Errors();
        void Execute(std::ostream&, const std::string&, Value& data);
        void Append(Template* t);

    private:
        ErrorList errors;
        std::string name;
        Node *tree;
        std::vector<Template*> templates;
    };

    Template* ParseFiles(std::vector<std::string> &files);
    Template* Must(Template* t);
}

#endif //CPP_TEMPLATE_ENGINE_TEMPLATE_H
