#include <cassert>
#include <string>
#include <utility>
#include "../src/CacheEntry.h"


struct ColdData
{
    ColdData(bool f0, float f1, double f2, std::string&& f3)
        : field0(f0), field1(f1), field2(f2), field3(std::move(f3)) {}
    bool field0;
    float field1;
    double field2;
    std::string field3;
};

class TestClass
    : public CacheEntry<ColdData> 
{
public:
    template <class... Args>
    TestClass(int v, Args&&... args)
        : value(v), CacheEntry(std::forward<Args>(args)...) {}

    int value;
};

int main()
{
    TestClass t0(10, false, 1.0, 2.0, "Hello World");

    assert(sizeof(t0) == sizeof(int));

    assert(t0.value == 10);
    t0.value = 20;
    assert(t0.value == 20);

    assert(t0.getColdData().field0 == false);
    assert(t0.getColdData().field3 == "Hello World");

    t0.getColdData().field1 = 3.0;
    assert(t0.getColdData().field1 == 3.0);

    return 0;
}