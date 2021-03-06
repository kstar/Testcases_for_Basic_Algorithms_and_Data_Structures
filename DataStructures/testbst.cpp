/***************************************************************************
                              testbst.cpp  -
                             -------------------
    begin                : Tue 04 Apr 2017 17:17:17 CDT
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
#include "bst.h"

/* STL Includes */
#include <set>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include <iostream>

int main() {
    const int numTestCases = 512;
    const int maxInitialSize = 2048;
    const int maxKey = 1024;
    const int maxOperations = 128;

    std::srand( std::time( 0 ) );

    BinarySearchTree testTree;
    std::multiset<int> refTree;

    for ( int k = 0; k < numTestCases; ++k ) {
        std::cout << "Testcase " << k << " of " << numTestCases << " (" << int( float( k )/numTestCases * 100. ) << "%)" << std::endl;
        int initialSize = rand()%( maxInitialSize + 1 );

        // Put some initial data
        for ( int j = 0; j < initialSize; ++j ) {
            int key = rand()%( maxKey + 1 );
            testTree.insert( key );
            refTree.insert( key );
            assert( testTree.size() == refTree.size() );
        }
        std::string errorString;
        if ( !testTree.checkTree( &errorString ) ) {
            std::cerr << "Tree check failed after initial data insertion. Error: " << errorString << std::endl;
            assert( false );
        }

        // Do some random sequence of tree-changing operations
        int Nops = rand()%( maxOperations + 1 );
        for ( int j = 0; j < Nops; ++j ) {
            int key = rand()%( maxKey + 1 );
            int op = rand()%2;
            switch( op ) {
            case 0:
                testTree.insert( key );
                refTree.insert( key );
                break;
            case 1: {
                bool found = testTree.erase( key ); // BinarySearchTree::erase() behaves differently from std::multiset::erase()
                int eraseCount = refTree.erase( key );
                if ( eraseCount == 0 )
                    assert( !found );
                else {
                    assert( found );
                    for ( int h = 0; h < eraseCount - 1; ++h )
                        refTree.insert( key );
                }
                break;
            }
            }
            errorString = "";
            if ( !testTree.checkTree( &errorString ) ) {
                std::cerr << "Tree check failed. Error: " << errorString << ". Last operation was " << std::string( op ? "erase" : "insert" ) << std::endl;
                assert( false );
            }
        }

        // Traverse the trees
        auto refIt = refTree.cbegin();
        auto testIt = testTree.cbegin();
        while ( refIt != refTree.cend() ) {
            assert( *refIt == *testIt );
            assert( refTree.count( *refIt ) == testTree.count( *testIt ) );
            ++refIt;
            ++testIt;
        }
        while ( refIt != refTree.cbegin() ) {
            --refIt;
            --testIt;
            assert( *refIt == *testIt );
            assert( refTree.count( *refIt ) == testTree.count( *testIt ) );
        }

        refTree.clear();
        testTree.clear(); // if the clear() method does not work correctly, the next testcase may fail
    }
}
