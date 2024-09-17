#pragma once
#include <unordered_map>
#include <memory>

template <class HotData, class ColdData>
class CacheEntry
{
    inline static std::unordered_map<CacheEntry const*, std::unique_ptr<ColdData>> coldDataMap;
    HotData hotData;

public:
    template <class... Args>
    CacheEntry(Args&&... args): hotData(std::forward<Args>(args)...) 
    {
        coldDataMap[this] = nullptr;
    }

    template <class... Args>
    void initColdData(Args&&... args)
    {
        coldDataMap[this] = std::make_unique<ColdData>(std::forward<Args>(args)...);
    }

    ~CacheEntry()
    {
        coldDataMap.erase(this);
    }

    explicit CacheEntry(CacheEntry&& other)
    { 
        (*this) = std::move(other); 
    }
    
    CacheEntry& operator=(CacheEntry&& other) 
    {
        coldDataMap[this] = std::move(coldDataMap[&other]);
        coldDataMap.erase(&other);
        hotData = std::move(other.hotData);
        return *this;
    }

    ColdData& getColdData() noexcept
    {
        return *coldDataMap[this];
    }

    ColdData const& getColdData() const noexcept
    {
        return *coldDataMap[this];
    }

    HotData& getHotData() noexcept
    {
        return hotData;
    }

    HotData const& getHotData() const noexcept
    {
        return hotData;
    }
};