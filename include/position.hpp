#ifndef CPP_TEMPLATE_ENGINE_POSITION_H
#define CPP_TEMPLATE_ENGINE_POSITION_H

#include <ostream>
#include <string>

namespace Template {
    class Position {
    public:
        Position(std::string, int, int);
        int Column() const;
        int Line() const;
        std::string Name() const;

    private:
        int col, line;
        std::string name;
    };
}

std::ostream& operator<<(std::ostream& os, const Template::Position& p);

#endif //CPP_TEMPLATE_ENGINE_POSITION_H
