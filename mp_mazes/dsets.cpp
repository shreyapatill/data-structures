/**
 * @file dsets.cpp
 *
 */

#include "dsets.h"

using namespace std;

void DisjointSets::addelements (int num){
    for( int i = 0; i < num; i++ )
        elements.push_back(-1);
}

int DisjointSets::find (int elem){
    if( elements[elem] < 0 )
        return elem;
    else{
        elements[elem] = find(elements[elem]);
        return elements[elem];
    }
}

void DisjointSets::setunion (int a, int b){
    int rootA = find(a);
    int rootB = find(b);
    if( rootA == rootB )
        return;
    int size = elements[rootA] + elements[rootB];
    if( elements[rootA] > elements[rootB] ){
        elements[rootB] = size;
        elements[rootA] = rootB;
    }else{
        elements[rootA] = size;
        elements[rootB] = rootA;
    }
}

int DisjointSets::size (int elem){
    int temp = find(elem);
    return elements[temp] * -1;
}