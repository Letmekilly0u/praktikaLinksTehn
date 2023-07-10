#include "iApcTest.h"

const int formatsCount = 20;

std::string nabor[formatsCount] = {"1.png", "2.png", "3.png", "4.png", "5.png",
"1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp",
"1.gif", "2.gif", "3.gif", "4.gif", "5.gif",
"1.ico", "2.ico", "3.ico", "4.ico", "5.ico"};

std::vector<uint8_t> LoadImageToMemory(std::string nameFile)
{
  std::ifstream file(nameFile, std::ios::binary | std::ios::ate);
  size_t size = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<char> buffer;
  buffer.resize(size);
  file.read(buffer.data(), size);
  std::vector<uint8_t> outVector;
  outVector.resize(size);

  for(int i = 0; i < outVector.size(); i++)
  {
    outVector[i] = buffer[i];
  }

  return outVector;
}


int Test::TestEncodeToJPEG(std::string *filesNames)
{
  int failedTestsCount = 0;
  int passedTestCount = 0;
  FreeImageLibHolder init = FreeImageLibHolder();
  std::cout << "__________________________________________________________________________________________\n";
  std::cout << "Testing function encodeImageToJPEG\n";
  for(int i = 0; i < formatsCount; i++)
  {
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Test number: " << (i+1) << "\n";
    std::cout << "File name: " << filesNames[i] << "\n";
    std::vector<uint8_t> memoryImg = LoadImageToMemory(filesNames[i]);
    std::cout << "Input vector size : " << memoryImg.size() << "\n";
    std::vector<uint8_t> saveToMemoryVector;
    std::string outStr = "";
    IApcGraphicsHelper GraphicHelper;
    int errorValue = 0;
    errorValue = GraphicHelper.encodeImageToJPEG(memoryImg.data(), memoryImg.size(), saveToMemoryVector);
    GraphicHelper.getImageFormat(memoryImg.data(), memoryImg.size(), outStr);
    if (errorValue != 0 || saveToMemoryVector.size() == 0)
    {
      std::cout << "The test number: " << (i+1) <<" failed validation.\n";
      //std::cout << "Image format: " << outStr << "\n";
      std::cout << "Output vector size: " << saveToMemoryVector.size() << "\n";
      failedTestsCount++;
      std::cout << "After convertion | ";
      GraphicHelper.getImageFormat(saveToMemoryVector.data(), saveToMemoryVector.size(), outStr);
    }
    else
    {
      std::cout << "The test number: " << (i+1) <<" was successfully completed.\n";
      //std::cout << "Image format: " << outStr << "\n";
      std::cout << "Output vector size: " << saveToMemoryVector.size() << "\n";
      passedTestCount++;
      std::cout << "After convertion | ";
      GraphicHelper.getImageFormat(saveToMemoryVector.data(), saveToMemoryVector.size(), outStr);
        //std::cout << "Image format: " << outStr << "\n";
    }
  }
  std::cout << "#################################################################\n";
  std::cout << "RESULT: \n";
  std::cout << "Total number of tests: " << formatsCount << "\n";
  std::cout << "Number of tests passed:" << passedTestCount << "\n";
  std::cout << "Number of failed tests:" << failedTestsCount << "\n";
  std::cout << "#################################################################\n";
  return 0;
}



