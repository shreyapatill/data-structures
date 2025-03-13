/* your code here! */
#include "maze.h"

SquareMaze::SquareMaze(){
    borders_ = new vector<Node>;
    dSets_ = new DisjointSets(); 
    width_ = 0;
    height_ = 0;
}

void SquareMaze::makeMaze(int width, int height){
    width_ = width;
    height_ = height;

    int area = width_ * height_;
    dSets_->addelements(area);

    for( int i = 0; i < area; i++ )
        borders_->push_back(Node(true, true));

    for( int i = 0; i < area - 1; i++ ){
        vector<int> directions;
        if( (i+1)%width_ != 0 && dSets_->find(i) != dSets_->find(i+1) )
            directions.push_back(0);
        if( i < width_*(height_-1) && dSets_->find(i) != dSets_->find(i+width_) )
            directions.push_back(1);
        if( i%width_ != 0 && dSets_->find(i) != dSets_->find(i-1) )
            directions.push_back(2);
        if( i >= width_ && dSets_->find(i) != dSets_->find(i-width_) )
            directions.push_back(3);
        if( directions.size() == 0 )
            continue;
        int rand_dir = directions[ rand() % directions.size() ];
        if( rand_dir == 0 ){
            dSets_->setunion(i, i + 1);
            (*borders_)[i].first_ = false;
        }else if(rand_dir == 1){
            dSets_->setunion(i, i + width_);
            (*borders_)[i].second_ = false;
        }else if(rand_dir == 2){
            dSets_->setunion(i, i - 1);
            (*borders_)[i-1].first_ = false;
        }else if(rand_dir == 3){
            dSets_->setunion(i, i - width_);
            (*borders_)[i-width_].second_ = false;
        }
    }
}

bool SquareMaze::canTravel (int x_coor, int y_coor, int dir) const{
    if( dir == 0 ) {
        if( x_coor >= width_ - 1 )
            return false;
        bool walls_first = (*borders_)[ x_coor + y_coor * width_ ].first_;
        return !walls_first;
    }else if( dir == 1 ){
        if( y_coor >= height_ - 1 )
            return false;
        bool walls_second = (*borders_)[ x_coor + y_coor * width_ ].second_;
        return !walls_second;
    }else if( dir == 2 ){
        if( x_coor < 1 )
            return false;
        bool walls_first = (*borders_)[ x_coor - 1 + y_coor * width_ ].first_;
        return !walls_first;
    }else if( dir == 3 ){
        if( y_coor < 1 )
            return false;
        bool walls_second = (*borders_)[ x_coor + ( y_coor - 1 ) * width_ ].second_;
        return !walls_second;
    }else{
        return false;
    }
}

void SquareMaze::setWall (int x_coor, int y_coor, int dir, bool exists){
    if( dir == 0 )
        (*borders_)[ x_coor + y_coor * width_ ].first_ = exists;
    else
        (*borders_)[x_coor + y_coor * width_].second_ = exists;
}

vector<int> SquareMaze::solveMaze(){
    vector<vector<pair<int, int>>> solve;
    for( int x = 0; x < width_; x++ ){
        solve.push_back(vector<pair<int, int>>());
        for( int y = 0; y < height_; y++ )
            solve.back().push_back(pair<int, int>(-1,-1));
    }
    solveHelper( &solve, pair<int, int>(0,0) );
    pair<int, int> pr( 0, height_ - 1 );
    int longest = solve[0][height_-1].first;
    for( int x = 0; x < width_; x++ ){
        if( solve[x][height_-1].first > longest ){
            longest = solve[x][height_- 1].first;
            pr = pair<int, int>(x, height_ - 1);
        }
    }
    vector<int> solution;
    while( pr != pair<int, int>(0, 0) ){
        int x = pr.first;
        int y = pr.second;
        int parent = solve[x][y].second;
        int dir = -1;
        dir = parent == 0 ? 2 : dir;
        dir = parent == 1 ? 3 : dir;
        dir = parent == 2 ? 0 : dir;
        dir = parent == 3 ? 1 : dir;
        solution.push_back(dir);
        pr = (parent == 0) ? pair<int, int>(x+1, y) : pr;
        pr = (parent == 1) ? pair<int, int>(x, y+1) : pr;
        pr = (parent == 2) ? pair<int, int>(x-1, y) : pr;
        pr = (parent == 3) ? pair<int, int>(x, y-1) : pr;
    }
    reverse(solution.begin(), solution.end());
    return solution;
}

