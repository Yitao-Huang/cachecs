#include "SplitData.h"

template <class HotData, class ColdData>
class CacheEntry
    : private SplitData<ColdData>
{
public:
    template <class... Args>
    CacheEntry(Args&&... args): hotData(std::forward<Args>(args)...) {}

    template <class... Args>
    void initColdData(Args&&... args)
    {
        SplitData<ColdData>::initColdData(std::forward<Args>(args)...);
    }

    ColdData& getColdData() noexcept
    {
        return SplitData<ColdData>::get();
    }

    ColdData const& getColdData() const noexcept
    {
        return SplitData<ColdData>::get();
    }

    HotData& getHotData() noexcept
    {
        return hotData;
    }

    HotData const& getHotData() const noexcept
    {
        return hotData;
    }

    ~CacheEntry() = default;

private:
    HotData hotData;
};