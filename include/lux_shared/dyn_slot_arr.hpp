#pragma once

#include <vector>
//
#include <lux_shared/int.hpp>

class DynSlotArr {
    public:
    struct Iter {
        public:
        Iter& operator++();
        bool operator!=(Iter const& other);
        bool operator*();

        SizeT idx;
        DynSlotArr* arr;
    };
    friend class Iter;
    friend class CIter;

    SizeT emplace();
    void  erase(SizeT idx);

    void shrink_to_fit();

    bool contains(SizeT idx) const;
    SizeT size() const;

    Iter begin();
    Iter end();
    private:
    std::vector<bool> slots;
};
