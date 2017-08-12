#include <iostream>
#include <sstream>

#include "ast.hpp"

using namespace std;
using namespace Template;

string Node::String() const {
    return "Node";
}

string Node::Render(SymTab stab, const Value &v) const {
    return "";
}

Document::~Document() {
    for (vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
        delete *iter;
    }
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

/* For */
For::For(int fr, Node *ea, int in, Node *arr, std::vector<Node *> inner) :
        fr(fr), each(ea), in(in), array(arr), nodes(inner) {}

For::~For() {
    delete each;
    delete array;
    for (vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
        delete *iter;
    }
}

string For::String() const {
    ostringstream ss;
    for (unsigned int i = 0; i < nodes.size(); i++) {
        ss << nodes.at(i)->String() << (i < nodes.size() ? ", " : "");
    }
    return "For(" + each->String() + "=>" + array->String() + ")" +
            "{" + ss.str() + "}";
}

string For::Render(SymTab stab, const Value& v) const {
    ostringstream ss;
    stab.Open();
    try {
        for (Value::ValueIter iter = v.Begin(); iter != v.End(); ++iter) {
            Value tmp;
            if (iter.Type() == Value::mapType) {
                tmp = iter.Second();
            } else {
                tmp = *iter;
            }
            stab.Insert(each->String(), tmp);
            for (unsigned int i = 0; i < nodes.size(); i++) {
                ss << nodes[i]->Render(stab, tmp);
            }
        }
    } catch (exception&) {
        /* TODO should handle the error so programmer isn't left twisting in the wind */
    };
    stab.Close();
    return ss.str();
}

string Html::String() const {
    return "Html";
}

string Html::Render(SymTab stab, const Value &v) const {
    return html;
}

string Ident::String() const {
    return name;
}

string Ident::Render(SymTab stab, const Value& v) const {
    Value res = stab.Lookup(name);
    if (res == Value()) {
        res = v.At(name);
    }
    if (res == Value()) {
        return "";
    }
    return res.String();
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
    Value v;
    try {
        v = table[ident];
    } catch(exception& e) {
        if (parent != NULL) {
            parent->Lookup(ident);
        }
    }
    return v;
}

void SymTab::Insert(std::string key, Value value) {
    table[key] = value;
}