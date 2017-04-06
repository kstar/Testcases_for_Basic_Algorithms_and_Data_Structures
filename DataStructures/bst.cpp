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
}

bool BinarySearchTree::erase(int key) {
    bool success = false;

    // Implement code to erase a key from the BST.

    if ( success )
        --m_size;
    return success;
}

int BinarySearchTree::count(int key) const {

    // Implement code to count the number of entries with the given key

    return 0;
}

void BinarySearchTree::clear() {

    // Implement code to delete the entire BST

    m_size = 0;
}

const BinarySearchTree::TreeNode* BinarySearchTree::first() const {
    const TreeNode *ret = m_root;

    // Implement code to find the leftmost leaf of the BST

    return ret;
}

const BinarySearchTree::TreeNode* BinarySearchTree::last() const {
    const TreeNode *ret = m_root;

    // Implement code to find the rightmost leaf of the BST

    return ret;
}


const BinarySearchTree::TreeNode* BinarySearchTree::successor( const BinarySearchTree::TreeNode* node ) const {
    if ( !node ) // we treat the successor of nullptr to be the first node
        return first();

    const TreeNode *ret = node;

    // Implement code to find the successor of ret and return it.
    // If the current node is the last, return nullptr

    return ret;
}

const BinarySearchTree::TreeNode* BinarySearchTree::predecessor( const BinarySearchTree::TreeNode* node ) const {
    if ( !node ) // we treat the predecessor of nullptr to be the last node
        return last();

    const TreeNode *ret = node;

    // Implement code to find the successor of ret and return it.
    // If the current node is the first, return nullptr

    return ret;
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
