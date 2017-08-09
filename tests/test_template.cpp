#include "scanner.h"
#include "parser.h"
#include "template.h"

#include <iostream>

using namespace std;

int main(void) {
    string str = "<!doctype html>\n"
            "<html>\n"
            "<head><title>Simple Template Example</title></head>\n"
            "<body>\n"
            "<p>The answer to life, the universe and everything: {{ answer }}</p>\n"
            "<ul>\n"
            "{{ for elem in . }}"
            "<li>{{ elem }}</li>\n"
            "{{ end }}"
            "</ul>\n"
            "</body>\n"
            "</html>";
    Lex::Template t = Lex::Template("html", str);
    Value map = Value(Value::mapType);
    map["answer"] = 42;
    //map["pi"] = 3.14;
    //map["foobar"] = "baz";
    //map["narf"] = "bap";
    //map["narf"] = "blarg";
    t.Execute(cout, "html", map);

    return 0;
}