/***************************************************************************
                          testcasefactory.cpp  -
                             -------------------
    begin                : Wed 29 Mar 2017 20:09:36 CDT
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
#include "testcasefactory.h"

/* STL Includes */
#include <ctime>
#include <cstdlib>
#include <numeric>

TestCaseFactory::TestCaseFactory(int maxSize, int numLimit, bool randSize)
    : m_maxSize( maxSize ), m_numLimit( numLimit ), m_randSize( randSize ) {
    if ( maxSize <= 0 )
        m_maxSize = 1;
    std::srand( std::time( 0 ) );
}

std::vector<int> TestCaseFactory::testcase() {
    std::vector<int> tc;

    int N = m_randSize ? rand() % m_maxSize + 1 : m_maxSize;
    tc.reserve( N );
    for ( int i = 0; i < N; ++i )
        tc.push_back( rand() % m_numLimit );

    return tc;
}


std::vector<int> TestCaseFactory::testcaseNoReps() {

    if ( m_numLimit < m_maxSize )
        return std::vector<int>();

    // Use a Knuth shuffle to produce the required testcase
    std::vector<int> bank( m_numLimit );
    std::iota( bank.begin(), bank.end(), 0 );

    int N = m_randSize ? rand() % m_maxSize + 1 : m_maxSize;

    for ( int i = 0; i < N; ++i ) {
        int swapIndex = i + rand() % ( m_numLimit - i );
        std::swap( bank[i], bank[swapIndex] );
    }

    bank.resize( N );

    return bank;
}


bool TestCaseFactory::checkSorted( const std::vector<int>& v ) {
    int prev = std::numeric_limits<int>::min();
    for ( int x : v ) {
        if ( x < prev )
            return false;
        prev = x;
    }
    return true;
}
