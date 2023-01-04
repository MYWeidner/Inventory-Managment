#include "Treap.h"

Treap::Treap(){
    root = NULL; // initialize root pointer as null 
}

Treap::~Treap(){
    
}

shared_ptr<TreapNode>Treap:: InitNode(int key, float max_inv, float curr_inv, float min_inv, string item){
    // initialize new node from heap memory & individual variables with given value
    shared_ptr<TreapNode> node(new TreapNode); 
    node->key = key;
    node->max_inv = max_inv;
    node->curr_inv = curr_inv;
    node->min_inv = min_inv;
    node->item = item;
    node->left = NULL;
    node->right = NULL;
    node->priority = 100 - (node->curr_inv / node->max_inv) * 100; // full node - ratio of current inventory to max inventory  
    return node;
}

void Treap::Insert(shared_ptr<TreapNode> &root, int key, float max_inv, float curr_inv, float min_inv, string item){
    // base case; if treap is empty, create new root node
    if(root == NULL){
        root = InitNode(key, max_inv, curr_inv, min_inv, item);
        return;
    }
    // recursive case 1: if given key < root key, insert in left subtree (BST invariant check)
    // fix heap property: parent's priority must be greater than their children
    // rotate right if root's left child is not null and
    // left child priority > root priority
    if(key < root->key){
        Insert(root->left, key, max_inv, curr_inv, min_inv, item);
        if(root->left != NULL && root->left->priority > root->priority){
            rotateRight(root);
        }
    }
    // recursive case 2: if given key > root key, insert in right subtree (BST invariant check)
    // fix heap property: parent's priority must be greater than their children
    // rotate left if root's right child is not null and
    // right child priority > root priority
    else {
        Insert(root->right, key, max_inv, curr_inv, min_inv, item);
        if(root->right != NULL && root->right->priority > root->priority){
            rotateLeft(root);
        }
    }
}

void Treap::rotateRight(shared_ptr<TreapNode> &root){
    // visual representation of rotations; variable names based on diagram
    /*         A               B
              / \             / \
             B   C   ---->   D   A
            / \                 / \
           D   E               E   C
    */
    // initialization based on diagram above (LHS)
    shared_ptr<TreapNode> B = root->left; // node B pointer points to root's left child
    shared_ptr<TreapNode> E = root->left->right; // node E pointer points to root's left child's right child
    // right rotation; see diagram above (RHS)
    B->right = root; // node B (new root) right child pointer points to old root; old root becomes new root's right child
    root->left = E; // old root's left child pointer points to E; new root's right child becomes old root's left child
    // set new root
    root = B; // root pointer points to B
}

void Treap::rotateLeft(shared_ptr<TreapNode> &root){
    /*       A               C
            / \             / \
           B   C   ---->   A   E
              / \         / \
             D   E       B   D
    */
    // initialization based on diagram above (LHS)
    shared_ptr<TreapNode> C = root->right; // node C pointer points to root's right child
    shared_ptr<TreapNode> D = root->right->left; // node D pointer points to root's right child's left child
    // left rotation; see diagram above (RHS)
    C->left = root; // node C left child pointer points to old root; old root becomes new root's left child
    root->right = D; // old root's right child pointer points to D; new root's left child becomes old root's right child
    // set new root
    root = C; // root pointer points to C
}

void Treap::Remove(shared_ptr<TreapNode> &root, int key){
    // base case: treap is empty; key not found
    if(root == NULL){
        return;
    }
    // recursively search left subtree for key if key < root key (BST invariant check)
    if(key < root->key){
        Remove(root->left, key);
    }
    // recursively search right subtree for key if key > root key (BST invariant check)
    else if(key > root->key){
        Remove(root->right, key);
    }
    // if key is found
    else {
        // recursive case 1: node to be removed is root and has no children (leaf)
        // set root equal to null 
        if(root->left == NULL && root->right == NULL){
            root = NULL;
        }
        
        // recursive case 2: node to be removed has 2 children
        else if(root->left != NULL && root->right != NULL){
            // if left child priority < right child priority, then rotateLeft on root until root becomes leaf
            // recursively remove left child
            if(root->left->priority < root->right->priority){
                rotateLeft(root);
                Remove(root->left, key);
            }
            // if left child priority > right child priority, then rotateRight on root until root becomes leaf
            // recursively remove right child
            else{
                rotateRight(root);
                Remove(root->right, key);
            }
        }
        // recursive case 3: node to be removed has 1 child
        // condition ? result1 : result2 
        // determine whether child node is root's left or the right child
        // root pointer points to child
        else {
            shared_ptr<TreapNode> child = (root->left)? root->left: root->right;
            root = child;
        }
    }
}

bool Treap::Search(shared_ptr<TreapNode> root, int key){
    // key is not present in treap
    if(root == NULL){
        return false;
    }
    // key is root
    if(root->key == key){
        return true;
    }
    // if key is < root, search left subtree
    if(key < root->key){
        return Search(root->left, key);
    }
    // if key is > root, search right subtree
    return Search(root->right, key);
}

void Treap::changePriority(shared_ptr<TreapNode> &root, int key, int new_key, float new_curr_inv){   
    shared_ptr<TreapNode> temp = root; // temp node to store current root info
    Remove(temp, temp->key); // remove node with old priority
    Insert(temp, temp->key, temp->max_inv, temp->curr_inv, temp->min_inv, temp->item); // reinsert node to maintain old root info; avoid inadvertently deleting node permanently
    Insert(root, new_key, root->max_inv, new_curr_inv, root->min_inv, root->item);  // insert node with new priority
    float reorder_qty = root->max_inv - new_curr_inv; // computes reorder amount
    cout << "Time to reorder "<< temp->item << ". Order " << reorder_qty << " units." << endl; // reorder message
}
