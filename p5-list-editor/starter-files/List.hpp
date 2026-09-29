#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    if(first == nullptr){
      return true;
    }
    return false;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const{
    return size0;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node *newcode = new Node{first, nullptr, datum};
    if(empty()){
      last = newcode;
    }else{
      first->prev = newcode;
    }
    first = newcode;
    size0++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node *newcode = new Node{nullptr, last, datum};
    if(empty()){
      first = newcode;
    }else{
      last->next = newcode;
    }
    last = newcode;
    size0++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    Node *remove = first;
    first=first->next;
    if(first){
      first->prev=nullptr;
    }else{
      last=nullptr;
    }
    delete remove;
    size0--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    Node *remove = last;
    last=last->prev;
    if(last){
      last->next=nullptr;
    }else{
      first=nullptr;
    }
    delete remove;
    size0--;
  }

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear(){
    while(!empty()){
      pop_front();
    }
  }
  List() : first(nullptr), last(nullptr), size0(0) {}

  ~List() { clear();}

  List(const List &other) : first(nullptr), last(nullptr), size0(0) {
    copy_all(other);
  }

  List &operator=(const List &other) {
    if(this == &other){
      return *this;
    }
    clear();
    copy_all(other);
    return *this;
}

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    for(Node *n=other.first; n; n=n->next){
      push_back(n->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int size0 = 0;
public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}
    T &operator*() const {
      return node_ptr->datum;
    }
    Iterator &operator++(){
      node_ptr = node_ptr->next;
      return *this;
    }
    Iterator operator++(int){
      Iterator copy=*this;
      operator++();
      return copy;
    }
    bool operator==(const Iterator &other) const{
      return list_ptr==other.list_ptr && node_ptr==other.node_ptr;
    }
    bool operator!=(const Iterator &other) const{
      return !(*this == other);
    }

    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.



    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.



    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np): list_ptr(lp), node_ptr(np) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const{
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator(this, nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i){
    Node *index = i.node_ptr;
    Node *next = index->next;
    Node *prevIndex = index->prev;
    if(prevIndex){
      prevIndex->next = next;
    }else{
      first = next;
    }
    if(next){
      next->prev=prevIndex;
    }else{
      last=prevIndex;
    }
    delete index;
    size0--;
    return Iterator(this, next);
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum){
    Node *next = i.node_ptr;
    if(next==nullptr){
      push_back(datum);
      return Iterator(this, last);
    }
    Node *prev = next->prev;
    Node *newNode= new Node{next, prev, datum};
    if(prev){
      prev->next=newNode;
    }else{
      first=newNode;
    }
    next->prev = newNode;
    size0++;
    return Iterator(this, newNode);
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
