#pragma once

#include <algorithm>
#include <vector>
//
#include <lux_shared/memory.hpp>

template<typename T, typename _Id = U32>
class SparseDynArr {
    public:
    typedef _Id Id;

    ~SparseDynArr();

    template<typename ...Args>
    Id emplace(Args &&...args);
    void erase(Id id);

    void shrink_to_fit();
    SizeT size() const;
    T&       operator[](Id id);
    T const& operator[](Id id) const;
    T*       at(Id id);
    T const* at(Id id) const;
    template<typename F>
    void foreach(F f);
    template<typename F>
    void foreach_while(F f);

    Id begin() const;
    Id end() const;
    Id next(Id id) const;
    bool contains(Id id);
    void free_slots();
    private:
    ///those are the slots that are for valid elements
    std::vector<bool> slots;
    ///those are slots that are not considered free for emplacing
    //@IMPROVE redundant size (slots == full)
    std::vector<bool> full;
    T*                data;
    SizeT             cap = 0;
};

template<typename T, typename _Id>
SparseDynArr<T, _Id>::~SparseDynArr() {
    if(cap > 0) {
        for(auto it = begin(); it != end(); it = next(it)) {
            erase(it);
        }
        lux_free<T>(data);
    }
}

template<typename T, typename _Id>
template<typename ...Args>
typename SparseDynArr<T, _Id>::Id SparseDynArr<T, _Id>::emplace(Args &&...args) {
    Id id = std::find(full.cbegin(), full.cend(), false) - full.cbegin();
    if(id == slots.size()) {
        if(cap < id + 1u) {
            if(cap == 0) {
                cap  = 1;
                data = lux_alloc<T>(cap);
            } else {
                cap *= 2;
                T* new_data = lux_alloc<T>(cap);
                for(auto it = begin(); it != end(); it = next(it)) {
                    new (new_data + it) T(std::move(data[it]));
                    data[it].~T();
                }
                lux_free<T>(data);
                data = new_data;
            }
        }
        slots.emplace_back(true);
        full.emplace_back(true);
    } else {
        slots[id] = true;
        full[id]  = true;
    }
    new (data + id) T(args...);
    return id;
}

template<typename T, typename _Id>
void SparseDynArr<T, _Id>::erase(Id id) {
    LUX_ASSERT(contains(id));
    data[id].~T();
    slots[id] = false;
}

template<typename T, typename _Id>
void SparseDynArr<T, _Id>::shrink_to_fit() {
    if(slots.size() == 0) {
        lux_free<T>(data);
        data = nullptr;
    } else {
        T* new_data = lux_alloc<T>(slots.size());
        for(auto it = begin(); it != end(); it = next(it)) {
            new (new_data + it) T(std::move(data[it]));
            data[it].~T();
        }
        lux_free<T>(data);
        data = new_data;
    }
    cap = slots.size();
    slots.shrink_to_fit();
    full.shrink_to_fit();
}

template<typename T, typename _Id>
SizeT SparseDynArr<T, _Id>::size() const {
    SizeT size = 0;
    for(auto it = begin(); it != end(); it = next(it)) {
        size += 1;
    }
    return size;
}

template<typename T, typename _Id>
T& SparseDynArr<T, _Id>::operator[](Id id) {
    LUX_ASSERT(contains(id));
    return data[id];
}

template<typename T, typename _Id>
T const& SparseDynArr<T, _Id>::operator[](Id id) const {
    LUX_ASSERT(contains(id));
    return data[id];
}

template<typename T, typename _Id>
T* SparseDynArr<T, _Id>::at(Id id) {
    if(!contains(id)) return nullptr;
    return &data[id];
}

template<typename T, typename _Id>
T const* SparseDynArr<T, _Id>::at(Id id) const {
    if(!contains(id)) return nullptr;
    return &data[id];
}

template<typename T, typename _Id>
template<typename F>
void SparseDynArr<T, _Id>::foreach(F f) {
    for(Id id = begin(); id != end(); ++id) {
        if(slots[id]) f(id);
    }
}

template<typename T, typename _Id>
template<typename F>
void SparseDynArr<T, _Id>::foreach_while(F f) {
    for(Id id = begin(); id != end(); ++id) {
        if(slots[id]) {
            if(!f(id)) break;
        }
    }
}

template<typename T, typename _Id>
typename SparseDynArr<T, _Id>::Id SparseDynArr<T, _Id>::begin() const {
    return (Id)(std::find(slots.begin(), slots.end(), true) - slots.begin());
}

template<typename T, typename _Id>
typename SparseDynArr<T, _Id>::Id SparseDynArr<T, _Id>::end() const {
    return (Id)slots.size();
}

template<typename T, typename _Id>
typename SparseDynArr<T, _Id>::Id SparseDynArr<T, _Id>::next(Id id) const {
    return std::find(slots.begin() + id + 1,
                     slots.end(), true) - slots.begin();
}

template<typename T, typename _Id>
bool SparseDynArr<T, _Id>::contains(Id id) {
    if(id >= slots.size()) return false;
    return slots[id];
}

template<typename T, typename _Id>
void SparseDynArr<T, _Id>::free_slots() {
    SizeT actual_sz = slots.size() -
        (std::find(slots.rbegin(), slots.rend(), true) - slots.rbegin());
    slots.resize(actual_sz);
    full = slots;
}
