#include "iApcFreeImageGraphicsHelper.h"


//Внешние функции
//Загрузка изображения в память (дя того чтобы тестировать обертку надо что-то поожить в память и это что-то храниться в типе uint8_t и имеет размер size_t)
std::vector<uint8_t> LoadImageToMemory(std::string nameFile);

//Касс тестирования
class Test
{
public:
  Test()
  {
    std::cout << "Launching the autotest system\n";
  }

  ~Test()
  {
    std::cout << "Shutduwn of the autotest system\n";
  }

  static int TestEncodeToJPEG(std::string *filesNames);

  static int TestEncodeToBMP(std::string *filesNames);

  static int TestRotateImageEncodeToJPEG(std::string *filesNames);

};
