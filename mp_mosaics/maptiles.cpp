/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     MosaicCanvas* mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     map<Point<3>, TileImage*> map;
     vector<Point<3>> pts;

     for( vector<TileImage>::iterator i = theTiles.begin(); i < theTiles.end(); i++ ){
         LUVAPixel pixel = i->getAverageColor();
         Point<3> p = convertToXYZ(pixel);
         pts.push_back(p);
         map[p] = &*i;
     }

     KDTree<3> tree(pts);

     for( int i = 0; i < mosaic->getRows(); i++ ){
         for( int j = 0; j < mosaic->getColumns(); j++ ){
             LUVAPixel pixel = theSource.getRegionColor(i, j);
             Point<3> point = convertToXYZ(pixel);
             Point<3> nearestNeighbor = tree.findNearestNeighbor(point);
             TileImage* best = map[nearestNeighbor];
             mosaic->setTile(i, j, best);
         }
     }

     return mosaic;
}

