/***************************************************************************
                               heap.cpp  -
                             -------------------
    begin                : Tue 04 Apr 2017 02:56:28 CDT
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


/* Project Includes */
#include "heap.h"

/* STL Includes */
#include <assert.h>

// Instructions:
// Implement a Max Heap in the vector MaxHeap::m_heap

MaxHeap::MaxHeap(int sizeHint) {
    m_heap.reserve( sizeHint );
}

MaxHeap::MaxHeap(const std::vector<int>& v) : m_heap( v ) {
    // Implement code to build a heap in O(N) from the vector
}

void MaxHeap::push(int key) {
    // Implement code to push a key onto the max heap
}

int MaxHeap::pop() {
    // Implement code to pop (also known as extract max) from the max heap
    return 0;
}
