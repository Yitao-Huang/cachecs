#include <cassert>
#include "../src/cache_entry.h"

struct test_class
{
    cache_entry<bool> field0;
    cache_entry<int> field1;
    cache_entry<float> field2;
    cache_entry<double> field3;
    cache_entry<std::string> field4;
};

int main()
{
    test_class t[2];

    t[0].field0.set(true);
    t[1].field0.set(false);
    bool f0;
    t[0].field0.get(f0);
    assert(f0);
    t[1].field0.get(f0);
    assert(!f0);

    t[0].field1.set(20);
    t[1].field1.set(50);
    int f1;
    t[0].field1.get(f1);
    assert(f1 == 20);
    t[1].field1.get(f1);
    assert(f1 == 50);

    t[0].field4.set("Hello");
    t[1].field4.set("World");
    std::string f4;
    t[0].field4.get(f4);
    assert(f4 == "Hello");
    t[1].field4.get(f4);
    assert(f4 == "World");

    return 0;
}