#ifndef Treap_H__
#define Treap_H__

#include <string>
#include <memory>
#include <iostream>

using namespace std;

// This struct is the treap’s node structure
struct TreapNode{
  int key; // for BST ordering
  float priority; // for max heap property; item that is closest to being out-of-stock has the highest priority as this item will need to be replenished soonest
  float max_inv; // maximum inventory (amount that fits on shelf/ warehouse)
  float curr_inv; // current inventory
  float min_inv; // minimum amount that should be on hand at all times
  string item; // item name
  shared_ptr<TreapNode> left;
  shared_ptr<TreapNode> right;
};
class Treap{
public:
  // Constructor used to initialize class variables and pointers
  Treap();

  // Deconstructor not needed since smart pointers are used
  ~Treap();

  // Allocates memory for a TreapNode structure and returns pointer to it
  shared_ptr<TreapNode> InitNode(int key, float max_inv, float curr_inv, float min_inv, string item);

  // Recursive function to insert given key with a priority into treap
  // If treap is empty, insert node at root
  // If key is less than root key, then insert in left subtree, else, insert in right subtree
  // If priority of node is greater than that of its parent, perform tree rotations until balanced
  // Must obey BST invariants and heap properties
  void Insert(shared_ptr<TreapNode> &root, int key, float max_inv, float curr_inv, float min_inv, string item);

  // Utility function for Insert and Remove
  // Function will rotate the treap right to balance itself
  // When right rotation is performed on root (highest priority - A), root’s left child becomes new root (B) and old root becomes new root’s right child
  // New root’s right child (E) becomes old root’s left child
  /*         A               B
            / \             / \
           B   C   ---->   D   A
          / \                 / \
         D   E               E   C
  */
  void rotateRight(shared_ptr<TreapNode> &root); 

  // Utility function for Insert and Remove
  // Function will rotate the treap left to balance itself
  // When left rotation is performed on root (A), root’s right child (C) becomes new root and old root becomes new root’s left child
  // New root’s left child (D) becomes old root’s right child
  /*         A               C
            / \             / \
           B   C   ---->   A   E
              / \         / \
             D   E       B   D
  */ 
  void rotateLeft(shared_ptr<TreapNode> &root);

  // Recursive function to remove node from treap
  // If treap is empty, return
  // If node is a leaf, remove node
  // If node has 2 children, determine which child has highest priority and perform rotations until treap is balanced
  // If node has 1 child, remove node, and make child of node the child of the node’s parent
  void Remove(shared_ptr<TreapNode> &root, int key);

  // Recursive function to search for a key in treap using reverse inorder traversal starting with the root node
  // If key not found return false
  // If value of root equals key, then key is found and return true
  // If value of root is greater than key, then search for key in left subtree 
  // Else search right subtree until node is found 
  bool Search(shared_ptr<TreapNode> root, int key);

  // Function to change the priority and key of a node
  // If node’s inventory level drops significantly then node's priority and key are increased and thus it becomes the new root node and triggers a replenishment request
  // treap is rebalanced to maintain BST and heap properties
  void changePriority(shared_ptr<TreapNode> &root, int key, int new_key, float new_curr_inv);

private:
  // Pointer will always point to the root of the tree (highest priority)
  shared_ptr<TreapNode> root;  
};

#endif // Treap_H__