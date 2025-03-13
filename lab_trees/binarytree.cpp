#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;
    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subroot)
{
    if(subroot == NULL){
        return;
    }
    Node*temp = subroot->left;
    subroot->left = subroot->right;
    subroot->right = temp;
    mirror(subroot->left);
    mirror(subroot->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    return isOrderedRecursive(root);
}

template <typename T>
int BinaryTree<T>::findMin( const Node * subRoot ) const{
    int min = subRoot->elem;
    if( subRoot->left != NULL ){
        int leftmost = findMin(subRoot->left);
        if(leftmost < min)
            min = leftmost;
    }
    if(subRoot->right != NULL){
        int rightmost = findMin(subRoot->right);
        if(rightmost < min)
            min = rightmost;
    }
    return min;
}

template <typename T>
int BinaryTree<T>::findMax( const Node * subRoot ) const{
    int max = subRoot->elem;
    if(subRoot->left != NULL){
        int leftmost = findMax(subRoot->left);
        if(leftmost > max)
            max = leftmost;
    }
    if(subRoot->right != NULL){
        int rightmost = findMin(subRoot->right);
        if(rightmost > max)
            max = rightmost;
    }
    return max;
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const Node* subRoot) const{
    if (subRoot == NULL){
        return true;
    }
    if (subRoot->left == NULL && subRoot->right == NULL){
        return true;
    }
    if (subRoot->left == NULL){
        if  ((subRoot->elem < findMin(subRoot->right)) && 
        isOrderedRecursive(subRoot->left) && 
        isOrderedRecursive(subRoot->right)){
            return true;
        }
        return false;
    }
    if(subRoot->right == NULL){
        if ((subRoot->elem > findMax(subRoot->left)) && 
        isOrderedRecursive(subRoot->left) && 
        isOrderedRecursive(subRoot->right)){
            return true;
        }
        return false;
    }
    if(subRoot->left != NULL && subRoot->right != NULL){
        if ((subRoot->elem > findMax(subRoot->left)) && 
        (subRoot->elem < findMin(subRoot->right)) && 
        isOrderedRecursive(subRoot->left) && 
        isOrderedRecursive(subRoot->right)){
            return true;
        }
    }
    return false;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrderedRecursive(root);
}
