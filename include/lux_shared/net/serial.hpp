#pragma once

#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/net_order.hpp>

LUX_MAY_FAIL buff_sz_at_least(SizeT sz, U8 const* iter, U8 const* end);

template<typename T> struct HasStaticSz { bool static constexpr val = false; };
template<> struct HasStaticSz<bool> { bool static constexpr val = true; };
template<> struct HasStaticSz<char> { bool static constexpr val = true; };
template<> struct HasStaticSz<U8>   { bool static constexpr val = true; };
template<> struct HasStaticSz<U16>  { bool static constexpr val = true; };
template<> struct HasStaticSz<U32>  { bool static constexpr val = true; };
template<> struct HasStaticSz<U64>  { bool static constexpr val = true; };
template<> struct HasStaticSz<I8>   { bool static constexpr val = true; };
template<> struct HasStaticSz<I16>  { bool static constexpr val = true; };
template<> struct HasStaticSz<I32>  { bool static constexpr val = true; };
template<> struct HasStaticSz<I64>  { bool static constexpr val = true; };
template<> struct HasStaticSz<F32>  { bool static constexpr val = true; };
template<> struct HasStaticSz<F64>  { bool static constexpr val = true; };

template<typename T, SizeT len>
struct HasStaticSz<Arr<T, len>> {
    bool static constexpr val = HasStaticSz<T>::val;
};
template<typename T, I32 len>
struct HasStaticSz<Vec<T, len>> {
    static_assert(HasStaticSz<T>::val);
    bool static constexpr val = true;
};

template<typename T>
SizeT get_real_sz(T const& val);
template<typename K, typename Hasher>
SizeT get_real_sz(HashSet<K, Hasher> const&);
template<typename K, typename V, typename Hasher>
SizeT get_real_sz(HashMap<K, V, Hasher> const&);
template<typename T>
SizeT get_real_sz(DynArr<T> const&);

template<typename T>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, T*);
template<typename K, typename Hasher>
LUX_MAY_FAIL deserialize(U8 const**, U8 const*, HashSet<K, Hasher>*);
template<typename K, typename V, typename Hasher>
LUX_MAY_FAIL deserialize(U8 const**, U8 const*, HashMap<K, V, Hasher>*);
template<typename T>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, DynArr<T>*);
template<typename T, I32 len>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, Vec<T, len>*);
template<typename T, SizeT len>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, Arr<T, len>*);

template<typename T>
void serialize(U8** buff, T const&);
template<typename K, typename Hasher>
void serialize(U8** buff, HashSet<K, Hasher> const&);
template<typename K, typename V, typename Hasher>
void serialize(U8** buff, HashMap<K, V, Hasher> const&);
template<typename T>
void serialize(U8** buff, DynArr<T> const&);
template<typename T, I32 len>
void serialize(U8** buff, Vec<T, len> const&);
template<typename T, SizeT len>
void serialize(U8** buff, Arr<T, len> const&);

template<typename T>
SizeT get_real_sz(T const& val) {
    (void)val;
    static_assert(HasStaticSz<T>::val);
    return sizeof(T);
}

template<typename T>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, T* val) {
    static_assert(HasStaticSz<T>::val);
    if(buff_sz_at_least(sizeof(T), *buff, buff_end) != LUX_OK) return LUX_FAIL;
    net_order(val, (T const*)*buff);
    *buff += sizeof(T);
    return LUX_OK;
}

template<typename T>
void serialize(U8** buff, T const& val) {
    static_assert(HasStaticSz<T>::val);
    net_order((T*)*buff, &val);
    *buff += sizeof(T);
}

template<typename K, typename Hasher>
SizeT get_real_sz(HashSet<K, Hasher> const& val) {
    static_assert(HasStaticSz<K>::val);
    return val.size() * sizeof(K);
}

