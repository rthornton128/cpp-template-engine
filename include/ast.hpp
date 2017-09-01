#ifndef CPP_TEMPLATE_ENGINE_AST_H
#define CPP_TEMPLATE_ENGINE_AST_H

#include <string>
#include <vector>

#include "value.hpp"

namespace Template {
    class SymTab {
    public:
        explicit SymTab(SymTab* parent = NULL);
        ~SymTab();

        void Open();
        void Close();
        void Insert(std::string, Value);
        Value Lookup(const std::string& ident);

    private:
        SymTab* parent;
        std::map<std::string, Value> table;
    };

    class Node {
    public:
        virtual ~Node() = default;
        virtual std::string String() const = 0;
        virtual std::string Render(SymTab, const Value&) const;
    };

    class Document : public Node {
    public:
        Document() = default;
        ~Document();

        void Append(Node*);
        std::string String() const;
        std::string Render(SymTab, const Value&) const;

    private:
        std::vector<Node *> nodes;
    };

    class End : public Node {
    public:
        explicit End(int end) : end(end) {}
        std::string String() const;

    private:
        int end;
    };

    class Expression : public Node {
    public:
        std::string String() const;
        Expression(int open, int close) :
                open(open),
                close(close) {}

    private:
        int open, close;
    };

    class For : public Node {
    public:
        For(int fr, Node *ea, int in, Node *arr, std::vector<Node *> inner);
        ~For();

        std::string Render(SymTab stab, const Value&) const;
        std::string String() const;

    private:
        int fr, in;
        Node *each, *array;
        std::vector<Node *> nodes;
    };

    class Html : public Node {
    public:
        Html(int pos, std::string text) : pos(pos), html(text) {}

        std::string Render(SymTab stab, const Value&) const;
        std::string String() const;

    private:
        std::string html;
        int pos;
    };

    class Ident : public Node {
    public:
        Ident(int pos, std::string lit) : pos(pos), name(lit) {}

        void AddFilter(Node* node);
        std::string Render(SymTab stab, const Value& v) const;
        std::string String() const;

    private:
        int pos;
        std::string name;
        std::vector<Node*> filters;
    };

    class If : public Node {
    public:
        If(int posIf, Node*, std::vector<Node*>& inner);

        std::string String() const;
        std::string Render(SymTab stab, const Value& v) const;

    private:
        int posIf;
        Node* predicate;
        std::vector<Node*> inner;
    };

    class QualifiedIdent : public Node {
    public:
        QualifiedIdent(Ident *lhs, int dot, Ident *rhs) :
                lhs(lhs), dot(dot), rhs(rhs) {}
        ~QualifiedIdent() { delete lhs; delete rhs; }
        std::string String() const;

    private:
        Ident *lhs;
        int dot;
        Ident *rhs;
    };
}

#endif //CPP_TEMPLATE_ENGINE_AST_H
