//
// Created by rthornton on 08/06/17.
//

#ifndef VALUE_H
#define VALUE_H

#include <map>
#include <iostream>
#include <string>
#include <vector>

class Value {

public:
    enum ValueType {
        nullType,
        arrType,
        intType,
        floatType,
        strType,
        mapType,
    };

    class ValueIter {
    public:
        explicit ValueIter(const std::map<std::string, Value>::iterator& iterator);
        explicit ValueIter(const std::vector<Value>::iterator& iterator);
        ValueIter(const ValueIter&);
        ~ValueIter();

        ValueType Type();

        std::string First();
        Value& Second();

        ValueIter& operator= (const ValueIter& other);
        bool operator==(const ValueIter& other);
        bool operator!=(const ValueIter& other);
        Value& operator*();
        ValueIter& operator++();
        ValueIter& operator++(int);
        ValueIter& operator--();
        ValueIter& operator--(int);

    private:
        ValueType type;
        union {
            std::map<std::string, Value>::iterator* _map_iter;
            std::vector<Value>::iterator* _vec_iter;
        };
    };

    explicit Value(const ValueType& t = nullType);
    explicit Value(const int& i);
    explicit Value(const double& f);
    explicit Value(const std::string& s);
    Value(const Value& v);
    ~Value();

    // Array
    void Append(const int& i);
    void Append(const double& i);
    void Append(const std::string& i);
    void Append(const Value& value);
    Value& operator[] (const size_t& i);

    // General
    size_t Length();
    ValueType Type();

    // Iterator for array and map
    ValueIter Begin();
    ValueIter End();

    // Map
    void Insert(const std::string& key, const Value& value);
    Value& At(const std::string& key) const;
    Value& operator[] (const std::string& key);

    int Int();
    double Float();
    std::string String();

    // Operators
    bool operator==(const int& other);
    bool operator==(const double& other);
    bool operator==(const std::string& other);
    bool operator==(const Value& other);
    bool operator!=(const int& other);
    bool operator!=(const double& other);
    bool operator!=(const std::string& other);
    bool operator!=(const Value& other);
    Value& operator= (const int& i);
    Value& operator= (const double& d);
    Value& operator= (const std::string& s);
    Value& operator= (const Value& other);

private:
    ValueType _type;
    union {
        int _int;
        double _float;
        std::vector<Value>* _vec;
        std::string* _str;
        std::map<std::string, Value>* _map;
    };
};

#endif //VALUE_H
