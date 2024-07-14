#include <iostream>
using namespace std;

// A BTree Node:
class BTreeNode{
    // array of key
    int *keys;
    // minimum degree (defines the range for number of keys)
    int t;
    // An array of child pointers
    BTreeNode* *CP_arr;
    // Current number of keys
    int num_keys;
    // Is the current node a leaf node?
    bool leaf;
public:
    // Constructor:
    BTreeNode(int min_degree, bool isleaf); 

    // Insert a new key in the subtree rooted with this node
    // The node must bbe non-full when this function is called
    void insertNonFull(int new_key);

    // Split the child y of this node, i is the index of y
    // in the child array CP_arr[]. The child y must be full
    // when the function is called.
    void splitChild(int index, BTreeNode* y);

    // Traverse the subtree rooted with this node
    void traverse();

    // Search a key in the subtree rooted with this node
    BTreeNode* search(int key);

    // A function that returns the index of the first key
    // that is greater or equal to k
    int findKey(int key);

    // A function to remove the key k in subtree rooted with
    // this node
    void remove(int key);

    // A function to remove the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int idx);

    // A function to remove the key present in idx-th position
    // in the this node which is a non-leaf node
    void removeFromNonLeaf(int idx);

    // A function to get the predecessor of the key
    // the key is present in the idx-th position in the node
    int getPred(int idx);

    // A function to get the successor of the key
    // the key is present in the idx-th position in the node
    int getSucc(int idx);

    // A function to fill up the child node present in the 
    // idx-th position in the CP_arr[] array if that child
    // has less than t-1 keys
    void fill(int idx);

    // A function to borrow a key from the CP_arr[idx - 1] -th
    // node and place it in C[idx]th node (mượn thằng anh em bên trái)
    void borrowFromPrev(int idx);

    // A function to borrow a key from the CP_arr[idx + 1] -th 
    // node and place it in C[idx]th node (mượn thằng anh em bên phải)
    void borrowFromNext(int idx);

    // Merge idx-th child with idx+1 -th child 
    // Merge hai thằng bên cạnh lại với nhau
    void merge(int idx);

// To access private and protected members of BTreeNode class in BTree class
friend class BTree;
};

// A Tree:
class BTree{
    // Pointer to the root node
    BTreeNode* root;
    // Minimum degree
    int t;
public:
    // Constructor:
    BTree(int min_degree){
        root = NULL;
        t = min_degree;
    }
    // Function to traverse the tree:
    void traverse(){
        if (root == NULL){
            return;
        }
        root->traverse();
    }
    // Function to search a key in this tree:
    BTreeNode* search(int key){
        if (root != NULL){
            return root->search(key);
        }
        return NULL;
    }
    // Function to insert new key to this tree:
    void insert(int key);
    // Function to remove a new key in this B-Tree
    void remove(int key);
};

// Constructor for BTreeNode class:
BTreeNode::BTreeNode(int min_degree, bool isLeaf){
    t = min_degree;
    leaf = isLeaf;
    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2*min_degree - 1];
    CP_arr = new BTreeNode*[2*min_degree];
    // Initialize number of keys as 0
    num_keys = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse(){
    int i;
    for (i = 0; i < num_keys; i ++){
        if (leaf == false){
            CP_arr[i]->traverse();
        }
        cout << keys[i] << " ";
    }
    if (leaf == false){
        CP_arr[i + 1]->traverse();
    }
}

// Function to search key k in subtree rooted with this node:
BTreeNode* BTreeNode::search(int key){
    int index = 0;
    while (index < num_keys && keys[index] < key){
        index ++;
    }
    if (keys[index] == key){
        return this;
    }
    if (leaf == true){
        return NULL;
    }
    // Since we are already at the key which is larger than wanted key
    return CP_arr[index]->search(key);
}

// Insert a new key in this B-Tree
void BTree::insert(int key){
    // if Tree is empty
    if (root == NULL){
        root = new BTreeNode(t, true);
        root->keys[0] = key;
        root->num_keys = 1;
    }
    else{
        // If Tree is full, then tree grows in height
        if (root->num_keys == 2*t - 1){
            // Allocate memory for new root:
            BTreeNode* newNode = new BTreeNode(t, false);
            // Make old root as child of new root:
            newNode->CP_arr[0] = root;
            // Split the old root and move 1 key to the new root
            newNode->splitChild(0, root);
            // And now the newNode has 2 children, decide which one
            // should have a new key
            int index = 0;
            if (newNode->keys[0] < key){
                index ++;
            }
            newNode->CP_arr[index]->insertNonFull(key);
            // Change root:
            root = newNode;
        }
        else{
            root->insertNonFull(key);
        }
    }
}