template<typename K, typename Hasher>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         HashSet<K, Hasher>* val) {
    static_assert(HasStaticSz<K>::val);
    U32 len;
    if(deserialize(buff, buff_end, &len) != LUX_OK ||
       buff_sz_at_least(len * sizeof(K), *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }
    for(Uns i = 0; i < len; ++i) {
        K key;
        (void)deserialize(buff, buff_end, &key);
        val->emplace(key);
    }
    return LUX_OK;
}

template<typename K, typename Hasher>
void serialize(U8** buff, HashSet<K, Hasher> const& val) {
    static_assert(HasStaticSz<K>::val);
    serialize(buff, (U32 const&)val.size());
    for(auto const& key : val) serialize(buff, key);
}

template<typename K, typename V, typename Hasher>
SizeT get_real_sz(HashMap<K, V, Hasher> const& val) {
    static_assert(HasStaticSz<K>::val);
    if constexpr(HasStaticSz<V>::val) {
        return val.size() * (sizeof(K) + sizeof(V));
    } else {
        SizeT sz = val.size() * sizeof(K);
        for(auto const& x : val) {
            sz += get_real_sz(x);
        }
        return sz;
    }
}

template<typename K, typename V, typename Hasher>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         HashMap<K, V, Hasher>* val) {
    static_assert(HasStaticSz<K>::val);
    U32 len;
    if(deserialize(buff, buff_end, &len) != LUX_OK) return LUX_FAIL;
    if constexpr(HasStaticSz<V>::val) {
        if(buff_sz_at_least(len * (sizeof(K) + sizeof(V)), *buff, buff_end)
               != LUX_OK) {
            return LUX_FAIL;
        }
        for(Uns i = 0; i < len; ++i) {
            K key;
            (void)deserialize(buff, buff_end, &key);
            (void)deserialize(buff, buff_end, &(*val)[key]);
        }
    } else {
        for(Uns i = 0; i < len; ++i) {
            K key;
            if(deserialize(buff, buff_end, &key)      != LUX_OK ||
               deserialize(buff, buff_end, &val[key]) != LUX_OK) {
                return LUX_FAIL;
            }
        }
    }
    return LUX_OK;
}

template<typename K, typename V, typename Hasher>
void serialize(U8** buff, HashMap<K, V, Hasher> const& val) {
    static_assert(HasStaticSz<K>::val);
    serialize(buff, (U32 const&)val.size());
    for(auto const& pair : val) {
        serialize(buff, pair.first);
        serialize(buff, pair.second);
    }
}

template<typename T>
SizeT get_real_sz(DynArr<T> const& val) {
    if constexpr(HasStaticSz<T>::val) {
        return val.size() * sizeof(T);
    } else {
        SizeT sz = 0;
        for(auto const& x : val) {
            sz += get_real_sz(x);
        }
        return sz;
    }
}

template<typename T>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, DynArr<T>* val) {
    U32 len;
    if(deserialize(buff, buff_end, &len) != LUX_OK) return LUX_FAIL;
    val->resize(len);
    if constexpr(HasStaticSz<T>::val) {
        if(buff_sz_at_least(len * sizeof(T), *buff, buff_end) != LUX_OK) {
            return LUX_FAIL;
        }
        for(Uns i = 0; i < len; ++i) {
            (void)deserialize(buff, buff_end, val->data() + i);
        }
    } else {
        for(Uns i = 0; i < len; ++i) {
            if(deserialize(buff, buff_end, val->data() + i) != LUX_OK) {
                return LUX_FAIL;
            }
        }
    }
    return LUX_OK;
}

template<typename T>
void serialize(U8** buff, DynArr<T> const& val) {
    serialize(buff, (U32 const&)val.size());
    for(auto const& x : val) {
        serialize(buff, x);
    }
}

template<typename T, I32 len>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         Vec<T, len>* val) {
    static_assert(HasStaticSz<T>::val);
    static_assert(len > 1);
    for(Uns i = 0; i < len; ++i) (void)deserialize(buff, buff_end, &val[i]);
    return LUX_OK;
}

template<typename T, I32 len>
void serialize(U8** buff, Vec<T, len> const& val) {
    static_assert(HasStaticSz<T>::val);
    static_assert(len > 1);
    for(Uns i = 0; i < len; ++i) serialize(buff, val[i]);
}

template<typename T, SizeT len>
LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end,
                         Arr<T, len>* val) {
    if constexpr(HasStaticSz<T>::val) {
        if(buff_sz_at_least(len * sizeof(T), *buff, buff_end) != LUX_OK) {
            return LUX_FAIL;
        }
        for(Uns i = 0; i < len; ++i) {
            (void)deserialize(buff, buff_end, val + i);
        }
    } else {
        for(Uns i = 0; i < len; ++i) {
            if(deserialize(buff, buff_end, val + i) != LUX_OK) return LUX_FAIL;
        }
    }
    return LUX_OK;
}

template<typename T, SizeT len>
void serialize(U8** buff, Arr<T, len> const& val) {
    for(Uns i = 0; i < len; ++i) serialize(buff, val[i]);
}
