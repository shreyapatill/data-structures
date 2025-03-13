#include "Image.h"
#include <cmath>
#include <iostream>

using cs225::HSLAPixel;
using cs225::PNG;


void Image::lighten(){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l += 0.1;
            if(pixel.l > 1)
                pixel.l = 1;
        }
    }
}
void Image::lighten(double amount){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l += amount;
            if(pixel.l > 1)
                pixel.l = 1;
        }
    }
}
void Image::darken(){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l -= .1;
            if(pixel.l < 0)
                pixel.l = 0;
        }
    }    
}
void Image::darken(double amount){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l -= amount;
            if(pixel.l < 0)
                pixel.l = 0;
        }
    }  
}

void Image::saturate(){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s += .1;
            if(pixel.s > 1)
                pixel.s = 1;
        }
    }  
}
void Image::saturate(double amount){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s += amount;
            if(pixel.s > 1)
                pixel.s = 1;
        }
    }  
}
void Image::desaturate(){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s -= .1;
            if(pixel.s < 0)
                pixel.s = 0;
        }
    }  
}
void Image::desaturate(double amount){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s -= amount;
            if(pixel.s < 0)
                pixel.s = 0;
        }
    }
}
void Image::grayscale(){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}
void Image::rotateColor(double degrees){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            pixel.h += degrees;
            while(pixel.h < 0){
                pixel.h += 360;
            }
            pixel.h = fmod(pixel.h, 360);
        }
    }
}
void Image::illinify(){
    for(unsigned x = 0; x < width(); x++){
        for(unsigned y = 0; y < height(); y++){
            HSLAPixel & pixel = getPixel(x, y);
            if(pixel.h >= 114 && pixel.h <= 243)
                pixel.h = 216;
            else
                pixel.h = 11;
        }
    }
}
void Image::scale(double factor){
    double scaledWidth = width()*factor;
    double scaledHeight = height()*factor;

    PNG * original = new PNG(*this);
    this->resize((unsigned)scaledWidth, (unsigned)scaledHeight);

    unsigned newX = 0;
    unsigned newY = 0;

    for(unsigned x = 0; x < scaledWidth; x++){
        for(unsigned y = 0; y < scaledHeight; y++){
            newX = floor(x/factor);
            newY = floor(y/factor);

            HSLAPixel &targetPixel = this->getPixel(x,y);
            HSLAPixel &originalPixel = original->getPixel((unsigned)newX, (unsigned)newY);
            targetPixel = originalPixel;
        }
    }        

}
void Image::scale(unsigned w, unsigned h){
    double widthRatio = (double)w/(double)width();
    double heightRatio = (double)h/(double)height();

    if(widthRatio < heightRatio)
        scale(widthRatio);
    else
        scale(heightRatio);
}