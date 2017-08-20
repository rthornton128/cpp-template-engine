#include "value.hpp"
#include "assert.hpp"

using namespace Template;
using namespace std;

int main() {
    Value n;
    assert(n.String() == "null");
    Value n2 = n;
    assert(n2.String() == "null");

    Value i(24);
    assert(i.String() == "24");
    assert(i.Int() == 24);
    Value i2 = i;
    assert(i2.Int() == 24);

    // float equality is a terrible idea but it works in this instance
    Value f(3.14);
    assert(f.String() == "3.14");
    assert(f.Float() == 3.14);
    Value f2 = f;
    assert(f2.Float() == 3.14);

    Value s("Hello!");
    assert(s.String() == "Hello!");
    Value s2 = s;
    assert(s2.String() == "Hello!");

    Value a(Value::arrType);
    a.Append(42);
    a.Append(f);
    a.Append("myString");
    assert(a.Length() == 3);
    assert(a[0] == 42);
    assert(a[1] == f2);
    assert(a[2] == "myString");
    Value a2 = a;
    assert(a.Length() == 3);
    assert(a[0] == 42);
    assert(a[1] == 3.14);
    assert(a[2] == "myString");
    a2[0] = 8;
    assert(a[0] == 42 && a2[0] == 8);

    Value m(Value::mapType);
    m["test"] = 999;
    m.Insert("int", i);
    m.Insert("float", f);
    m["str"] = s;
    m.Insert("arr", a);
    assert(m.Length() == 5);
    assert(m["test"] == 999);
    assert(m.At("int") == 24);
    assert(m.At("float") == 3.14);
    assert(m.At("str") == "Hello!");
    assert(m.At("arr")[0] == 42);

    Value m2 = m;
    assert(m2.Length() == 5);
    assert(m2["int"] == 24);
    assert(m2["float"] == 3.14);
    assert(m2["str"] == "Hello!");
    assert(m["arr"][2] == a[2]);
    assert(m.Type() == m2.Type());

    assert_exception(n.At("foo"));
    assert_exception(a.At("foo"));
    assert_exception(m[0]);

    Value::ValueIter iter = a.Begin();
    assert(*iter == 42);
    iter = a.End();
    --iter;
    assert(*iter == "myString");
    --iter;
    assert(*iter == 3.14);

    for (Value::ValueIter x = m.Begin(); x != m.End(); ++x) {
        assert(x.Second() == m2[x.First()]);
    }

    return 0;
}