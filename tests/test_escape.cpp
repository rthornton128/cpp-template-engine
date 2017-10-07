#include "assert.hpp"
#include "escape.hpp"

using std::string;
using namespace Template;

int main() {
    string in[5] = {"\"", "\'", "&", "<", ">"};
    string out[5] = {"&quot", "&apos", "&amp", "&lt", "&gt"};

    for (int i = 0; i < 5; i++) {
        assert_eq(escapeHTML(in[i]), out[i]);
    }

    // Whole string test
    string html = "<!doctype><html><body foo=\"bar\" baz='narf'>&</body></html>";
    string expect = "&lt!doctype&gt&lthtml&gt&ltbody foo=&quotbar&quot baz=&aposnarf&apos&gt&amp&lt/body&gt&lt/html&gt";

    string got = escapeHTML(html);
    assert_eq(got, expect);
}
