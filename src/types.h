#include <cstddef>
#include <string>

#define INVALID_TYPE_ID -1

template<class T> inline constexpr size_t get_type() { return INVALID_TYPE_ID; }

/* supported types */
template<> inline constexpr size_t get_type<bool>() { return 0; }
template<> inline constexpr size_t get_type<int>() { return 1; }
template<> inline constexpr size_t get_type<float>() { return 2; }
template<> inline constexpr size_t get_type<double>() { return 3; }
template<> inline constexpr size_t get_type<uint64_t>() { return 4; }
template<> inline constexpr size_t get_type<uint16_t>() { return 5; }
template<> inline constexpr size_t get_type<uint8_t>() { return 6; }
template<> inline constexpr size_t get_type<char>() { return 7; }
template<> inline constexpr size_t get_type<std::string>() { return 8; }
template<> inline constexpr size_t get_type<void*>() { return 9; }

/* need to be manually updated every time when there's a new type */
#define NUM_SUPPORTED_TYPES 10