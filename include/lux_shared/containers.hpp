#pragma once

#include <type_traits>
#include <forward_list>
#include <vector>
#include <string>
#include <array>
#include <queue>
#include <deque>
#include <unordered_map>
#include <unordered_set>
//
#include <lux_shared/slice.hpp>
#include <lux_shared/util/packer.hpp>
#include <lux_shared/util/identity.hpp>

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
template<typename K, typename V, typename Hasher>
using HashMap   = std::unordered_map<K, V, Hasher>;
template<typename V, typename Hasher>
using HashSet = std::unordered_set<V, Hasher>;
template<typename K, typename V>
using HashTable = HashMap<K, V, util::Identity<K>>;
template<typename K, typename V>
using VecMap = HashMap<K, V, util::Packer<K>>;
template<typename V>
using VecSet = HashSet<V, util::Packer<V>>;
template<typename T>
using AlignArr = std::aligned_storage_t<sizeof(T), alignof(T)>;

typedef std::string String;
