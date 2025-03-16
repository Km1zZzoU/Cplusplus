
#ifndef TREAP_H
#define TREAP_H

#include <optional>
#include <utility>
/** Note: design of data strutures is C++ 
  *
  * I think that in some places your code
  * is overcomplicated.
  * I guess it happens due to the chosen C-like design 
  * - your Treap class has too much responsibillity:
  *
  * 1) It owns memory
  * 2) It provides some treap-specific operations and keeps invariants
  *
  * Often to solve this problem tree-like
  * structures design in the another way - see binary_tree.hpp sample
  *
  * ----
  * 
  * It might seems hard to convert your Treap to such form, 
  * but actually you already have done treap-nodes
  * and all you need to do - wrap it into Treap class.
  * This desing allow you to make empty containers without using optionals
  * Maybe some other functions will be simplified 
  *
  * ----
  * 
  * And remember - this is just an advice
  * You can fix all comments without using this design. 
  * This comment does not affect on the NSTTs acceptance.
  * You may not implement this
  *
  * I implemented BST using this design, so you can see how it's looks like
  * See: reviewExamples/binary_tree.hpp
  *
  */
class Treap {
  int key_;

public:
  /** RE: About an empty Treap and optional
    *
    * I understand why do you need optional here
    * - it is used to mark an empty Treap. 
    *
    * Personally I think that it is not great design
    * because it complicate some things (about them later), 
    * but it is okay.
    * 
    * But where actually review starts - in the encapsulation point
    * I think that user should not know about your implementation details
    * 
    * So we can make this field private and add functions like
    *
    * std::optional<int> find(val);
    * bool hasVal(val);
    *
    * ----
    *
    * RE: Removing last element 
    * Imagine that user removes last value from your treap
    * For now it is UB (see test 'RemoveLast')
    *
    * You need to think about the behavior of the data structure in this case.
    * There is possible solutions:
    *
    * - If you decide to redesign the data structure as I wrote above, 
    *   then this problem will simply disappear.
    *
    * - If there is the last value in the Treap - don't delete the last node,
    *   make an optional nullopt 
    *
    * - Or don't allow user remove last element in some way (not really nice solution, but acceptable)
    *
    * Or maybe you can come up with more elegant solution, it is up to you)
    */
  std::optional<int> value;
  /** RE: encapsulation
    * Trough this pointers user can broke up all invariants of your treap
    * see test 'Im_User_and_Im_dumb_and_Im_doing_what_I_want'
    */
  Treap*             left;
  Treap*             right;

  Treap();
  explicit Treap(int value);
  ~Treap();
  Treap(const Treap& other);
  Treap(Treap&& other);
  Treap& operator=(Treap&& other);
  Treap& operator=(const Treap& other);

private:
  std::pair<Treap*, Treap*> split(int k);
  Treap*                    merge(Treap* t);
  Treap* clone() const;

  // void free();
public:
  void insert(int value);
  void remove(int value);
  int  sum() const;
  /** RE: actually what was about the previous review
    * Your treap is balanced BST, right? So lets add search function to it)
    */
};


#endif // TREAP_H
