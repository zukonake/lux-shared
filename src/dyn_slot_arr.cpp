#include <algorithm>
//
#include <lux_shared/macro.hpp>
#include <lux_shared/int.hpp>
#include <lux_shared/dyn_slot_arr.hpp>

SizeT DynSlotArr::emplace() {
    SizeT idx = std::find(slots.cbegin(), slots.cend(), false) - slots.cbegin();
    if(idx == slots.size()) {
        slots.emplace_back(true);
    } else {
        slots[idx] = true;
    }
    return idx;
}

void DynSlotArr::erase(SizeT idx) {
    LUX_ASSERT(idx < slots.size());
    slots[idx] = false;
}

void DynSlotArr::shrink_to_fit() {
    SizeT last_full_idx =
        std::find(slots.crbegin(), slots.crend(), true) - slots.crbegin();
    slots.resize(last_full_idx + 1);
    slots.shrink_to_fit();
}

bool DynSlotArr::contains(SizeT idx) const {
    if(idx >= slots.size()) return false;
    return slots[idx];
}

SizeT DynSlotArr::size() const {
    SizeT size = 0;
    for(Uns i = 0; i < slots.size(); ++i) {
        size += slots[i];
    }
    return size;
}

typename DynSlotArr::Iter DynSlotArr::begin() {
    return {(SizeT)(std::find(slots.begin(),
                              slots.end(), true) - slots.begin()), this};
}

typename DynSlotArr::Iter DynSlotArr::end() {
    return {slots.size(), this};
}

typename DynSlotArr::Iter& DynSlotArr::Iter::operator++() {
    idx = std::find(arr->slots.begin() + idx + 1,
                    arr->slots.end(), true) - arr->slots.begin();
    return *this;
}

bool DynSlotArr::Iter::operator!=(Iter const& other) {
    return idx != other.idx;
}

bool DynSlotArr::Iter::operator*() {
    return arr->contains(idx);
}
