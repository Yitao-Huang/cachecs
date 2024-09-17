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
    : public CacheEntry<int, ColdData> 
{
public:
    TestClass(): CacheEntry<int, ColdData>(10) {}
};

class TestClassCRTP
    : public CacheEntryExternal<TestClassCRTP, ColdData> 
{
public:
    template <class... Args>
    TestClassCRTP(Args&&... args): CacheEntryExternal(std::forward<Args>(args)...) {}

    int value = 10;
};

int main()
{
    TestClass t0;

    assert(sizeof(t0) == sizeof(int));

    assert(t0.getHotData() == 10);
    t0.getHotData() = 20;
    assert(t0.getHotData() == 20);

    t0.initColdData(false, 1.0, 2.0, "Hello World");
    assert(t0.getColdData().field0 == false);
    assert(t0.getColdData().field3 == "Hello World");

    t0.getColdData().field1 = 3.0;
    assert(t0.getColdData().field1 == 3.0);

    TestClassCRTP t1(false, 1.0, 2.0, "Hello World");
    assert(t1.getHotData().value == 10);
    t1.getHotData().value = 20;
    assert(t1.getHotData().value == 20);

    return 0;
}