int Test::TestEncodeToBMP(std::string *filesNames)
{
  int failedTestsCount = 0;
  int passedTestCount = 0;
  FreeImageLibHolder init = FreeImageLibHolder();
  std::cout << "__________________________________________________________________________________________\n";
  std::cout << "Testing function encodeImageToBMP\n";
  for(int i = 0; i < formatsCount; i++)
  {
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Test number: " << (i+1) << "\n";
    std::cout << "File name: " << filesNames[i] << "\n";
    std::vector<uint8_t> memoryImg = LoadImageToMemory(filesNames[i]);
    std::cout << "Input vector size : " << memoryImg.size() << "\n";
    std::vector<uint8_t> saveToMemoryVector;
    std::string outStr = "";
    IApcGraphicsHelper GraphicHelper;
    int errorValue = 0;
    errorValue = GraphicHelper.encodeImageToBMP(memoryImg.data(), memoryImg.size(), saveToMemoryVector);
    GraphicHelper.getImageFormat(memoryImg.data(), memoryImg.size(), outStr);
    if (errorValue != 0 || saveToMemoryVector.size() == 0)
    {
      std::cout << "The test number: " << (i+1) <<" failed validation.\n";
      //std::cout << "Image format: " << outStr << "\n";
      std::cout << "Output vector size: " << saveToMemoryVector.size() << "\n";
      failedTestsCount++;
      std::cout << "After convertion | ";
      GraphicHelper.getImageFormat(saveToMemoryVector.data(), saveToMemoryVector.size(), outStr);
    }
    else
    {
      std::cout << "The test number: " << (i+1) <<" was successfully completed.\n";
      //std::cout << "Image format: " << outStr << "\n";
      std::cout << "Output vector size: " << saveToMemoryVector.size() << "\n";
      passedTestCount++;
      std::cout << "After convertion | ";
      GraphicHelper.getImageFormat(saveToMemoryVector.data(), saveToMemoryVector.size(), outStr);
        //std::cout << "Image format: " << outStr << "\n";
    }
  }
  std::cout << "#################################################################\n";
  std::cout << "RESULT: \n";
  std::cout << "Total number of tests: " << formatsCount << "\n";
  std::cout << "Number of tests passed:" << passedTestCount << "\n";
  std::cout << "Number of failed tests:" << failedTestsCount << "\n";
  std::cout << "#################################################################\n";
  return 0;
}



int Test::TestRotateImageEncodeToJPEG(std::string *filesNames)
{
  int failedTestsCount = 0;
  int passedTestCount = 0;
  FreeImageLibHolder init = FreeImageLibHolder();
  std::cout << "__________________________________________________________________________________________\n";
  std::cout << "Testing function rotateImageEncodeToJPEG\n";
  for(int i = 0; i < formatsCount; i++)
  {
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Test number: " << (i+1) << "\n";
    std::cout << "File name: " << filesNames[i] << "\n";
    std::vector<uint8_t> memoryImg = LoadImageToMemory(filesNames[i]);
    std::cout << "Input vector size : " << memoryImg.size() << "\n";
    std::vector<uint8_t> saveToMemoryVector;
    std::string outStr = "";
    IApcGraphicsHelper GraphicHelper;
    int errorValue = 0;
    errorValue = GraphicHelper.rotateImageEncodeToJPEG(memoryImg.data(), memoryImg.size(), 30, saveToMemoryVector);
    GraphicHelper.getImageFormat(memoryImg.data(), memoryImg.size(), outStr);
    if (errorValue != 0 || saveToMemoryVector.size() == 0)
    {
      std::cout << "The test number: " << (i+1) <<" failed validation.\n";
      //std::cout << "Image format: " << outStr << "\n";
      std::cout << "Output vector size: " << saveToMemoryVector.size() << "\n";
      failedTestsCount++;
      std::cout << "After rotation and encode | ";
      GraphicHelper.getImageFormat(saveToMemoryVector.data(), saveToMemoryVector.size(), outStr);
    }
    else
    {
      std::cout << "The test number: " << (i+1) <<" was successfully completed.\n";
      //std::cout << "Image format: " << outStr << "\n";
      std::cout << "Output vector size: " << saveToMemoryVector.size() << "\n";
      passedTestCount++;
      std::cout << "After rotation and encode | ";
      GraphicHelper.getImageFormat(saveToMemoryVector.data(), saveToMemoryVector.size(), outStr);
        //std::cout << "Image format: " << outStr << "\n";
    }
  }
  std::cout << "#################################################################\n";
  std::cout << "RESULT: \n";
  std::cout << "Total number of tests: " << formatsCount << "\n";
  std::cout << "Number of tests passed:" << passedTestCount << "\n";
  std::cout << "Number of failed tests:" << failedTestsCount << "\n";
  std::cout << "#################################################################\n";
  return 0;
}
