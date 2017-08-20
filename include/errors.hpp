#ifndef CPP_TEMPLATE_ENGINE_ERRORS_H
#define CPP_TEMPLATE_ENGINE_ERRORS_H

#include <ostream>
#include <string>
#include <vector>

#include "position.hpp"

namespace Template {
    class Error {
    public:
        Error(Position p, std::string m);
        std::string String() const;

    private:
        Position position;
        std::string message;
    };

    class ErrorList {
    public:
        explicit ErrorList(int max_errors = 0);
        void Append(const Error& err);
        unsigned int NErrors();
        std::string String() const;

    private:
        std::vector<Error> errors;
        int max_errors;
    };
}

std::ostream& operator<<(std::ostream&, const Template::Error&);
std::ostream& operator<<(std::ostream&, const Template::ErrorList&);

#endif //CPP_TEMPLATE_ENGINE_ERRORS_H
