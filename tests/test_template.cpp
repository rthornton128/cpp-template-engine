#include "scanner.hpp"
#include "parser.hpp"
#include "template.hpp"

#include <iostream>

using namespace std;
using namespace Template;

int main() {
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
            "{{ if answer }}"
            "<p>Answer is true</p>\n"
            "{{ if false }}"
            "<p>This should not show up.</p>\n"
            "{{ end }}"
            "{{ end }}"
            "</body>\n"
            "</html>";
    Template::Template t = Template::Template("html", str);
    if (t.Errors().NErrors()) {
        cout << t.Errors() << endl;
        return 1;
    }
    Value map = Value(Value::mapType);
    map["answer"] = 42;
    map["pi"] = 3.14;
    map["foobar"] = string("baz");
    map["narf"] = "bap";
    map["narf"] = "blarg";
    map["false"] = false;
    t.Execute(cout, "html", map);

    return 0;
}