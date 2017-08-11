#include "file.hpp"

using namespace Template;

void File::AddLine(int pos) {
    lines.push_back(pos);
}

void File::AddError(int pos, std::string msg) {
    el.Append(Error(this->Pos(pos), msg));
}

ErrorList File::Errors() { return el; }

bool File::HasErrors() { return el.NErrors() > 0; }

std::string File::Name() { return name; }

Position File::Pos(int pos) {
    if (pos < 0 || pos >= src.length()) {
        throw "pos out of bounds";
    }

    int col = pos, line = 1;
    for (int i = 0; i < lines.size() && lines[i] < pos; i++) {
        col -= lines[i];
        line++;
    }

    return Position(name, line, col);
}

std::string File::Source() { return src; }
