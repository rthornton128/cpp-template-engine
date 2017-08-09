//
// Created by rthornton on 04/06/17.
//

#ifndef LEARN_CPP_FILE_H
#define LEARN_CPP_FILE_H

#include "position.h"
#include "errors.h"

#include <string>
#include <vector>

namespace Lex {
    class File {
    public:
        File(std::string name, std::string src) : name(name), src(src) {}
        void AddLine(int pos);
        void AddError(int pos, std::string msg);
        ErrorList Errors();
        bool HasErrors();
        std::string Name();
        Position Pos(int);
        std::string Source();
    private:
        std::string name, src;
        std::vector<int> lines;
        ErrorList el;
    };
}

#endif //LEARN_CPP_FILE_H
