#include "../src/cache_entry.h"
#include <cstddef>

#define NUM_OF_OBJS 1000000

struct test_class
{
    cache_entry<bool> field0;
    cache_entry<int> field1;
    cache_entry<float> field2;
    cache_entry<float> field3;
    cache_entry<double> field4;
    cache_entry<double> field5;
    cache_entry<std::string> field6;
    cache_entry<std::string> field7;
};

struct control_class
{
    bool field0;
    int field1;
    float field2;
    float field3;
    double field4;
    double field5;
    std::string field6;
    std::string field7;
};

void benchmark_test()
{
    test_class test[NUM_OF_OBJS];
    for (size_t i = 0; i < NUM_OF_OBJS; i++)
    {
        test[i].field1.set(i);
    }
    int sum = 0, cur;
    for (size_t i = 0; i < NUM_OF_OBJS; i++)
    {
        test[i].field1.get(cur);
        sum += cur;
    }
}

void benchmark_control()
{
    control_class control[NUM_OF_OBJS];
    for (size_t i = 0; i < NUM_OF_OBJS; i++)
    {
        control[i].field1 = i;
    }
    int sum = 0, cur;
    for (size_t i = 0; i < NUM_OF_OBJS; i++)
    {
        sum += control[i].field1;
    }
}

int main(int argc, char* argv[])
{
    if (strcmp(argv[0], "test") == 0)
    {
        benchmark_test();
    }
    else 
    {
        benchmark_control();
    }

    return 0;
}