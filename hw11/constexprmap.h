#pragma once

#include <array>
#include <type_traits>
#include <utility>
#include <stdexcept>


/**
 * Compiletime generic lookup map.
 *
 * storage: std::array
 * search-time: linear
 *
 * when the compiler errors, make sure no duplicate keys exist,
 * and that existing keys are requested.
 * exceptions are thrown, which lead to compiler errors otherwise
 *
 * The message may be: "error: ‘*0u’ is not a constant expression"
 * -> nonexistant key
 */
template<typename K, typename V, size_t count>
class CexprMap {
public:
    using key_type = K;
    using value_type = V;

    template<class... Entries>
    constexpr CexprMap(Entries&&... entries){/*TODO*/}

    /**
     * Entry count.
     */
    constexpr size_t size() const {
    }

    /**
     * Is the key in the map?
     */
    constexpr bool contains(const K &key) const {
    }

    /**
     * Get a key's value
     */
    constexpr const V &get(const K &key) const {
    }

    /**
     * Get a key's value by map[key].
     */
    constexpr const V &operator [](const K &key) const {
    }

private:
    /**
     * Checks if keys are duplicated.
     * Throws std::invalid_argument on duplicate key.
     */
    constexpr void verify_no_duplicates() const {
    }

    /**
     * Returns the iterator matching key from the array.
     *  - `values.end()` if the key is not found.
     */
    constexpr auto find(const K &key) const {
    }

    /**
     * The entries associated with this map.
     */
    std::array<std::pair<K, V>, count> values;
};


/**
 * Returns CexprMap, a compiletime lookup table from
 * K to V, where all entries of K must be unique.
 *
 * usage: constexpr auto bla = create_cexpr_map<type0, type1>(entry0, entry1, ...);
 */
template<typename K, typename V, typename... Entries>
constexpr auto create_cexpr_map(Entries&&... entry) {
}

/**
 * Template deduction guide to deduce the Key-Value types
 * for the CexprMap from the paired entries passed.
 *
 * usage: constexpr CexprMap boss{std::pair{k0, v0}, std::pair{k1, v1}, ...};
 *
 * Uses requires-clause to check if all entries have the same type.
 */
template<typename Entry, typename... Rest>
requires std::conjunction_v<std::is_same<Entry, Rest>...>
CexprMap(Entry, Rest&&...) -> /* TODO */;
