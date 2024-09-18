#include "../src/CacheEntry.h"
#include <chrono>
#include <iostream>

struct ControlClass 
{
    uint32_t value;
    std::string metadata;
};

struct TestClass 
    : public CacheEntry<std::string> 
{
    uint32_t value;
};

template <class Data>
auto generateData() {
    srand(108289);
    std::vector<Data> data(10000000);
    for (Data& d : data) 
    {
        d.value = rand();
    }
    return data;
}

template <class Data>
void benchmark(const char* const name, const Data& data, const bool print) {
    uint32_t running = 0;
    const auto before = std::chrono::system_clock::now();

    for (const auto& d : data)
    {
        running += d.value;
    }

    const auto after = std::chrono::system_clock::now();

    if (print) {
        std::cout << name << " took " << (after - before).count() << "ns and the result is " 
                  << running << std::endl;
    }
}

int main() {
    const auto control  = generateData<ControlClass>();
    const auto test = generateData<TestClass>();

    benchmark("With cold data in-line (original) ", control, false);
    benchmark("With cold data in-line (original) ", control, true);

    benchmark("With CacheEntry                   ", test, false);
    benchmark("With CacheEntry                   ", test, true);

    return 0;
}
