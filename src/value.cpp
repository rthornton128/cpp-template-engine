//
// Created by rthornton on 01/06/17.
//

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "value.hpp"

using namespace Template;
using namespace std;

Value::Value(const ValueType& t) : _type(t) {
    switch (t) {
        case arrType:
            _vec = new vector<Value>;
            break;
        case mapType:
            _map = new map<std::string, Value>;
            break;
        case strType:
            _str = new string;
            break;
        default:
            _int = 0;
    }
}

Value::Value(const int& i) : _type(intType), _int(i) {}
Value::Value(const double& f) : _type(floatType), _float(f) {}

Value::Value(const string& s) : _type(strType){
    _str = new string(s);
}

Value::Value(const Value& other)  {
    _type = other._type;
    switch (_type) {
        case arrType:
            _vec = new vector<Value>(*other._vec);
            break;
        case mapType:
            _map = new map<string,Value>(*other._map);
            break;
        case strType:
            _str = new string(*other._str);
            break;
        case intType:
            _int = other._int;
            break;
        case floatType:
            _float = other._float;
            break;
        case nullType:
            break;
        default:
            throw runtime_error("unreachable");
    }
}

Value::~Value() {
    switch (_type) {
        case arrType:
            delete _vec;
            break;
        case mapType:
            delete _map;
            break;
        case strType:
            delete _str;
            break;
        default:
            return;
    }
}

/** Array */
void Value::Append(const int& i) { this->Append(Value(i)); }
void Value::Append(const double& i) { this->Append(Value(i)); }
void Value::Append(const std::string& i) { this->Append(Value(i)); }

void Value::Append(const Value& value) {
    if (this->_type != arrType) {
        throw out_of_range("may not append to non-array Value");
    }
    _vec->push_back(value);
}

Value& Value::operator[] (const size_t& i) {
    if (_type != arrType) {
        throw runtime_error("may not index non-array Value");
    }
    if (Length() <= i) {
        throw out_of_range("index out of range");
    }
    return (*_vec)[i];
}

/** General / Iterators */
Value::ValueIter Value::Begin() {
    switch (_type) {
        case arrType:
            return ValueIter(_vec->begin());
        case mapType:
            return ValueIter(_map->begin());
        default:
            throw runtime_error( "undefined to get iter of something not an "
                "array or map");
    }
}

Value::ValueIter Value::End() {
    switch (_type) {
        case arrType:
            return ValueIter(_vec->end());
        case mapType:
            return ValueIter(_map->end());
        default:
            throw runtime_error(
                    "undefined to get iter of something not an array or map");
    }
}

size_t Value::Length() {
    switch (_type) {
        case arrType:
            return _vec->size();
        case mapType:
            return _map->size();
        default:
            return 0;
    }
}

Value::ValueType Value::Type() { return _type; }

/** Maps */
void Value::Insert(const std::string& key, const Value& value) {
    if (_type != mapType) {
        throw runtime_error("may not use string as index of non-map");
    }
    _map->insert(pair<string,Value>(key, value));
}

Value& Value::At(const std::string& key) const {
    if (_type != mapType) {
        throw runtime_error("may not use string as index of non-map");
    }
    return _map->at(key);
}

Value& Value::operator[] (const string& key) {
    if (_type != mapType) {
        throw runtime_error("may not use string as index of non-map");
    }
    return (*_map)[key];
}

/** Getters */
int Value::Int() { return _int; }
double Value::Float() { return _float; }

std::string Value::String() {
    ostringstream ss;
    switch (_type) {
        case nullType:
            ss << "null";
            break;
        case arrType:
            ss << "{";
            for (unsigned int i = 0; i < _vec->size(); i++) {
                if (i != 0) {
                    ss << ", ";
                }
                ss << (*_vec)[i].String();
            }
            ss << "}";
            break;
        case intType:
            ss << _int;
            break;
        case floatType:
            ss << _float;
            break;
        case strType:
            ss << *_str;
            break;
        case mapType:
            ss << "[";
            map<string,Value>::iterator i;
            for (i = _map->begin(); i != _map->end(); ++i) {
                if (i != _map->begin()) {
                    ss  << ", ";
                }
                ss << i->first << ":" << i->second.String();
            }
            ss << "]";
            break;
    }
    return ss.str();
}

/** Operators */
bool Value::operator==(const int& other) { return _int == other; }
bool Value::operator==(const double& other) { return *this == Value(other); }

bool Value::operator==(const std::string& other) {
    return *this == Value(other);
}

bool Value::operator==(const Value &other) {
    if (_type != other._type) {
        return false;
    }

    switch (_type) {
        case nullType:
            return true;
        case intType:
            return _int == other._int;
        case floatType:
            return _float == other._float;
        case strType:
            return *_str == *other._str;
        case arrType:
            return _vec->size() == other._vec->size();
        case mapType:
            return _map->size() == other._map->size();
        default:
            throw runtime_error("unreachable");
    }
}

bool Value::operator!=(const int& other) { return *this != Value(other); }
bool Value::operator!=(const double& other) { return *this != Value(other); }

