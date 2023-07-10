#include <iostream>
#include <FreeImage.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstring>


//Класс (обертка FITBITMAP)
class TFitBitmapHolder
{
public:
  FIBITMAP* m_pBitmap;

  TFitBitmapHolder()
  :m_pBitmap(nullptr){};

  ~TFitBitmapHolder()
  {
    if(m_pBitmap){
    FreeImage_Unload(m_pBitmap);
    }
  }
};

//Класс (обертка FIMEMORY)
class TFiMemoryHolder
{
public:
  FIMEMORY* m_pMemory;

  TFiMemoryHolder()
  :m_pMemory(nullptr){};

  ~TFiMemoryHolder()
  {
    if(m_pMemory){
    FreeImage_CloseMemory(m_pMemory);
    }
  }
};

//Класс, описывающий внутриннюю реализацию библиотеки, скрытую от пользователя
class IApcGraphicsHelperInternalFunction
{
public:
  //Создание изображения FreeImage (BMP формат)
  static int createFreeImage(unsigned char *memory,
    size_t fileSize,
    TFitBitmapHolder& image);

  //Сохранение изображение в память (выгрузка из функции)
  static int saveFreeImageToMemory(
    std::vector<uint8_t> &outputVector,
    TFitBitmapHolder &image,
    FREE_IMAGE_FORMAT free_img_format);

  //Копирование в вектор
  static int copyTo(
    std::vector<uint8_t> &outputVector,
    TFiMemoryHolder &fiMemory);

  //Вращение изображения (для функций)
  static int rotateImage(TFitBitmapHolder& image,
    double angle);

//Получения размеров изображение (для функций)
  static int getImageSize(TFitBitmapHolder& image);
};
