/**
 * @file drawable.h
 * Declaration of the Drawable class.
 */

#pragma once

#include "cs225/PNG.h"
using namespace cs225;

/**
 * A pure virtual interface class that can draw itself to a canvas
 */
class Drawable
{
  public:
    virtual ~Drawable() {};

    /**
     * This method will draw the object onto the canvas.
     *
     * @param canvas to draw onto.
     */
    virtual void draw(PNG* canvas) const = 0;
};

