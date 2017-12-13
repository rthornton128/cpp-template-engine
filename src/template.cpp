//
// Created by rthornton on 08/06/17.
//

#include "template.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace Template;
using namespace std;

Template::Template::Template() {}

Template::Template::Template(string name, string src) : name(name) {
    File f = File(name, src);
    Parser parser = Parser();
    tree = parser.Parse(&f);

    cout << "parsetree: " << tree->String() << endl;
}

Template::Template::~Template() {
    delete tree;
    vector<Template*>::iterator t;
    for (t = templates.begin(); t != templates.end(); ++t) {
        delete *t;
    }
}

ErrorList& Template::Template::Errors() {
    return errors;
}

void Template::Template::Append(Template* t) {
    this->templates.push_back(t);
}

void Template::Template::Execute(ostream& os, const string& name, Value& data) {
    // Find the template matching 'name' and call Render() with 'data' as
    // its value.
    if (this->name == name) {
        SymTab stab;
        os << tree->Render(stab, data);
        return;
    }
    vector<Template*>::iterator t;
    for (t = templates.begin(); t != templates.end(); ++t) {
        (*t)->Execute(os, name, data);
    }
}

/* Parse the file list into a template */
Template::Template* Template::ParseFiles(std::vector<std::string>& files) {
    vector<string>::iterator i;
    Template *t = new Template();
    for (i = files.begin(); i != files.end(); ++i) {
        ifstream f(*i);
        stringstream buf;
        if (f.is_open()) {
            buf << f.rdbuf();
        }
        f.close();
        t->Append(new Template(*i, buf.str()));
    }
    return t;
}

/* Throws an exception if templates fail to load with the expectation that the program will be unable to
 * run without the template(s) present. */
Template::Template* Template::Must(Template* t) {
    if (t->Errors().NErrors()) {
        throw runtime_error("failed to parse mandatory template");
    }
}
