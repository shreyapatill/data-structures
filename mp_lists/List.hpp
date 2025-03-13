/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return head_;
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return NULL;
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if( length_ == 0 )
    return;

  while( head_ != NULL ){
    ListNode * node = head_->next;
    delete head_;
    head_ = node;
  }
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  if( length_ == 0 ){
    tail_ = newNode;
    head_ = newNode;
  }else{
    head_ -> prev = newNode;
    newNode -> next = head_;
    newNode -> prev = NULL;
    head_ = newNode;
  }

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = NULL;

  if( length_ == 0 ){
    tail_ = newNode;
    head_ = newNode;
  }else{
    tail_ -> next = newNode;
    newNode -> prev = tail_;
    tail_ = newNode;
  }

  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    curr->prev->next = NULL;
    curr->prev = NULL;
    return curr;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the end 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if( length_ == 0 )
    return;

  bool start = true;
  ListNode * node = head_;
  
  while( true ){
    if( node->next == NULL )
      return;

    ListNode * nodeNext = node->next;
    if( nodeNext->next == NULL )
      return;

    ListNode * nodeNextNext = nodeNext->next;
    if( nodeNextNext->next == NULL ){
      if( start ){
        head_ = nodeNext;
        nodeNext->prev = NULL;
      }else{
        nodeNext->prev = node->prev;
        node->prev->next = nodeNext;
      }

      nodeNextNext->next = node;
      node->prev = nodeNextNext;
      node->next = NULL;
      tail_ = node;
      return;
    }
    
    ListNode * nodeTemp = nodeNextNext->next;
    head_ = nodeNext;
    nodeNext->prev = NULL;
    nodeNextNext->next = node;
    node->next = nodeTemp;
    node->prev = nodeNextNext;
    nodeTemp->prev = node;
    start = false;
    node = nodeTemp;

  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
  ListNode * node = head_;
  head_ = tail_;
  tail_ = node;
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the end node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode * startNode = startPoint->prev;
  ListNode * endNode = endPoint->next;
  ListNode * currNode = startPoint;

  if( currNode == NULL || currNode->next == endPoint->next )
    return;

  ListNode * firstNode = currNode->next;
  currNode->prev = firstNode;
  currNode->next = endNode;

  if( endNode != NULL )
    endNode->prev = currNode;

  while( true ){
    if( firstNode->next == endNode ){
      firstNode->next = currNode;
      firstNode->prev = startNode;
      if( startNode != NULL )
        startNode->next = firstNode;
      return;
    }

    ListNode * secondNode = firstNode->next;
    firstNode->next = currNode;
    firstNode->prev = secondNode;
    currNode = firstNode;
    firstNode = secondNode;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  bool start = true;
  ListNode * node1 = head_;
  ListNode * node2 = head_;

  while( true ){
    for( int i = 1; i < n && node2->next != NULL; i++ )
      node2 = node2->next;
    
    ListNode * node = node2->next;
    reverse( *&node1, *&node2 );
    
    if( start )
      head_ = node2;
    
    if( node == NULL ){
      tail_ = node1;
      return;
    }

    node1 = node;
    node2 = node;
    start = false;
  }
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if( first == NULL && second == NULL )
    return NULL;

  if( first == NULL )
    return second;

  if( second == NULL )
    return first;

  bool start = true;
  ListNode * node1 = NULL;
  ListNode * node2 = NULL;
  ListNode * node3 = NULL;

  while(true){
    if( first->data < second->data){
      node3 = first;
      first = first->next;
      
      if( start ){
        node1 = node3;
      }
      else{
        node2->next = node3;
        node3->prev = node2;
        node3->next = NULL;
      }

      node2 = node3;
      if ( first == NULL ){
        node2->next = second;
        return node1;
      }
    }else{      
      node3 = second;
      second = second->next;

      if( start ){
        node1 = node3;
      }
      else{
        node2->next = node3;
        node3->prev = node2;
        node3->next = NULL;
      }

      node2 = node3;
      if( second == NULL ){
        node2->next = first;
        return node1;
      }
    }
    start = false;
  }
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if ( start->next == NULL )
    return start;

  ListNode * second = split(start, chainLength/2);
  second = mergesort(second, chainLength - chainLength/2);
  start = mergesort(start, chainLength/2);
  return merge( start, second );
}
