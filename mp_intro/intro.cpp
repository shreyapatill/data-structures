#include "cs225/PNG.h"

#include "cs225/HSLAPixel.h"
#include "intro.h"

#include <string>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  PNG* original = new PNG();

  original->readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();

  PNG* output = new PNG(width, height);

  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width; x++) {
      HSLAPixel& in_pixel = original->getPixel(x, y);
      HSLAPixel& out_pixel = output->getPixel(width - x - 1, height - y - 1);
      
      out_pixel = in_pixel;
    }
  }

  output->writeToFile(outputFile);

  delete output;
  delete original;
  }

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  
  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width; x++) {
      HSLAPixel &pixel = png.getPixel(x, y);
      unsigned modified_width = width/3;
      if( x <= modified_width ){
        pixel.h = 154;
        pixel.s = .75;
        pixel.l = .35;
      }else if( x <= modified_width * 2 ){
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 1;
      }else{
        pixel.h = 23;
        pixel.s = 1;
        pixel.l = .62;
      }
      pixel.a = 1.0;
    }
  }
  
  return png;
}
