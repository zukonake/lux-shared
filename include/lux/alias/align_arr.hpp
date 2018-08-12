#pragma once

#include <type_traits>

template<typename T>
using AlignArr = std::aligned_storage_t<sizeof(T), alignof(T)>;
