#include "assert.hpp"
#include <parser.hpp>

using namespace Template;
static void TestHTMLOnly(Parser* p);

int main() {
    Parser p;

    TestHTMLOnly(&p);
}

void TestHTMLOnly(Parser* p) {
    File f("HTMLOnly", "<!doctype html><html></html>");
    Node* n = p->Parse(&f);

    assert_neq(n, NULL);
}