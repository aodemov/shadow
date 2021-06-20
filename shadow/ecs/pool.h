#pragma once
#include <vector>
#include <type_traits>

namespace Shadow {
template <typename TComponent>
class Pool
{
private:
    std::vector<std::pair<uint32_t, TComponent>> mComponentList{}; // dense array of components
    std::vector<int32_t> mEntityIndices{}; // objectId to components index

    size_t size_ = 0; // Number of components (dense array size)
    size_t capacity_ = 0; // Number of objects (sparse array size)

public:
    Pool() = default;

    using iterator       = typename std::vector<std::pair<uint32_t, TComponent>>::iterator;
    using const_iterator = typename std::vector<std::pair<uint32_t, TComponent>>::const_iterator;

    iterator begin() { return mComponentList.begin(); }
    const_iterator begin() const { return mComponentList.begin(); }

    iterator end() { return mComponentList.begin() + size_; }
    const_iterator end() const { return mComponentList.begin() + size_; }

    std::pair<uint32_t, TComponent>& operator[](uint32_t index) {
        return mComponentList[index];
    }

    size_t size() const { return size_; }
    size_t capacity() const	{ return capacity_; }

    bool empty() const { return size_ == 0; }

    void clear() { size_ = 0; }

    void reserve(size_t size)
    {
        if (size > capacity_)
        {
            mEntityIndices.resize(size, -1);
            capacity_ = size;
        }
    }

    bool has(uint32_t entityId) const
    {
        return entityId < capacity_ &&
               mEntityIndices[entityId] < size_ &&
               mEntityIndices[entityId] >= 0;
    }

    void add(uint32_t entityId, TComponent& component)
    {
        if (!has(entityId))
        {
            if (entityId >= capacity_)
                reserve(entityId + 1);

            mComponentList.emplace_back(entityId, std::move(component));
            mEntityIndices[entityId] = size_;
            ++size_;
        }
    }

    void remove(uint32_t entityId)
    {
        if (has(entityId))
        {
            mComponentList[mEntityIndices[entityId]] = mComponentList[size_ - 1];
            mEntityIndices[entityId] = -1;
            --size_;
        }
    }

    TComponent& getComponent(uint32_t entityId) {
        return mComponentList[mEntityIndices[entityId]].second;
    }
};
}