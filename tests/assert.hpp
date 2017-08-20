#ifndef HTML_TEMPLATE_ASSERT_H_H
#define HTML_TEMPLATE_ASSERT_H_H

#define assert_out cerr << "assert on line " << __LINE__ << " failed"
#define assert(x) { if (!(x)) { assert_out << endl; } }
#define assert_eq(x,y) { if ((x) != (y)) { assert_out << "(EQ) expected: " << (y) << ", got: " << (x) << endl; } }
#define assert_neq(x,y) { if ((x) == (y)) { assert_outr << "(NEQ) expected:" << (y) << ", got:" << (x) << endl; } }
#define assert_exception(x) { try { x; assert_out; } catch (exception& e) { }}

#endif //HTML_TEMPLATE_ASSERT_H_H
