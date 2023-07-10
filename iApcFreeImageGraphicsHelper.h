#include <iostream>
#include <FreeImage.h>
#include <string>
#include <algorithm>
#include <fstream>
class TFitBitmapHolder;
class TFiMemoryHolder;

// Класс для инициализации и уничтожения библиотеки автоматически
class FreeImageLibHolder
{
  public:
    FreeImageLibHolder()
    {
      FreeImage_Initialise();
    }
    ~FreeImageLibHolder()
    {
      FreeImage_DeInitialise();
    }
};

class IApcGraphicsHelper
{
public:
  //Декодирование в JPEG
  static int encodeImageToJPEG(unsigned char *memory,
    size_t fileSize,
    std::vector<uint8_t> &outputVector);

  //Декодирование в JPEG с учетом размера
  static int encodeImageToJPEG(unsigned char *memory,
    size_t fileSize,
    int anMaxWidth,
    int anMaxHeight,
    std::vector<uint8_t> &outputVector);

  //Вращение изображения и декодирование в JPEG
  static int rotateImageEncodeToJPEG(unsigned char *memory,
    size_t fileSize,
    double angle,
    std::vector<uint8_t> &outputVector);

  //Обоезает по краям изображение на заданное число пикселей
  static int cutImageMiddle(unsigned char *memory,
    size_t fileSize,
    int pixelCount,
    std::vector<uint8_t> &outputVector);

 //Обрезает изображение по зданным точкам
 static int cutImagePoints(unsigned char *memory,
   size_t fileSize,
   const int pointLeft,
   const int pointTop,
   const int pointRight,
   const int pointBottomop,
   std::vector<uint8_t> &outputVector);

//Получение формата изображения
static int getImageFormat(unsigned char *memory,
  size_t fileSize,
  std::string &outputFormat);

//Декодирование в BMP
static int encodeImageToBMP(unsigned char *memory,
  size_t fileSize,
  std::vector<uint8_t> &outputVector);
};
