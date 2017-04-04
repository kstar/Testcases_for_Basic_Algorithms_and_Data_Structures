/***************************************************************************
                                heap.h  -  
                             -------------------
    begin                : Tue 04 Apr 2017 02:41:11 CDT
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



#ifndef HEAP_H
#define HEAP_H

#include <vector>

/**
 * @class MaxHeap
 * @short Specifies the interface for a Max Heap.
 * @author Akarsh Simha <akarsh.simha@kdemail.net>
 */

class MaxHeap {

public:
    /**
     * @short Default Constructor
     */
    MaxHeap( int sizeHint = 128 );

    /**
     * @short Array constructor -- builds heap from the given vector
     */
    explicit MaxHeap( const std::vector<int> &v );

    /**
     * @short Insert a key into the max heap
     */
    void push( int key );

    /**
     * @short Removes the max key
     */
    int pop();

    /**
     * @short Returns the max key
     */
    inline int top() { return m_heap[0]; }

    /**
     * @short Return the size of the heap
     */
    inline int size() { return m_heap.size(); }

    /**
     * @return whether the heap is empty
     */
    inline bool empty() { return m_heap.empty(); }

private:

    std::vector<int> m_heap;

    // Declare any private methods you may need
};

#endif
