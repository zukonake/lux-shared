#pragma once

#include <algorithm>
#include <vector>
//
#include <lux_shared/k_v_pair.hpp>
#include <lux_shared/memory.hpp>

template<typename T, typename _Id = U32>
class SparseDynArr {
    public:
    typedef _Id Id;
    template<typename V, typename Arr>
    struct IterT {
        Arr& arr;
        Id   id;
        KVPair<Id, V&> operator*() const { return {id, arr[id]}; }
        bool operator!=(IterT const& that) const { return id != that.id; }
        IterT& operator++() { id = arr.next(id); return *this; }
    };
    typedef IterT<T      , SparseDynArr<T, Id>      >  Iter;
    typedef IterT<T const, SparseDynArr<T, Id> const> CIter;

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

    Iter   begin();
    Iter   end();
    CIter cbegin() const;
    CIter cend() const;
    Id next(Id id) const;
    bool contains(Id id) const;
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
        for(auto pair : *this) erase(pair.k);
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
                for(Id id = 0; id != slots.size(); id++) {
                    if(!contains(id)) continue;
                    new (new_data + id) T(std::move(data[id]));
                    data[id].~T();
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
        for(Id id : *this) {
            if(!contains(id)) continue;
            new (new_data + id) T(std::move(data[id]));
            data[id].~T();
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
    for(auto it = cbegin(); it != cend(); ++it) {
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
typename SparseDynArr<T, _Id>::Iter SparseDynArr<T, _Id>::begin() {
    Iter it = {*this, 0};
    if(!contains(it.id)) ++it;
    return it;
}

template<typename T, typename _Id>
typename SparseDynArr<T, _Id>::Iter SparseDynArr<T, _Id>::end() {
    return {*this, (Id)slots.size()};
}

template<typename T, typename _Id>
typename SparseDynArr<T, _Id>::CIter SparseDynArr<T, _Id>::cbegin() const {
    CIter it = {*this, 0};
    if(!contains(it.id)) ++it;
    return it;
}

template<typename T, typename _Id>
typename SparseDynArr<T, _Id>::CIter SparseDynArr<T, _Id>::cend() const {
    return {*this, (Id)slots.size()};
}

template<typename T, typename _Id>
typename SparseDynArr<T, _Id>::Id SparseDynArr<T, _Id>::next(Id id) const {
    while(!contains(id) && id < slots.size()) id++;
    return id;
}

template<typename T, typename _Id>
bool SparseDynArr<T, _Id>::contains(Id id) const {
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
