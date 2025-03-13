#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image pixar;
  pixar.readFromFile("pixar.png");
  Image i;
  i.readFromFile("i.png");
  i.scale(.23);
  Image words;
  words.readFromFile("words.png");
  words.scale(.5);

  StickerSheet sheet(pixar, 2);
  sheet.addSticker(i, 230, 220);
  sheet.addSticker(words, 210, 20);

  Image myImage = sheet.render();

  myImage.writeToFile("myImage.png");

  return 0;
}
