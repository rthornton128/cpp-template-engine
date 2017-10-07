#include "escape.hpp"

#include <sstream>

using namespace std;

static void escapeHTMLStream(istream& is, ostream& os) {
    char c;
    while (is.get(c)) {
        switch (c) {
            case '"':
                os << "&quot";
                break;
            case '\'':
                os << "&apos";
                break;
            case '&':
                os << "&amp";
                break;
            case '<':
                os << "&lt";
                break;
            case '>':
                os << "&gt";
                break;
            default:
                os << c;
        }
    }
}

string Template::escapeHTML(const string& html) {
    istringstream is(html);
    ostringstream os("");
    escapeHTMLStream(is, os);
    return os.str();
}
