#include "iApcFreeImageGraphicsHelper.h"
#include "iApcFreeImageGraphicsHelperInternalCode.h"

// Функция загрузки изображения из памяти
int IApcGraphicsHelperInternalFunction::createFreeImage(unsigned char *memory, size_t fileSize, TFitBitmapHolder& image)
{
  //Проверка на корректность входных данных
  if (memory == nullptr || fileSize == 0){
      std::cout << "creatFreeImage: couldn't find the file in memory.\n";
      return -1;
  }

  //Открытие потока для загрузки из памяти устройства
  TFiMemoryHolder memoryHolder;
  memoryHolder.m_pMemory = FreeImage_OpenMemory(memory, fileSize);
  if (memoryHolder.m_pMemory == nullptr){
      std::cout << "creatFreeImage(): couldn't load image from ofBuffer, opening FreeImage memory failed.\n";
      return -1;
  }

  //Опредеоение формата файла из памяти устройства
  FREE_IMAGE_FORMAT free_img_format = FreeImage_GetFileTypeFromMemory(memoryHolder.m_pMemory);
  if (free_img_format == -1){
      std::cout << "creatFreeImage(): couldn't load image from ofBuffer, unable to guess image format from memory";
      return -1;
  }

  //Если изображение формата ICO
  if(free_img_format == FIF_ICO)
  {
    //Создание FreeImage изображения
    image.m_pBitmap = FreeImage_LoadFromMemory(free_img_format, memoryHolder.m_pMemory, ICO_MAKEALPHA);
    image.m_pBitmap = FreeImage_ConvertTo24Bits(image.m_pBitmap);
    if(image.m_pBitmap == nullptr){
      std::cout << "creatFreeImage(): function is failed, error loading from memory.\n";
      return -1;
    }
    return 0;
  }

  //Если изображение формата PNG
  if(free_img_format == FIF_PNG)
  {
    //Создание FreeImage изображения
    image.m_pBitmap = FreeImage_LoadFromMemory(free_img_format, memoryHolder.m_pMemory, PNG_IGNOREGAMMA);
    if(image.m_pBitmap == nullptr){
      std::cout << "creatFreeImage(): function is failed, error loading from memory.\n";
      return -1;
    }
    return 0;
  }

  //Если изображение формата GIF
  if(free_img_format == FIF_GIF)
  {
    //Создание FreeImage изображения
    image.m_pBitmap = FreeImage_LoadFromMemory(free_img_format, memoryHolder.m_pMemory, GIF_DEFAULT);
    if(image.m_pBitmap == nullptr){
      std::cout << "creatFreeImage(): function is failed, error loading from memory.\n";
      return -1;
    }
    return 0;
  }

  //Если изображение любого другого формата
  if(free_img_format == 0)
  {
    //Создание FreeImage изображения
    image.m_pBitmap = FreeImage_LoadFromMemory(free_img_format, memoryHolder.m_pMemory, 0);
    if(image.m_pBitmap == nullptr){
      std::cout << "creatFreeImage(): function is failed, error loading from memory.\n";
      return -1;
    }
    return 0;
  }
  else
  {
    std::cout << "creatFreeImage(): function is failed, error loading from memory.\n";
    return -1;
  }
}

//Копирование в вектор
int IApcGraphicsHelperInternalFunction::copyTo(
  std::vector<uint8_t> &outputVector,
  TFiMemoryHolder &fiMemory)
{
  if(fiMemory.m_pMemory == nullptr){
    std::cout << "copyTo(): fiMemory equal nullptr.\n";
    return -1;
  }

  BYTE *imageData = nullptr;
  DWORD imageSizeInBytes = 0;

  FreeImage_AcquireMemory(fiMemory.m_pMemory, &imageData, &imageSizeInBytes);

  outputVector.resize(imageSizeInBytes);
  memcpy(outputVector.data(), imageData, imageSizeInBytes);

  return 0;

}

