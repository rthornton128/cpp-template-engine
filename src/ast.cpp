#include <iostream>
#include <sstream>

#include "ast.hpp"

using namespace std;
using namespace Template;

string Node::String() const {
    return "Node";
}

string Node::Render(SymTab stab, const Value &) const {
    return "Node";
}

void Document::Append(Node *n) {
    nodes.push_back(n);
}

string Document::String() const {
    ostringstream ss;
    ss << "[";
    for(unsigned int i = 0; i < nodes.size(); i++) {
        ss << nodes.at(i)->String() << (i+1 < nodes.size() ? ", " : "");
    }
    ss << "]";
    return "Document: " + ss.str();
}

string Document::Render(SymTab stab, const Value& v) const {
    ostringstream ss;
    stab.Insert(".", v);
    for(unsigned int i = 0; i < nodes.size(); i++) {
        ss << nodes[i]->Render(stab, v);
    }
    return ss.str();
}

string End::String() const {
    return "End";
}

string Expression::String() const {
    return "Expression";
}

string For::String() const {
    ostringstream ss;
    for (unsigned int i = 0; i < nodes.size(); i++) {
        ss << nodes.at(i)->String() << (i < nodes.size() ? ", " : "");
    }
    return "For(" + each->String() + "=>" + array->String() + ")" +
            "{" + ss.str() + "}";
}

string For::Render(SymTab stab, const Value &v) const {
    ostringstream ss;
    cout << "for loop" << endl;
/*
    string each = this->each->String();
    stab.Insert(each, Value());
    string ident = this->array->String();
    cout << "each:" + this->each->String() + " array:" + this->array->String() << endl;
    Value array = v;
    if (ident != ".") {
        array = v.Fetch(this->array->String());
    }

    cout << "array => " << array.String() << endl;

    for (Value::ValueIter iter = array.Begin(); iter != array.End(); iter++) {
        cout << "loop" << endl;
        stab.Insert(each, iter.Second());
        for (unsigned int i = 0; i < nodes.size(); i++) {
            ss << nodes[i]->Render(stab, array);
        }
    }*/
    return ss.str();
}

string Html::String() const {
    return "Html";
}

string Html::Render(SymTab, const Value &) const {
    return html;
}

string Ident::String() const {
    return name;
}

string Ident::Render(SymTab stab, const Value& v) const {
    cout << "ident:" << name << endl;
    Value res = stab.Lookup(name);
    cout << "check result" << endl;
    if (res == Value()) {
        cout << "Looks to have been null, try fetch" << endl;
        res = v.At(name);
    }
    cout << "result" << res.String() << endl;
    return res.String();
    return "";
}

string QualifiedIdent::String() const {
    return "QualifiedIdent: {" + lhs->String() + "." + rhs->String() + "}";
}

/** Symbol Table */
SymTab::SymTab(SymTab *parent) : parent(parent) {}
SymTab::~SymTab() {
    //if (parent != NULL) {
        //delete parent;
    //}
}

void SymTab::Close() {}

void SymTab::Open() {

}

Value SymTab::Lookup(const std::string &ident) {
    //map<string, Value>::const_iterator iter;
    cout << "Symtab::Lookup: " << ident << endl;
    Value v;
    try {
        cout << "lookup: trying" << endl;
        v = table[ident];
        cout << v.String() << endl;
    } catch(exception& e) {
        cout << "caught exception" << endl;
        if (parent != NULL) {
            cout << "looking up parent" << endl;
            parent->Lookup(ident);
        }
    }
    /*for (iter = table.begin(); iter != table.end(); ++iter) {
        if (iter->first == ident) {
            return iter->second;
        }
    }*/
    cout << "return result:" << v.String() << endl;
    return v;
}

void SymTab::Insert(std::string key, Value value) {
    table[key] = value;
}