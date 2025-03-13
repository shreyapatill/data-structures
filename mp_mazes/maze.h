#pragma once

#include <queue>
#include <map>
#include <stack>
#include <vector>
#include <utility>

#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
using namespace cs225;

class SquareMaze{
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel (int x_coor, int y_coor, int dir) const;
        void setWall (int x_coor, int y_coor, int dir, bool exists);
        vector<int> solveMaze();
        void solveHelper(vector<vector<pair<int, int>>> * answer, pair<unsigned, unsigned> front);
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();
    private:
        class Node {
        public:
            Node(bool first, bool second) {
                first_ = first;
                second_ = second;
            }
            bool first_;
            bool second_;
        };
        int width_, height_;
        DisjointSets * dSets_;
        vector<Node> * borders_;
};