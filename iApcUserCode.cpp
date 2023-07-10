#include "iApcTest.h"

const int formatsCount1 = 20;

std::string nabor1[formatsCount1] = {"1.png", "2.png", "3.png", "4.png", "5.png",
"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp",
"1.gif", "2.gif", "3.gif", "4.gif", "5.gif",
"1.ico", "2.ico", "3.ico", "4.ico", "5.ico"};

int main(int argc, char **argv) {

  Test testVariable = Test();
  testVariable.TestEncodeToJPEG(nabor1);
  testVariable.TestEncodeToBMP(nabor1);
  testVariable.TestRotateImageEncodeToJPEG(nabor1);
  return 0;
}




































/*FreeImageLibHolder init = FreeImageLibHolder();
std::vector<uint8_t> memoryImg = LoadImageToMemory("one.png");
std::vector<uint8_t> saveToMemoryVector;
std::string outStr = "";
//size_t saveVectotSize = 10;
//saveToMemoryVector.resize(saveVectotSize);
//FIBITMAP* image;
IApcGraphicsHelper GraphicHelper;
//GraphicHelper.CreatImageBMP(memoryImg.data(), memoryImg.size(), image);
//GraphicHelper.encodeImageToJPEG(memoryImg.data(), memoryImg.size(), saveToMemoryVector);
      //GraphicHelper.rotateImageEncodeToJPEG(saveToMemoryVector.data(), saveToMemoryVector.size(), 70);
//GraphicHelper.encodeImageToJPEG(memoryImg.data(), memoryImg.size(), 150, 150,saveToMemoryVector);
//GraphicHelper.rotateImageEncodeToJPEG(memoryImg.data(), memoryImg.size(), 70, saveToMemoryVector);
//GraphicHelper.cutImageMiddle(memoryImg.data(), memoryImg.size(), 60, saveToMemoryVector);
//GraphicHelper.cutImagePoints(memoryImg.data(), memoryImg.size(), 60, 60, 600, 300, saveToMemoryVector);
//GraphicHelper.getImageFormat(memoryImg.data(), memoryImg.size(), saveToMemoryVector, outStr);
//GraphicHelper.encodeImageToBMP(memoryImg.data(), memoryImg.size(), saveToMemoryVector);
*/
