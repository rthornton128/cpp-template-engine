#include "assert.hpp"
#include "file.hpp"
#include "position.hpp"

using namespace Template;

int main() {
    File f("test0", "src");

    // test basics
    assert_eq(f.HasErrors(), false);
    assert_eq(f.Name(), "test0");
    assert_eq(f.Source(), "src");

    // test position
    f.AddLine(1);
    Position p0 = f.Pos(0);
    Position p1 = f.Pos(2);
    assert_eq(p0.Column(), 0);
    assert_eq(p0.Line(), 1);
    assert_eq(p0.Name(), "test0");
    assert_eq(p1.Column(), 1);
    assert_eq(p1.Line(), 2);
    assert_eq(p1.Name(), "test0");

    // test error list
    f.AddError(0, "my error");
    assert_eq(f.HasErrors(), true);
}