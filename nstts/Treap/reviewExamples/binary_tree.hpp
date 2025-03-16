#pragma once

#include <utility> // std::swap

// Note: just a sample, this thing shouldn't compile

/** This is the class that provides
  * interface to work with the binary search tree.
  * It is maintains 'search' invariant. 
  */
class BST {
    // This inner private class owns memory of left and right.
    // It is responsible for the correct work with memory.
    struct Node {
        int val;
        Node* left;
        Node* right;

        // Rule of three here is enough
        Node(int value) : val(value), left(nullptr), right(nullptr) {}

        Node(const Node& other) : val(other.val) {
            left  = other.hasLeft()  ? new Node(*other.left) : nullptr;
            right = other.hasRight() ? new Node(*other.left) : nullptr;
        }

        Node& operator=(const Node& other) {
            if (this != &other) {
                return *this;
            }
            
            delete left; 
            delete right;

            val = other.val;
            left  = other.hasLeft()  ? new Node(*left) : nullptr;
            right = other.hasRight() ? new Node(*right) : nullptr;

            return *this;
        }

        ~Node() {
            delete left;
            delete right;
        }

        inline bool hasLeft()  const { return left != nullptr; }
        inline bool hasRight() const { return left != nullptr; }


        /** Note: about friends
          * In C++ private inner classes have no access
          * to private fields of the enclosing class
          *
          * So we use friend to provide this access
          *
          * But be careful, this might broke encapsulation in your class
          * if node 'leaks' from BST
          */
        friend BST;
    };

    // This node is nullptr if and only if the BST is empty
    Node* root_ = nullptr;

    // So the enclosing class cares about 'search' invariant
    // while Nodes just storing topology of the tree
    Node* insertImpl(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);

        if (value < node->val) {
            node->left = insertImpl(node, value);
        } else if (value > node->val) {
            node->right = insertImpl(node, value);
        }

        return node;
    }


public:
    inline bool isEmpty()  const { return root_ == nullptr; };
    inline bool nonEmpty() const { return root_ != nullptr; };
    
    void insert(int value) {
        root_ = insertImpl(root_, value);
    }

    BST() {};

    BST(const BST& other) {
        root_ = other.nonEmpty() ? new Node(*other.root_) : nullptr;
    }

    BST& operator=(const BST& other) {
        if (this != &other) {
            return *this;
        }

        delete root_;

        root_ = nonEmpty() ? new Node(*other.root_) : nullptr;

        return *this;
    }

    // Note: pass ownership under the root it is all you need to do
    BST(BST&& other) : root_(other.root_) {
        other.root_ = nullptr;
    }
    
    /** RE: Think why this move assigment operator is correct
      * and write answer to me in tg
      * But if there were problems, also text me
      * and we try to answer this question together
      */
    BST& operator=(BST&& other) {
        if (this == &other) {
            return *this;
        }
        
        std::swap(root_, other.root_);
        return *this;
    }

    ~BST() {
        // BST owns only root_ node
        // so it should care about deleting it
        // other nodes will be deleted via Node dstr
        delete root_;
    }

};
