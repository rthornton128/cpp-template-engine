#include <iostream>

#include "assert.hpp"
#include "scanner.hpp"

using namespace std;
using namespace Template;

void TestScan(Scanner& s, vector<Token>& v) {
    int i(0);
    while (!s.Done()) {
        Item item = s.Scan();
        //cout << item.Lit() << endl; // TODO this should be tested for
        if (i < v.size()) {
            assert_eq(item.Tok(), v[i]);
        }
        i++;
    }
    assert_eq(i, v.size());
}

int main() {
    File f("test0", "");
    cout << f.Name() << endl;
    Scanner s(f);
    vector<Token> v;
    TestScan(s, v);

    f = File("test1", "<!doctype html><html></html>");
    cout << f.Name() << endl;
    s = Scanner(f);
    v = vector<Token>();
    v.push_back(TOK_HTML);
    TestScan(s, v);

    f = File("test2", "{{");
    cout << f.Name() << endl;
    s = Scanner(f);
    v = vector<Token>();
    v.push_back(TOK_OPEN_EXPR);
    TestScan(s, v);

    f = File("test3", "asdf{{asdf");
    cout << f.Name() << endl;
    s = Scanner(f);
    v = vector<Token>();
    v.push_back(TOK_HTML);
    v.push_back(TOK_OPEN_EXPR);
    v.push_back(TOK_IDENT);
    TestScan(s, v);

    f = File("test4", "asdf{asdf");
    cout << f.Name() << endl;
    s = Scanner(f);
    v = vector<Token>();
    v.push_back(TOK_HTML);
    v.push_back(TOK_HTML);
    TestScan(s, v);

    f = File("test identifier", "{{ asdf }}");
    cout << f.Name() << endl;
    s = Scanner(f);
    v = vector<Token>();
    v.push_back(TOK_OPEN_EXPR);
    v.push_back(TOK_IDENT);
    v.push_back(TOK_CLOSE_EXPR);
    TestScan(s, v);

    f = File("test string lit", "{{ \"asdf\" }}");
    cout << f.Name() << endl;
    s = Scanner(f);
    v = vector<Token>();
    v.push_back(TOK_OPEN_EXPR);
    v.push_back(TOK_STRING);
    v.push_back(TOK_CLOSE_EXPR);
    TestScan(s, v);

    f = File("test keywords", "for {{ for in if end template }}");
    cout << f.Name() << endl;
    s = Scanner(f);
    v = vector<Token>();
    v.push_back(TOK_HTML);
    v.push_back(TOK_OPEN_EXPR);
    v.push_back(TOK_FOR);
    v.push_back(TOK_IN);
    v.push_back(TOK_IF);
    v.push_back(TOK_END);
    v.push_back(TOK_TEMPLATE);
    v.push_back(TOK_CLOSE_EXPR);
    TestScan(s, v);

    f = File("test identifiers", "{{ . a .b c.d asdf a123 24 #$* }}");
    cout << f.Name() << endl;
    s = Scanner(f);
    v = vector<Token>();
    v.push_back(TOK_OPEN_EXPR);
    v.push_back(TOK_DOT);
    v.push_back(TOK_IDENT);
    v.push_back(TOK_DOT);
    v.push_back(TOK_IDENT);
    v.push_back(TOK_IDENT);
    v.push_back(TOK_DOT);
    v.push_back(TOK_IDENT);
    v.push_back(TOK_IDENT);
    v.push_back(TOK_IDENT); // a123
    v.push_back(TOK_ERR); // 2
    v.push_back(TOK_ERR); // 4
    v.push_back(TOK_ERR); // #
    v.push_back(TOK_ERR); // $
    v.push_back(TOK_ERR); // *
    v.push_back(TOK_CLOSE_EXPR);
    TestScan(s, v);
}
