#pragma once

#include <type_traits>
#include <forward_list>
#include <vector>
#include <array>
#include <queue>
#include <deque>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
//
#include <lux_shared/slice.hpp>
#include <lux_shared/bit_arr.hpp>
#include <lux_shared/sparse_dyn_arr.hpp>
#include <lux_shared/util/packer.hpp>
#include <lux_shared/util/identity.hpp>

template<typename T>
struct LuxHash;

template<typename T>
using DynArr = std::vector<T>;
template<typename T, std::size_t len>
using Arr = T[len];
template<typename T>
using Queue = std::queue<T>;
template<typename T>
using Deque = std::deque<T>;
template<typename T>
using List = std::forward_list<T>;
template<typename K, typename V>
using SortMap = std::map<K, V>;
template<typename V>
using SortSet = std::unordered_set<V>;
template<typename V, typename Hasher>
using AssocSet = std::unordered_set<V, Hasher>;
template<typename K, typename V, typename Hasher>
using AssocMap = std::unordered_map<K, V, Hasher>;
template<typename K, typename V>
using IdMap = AssocMap<K, V, util::Identity<K>>;
template<typename K, typename V>
using IdSet = AssocSet<K, util::Identity<K>>;
template<typename K, typename V>
using HashMap = AssocMap<K, V, LuxHash<K>>;
template<typename K, typename V>
using HashSet = AssocSet<K, LuxHash<K>>;
template<typename K, typename V>
using VecMap = AssocMap<K, V, util::Packer<K>>;
template<typename V>
using VecSet = AssocSet<V, util::Packer<V>>;