// Insert a new key in this node
// The node must be non full when this function is called
void BTreeNode::insertNonFull(int key){
    // Set the index to be the last element:
    int index = num_keys - 1;
    // If this is a leaf node:
    if (leaf == true){
        while (index >= 0 && keys[index] > key){
            keys[index + 1] = keys[index];
            index --;
        }
        keys[index + 1] = key;
        num_keys = num_keys + 1;
    }
    else{
        // Find the child that will have the new key:
        while (index >= 0 && keys[index] > key){
            index --;
        }
        // If the found child is full:
        if (CP_arr[index + 1]->num_keys == 2*t - 1){
            // If the child is full, split it
            splitChild(index + 1, CP_arr[index + 1]);
            // See which one of two children will have new key
            if (keys[index + 1] < key){
                index ++;
            }
        }
        CP_arr[index + 1]->insertNonFull(key);
    }
}

// Split the child y of this node 
// Node child must be full when this function is called
void BTreeNode::splitChild(int index, BTreeNode* child){
    // Create a new nnode which is going to store (t-1) keys of child:
    BTreeNode* newChild = new BTreeNode(child->t, child->leaf);
    newChild->num_keys = t - 1;
    // Copy the last (t-1) keys of child to newChild:
    for (int j = 0; j < t - 1; j ++){
        newChild->keys[j] = child->keys[j + t];
    }
    // Copy the last (t-1) children to newChild:
    if (child->leaf == false){
        for (int j = 0; j < t - 1; j ++){
            newChild->CP_arr[j] = child->CP_arr[j + t];
        }
    }
    // Reduce the number of keys in child:
    child->num_keys = t - 1;
    // Since this node will have a new child, create 
    // space of new child:
    for (int j = num_keys; j >= index + 1; j --){
        CP_arr[j + 1] = CP_arr[j];
    }
    // Link the newChild to this node:
    CP_arr[index + 1] = newChild;
    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = num_keys-1; j >= index; j--)
        keys[j+1] = keys[j];

    // Copy the middle key of y to this node
    keys[index] = child->keys[t-1];

    // Increment count of keys in this node
    num_keys = num_keys + 1;
}

int BTreeNode::findKey(int key){
    int index = 0;
    while (index < num_keys && key > keys[index]){
        ++index;
    }
    return index;
}

// Function to remove the key k from the sub-tree
// rooted with this node
void BTreeNode::remove(int key){
    int index = findKey(key);
    // If the key to be removed is present in this node:
    if (index < num_keys && keys[index] == key){
        if (leaf){
            removeFromLeaf(index);
        }
        else{
            removeFromNonLeaf(index);
        }
    }
    else{
        // If this is a leaf node --> key not in tree
        if (leaf){
            cout << "The key "<<key<<" does not exist in the tree";
            return;
        }
        // Whether the key is inside the subtree rooted
        // with the last key of this node
        bool flag = ( (index == num_keys)? true:false );
        // If the child where the key is supposed to exist
        // has less than t keys, we fill that child
        if (CP_arr[index]->num_keys < t){
            fill(index);
        }
        // If the last child has been merged, it must have
        // merged with the previous child and so we recursive
        // on the (idx-1)th child. 
        // Else, we recurse on the (idx)th child which now has atleast t keys
        if (flag && index > num_keys){
            CP_arr[index - 1]->remove(key);
        }
        else{
            CP_arr[index]->remove(key);
        }
    }
    return;
}

// A function to remove the idx-th key from the node - leaf node
void BTreeNode::removeFromLeaf(int index){
    for (int i = index + 1; i < num_keys; i ++){
        keys[i - 1] = keys[i];
    }
    num_keys --;
    return;
}

// A function to remove the idx-th key from this node - non-leaf node
void BTreeNode::removeFromNonLeaf(int index){
    int key = keys[index];
    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (CP_arr[index]->num_keys >= t){
        int pred = getPred(index);
        keys[index] = pred;
        CP_arr[index]->remove(pred);
    }   
    // Same thing, swap by the left most of the right child
    else if (CP_arr[index + 1]->num_keys >= t){
        int succ = getSucc(index);
        keys[index] = succ;
        CP_arr[index + 1]->remove(succ);
    }
    // Left and child don't have enough key, merge
    // and now the left child will represent the new child.
    else{
        merge(index);
        CP_arr[index]->remove(key);
    }
    return;
}