//Сохранение изображение в память (выгрузка из функции)
int IApcGraphicsHelperInternalFunction::saveFreeImageToMemory(
  std::vector<uint8_t> &outputVector,
  TFitBitmapHolder &image,
  FREE_IMAGE_FORMAT free_img_format)
{
  //Проверка на корректность входных данных
  if (outputVector.data() != nullptr || outputVector.size() != 0){
      std::cout << "loadFreeImageToMemory: non-empty parameters passed.\n";
      return -1;
  }

  if (image.m_pBitmap == nullptr){
    std::cout << "encodeImageToJPEG(): function is failed, failed to create image.\n";
    return -1;
  }

  //Открытие потока для загрузки в память устройства
  TFiMemoryHolder memoryHolder;
  memoryHolder.m_pMemory = FreeImage_OpenMemory(outputVector.data(), outputVector.size());
  if (memoryHolder.m_pMemory == nullptr){
      std::cout << "loadFreeImageToMemory(): couldn't load image from ofBuffer, opening FreeImage memory failed.\n";
      return -1;
  }

  if (free_img_format == FIF_JPEG)
  {
    FreeImage_SaveToMemory(free_img_format, image.m_pBitmap, memoryHolder.m_pMemory, JPEG_DEFAULT);
  }

  if (free_img_format == FIF_BMP)
  {
    FreeImage_SaveToMemory(free_img_format, image.m_pBitmap, memoryHolder.m_pMemory, BMP_DEFAULT);
  }

  copyTo(outputVector, memoryHolder);
  //Теперь необходимо записать из memoryHolder
  return 0;
}

//Вращение изображения (для функций) заменить входные параметры
int IApcGraphicsHelperInternalFunction::rotateImage(TFitBitmapHolder& image,
  double angle)
{
  if(angle <= 0)
  {
    std::cout << "rotateImage(): function is failed, uncorrected angle.\n";
  }
  image.m_pBitmap = FreeImage_Rotate(image.m_pBitmap, angle);
  if (image.m_pBitmap == nullptr){
    std::cout << "rotateImage(): function is failed, failed to create image.\n";
    return -1;
  }

  return 0;
}

//Получения размеров изображение (для функций)
int IApcGraphicsHelperInternalFunction::getImageSize(TFitBitmapHolder& image)
{
  int nImageWidth = FreeImage_GetWidth(image.m_pBitmap);
  int nImageHeight = FreeImage_GetHeight(image.m_pBitmap);
  if(!nImageWidth || !nImageHeight)
  {
    std::cout << "Image width: " << nImageWidth << "or image height: " << nImageHeight << "can't be return!";
    return -1;
  }
  else
  {
  std::cout << "Image size (width x height): " << nImageWidth << " x " << nImageHeight << ".\n";
  return 0;
  }
}
//------------------------------------------------------------------------------


//Декодирование в JPEG
int IApcGraphicsHelper::encodeImageToJPEG(unsigned char *memory,
  size_t fileSize,
  std::vector<uint8_t> &outputVector)
{
  IApcGraphicsHelperInternalFunction internalCode = IApcGraphicsHelperInternalFunction();
  TFitBitmapHolder bitmHolder;
  internalCode.createFreeImage(memory, fileSize, bitmHolder);
  if (bitmHolder.m_pBitmap == nullptr){
    std::cout << "encodeImageToJPEG(): function is failed, failed to create image.\n";
    return -1;
  }

  internalCode.saveFreeImageToMemory(outputVector, bitmHolder, FIF_JPEG);

  return 0;
}

