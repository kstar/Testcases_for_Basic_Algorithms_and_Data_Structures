/***************************************************************************
                                hash.h  -  
                             -------------------
    begin                : Thu 13 Apr 2017 02:38:07 CDT
    copyright            : (c) 2017 by Akarsh Simha
    email                : akarsh.simha@kdemail.net
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/



#ifndef HASH_H
#define HASH_H

#include <vector>
#include <assert.h>
#include <cstdlib>

/**
 * @class HashMap
 * @short Implement a hash map with chaining, complete with resizing
 * @author Akarsh Simha <akarsh.simha@kdemail.net>
 */

#define DEFAULT_SIZEHINT 16
#define DEFAULT_MAX_LOAD_FACTOR 0.8f
#define DEFAULT_MIN_LOAD_FACTOR 0.2f
#define TABLE_RESIZE_FACTOR 2.0f

template <typename KeyType, typename ValueType> class HashMap {

    struct ChainNode {
        KeyType key;
        ValueType value;
        ChainNode *next;

        ChainNode( const KeyType &_key, const ValueType &_value ) : key( _key ), value( _value ), next( nullptr ) {}
    };

public:

    /**
     * @short Constructor
     */
    HashMap( size_t sizeHint = DEFAULT_SIZEHINT,
             float maxLoadFactor = DEFAULT_MAX_LOAD_FACTOR, float minLoadFactor = DEFAULT_MIN_LOAD_FACTOR ) :
    m_data( sizeHint, nullptr ), m_size(0), m_loadFactor( 0. ),
        m_maxLoadFactor( maxLoadFactor ), m_minLoadFactor( minLoadFactor ), m_minSize( sizeHint )
    { assert( maxLoadFactor < 1.0f && minLoadFactor > 0.0f && maxLoadFactor > minLoadFactor ); }

    /**
     * @short Destructor
     */
    ~HashMap() { clear(); }

    /**
     * @return the number of (key, value) pairs stored in the map
     */
    inline size_t size() const { return m_size; }

    /**
     * @return whether the map is empty
     */
    inline bool empty() const { return m_size == 0; }

    /**
     * @short Inserts / updates a (key, value) pair with the new value

     * @note If the key does not exist already, the (key, value) pair
     * is inserted. If the key exists, the corresponding value is
     * updated with the supplied value
     */
    void insert( const KeyType &key, const ValueType &value );

    /**
     * @short Returns the value at the given key if exists. Otherwise, fails catastrophically.
     */
    ValueType& at( const KeyType &key );

    /**
     * @short Returns whether an item with the given key exists
     */
    bool count( const KeyType &key ) const;

    /**
     * @short Erases the element with the given key. Otherwise, returns false.
     * @return True if the element was found and erased. False otherwise.
     */
    bool erase( const KeyType &key );

    /**
     * @short Erases all elements in the map
     */
    void clear();

    /**
     * @short self-tests the internals of the table for consistency
     * @note This tests that the load factor hasn't exceeded the
     * threshold, and that the claimed sizes are equal to the actual
     * sizes
     */
    bool checkTable() const;

private:

    void resize( size_t newTableSize );

    std::vector<ChainNode *> m_data;

    size_t m_size; // This is the number of (key, value) pairs inserted into the table
    size_t m_tableSize; // This is the size of the table, i.e. = m_data.size()

    float m_loadFactor;
    const float m_maxLoadFactor, m_minLoadFactor;
    const size_t m_minSize; // Table size not to fall below this size
    std::hash<KeyType> m_hash;
};

#include "hash.hpp"

#endif
