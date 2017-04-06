/***************************************************************************
                                 bst.h  -  
                             -------------------
    begin                : Tue 04 Apr 2017 15:41:28 CDT
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



#ifndef BST_H
#define BST_H
/**
 * @class BinarySearchTree
 * @short Implement an unbalanced binary search tree.
 * @note Must allow for multiple copies (á la std::multiset)
 * @author Akarsh Simha <akarsh.simha@kdemail.net>
 */

#include <assert.h>
#include <string>

class BinarySearchTree {

private:

    struct TreeNode {
        int key;
        struct TreeNode *left, *right, *parent;
        TreeNode( int _key, struct TreeNode *_parent ) : key( _key ), parent( _parent ), left( nullptr ), right( nullptr ) {}
    };


public:

    /**
     * @short Constructor
     */
    BinarySearchTree() : m_root( nullptr ), m_size( 0 ) { }

    /**
     * @short Destructor
     */
    ~BinarySearchTree() { clear(); }

    /**
     * @short Inserts a key into the BST
     */
    void insert( int key );

    /**
     * @short Deletes a key from the BST
     */
    bool erase( int key );

    /**
     * @short Finds the number of copies of the given key in the BST
     */
    int count( int key ) const;

    /**
     * @short Erases the entire BST
     */
    void clear();

    /**
     * @short Return the size of the BST
     */
    inline int size() const { return m_size; }

    /**
     * @short Return whether the BST is empty or not
     */
    inline bool empty() const { return !m_root; }

    class const_iterator {
        typedef struct BinarySearchTree::TreeNode TreeNode;
        friend class BinarySearchTree;
    public:
        const_iterator& operator++() { assert( current ); current = successor(); return *this; }
        const_iterator operator++( int ) { assert( current ); const_iterator ret( current, bst ); current = successor(); return ret; }
        const_iterator& operator--() { current = predecessor(); assert( current ); return *this; }
        const_iterator operator--( int ) { const_iterator ret( current, bst ); current = predecessor(); assert( current ); return ret; }
        inline bool isValid() const { return current; }
        bool hasNext() const { return successor(); }
        const_iterator next() const { assert( current ); return const_iterator( successor(), bst ); }
        bool hasPrev() const { return predecessor(); }
        const_iterator prev() const { const TreeNode *p = predecessor(); assert( p ); return const_iterator( p, bst ); }
        inline int operator*() const { return current->key; }
    private:
        const TreeNode *current; // If current is nullptr, we assume this is the end() const_iterator.
        const BinarySearchTree *bst;
        const_iterator( const TreeNode *node, const BinarySearchTree *owner ) : current( node ), bst( owner ) { }
        inline const TreeNode *predecessor() const { return bst->predecessor( current ); }
        inline const TreeNode *successor() const { return bst->successor( current ); }
    };

    /**
     * @short Returns a const_iterator that points to the first element in an in-order traversal
     */
    inline const_iterator cbegin() const { return const_iterator( first(), this ); }

    /**
     * @short Returns a const_iterator that points to null
     */
    inline const_iterator cend() const { return const_iterator( nullptr, this ); }

    /**
     * @short Checks the tree for errors
     */
    bool checkTree( std::string *errorString = nullptr ) const;


private:

    /**
     * @return the first node in an in-order traversal
     */
    const TreeNode *first() const;

    /**
     * @return the last node in an in-order traversal
     */
    const TreeNode *last() const;

    /**
     * @return successor of the given node
     */
    const TreeNode *successor( const TreeNode *node ) const;

    /**
     * @return predecessor of the given node
     */
    const TreeNode *predecessor( const TreeNode *node ) const;

    TreeNode *find_right( int key ) const;

    friend class BinarySearchTree::const_iterator;

    int m_size;
    struct TreeNode *m_root;
};

#endif