//Декодирование в JPEG с учетом размера
int IApcGraphicsHelper::encodeImageToJPEG(unsigned char *memory,
  size_t fileSize,
  int anMaxWidth,
  int anMaxHeight,
  std::vector<uint8_t> &outputVector)
{
  IApcGraphicsHelperInternalFunction internalCode = IApcGraphicsHelperInternalFunction();
  TFitBitmapHolder bitmHolder;
  internalCode.createFreeImage(memory, fileSize, bitmHolder);
  if (bitmHolder.m_pBitmap == nullptr){
    std::cout << "encodeImageToJPEG(): function is failed, failed to create image.\n";
    return -1;
  }

  if (!FreeImage_GetWidth(bitmHolder.m_pBitmap) || !FreeImage_GetHeight(bitmHolder.m_pBitmap)){
    std::cout << "encodeImageToJPEG(): function is failed, the width or height has an incorrect size.\n";
    return -1;
  }

  if(!anMaxWidth || !anMaxHeight) {
    std::cout << "Max width: " << anMaxWidth << "or max height: " << anMaxHeight << "can't be return!";
    return -1;}

  int nImageWidth = FreeImage_GetWidth(bitmHolder.m_pBitmap);
  int nImageHeight = FreeImage_GetHeight(bitmHolder.m_pBitmap);

  if(!nImageWidth || !nImageHeight) {
    std::cout << "Max width: " << nImageWidth << "or max height: " << nImageHeight << "can't be return!";
    return -1;}

  double dblFirst = (double)anMaxWidth / (double)anMaxHeight;
  double dblSecond = (double)nImageWidth / (double)nImageHeight;

  //Если первое отношение меньше второго - режем по ширене
  std::string nTransformType = "";
  if(dblFirst < dblSecond)
  {
    nTransformType = "TRansformType_ProportionalWidth";
  }
  else
  {
    nTransformType = "TRansformType_ProportionalHeight";
  }

  if(nTransformType == "") {
    std::cout << "encodeImageToJPEG(): function is failed, error of execution.\n";
    return -1;}

  int nNewWidth = 0;
  int nNewHeigth = 0;

  if(nTransformType == "TRansformType_ProportionalWidth")
  {
    nNewWidth = anMaxWidth;
    nNewHeigth = int(double(FreeImage_GetHeight(bitmHolder.m_pBitmap)) * double(anMaxWidth) / double(FreeImage_GetWidth(bitmHolder.m_pBitmap)));
  }
  else
  {
    nNewHeigth = anMaxHeight;
    nNewWidth = int(double(FreeImage_GetWidth(bitmHolder.m_pBitmap)) * double(anMaxHeight) / double(FreeImage_GetHeight(bitmHolder.m_pBitmap)));
  }

  if (nNewWidth == 0 || nNewHeigth == 0){
    std::cout << "encodeImageToJPEG(): function is failed, error of execution.\n";
    return -1;
  }
  bitmHolder.m_pBitmap = FreeImage_Rescale(bitmHolder.m_pBitmap, nNewWidth, nNewHeigth, FILTER_BOX);

  internalCode.saveFreeImageToMemory(outputVector, bitmHolder, FIF_JPEG);

  return 0;
}

//Вращение изображения и декодирование в JPEG
int IApcGraphicsHelper::rotateImageEncodeToJPEG(unsigned char *memory,
  size_t fileSize,
  double angle,
  std::vector<uint8_t> &outputVector)
{
  IApcGraphicsHelperInternalFunction internalCode = IApcGraphicsHelperInternalFunction();
  TFitBitmapHolder bitmHolder;
  internalCode.createFreeImage(memory, fileSize, bitmHolder);
  if (bitmHolder.m_pBitmap == nullptr){
    std::cout << "encodeImageToJPEG(): function is failed, failed to create image.\n";
    return -1;
  }

  bitmHolder.m_pBitmap = FreeImage_Rotate(bitmHolder.m_pBitmap, angle);
  if(bitmHolder.m_pBitmap == nullptr){
    std::cout << "rotateImageEncodeToJPEG(): The image can't be rotate.\n";
    return -1;
  }

  internalCode.saveFreeImageToMemory(outputVector, bitmHolder, FIF_JPEG);
  return 0;
}

//Обоезает по краям изображение на заданное число пикселей
int IApcGraphicsHelper::cutImageMiddle(unsigned char *memory,
  size_t fileSize,
  int pixelCount,
  std::vector<uint8_t> &outputVector)
{
  IApcGraphicsHelperInternalFunction internalCode = IApcGraphicsHelperInternalFunction();
  TFitBitmapHolder bitmHolder;
  internalCode.createFreeImage(memory, fileSize, bitmHolder);
  if (bitmHolder.m_pBitmap == nullptr){
    std::cout << "cutImageMiddle(): function is failed, failed to create image.\n";
    return -1;
  }

  int nImageWidth = FreeImage_GetWidth(bitmHolder.m_pBitmap);
  int nImageHeight = FreeImage_GetHeight(bitmHolder.m_pBitmap);
  if(!nImageWidth || !nImageHeight) {
    std::cout << "Max width: " << nImageWidth << "or max height: " << nImageHeight << "can't be return!";
    FreeImage_Unload(bitmHolder.m_pBitmap);
    return -1;}

  //Создаем точки для обрезки изображения
  int pointLeft = pixelCount;
  int pointRight = nImageWidth - pixelCount;
  int pointTop = pixelCount;
  int pointBottom = nImageHeight - pixelCount;
  if(pointTop == 0 || pointLeft == 0 || pointRight == 0 || pointBottom == 0){
    std::cout << "cutImageMiddle(): function is failed, error of execution.\n";
    return -1;
  }

  bitmHolder.m_pBitmap = FreeImage_Copy(bitmHolder.m_pBitmap, pointLeft, pointTop, pointRight, pointBottom);
  if(bitmHolder.m_pBitmap == nullptr){
    std::cout << "cutImageMiddle(): The image can't be rotate.\n";
    return -1;
  }

  internalCode.saveFreeImageToMemory(outputVector, bitmHolder, FIF_JPEG);
  return 0;
}

