#pragma once
#include <unordered_map>
#include <memory>

template <class ColdData>
class SplitData {
  inline static std::unordered_map<SplitData const*, std::unique_ptr<ColdData>> coldDataMap;

public:
  SplitData()
  {
    coldDataMap[this] = nullptr;
  }

  template <class... Args>
  void initColdData(Args&&... args)
  {
    coldDataMap[this] = std::make_unique<ColdData>(std::forward<Args>(args)...);
  }

  ~SplitData() 
  {
    coldDataMap.erase(this);
  }

  explicit SplitData(SplitData&& other)
  { 
    (*this) = std::move(other); 
  }
  
  SplitData& operator=(SplitData&& other) {
    coldDataMap[this] = std::move(coldDataMap[&other]);
    coldDataMap.erase(&other);
    return *this;
  }

  SplitData(SplitData const&) = delete;
  SplitData& operator=(SplitData const&) = delete;

  ColdData& get() noexcept
  {
    return *coldDataMap[this];
  }

  ColdData const& get() const noexcept
  {
    return *coldDataMap[this];
  }
};
