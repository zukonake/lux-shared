#pragma once

#include <unordered_map>
//
#include <lux/util/packer.hpp>

template<typename K, typename V>
using PosMap = std::unordered_map<K, V, util::Packer<K>>;