//Обрезает изображение по зданным точкам
int IApcGraphicsHelper::cutImagePoints(unsigned char *memory,
  size_t fileSize,
  const int pointLeft,
  const int pointTop,
  const int pointRight,
  const int pointBottom,
  std::vector<uint8_t> &outputVector)
{
  IApcGraphicsHelperInternalFunction internalCode = IApcGraphicsHelperInternalFunction();
  TFitBitmapHolder bitmHolder;
  internalCode.createFreeImage(memory, fileSize, bitmHolder);
  if (bitmHolder.m_pBitmap == nullptr){
    std::cout << "cutImageMiddle(): function is failed, failed to create image.\n";
    return -1;
  }

  if(pointTop == 0 || pointLeft == 0 || pointRight == 0 || pointBottom == 0){
    std::cout << "cutImageMiddle(): function is failed, uncorrected poits.\n";
    return -1;
  }

  int nImageWidth = FreeImage_GetWidth(bitmHolder.m_pBitmap);
  int nImageHeight = FreeImage_GetHeight(bitmHolder.m_pBitmap);
  if(!nImageWidth || !nImageHeight) {
    std::cout << "Max width: " << nImageWidth << "or max height: " << nImageHeight << "can't be return!";
    return -1;}

  bitmHolder.m_pBitmap = FreeImage_Copy(bitmHolder.m_pBitmap, pointLeft, pointTop, pointRight, pointBottom);
  if(bitmHolder.m_pBitmap == nullptr){
    std::cout << "cutImageMiddle(): The image can't be rotate.\n";
    return -1;
  }

  internalCode.saveFreeImageToMemory(outputVector, bitmHolder, FIF_JPEG);
  return 0;
}

//Получение формата изображения
int IApcGraphicsHelper::getImageFormat(unsigned char *memory,
  size_t fileSize,
  std::string &outputFormat)
{
  //Проверка на корректность входных данных
  if (memory == nullptr || fileSize == 0){
      std::cout << "creatFreeImage: couldn't find the file in memory.\n";
      return -1;
  }

  //Открытие потока для загрузки из памяти устройства
  TFiMemoryHolder memoryHolder;
  memoryHolder.m_pMemory = FreeImage_OpenMemory(memory, fileSize);
  if (memoryHolder.m_pMemory == nullptr){
      std::cout << "creatFreeImage(): couldn't load image from ofBuffer, opening FreeImage memory failed.\n";
      return -1;
  }

  //Опредеоение формата файла из памяти устройства
  FREE_IMAGE_FORMAT free_img_format = FreeImage_GetFileTypeFromMemory(memoryHolder.m_pMemory);
  if (free_img_format == -1){
      std::cout << "creatFreeImage(): couldn't load image from ofBuffer, unable to guess image format from memory";
      return -1;
  }

  if (memoryHolder.m_pMemory == nullptr)
  {
    std::cout << "creatFreeImage(): WARNING! The stream is not closed.\n";
    return -1;
  }

  outputFormat = FreeImage_GetFormatFromFIF(free_img_format);
  std::cout << "File type: " << FreeImage_GetFormatFromFIF(free_img_format) << "\n";
  return 0;
}

//Декодирование в BMP
int IApcGraphicsHelper::encodeImageToBMP(unsigned char *memory,
  size_t fileSize,
  std::vector<uint8_t> &outputVector)
{
  IApcGraphicsHelperInternalFunction internalCode = IApcGraphicsHelperInternalFunction();
  TFitBitmapHolder bitmHolder;
  internalCode.createFreeImage(memory, fileSize, bitmHolder);
  if (bitmHolder.m_pBitmap == nullptr){
    std::cout << "encodeImageToBMP(): function is failed, failed to create image.\n";
    return -1;
  }

  internalCode.saveFreeImageToMemory(outputVector, bitmHolder, FIF_BMP);
  return 0;
}
