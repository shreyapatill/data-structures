#include <cmath>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"

using namespace std;
using namespace cs225;

void StickerSheet::copy_(const StickerSheet &other){
    baseImage_ = other.baseImage_;
    maxSticker_ = other.maxSticker_;
    stickerArray_ = new Image[maxSticker_]; 
    numSticker_ = other.numSticker_;
    xCoordinate_ = new unsigned[maxSticker_];
    yCoordinate_ = new unsigned[maxSticker_];

    for( unsigned i = 0; i < numSticker_; i++ ){
        stickerArray_[i] = other.stickerArray_[i];
        xCoordinate_[i] = other.xCoordinate_[i];
        yCoordinate_[i] = other.yCoordinate_[i];
    }
}

void StickerSheet::delete_(){
    delete [] xCoordinate_;
    delete [] yCoordinate_;
    delete [] stickerArray_;
}

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    baseImage_ = picture;

    maxSticker_ = max;
    numSticker_ = 0;

    stickerArray_ = new Image[max];
    xCoordinate_ = new unsigned[max];
    yCoordinate_ = new unsigned[max];
}
StickerSheet::~StickerSheet(){
    delete_();
}

StickerSheet::StickerSheet(const StickerSheet &other){
    copy_(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    delete_();
    copy_(other);
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    Image* sticker = new Image[max];
    unsigned* x = new unsigned[max];
    unsigned* y = new unsigned[max];
    
    if( numSticker_ > max )
        numSticker_ = max;

    for( unsigned i = 0; i < numSticker_; i++ ){
        sticker[i] = stickerArray_[i];
        x[i] = xCoordinate_[i];
        y[i] = yCoordinate_[i];
    }

    maxSticker_ = max;
    delete_();
    stickerArray_ = sticker;
    xCoordinate_ = x;
    yCoordinate_ = y;

}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    stickerArray_[numSticker_] = sticker;
    xCoordinate_[numSticker_] = x;
    yCoordinate_[numSticker_] = y;
    numSticker_++;
    return numSticker_ - 1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if( index >= numSticker_ || x >= baseImage_.width() || y >= baseImage_.height() )
        return false;
    
    xCoordinate_[index] = x;
    yCoordinate_[index] = y;

    return true;
}

void StickerSheet::removeSticker(unsigned index){
    for( unsigned i = index; i < numSticker_-1 ; i++ ){
        stickerArray_[i] = stickerArray_[i+1];
        xCoordinate_[i] = xCoordinate_[i+1];
        yCoordinate_[i] = yCoordinate_[i+1];
    }
    numSticker_--;
}

Image* StickerSheet::getSticker(unsigned index){
    if( index >= numSticker_ )
        return NULL;
    return & stickerArray_[index];
}

Image StickerSheet::render() const{
    unsigned x = baseImage_.width();
    unsigned y = baseImage_.height();

    for( unsigned i = 0; i < numSticker_ ; i++ ){
        unsigned xTemp = xCoordinate_[i] + stickerArray_[i].width();
        unsigned yTemp = yCoordinate_[i] + stickerArray_[i].height();
        if( x < xTemp )
            x = xTemp;
        if( y < yTemp )
            y = yTemp;
    }

    Image base = baseImage_;
    base.resize(x, y);

    for( unsigned i = 0; i < numSticker_ ; i++ ){
        x = xCoordinate_[i];
        y = yCoordinate_[i];
        for( unsigned w = 0; w < stickerArray_[i].width(); w++ ){
            for( unsigned h = 0; h < stickerArray_[i].height(); h++ ){
                HSLAPixel & pixelSticker = stickerArray_[i].getPixel(w, h);
                HSLAPixel & pixelBase = base.getPixel(x+w, y+h);
                if( pixelSticker.a != 0 ){
                    pixelBase.h = pixelSticker.h;
                    pixelBase.s = pixelSticker.s;
                    pixelBase.l = pixelSticker.l;
                }
            }
        }
    }

    return base;
}