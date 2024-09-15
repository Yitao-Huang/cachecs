#include <cassert>
#include <string>
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
    : public CacheEntry<int, ColdData> 
{
public:
    TestClass(): CacheEntry<int, ColdData>(10) {}
};

int main()
{
    TestClass t;

    assert(t.getHotData() == 10);
    t.getHotData() = 20;
    assert(t.getHotData() == 20);

    t.initColdData(false, 1.0, 2.0, "Hello World");
    assert(t.getColdData().field0 == false);
    assert(t.getColdData().field3 == "Hello World");

    t.getColdData().field1 = 3.0;
    assert(t.getColdData().field1 == 3.0);

    return 0;
}