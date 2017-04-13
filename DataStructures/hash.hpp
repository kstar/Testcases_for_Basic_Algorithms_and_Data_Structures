/***************************************************************************
                               hash.hpp  -
                             -------------------
    begin                : Thu 13 Apr 2017 04:29:08 CDT
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



#ifndef HASH_HPP
#define HASH_HPP

#include <utility>
#include <iostream>


/**
 * Instructions:
 *
 * Implement hashing with chaining. The hash table must resize if the
 * load factor exceeds the max load factor, or falls below the min
 * load factor.
 *
 * The map's data is stored in a vector, m_data
 *
 * The entries of the vector are pointers to ChainNode *, a struct
 * that represents a linked-list node. struct ChainNode is defined as
 *
 *    struct ChainNode {
 *          KeyType key;
 *          ValueType value;
 *          ChainNode *next;
 *          ChainNode( const KeyType &_key, const ValueType &_value ) : key( _key ), value( _value ), next( nullptr ) {}
 *    };
 *
 * So m_data is declared as std::vector<ChainNode *> m_data
 *
 * Use m_hash( key ) to compute hashes (this is an object of std::hash<KeyType>)
 *
 * With every operation, a few numbers must be updated:
 *    1) the size of the map ( = number of entries ) : size_t m_size
 *    2) the size of the table ( = size of vector m_data ) : size_t m_tableSize
 *    3) the load factor of the table : float m_loadFactor
 *
 * If the load factor exceeds the threshold given in m_maxLoadFactor,
 * or falls below m_minLoadFactor, the table must resize() by
 * TABLE_RESIZE_FACTOR. The private method resize( size_t newTableSize
 * ) is to take care of this process. However, the data vector must
 * not be resized to be smaller than m_minSize
 *
 */

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    // If the key does not exist in the map, insert the key with the value
    // If the key already exists in the map, update its value with the value supplied
    // If the load factor exceeds beyond const float m_thresholdLoadFactor, call resize()
}

template <typename KeyType, typename ValueType>
ValueType& HashMap<KeyType, ValueType>::at( const KeyType &key ) {
    // Return a reference to the value corresponding to the given key
    // assert( false ) if the key does not exist
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::count( const KeyType &key ) const {
    // Return whether key exists in the map or not
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::erase( const KeyType &key ) {
    if ( !count( key ) )
        return false;

    // Write code to remove the key from the given map. If the table
    // size falls below the appropriate threshold, resize()

    return true;
}


template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::clear() {
    // Erase all elements in the table and reinitialize the table with null pointers
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::resize( size_t newTableSize ) {
    if ( newTableSize < m_minSize )
        newTableSize = m_minSize;

    // Write code to resize the table to the newTableSize
}


/*
 * This is a pre-implemented method to check that the load balancing
 * and removal is being done correctly.
 *
 */
template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::checkTable() const {
    if ( m_data.size() != m_tableSize ) {
        std::cerr << "Wrong m_tableSize" << std::endl;
        return false; // wrong m_tableSize
    }

    size_t counter = 0;
    for ( size_t i = 0; i < m_data.size(); ++i ) {
        ChainNode *head = m_data[i];
        while ( head ) {
            ++counter;
            size_t hash = m_hash( head->key )%( m_tableSize );
            if ( hash != i ) {
                std::cerr << "Key is assigned to wrong hash bucket." << std::endl;
                return false; // wrong bin
            }
            head = head->next;
        }
    }
    if ( counter != m_size ) {
        std::cerr << "Number of elements " << counter << " is not equal to m_size = " << m_size << std::endl;
        return false; // wrong m_size / items not removed from the chain by erase()
    }

    if ( m_loadFactor != float( m_size )/float( m_tableSize ) ) {
        std::cerr << "m_loadFactor not maintained correctly." << std::endl;
        return false; // m_loadFactor not maintained correctly
    }

    if ( m_tableSize < m_minSize ) {
        std::cerr << "m_tableSize smaller than minimum m_minSize." << std::endl;
        return false; // table size is smaller than minimum
    }

    if ( m_loadFactor > m_maxLoadFactor || ( m_loadFactor < m_minLoadFactor && m_tableSize != m_minSize ) ) {
        std::cerr << "Load factor not within limits." << std::endl;
        return false; // load factor is not within limits
    }

    return true;
}

#endif
