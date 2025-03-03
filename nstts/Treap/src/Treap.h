
#ifndef TREAP_H
#define TREAP_H

#include <optional>
#include <utility>
#include <vector>
/* RE: about Treap and implicit Treap
 * Key thing in treap - is the Idea
 * how to fastly build balanced binary tree using random numbers
 * From the stock this idea help us do the same things as other 
 * self balanced BST's, like Red-black tree, or AVL tree
 * Interface of this data structures is logN map operations (insert, delete, find and so on)
 * 
 * Other scenario of usage treap is building effective mutable array
 * which operations runs in logN
 * 
 * To implement this functionality we need to use 'implicit' keys.
 * In case of MutableArray the keys are position in array
 *
 * We call them implicit because we don't actually store them in ds
 * (when inserting into middle of array we need to update all positions - it is too expencive)
 * But we maintain them using some explicit parameters - in this case size of subtrees
 * It can be easely update with all of your operations
 *
 * But your treap doesn't contain neither keys or size of subtrees
 * 
 * You need to choose which interface you want to implement
 * either TreeMap or MutableArray
 * And then implement it with respect to time complixety of operations
 * Note: you can find these interface at the end of this file
 */
class Treap {
  int key_;

public:
  std::optional<int> value;
  Treap*             left;
  Treap*             right;

  Treap();
  explicit Treap(int value);
  ~Treap();
  Treap(const Treap& other);
  Treap& operator=(const Treap& other);

private:
  std::pair<Treap*, Treap*> split(int k);
  Treap*                    merge(Treap* t);

public:
  void free();
  void insert(int value);
  void remove(int value);
  int  sum() const;
};

/* Note: Interfaces
 * this is just contract, you don't need to actually inherit it
 * and implement methods, because you don't discuss inheritance on lectures yet
 *
 * Just see which methods are required and their time complixety
 */
class TreeMap {
public:
    /* O(logN) in average */
    virtual bool find(int) = 0;

    /* O(logN) in average */
    virtual void insert(int) = 0;

    /* O(logN) in average */
    virtual void erase(int) = 0;
    
    /* O(logN) in average */
    virtual int min() = 0;

    /* Should have O(N)
     * Get all elements in ascending order
     */
    virtual std::vector<int> inorder();
};

/* MutableArray that indexed with integers
 * a_0, a_1, ..., a_(n - 1), a_n
 */
class MutableArray {
    /* O(logN) in average
     * Inserts new element at position pos 
     * --
     * Before insert_pos(1, 42): [0, 1, 2] 
     * After: [0, 42, 1, 2] 
     */
    virtual void insert_pos(size_t pos, int val) = 0;

    /* O(logN) in average
     * Modifies element at position pos
     * --
     * Before modify(1, 42): [0, 1, 2]
     * After: [0, 42, 2]
     */
    virtual void modify_pos(size_t pos, int val) = 0;

    /* O(logN) in average
     * Erases element at position pos
     * --
     * Before erase(1): [0, 1, 2]
     * After: [0, 1]
     */
    virtual void erase_pos(size_t pos) = 0;

    /* O(logN) in average
     * --
     * [42, 7, 33].at(0) == 42
     * [42, 7, 33].at(1) == 7
     * [42, 7, 33].at(3) == 33 
     */
    virtual void at(size_t pos) = 0;

    /* O(N) 
     * converts MutableArray to vector
     * the order of elements should be saved
     */
    virtual std::vector<int> to_vector();


    // ---- Optional part ----
    // implement if you have a time and if it is interesting for you
    // This changes doesn't affect on acceptance of NSTT

    /* O(logN) in average 
     * --
     * [0, 1, 2, 3, 4].sum(1, 3) == 6
     */
    virtual int sum(size_t from, size_t to) = 0;
    
    /* O(logN) in average
     * returns minimum on specified segment
     * --
     * [0, 3, 2, 1, 4].min(1, 3) == 1 
     */
    virtual void min(size_t from, size_t to) = 0;

    /* O(logN) in average
     * adds number on specified range
     * --
     * [0, 1, 2, 3, 4].add(0, 3, 1) == [1, 2, 3, 4, 4]
     */
    virtual void add(size_t from, size_t to, int n) = 0;

    /* O(logN) in average
     * reverses array in specified range
     * --
     * [0, 1, 2, 3, 4].reverse(1, 2) == [0, 2, 1, 3, 4]
     */
    virtual void reverse(size_t from, size_t to) = 0;

};

#endif // TREAP_H