void SquareMaze::solveHelper(vector<vector<pair<int, int>>> * answer, pair<unsigned, unsigned> front){
    int x = front.first;
    int y = front.second;
    if( ( !canTravel(x, y, 0) || (*answer)[x+1][y].second == 0) && ( !canTravel(x, y, 1) || (*answer)[x][y+1].second == 1) && ( !canTravel(x, y, 2) || (*answer)[x-1][y].second == 2) && ( !canTravel(x, y, 3) || (*answer)[x][y-1].second == 3) )
        return;
    pair<int, int> pr = (*answer)[x][y];
    if( canTravel(x, y, 0) && (*answer)[x+1][y].first == -1 ){
        (*answer)[x+1][y] = pair<int, int>(pr.first+1, 2);
        solveHelper( answer, pair<int, int>(x+1, y) );
    }
    if( canTravel(x, y, 1) && (*answer)[x][y+1].first == -1 ){
        (*answer)[x][y+1] = pair<int, int>(pr.first+1, 3);
        solveHelper( answer, pair<int, int>(x, y+1) );
    }
    if( canTravel(x, y, 2) && (*answer)[x-1][y].first == -1 ){
        (*answer)[x-1][y] = pair<int, int>(pr.first+1, 0);
        solveHelper( answer, pair<int, int>(x-1, y) );
    }
    if( canTravel(x, y, 3) && (*answer)[x][y-1].first == -1 ){
        (*answer)[x][y-1] = pair<int, int>(pr.first+1, 1);
        solveHelper( answer, pair<int, int>(x, y-1) );
    }
}


PNG* SquareMaze::drawMaze() const{
    PNG * png = new PNG(width_ * 10 + 1, height_ * 10 + 1);
    for( int x = 0; x < width_; x++ ){
        for( int y = 0; y < height_; y++ ){
            if( y == 0 ){
                for( unsigned i = 0; i < 10; i++ ){
                    if( 10*x + i < 1 || 10*x + i > 9 ){
                        HSLAPixel & pixel = png->getPixel(10*x + i , 0);
                        pixel.l = 0;
                    }
                }
            }
            if( x == 0 ){
                for( unsigned i = 0; i < 10; i++ ){
                    HSLAPixel & pixel = png->getPixel(0 , 10*y + i);
                    pixel.l = 0;
                }
            }
            if( !canTravel(x, y, 0) ){
                for( unsigned i = 0; i <= 10; i++ ){
                    HSLAPixel & pixel = png->getPixel(10 * (x+1) , 10*y + i);
                    pixel.l = 0;
                }
            }
            if( !canTravel(x, y, 1) ){
                for( unsigned i = 0; i <= 10; i++ ){
                    HSLAPixel & pixel = png->getPixel(10*x + i , 10 * (y+1) );
                    pixel.l = 0;
                }
            }
        }
    }

	return png;
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG * png = drawMaze();
    vector<int> sol = solveMaze();
    pair<int, int> point( 5, 5 );

    for( auto s : sol ){
        for( int i = 0; i < 10; i++ ){
            HSLAPixel & pixel = png->getPixel(point.first, point.second);
            pixel.h = 0;
            pixel.s = 1;
            pixel.l = 0.5;
            if( s == 0 )
                point.first++;
            else if( s == 1 )
                point.second++;
            else if( s == 2 )
                point.first--;
            else if( s == 3 )
                point.second--;
        }
    }
    HSLAPixel & pixel = png->getPixel(point.first, point.second);
    pixel.h = 0;
    pixel.s = 1;
    pixel.l = 0.5;

    point.first -= 4;
    point.second += 5;

    for( int i = point.first; i < point.first + 9; i++ ) {
        HSLAPixel & pixel = png->getPixel( i, height_*10 );
        pixel.l = 1;
    }

    return png;
}