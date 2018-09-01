#pragma once

#include <unordered_map>
//
#include <lux/util/identity.hpp>

template<typename K, typename V>
using HashTable = std::unordered_map<K, V, util::Identity<K>>;
