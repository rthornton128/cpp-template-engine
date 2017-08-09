//
// Created by rthornton on 08/06/17.
//

#include "template.h"

#include <iostream>

using namespace Lex;
using namespace std;

Template::~Template() {
    if (tree != NULL) {
        delete tree;
    }
}

void Template::Execute(ostream& os, string name, Value data) {
    // Find the template matching 'name' and call Render() with 'data' as
    // its value.
    cout << this->name << " vs " << name << endl;
    if (this->name == name) {
        cout << "template: match, rendering template: " << name << endl;
        SymTab stab;
        os << tree->Render(stab, data);
        return;
    }
    //for (unsigned int i = 0; i < templates.size(); i++) {

    //}
}

Template::Template(string name, string src) :
name(name) {
    File f = Lex::File(name, src);
    Parser parser = Lex::Parser();
    tree = parser.Parse(&f);

    cout << "parsetree: " << tree->String() << endl;
}

