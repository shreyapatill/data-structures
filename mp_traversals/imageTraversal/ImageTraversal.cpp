#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param point1 First pixel
 * @param point2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & point1, const HSLAPixel & point2) {
  double h = fabs(point1.h - point2.h);
  double s = point1.s - point2.s;
  double l = point1.l - point2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  end = false;
  traversal_ = NULL;
}

ImageTraversal::Iterator::Iterator(PNG png, Point point, double tolerance, ImageTraversal* traversal) {
  png_ = png;
  begin_ = point;
  point_ = point;
  tolerance_ = tolerance;
  traversal_ = traversal;
  end = false;

  for( unsigned i = 0; i < png.width()*png.height() ; i++ )
    finished_.push_back(false);
  
  if( operationHelper(point) ){
    finished_[ point.x + point.y*png.width() ] = true;
    traversal->add(point);
    ordered_.push_back(point);
  }else{
    end = true;
  }

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal_ of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  auto point1 = Point( point_.x+1, point_.y );
  auto point2 = Point( point_.x, point_.y+1 );
  auto point3 = Point( point_.x-1, point_.y );
  auto point4 = Point( point_.x, point_.y-1 );

  if( operationHelper( point1 ) )
    traversal_->add( point1 );
    
  if( operationHelper( point2 ) )
    traversal_->add( point2 );

  if( operationHelper( point3 ) )
    traversal_->add( point3 );

  if( operationHelper( point4 ) )
    traversal_->add( point4 );

  if( traversal_->empty() ){
    end = true;
    return *this;
  }

  Point p = traversal_->pop();
  end = false;
  
  while( finished_[p.x + p.y*png_.width() ] ){
    if( traversal_->empty() ){
      end = true;
      return *this;
    }
    p = traversal_->pop();
  }

  point_ = p;
  ordered_.push_back(point_);  
  finished_[p.x + p.y*png_.width() ] = true;
  
  return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return point_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return end!=other.end;
}

bool ImageTraversal::Iterator::operationHelper(Point p){
  if( p.x < 0 || p.y < 0 || p.y >= png_.height() || p.x >= png_.width() )
    return false;

  HSLAPixel begin = png_.getPixel(begin_.x, begin_.y);
  HSLAPixel current = png_.getPixel(p.x, p.y);

  if( calculateDelta(begin, current) >= tolerance_ )
    return false;
  
  return true;
}
