/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>


using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int currDimensions) const
{
    /**
     * @todo Implement this function!
     */
    if( first[currDimensions] == second[currDimensions] )
      return (first < second);
    return first[currDimensions] < second[currDimensions];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int x = 0;
     int y = 0;

     for ( int i = 0; i < Dim; i++ ){
       x += (target[i] - currBest[i])*(target[i] - currBest[i]);
       y += (target[i] - potential[i])*(target[i] - potential[i]);
     }

     if( x == y )
      return potential < currBest;

     return x > y ;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     size = newPoints.size();

     if( size == 0 ){
       root = NULL;
       return;
     }

     vector<Point<Dim>> vec = newPoints;
     root = new KDTreeNode();
     nodeToVec( vec, root, 0);
}

template <int Dim>
void KDTree<Dim>::nodeToVec(vector<Point<Dim>> newPoints, KDTreeNode* myNode, int currDimensions ){
  int size = newPoints.size();
  vector<Point<Dim>> vec;

  while( !newPoints.empty() ){
    auto min = newPoints[0];
    int index = 0;

    for( size_t i = 1; i < newPoints.size(); i++ ){
      if( smallerDimVal(newPoints[i], min, currDimensions ) ){
        min = newPoints[i];
        index = i;
      }
    }

    vec.push_back(min);
    newPoints.erase(newPoints.begin()+index);
  }

  vector<Point<Dim>> left;
  vector<Point<Dim>> right;
  int middle = ( size - 1 ) / 2;
  myNode->point = vec[middle];

  for( int i = 0; i < middle; i++ )
    left.push_back( vec[i] );

  for( int i = middle + 1; i < size; i++ )
    right.push_back( vec[i] );

  if( left.size() > 0 ){
    myNode->left = new KDTreeNode();
    nodeToVec( left, myNode->left, (currDimensions + 1) % Dim );
  }else{
    myNode->left = NULL;
  }
  
  if( right.size() > 0 ){
    myNode->right = new KDTreeNode();
    nodeToVec( right, myNode->right, (currDimensions + 1) % Dim );
  }else{
    myNode->right = NULL;
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   delete root;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if( !root )
      return Point<Dim>();

    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode* currentNode, int currDimensions) const 
{
  Point<Dim> currBest;

  if( smallerDimVal(query, currentNode->point, currDimensions) ){

    if( currentNode->left ){

      currBest = findNearestNeighbor(query, currentNode->left, (currDimensions+1) % Dim);

      if( shouldReplace(query, currBest, currentNode->point) )
        currBest = currentNode->point;

    }
    else{

      currBest = currentNode->point;

    }

    if( currentNode->right ){

      int distance = 0;

      for( size_t i = 0; i < Dim; i++ )
        distance += (currBest[i] - query[i]) * (currBest[i] - query[i]);

      int dimDistance = (currentNode->point[currDimensions] - query[currDimensions]) * (currentNode->point[currDimensions] - query[currDimensions]);

      if( distance >= dimDistance ){
        auto nearestNeighborRight = findNearestNeighbor(query, currentNode->right, (currDimensions+1) % Dim);

        if( shouldReplace(query, currBest, nearestNeighborRight) )
          currBest = nearestNeighborRight;

      }

    }

  }
  else {

    if( currentNode->right){

      currBest = findNearestNeighbor(query, currentNode->right, (currDimensions+1) % Dim);

      if( shouldReplace(query, currBest, currentNode->point) )
        currBest = currentNode->point;

    }
    else{

      currBest = currentNode->point;

    }
    if(currentNode->left){

      int distance = 0;

      for(size_t i = 0; i < Dim; i++)
        distance += (currBest[i] - query[i]) * (currBest[i] - query[i]);

      int dimDistance = (currentNode->point[currDimensions] - query[currDimensions]) * (currentNode->point[currDimensions] - query[currDimensions]);

      if(distance >= dimDistance){

        auto nearestNeighborLeft = findNearestNeighbor(query, currentNode->left, (currDimensions+1) % Dim);
        
        if( shouldReplace(query, currBest, nearestNeighborLeft) )
          currBest = nearestNeighborLeft;

      }
    }

  }

  return currBest;
}