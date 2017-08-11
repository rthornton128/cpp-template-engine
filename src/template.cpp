//
// Created by rthornton on 08/06/17.
//

#include "template.hpp"

#include <iostream>

using namespace Template;
using namespace std;

Template::Template::~Template() {
    if (tree != NULL) {
        delete tree;
    }
}

void Template::Template::Execute(ostream& os, string name, Value data) {
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

Template::Template::Template(string name, string src) : name(name) {
    File f = File(name, src);
    Parser parser = Parser();
    tree = parser.Parse(&f);

    cout << "parsetree: " << tree->String() << endl;
}

