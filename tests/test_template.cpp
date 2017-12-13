#include "scanner.hpp"
#include "parser.hpp"
#include "template.hpp"
#include "assert.hpp"

#include <iostream>
#include <sstream>

using namespace std;
using namespace Template;

void TestComplex();
void TestParseFilesSingle();
void TestSimple();
void TestMust();

int main() {
    TestSimple();
    TestParseFilesSingle();
    TestComplex();
    TestMust();

    return 0;
}

void TestComplex() {
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
    if (t.Errors().NErrors() > 0) {
        cout << t.Errors() << endl;
        return;
    }
    Value map = Value(Value::mapType);
    map["answer"] = 42;
    map["pi"] = 3.14;
    map["foobar"] = string("baz");
    map["narf"] = "bap";
    map["narf"] = "blarg";
    map["false"] = false;
    t.Execute(cout, "html", map);
}

void TestSimple() {
    Template::Template t = Template::Template("simple", "{{ . }}");
    Value n(42);
    stringstream ss;
    t.Execute(ss, "simple", n);
    string expect = "42";
    assert_eq(ss.str(), expect);
}

void TestParseFilesSingle() {
    vector<string> files = {"C:\\Users\\Rob\\CLionProjects\\cpp-template-engine\\tests\\html.tpl"};
    auto t = ParseFiles(files);
    if (t->Errors().NErrors()) {
        cout << t->Errors() << endl;
        return;
    }
    Value v(42);
    t->Execute(cout, "C:\\Users\\Rob\\CLionProjects\\cpp-template-engine\\tests\\html.tpl", v);
}

void TestMust() {
    Template::Template t = Template::Template("html_only", "<html></html>");
    Template::Must(&t);

    //t = Template::Template("error", "{{ asdf }}"); // TODO segfault
    //assert_exception(Template::Must(&t));
}