bool Value::operator!=(const std::string& other) {
    return *this != Value(other);
}

bool Value::operator!=(const Value &other) {
    if (_type != other._type) {
        return true;
    }

    switch (_type) {
        case nullType:
            return false;
        case intType:
            return _int != other._int;
        case floatType:
            return _float != other._float;
        case strType:
            return *_str != *other._str;
        case arrType:
            return _vec->size() != other._map->size();
        case mapType:
            return _map->size() != other._map->size();
        default:
            throw runtime_error("unreachable");
    }

}

Value& Value::operator=(const int& i) {
    switch (_type) {
        case arrType:
            delete _vec; break;
        case mapType:
            delete _map; break;
        case strType:
            delete _str; break;
        default:
            break;
    }
    _type = intType;
    _int = i;
    return *this;
}

Value& Value::operator=(const double& d) {
    if (_type != floatType) {
        throw runtime_error("assignment of int to Value that is not an integer");
    }

    _float = d;
    return *this;
}

Value& Value::operator=(const string& s) {
    if (_type != strType) {
        throw runtime_error("assignment of int to Value that is not an integer");
    }
    delete _str;
    _str = new string(s);
    return *this;
}

Value& Value::operator=(const Value &other) {
    if (this == &other) {
        return *this;
    }

    // cleanup previous pointers
    switch (_type) {
        case strType:
            delete _str;
        case arrType:
            delete _vec;
        case mapType:
            delete _map;
        default:
            break;
    }

    _type = other._type;
    switch (_type) {
        case intType:
            _int = other._int; break;
        case floatType:
            _float = other._float; break;
        case strType:
            _str = new string(*other._str); break;
        case arrType:
            _vec = new vector<Value>(*other._vec); break;
        case mapType:
            _map = new map<string,Value>(*other._map); break;
        default:
            break;
    }

    return *this;
}

/**
 * Value iterator
 */

Value::ValueIter::ValueIter(const map<string, Value>::iterator& iterator) :
        type(mapType) {
    _map_iter = new map<string,Value>::iterator(iterator);
}

Value::ValueIter::ValueIter(const vector<Value>::iterator& iterator) :
        type(arrType) {
    _vec_iter = new vector<Value>::iterator(iterator);
}

Value::ValueIter::ValueIter(const ValueIter& other) : type(other.type) {
    switch (type) {
        case arrType:
            _vec_iter = new vector<Value>::iterator(*other._vec_iter);
            break;
        case mapType:
            _map_iter = new map<string,Value>::iterator(*other._map_iter);
            break;
        default:
            return;
    }
}

Value::ValueIter::~ValueIter() {
    switch (type) {
        case arrType:
            delete _vec_iter; break;
        case mapType:
            delete _map_iter; break;
        default:
            return;
    }
}

Value::ValueType Value::ValueIter::Type() { return type; }

string Value::ValueIter::First() {
    if (type != mapType) {
        throw runtime_error("not a map iterator");
    }
    return (*_map_iter)->first;
};

Value& Value::ValueIter::Second() {
    if (type != mapType) {
        throw runtime_error("not a map iterator");
    }
    return (*_map_iter)->second;
};

Value::ValueIter& Value::ValueIter::operator= (const Value::ValueIter& other) {
    if (this == &other) {
        return *this;
    }

    if (type != other.type) {
        throw runtime_error("may not assign iterator of different types");
    }

    switch (type) {
        case arrType:
            delete _vec_iter;
            _vec_iter = new vector<Value>::iterator(*other._vec_iter);
            break;
        case mapType:
            delete _map_iter;
            _map_iter = new map<string,Value>::iterator(*other._map_iter);
            break;
        default:
            throw runtime_error("unreachable");
    }

    return *this;
}

bool Value::ValueIter::operator==(const Value::ValueIter& other) {
    switch (type) {
        case arrType:
            return *_vec_iter == *other._vec_iter;
        case mapType:
            return *_map_iter == *other._map_iter;
        default:
            return false;
    }
}

bool Value::ValueIter::operator!= (const Value::ValueIter& other) {
    switch (type) {
        case arrType:
            return *_vec_iter != *other._vec_iter;
        case mapType:
            return *_map_iter != *other._map_iter;
        default:
            return false;
    }
}

Value::ValueIter& Value::ValueIter::operator++() {
    if (type == arrType) {
        ++(*_vec_iter);
        return *this;
    }
    ++(*_map_iter);
    return *this;
}

Value::ValueIter& Value::ValueIter::operator++(int) { ++*this; }

Value::ValueIter& Value::ValueIter::operator--() {
    if (type == arrType) {
        --(*_vec_iter);
        return *this;
    }
    --(*_map_iter);
    return *this;
}

Value::ValueIter& Value::ValueIter::operator--(int) { --*this; }

Value& Value::ValueIter::operator*() {
    if (type != arrType) {
        throw runtime_error("may not take address of non-array iterator");
    }
    return *(*_vec_iter);
}