// A function to get predecessor of keys[index]
// which is getting the right most key in the left side
int BTreeNode::getPred(int index){
    BTreeNode* left_child = CP_arr[index];
    // Keep moving to the right most node until we reach a leaf
    while (!left_child->leaf){
        left_child = left_child->CP_arr[left_child->num_keys];
    }
    // return the last key of the leaf
    return left_child->keys[left_child->num_keys - 1];
}

// A function to get successor of keys[index]
// which is getting the left most key in the right side
int BTreeNode::getSucc(int index){
    BTreeNode* right_child = CP_arr[index + 1];
    // Keep moving to the left node until we reach a leaf
    while (!right_child->leaf){
        right_child = right_child->CP_arr[0];
    }
    // return the first key of the leaf
    return right_child->keys[0];
}

// A function to fill child CP_arr[index] which has less than t-1 keys
void BTreeNode::fill(int index){
    // If the previous child has more than t-1 keys,
    // borrow a key from that child
    if (index != 0 && CP_arr[index - 1]->num_keys >= t){
        borrowFromPrev(index);
    }
    // If the next child has more than t-1 keys,
    // borrow a key from that child
    else if (index != num_keys && CP_arr[index + 1]->num_keys >= t){
        borrowFromNext(index);
    }
    // If CP_arr[idx] is the last child, merge it with the 
    // previous sibling, or with the right sibling
    else{
        if (index != num_keys){
            merge(index);
        }
        else{
            merge(index - 1);
        }
    }
    return;
}

// A function to borrow a key from CP_arr[index - 1]
// and insert it into CP_arr[index]
void BTreeNode::borrowFromPrev(int index){
    BTreeNode* child = CP_arr[index];
    BTreeNode* left_sibling = CP_arr[index - 1];
    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key

    // Moving all key in CP_arr[index] one step ahead
    for (int i = child->num_keys - 1; i >= 0; i --){
        child->keys[i + 1] = child->keys[i];   
    }
    // If CP_arr[index] is not a leaf, move all its child pointers
    // one step ahead
    if (!child->leaf){
        for (int i = child->num_keys; i >= 0; i --){
            child->CP_arr[i + 1] = child->CP_arr[i];
        }
    }
    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = keys[index - 1];
    // Moving sibling's last child as CP_arr[index]'s first child
    if (!child->leaf){
        child->CP_arr[0] = left_sibling->CP_arr[left_sibling->num_keys];
    }
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[index - 1] = left_sibling->keys[left_sibling->num_keys - 1];
    child->num_keys ++;
    left_sibling->num_keys --;
    return;
}

// A function to borrow a key from CP_arr[index + 1]
// and insert it into CP_arr[index]
void BTreeNode::borrowFromNext(int index){
    BTreeNode* child = CP_arr[index];
    BTreeNode* right_sibling = CP_arr[index + 1];
    child->keys[child->num_keys] = keys[index]; 
    if (!child->leaf){
        child->CP_arr[child->num_keys + 1] = right_sibling->CP_arr[0];
    } 
    keys[index] = right_sibling->keys[0];
    // moving all keys in sibling one step behind
    for (int i = 1; i < right_sibling->num_keys; i ++){
        right_sibling->keys[i - 1] = right_sibling->keys[i];
    }
    // moving child pointer of leaf 1 step behind
    if (!right_sibling->leaf){
        for (int i = 1; i < right_sibling->num_keys; i ++){
            right_sibling->CP_arr[i - 1] = right_sibling->CP_arr[i];
        }
    }
    child->num_keys ++;
    right_sibling->num_keys --;
    return;
}

// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void BTreeNode::merge(int index)
{
    BTreeNode *child = CP_arr[index];
    BTreeNode *sibling = CP_arr[index+1];

    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[t-1] = keys[index];

    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->num_keys; ++i)
        child->keys[i+t] = sibling->keys[i];

    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->num_keys; ++i)
            child->CP_arr[i+t] = sibling->CP_arr[i];
    }

    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i=index+1; i<num_keys; ++i)
        keys[i-1] = keys[i];

    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=index+2; i<=num_keys; ++i)
        CP_arr[i-1] = CP_arr[i];

    // Updating the key count of child and the current node
    child->num_keys += sibling->num_keys+1;
    num_keys--;

    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}

void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    // Call the remove function for root
    root->remove(k);

    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->num_keys==0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->CP_arr[0];

        // Free the old root
        delete tmp;
    }
    return;
}