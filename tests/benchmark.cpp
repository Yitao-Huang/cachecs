#include "../src/CacheEntry.h"
#include <cstddef>
#include <chrono>
#include <cstdint>
#include <iostream>

#define NUM_OF_OBJS 100000

struct ColdData
{
    ColdData(bool f0, float f1, double f2, std::string&& f3, std::string&& f4)
        : field0(f0), field1(f1), field2(f2), field3(std::move(f3)), field4(std::move(f4)) {}
    bool field0;
    float field1;
    double field2;
    std::string field3;
    std::string field4;
};

class TestClass
    : public CacheEntry<int, ColdData> 
{
public:
    TestClass(): CacheEntry<int, ColdData>(0) {}
};

struct ControlClass
{
    bool field0;
    int field1;
    float field2;
    double field3;
    std::string field4;
    std::string field5;
};

uint64_t benchmark_test()
{
    TestClass test[NUM_OF_OBJS];
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < NUM_OF_OBJS; i++)
    {
        test[i].getHotData() = i;
    }
    uint64_t sum = 0;
    for (size_t i = 0; i < NUM_OF_OBJS; i++)
    {
        sum += test[i].getHotData();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Time spent: " << duration.count() << " ns" << std::endl;
    return sum;
}

uint64_t benchmark_control()
{
    ControlClass control[NUM_OF_OBJS];
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < NUM_OF_OBJS; i++)
    {
        control[i].field1 = i;
    }
    uint64_t sum = 0;
    for (size_t i = 0; i < NUM_OF_OBJS; i++)
    {
        sum += control[i].field1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Time spent: " << duration.count() << " ns" << std::endl;
    return sum;
}

int main(int argc, char* argv[])
{
    uint64_t res;
    std::chrono::duration<long long, std::ratio<1, 1000>> duration;
    if (strcmp(argv[0], "test") == 0)
    {
        res = benchmark_test();
    }
    else 
    {
        res = benchmark_control();
    }

    std::cout << "Result: " << res << std::endl;

    return 0;
}