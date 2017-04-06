/***************************************************************************
                                bst.cpp  -
                             -------------------
    begin                : Tue 04 Apr 2017 16:58:04 CDT
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
#include <assert.h>
#include <functional>
#include <unordered_set>

/*
 * Note:
 *
 * struct BinarySearchTree::TreeNode is defined as:
 *
 *   struct TreeNode {
 *       int key;
 *       struct TreeNode *left, *right, *parent;
 *       TreeNode( int _key, struct TreeNode *_parent );
 *   };
 *
 * The root of the binary search tree is stored as TreeNode *BinarySearchTree::m_root
 *
 */

/*
 * Note:
 *   Use the following convention for the BST property
 *      left child <= node < right child
 *
 */

void BinarySearchTree::insert(int key) {
    ++m_size;

    // Implement code to insert a key into the BST

    // Use the following convention:
    // left child <= node < right child

    if ( !m_root ) {
        m_root = new TreeNode( key, nullptr );
        return;
    }

    TreeNode *parent = m_root;
    do {
        assert( parent );
        if ( key > parent->key ) {
            if ( parent->right )
                parent = parent->right;
            else {
                parent->right = new TreeNode( key, parent );
                return;
            }
        }
        else {
            if ( parent->left )
                parent = parent->left;
            else {
                parent->left = new TreeNode( key, parent );
                return;
            }
        }
    } while ( true );
}

bool BinarySearchTree::erase(int key) {
    bool success = false;

    // Implement code to erase a key from the BST.

    TreeNode *node = find_right( key );
    if ( !node )
        return false;

    assert( node->key == key );

    std::function<void( TreeNode * )> removeNode = [&removeNode, this]( TreeNode *node ) -> void {
        // Case 2: Has both children -- swap out with predecessor and call erase on predecessor
        if ( node->left && node->right ) {
            TreeNode *predecessor = node->left;
            assert( node->left->key <= node->key );
            while ( predecessor->right )
                predecessor = predecessor->right;
            node->key = predecessor->key;
            removeNode( predecessor );
            return;
        }

        // Case 0 : No children -- simply remove node
        if ( !node->left && !node->right ) {
            TreeNode *parent = node->parent;
            assert( node == parent->left || node == parent->right );
            ( parent ? ( node == parent->left ? parent->left : parent->right ) : m_root ) = nullptr;
            delete node;
            return;
        }

        // Case 1: Only one child -- splice out the node
        assert( ( node->left && !node->right ) || ( node->right && !node->left ) );
        TreeNode *subTreeRoot = node->left ? node->left : node->right;
        assert( subTreeRoot );
        TreeNode *parent = node->parent;
        ( parent ? ( node == parent->left ? parent->left : parent->right ) : m_root ) = subTreeRoot;
        subTreeRoot->parent = parent;
        delete node;
    };

    removeNode( node );

    --m_size;
    return true;

}

int BinarySearchTree::count(int key) const {

    // Implement code to count the number of entries with the given key
    const TreeNode *node = find_right( key );
    if ( !node || node->key != key )
        return 0;

    int c = 1;

    while ( ( node = predecessor( node ) ) && node->key == key )
        ++c;

    return c;
}

void BinarySearchTree::clear() {

    // Implement code to delete the entire BST

    std::function<void( TreeNode * )> deleteSubTree = [&deleteSubTree]( TreeNode *subTreeRoot ) {
        if ( !subTreeRoot )
            return;

        deleteSubTree( subTreeRoot->left );
        deleteSubTree( subTreeRoot->right );
        delete subTreeRoot;
    };

    deleteSubTree( m_root );
    m_root = nullptr;

    m_size = 0;
}

const BinarySearchTree::TreeNode* BinarySearchTree::first() const {
    const TreeNode *ret = m_root;

    // Implement code to find the leftmost leaf of the BST
    if ( !ret )
        return nullptr;

    while ( ret->left )
        ret = ret->left;

    return ret;
}

const BinarySearchTree::TreeNode* BinarySearchTree::last() const {
    const TreeNode *ret = m_root;

    // Implement code to find the rightmost leaf of the BST
    if ( !ret )
        return nullptr;

    while ( ret->right )
        ret = ret->right;

    return ret;
}


const BinarySearchTree::TreeNode* BinarySearchTree::successor( const BinarySearchTree::TreeNode* node ) const {
    if ( !node ) // we treat the successor of nullptr to be the first node
        return first();

    const TreeNode *ret = node;

    // Implement code to find the successor of ret and return it.
    // If the current node is the last, return nullptr
    if ( ret->right ) {
        ret = ret->right;
        while ( ret->left )
            ret = ret->left;
    }
    else {
        while ( ret->parent && ret == ret->parent->right )
            ret = ret->parent;
        ret = ret->parent;
    }

    return ret;
}

const BinarySearchTree::TreeNode* BinarySearchTree::predecessor( const BinarySearchTree::TreeNode* node ) const {
    if ( !node ) // we treat the predecessor of nullptr to be the last node
        return last();

    const TreeNode *ret = node;

    // Implement code to find the successor of ret and return it.
    // If the current node is the first, return nullptr
    if ( ret->left ) {
        ret = ret->left;
        while ( ret->right )
            ret = ret->right;
    }
    else {
        while ( ret->parent && ret == ret->parent->left )
            ret = ret->parent;
        ret = ret->parent;
    }

    return ret;
}

BinarySearchTree::TreeNode* BinarySearchTree::find_right( const int key ) const {
    // Find an instance first
    if ( !m_root )
        return nullptr;

    TreeNode *node = m_root;

    while ( node ) {
        if ( key > node->key )
            node = node->right;
        else if ( key < node->key )
            node = node->left;
        else
            break;
    }

    assert( !node || node->key == key );
    assert( !node || !successor( node ) || successor( node )->key != key );
    return node;
}


bool BinarySearchTree::checkTree( std::string *errorString ) const {
    std::unordered_set<TreeNode *> visited;
    std::function<bool( TreeNode * )> checkSubTree = [&checkSubTree, &visited, errorString]( TreeNode *root ) -> bool {
        if ( !root )
            return true;
        if ( visited.count( root ) ) {
            if ( errorString ) *errorString = "There is a cycle";
            return false; // cyclic
        }
        visited.insert( root );
        if ( ( root->left && root->left->key > root->key ) || ( root->right && root->right->key <= root->key ) ) {
            if ( errorString ) *errorString = "BST property (left child <= node <= right child) violation";
            return false;
        }
        if ( ( root->left && root->left->parent != root ) || ( root->right && root->right->parent != root ) ) {
            if ( errorString ) *errorString = "Mangled parent pointers";
            return false;
        }
        return checkSubTree( root->left ) && checkSubTree( root->right );
    };
    if( m_root && m_root->parent ) {
        if ( errorString ) *errorString = "Root node has a parent";
        return false;
    }
    return checkSubTree( m_root );
}
