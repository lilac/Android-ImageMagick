#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
//#include "magick_MagickImage.h"
#include "jmagick.h"

#include <android/log.h>

#define APPNAME "Magick"

#define LOG(a) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a);
#define LOG2(a,b) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, a, b);


/*
 * Class:     magick_MagickImage
 * Method:    initMultiImage
 * Signature: ([Lmagick/MagickImage;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_initMultiImage
  (JNIEnv *env, jobject self, jobjectArray images)
{
    Image *image, *newImage, *lastImage, *p;
    jsize arrayLen;
    jobject obj;
    jfieldID fieldID = 0;
    ExceptionInfo exception;
    int i;

    arrayLen = (*env)->GetArrayLength(env, images);
    if (arrayLen < 1) {
        throwMagickException(env, "No images specified");
        return;
    }

    /* Get the first element in the array and clone it. */
    obj = (*env)->GetObjectArrayElement(env, images, 0);
    if (obj == NULL) {
        throwMagickException(env, "First image in array null");
        return;
    }
    image = (Image*) getHandle(env, obj, "magickImageHandle", &fieldID);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain image handle");
        return;
    }

    GetExceptionInfo(&exception);
    newImage = CloneImage(image, 0, 0, 0, &exception);
    if (newImage == NULL) {
        throwMagickApiException(env, "Unable to clone image", &exception);
        DestroyExceptionInfo(&exception);
        return;
    }

    /* Move the lastImage pointer to the last image of the list. */
    for (lastImage = newImage;
         lastImage->next != NULL;
         lastImage = lastImage->next)
        ;

    /* Move the newImage pointer to the head of the list. */
    for (; newImage->previous != NULL; newImage = newImage->previous)
        ;

    /* Clone the other images in the array and append to list */
    for (i = 1; i < arrayLen; i++) {

        /* Get the next image in the array */
        obj = (*env)->GetObjectArrayElement(env, images, i);
        if (obj == NULL) {
            throwMagickException(env, "Image in array index null");
            return;
        }
        image = (Image*) getHandle(env, obj, "magickImageHandle", &fieldID);
        if (image == NULL) {
            throwMagickException(env, "Unable to obtain image handle");
            return;
        }

        /* Clone the image */
        GetExceptionInfo(&exception);
        image = CloneImage(image, 0, 0, 0, &exception);
        if (image == NULL) {
            throwMagickApiException(env, "Unable to clone image", &exception);
            DestroyExceptionInfo(&exception);
            DestroyImages(newImage);
            return;
        }

        /* Find the head of the list */
        for (p = image; p->previous != NULL; p = p->previous)
            ;

        /* Link it up */
        lastImage->next = p;
        p->previous = lastImage;

        /* Move lastImage to the end of the list */
        for (lastImage = image;
             lastImage->next != NULL;
             lastImage = lastImage->next)
            ;
    }

    /* Set the image handle */
    image = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (image != NULL) {
        DestroyImages(image);
    }
    setHandle(env, self, "magickImageHandle", (void*) newImage, &fieldID);
}




/*
 * Class:     magick_MagickImage
 * Method:    allocateImage
 * Signature: (Lmagick/ImageInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_allocateImage
  (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *imageInfo = NULL;
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;

    /* Obtain the ImageInfo pointer */
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Cannot obtain ImageInfo object");
	return;
    }

    /* Allocate the image object. */
    image = AllocateImage(imageInfo);

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
	DestroyImages(oldImage);
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}



/*
 * Class:     magick_MagickImage
 * Method:    readImage
 * Signature: (Lmagick/ImageInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_readImage
    (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *imageInfo = NULL;
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    ExceptionInfo exception;

    /* Obtain the ImageInfo pointer */
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Cannot obtain ImageInfo object");
	return;
    }

    /* Read the image. */
#ifdef DIAGNOSTIC
    fprintf(stderr, "Attempting to read from file %s\n", imageInfo->filename);
#endif
    LOG2("Attempting to read from file %s\n", imageInfo->filename);
    GetExceptionInfo(&exception);
    image = ReadImage(imageInfo, &exception);
    if (image == NULL) {
	LOG("MagickImage: unable to read image");
        throwMagickApiException(env, "Unable to read image", &exception);
	DestroyExceptionInfo(&exception);
	return;
    }
    DestroyExceptionInfo(&exception);

#ifdef DIAGNOSTIC
    fprintf(stderr, "ReadImage completed\n");
#endif

    LOG("ReadImage completed\n");
    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
	DestroyImages(oldImage);
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}


/*
 * Class:     magick_MagickImage
 * Method:    pingImage
 * Signature: (Lmagick/ImageInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_pingImage
    (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *imageInfo = NULL;
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    ExceptionInfo exception;


    // Obtain the ImageInfo pointer
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Cannot obtain ImageInfo object");
	return;
    }

    // Read the image.
#ifdef DIAGNOSTIC
    fprintf(stderr, "Attempting to read from file %s\n", imageInfo->filename);
#endif

    GetExceptionInfo(&exception);

    image = PingImage(imageInfo, &exception);
    if (image == NULL) {
        throwMagickApiException(env, "Unable to ping image", &exception);
	DestroyExceptionInfo(&exception);
	return;
    }

    DestroyExceptionInfo(&exception);

#ifdef DIAGNOSTIC
    fprintf(stderr, "PingImage completed\n");
#endif

    // Get the old image handle and deallocate it (if required).
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
	DestroyImages(oldImage);
    }

    // Store the image into the handle.
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}


/*
 * Class:     magick_MagickImage
 * Method:    writeImage
 * Signature: (Lmagick/ImageInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_writeImage
    (JNIEnv *env, jobject self, jobject imageInfoObj)
{
    ImageInfo *imageInfo = NULL;
    Image *image = NULL;
    int status;

    /* Obtain the ImageInfo pointer. */
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Cannot obtain ImageInfo object");
	return JNI_FALSE;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to write");
	return JNI_FALSE;
    }

    /* Write the image. */
    status = WriteImage(imageInfo, image);

    return (status) ? (JNI_TRUE) : (JNI_FALSE);
}




/*
 * Class:     magick_MagickImage
 * Method:    getFileName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_magick_MagickImage_getFileName
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to get file name");
	return NULL;
    }

    return (*env)->NewStringUTF(env, image->filename);
}




/*
 * Class:     magick_MagickImage
 * Method:    setFileName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setFileName
    (JNIEnv *env, jobject self, jstring fileName)
{
    Image *image = NULL;
    const char *cstr;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set file name");
	return;
    }

    cstr = (*env)->GetStringUTFChars(env, fileName, 0);
    strcpy(image->filename, cstr);
    (*env)->ReleaseStringUTFChars(env, fileName, cstr);
}




/*
 * Class:     magick_MagickImage
 * Method:    setFilter
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setFilter
  (JNIEnv *env, jobject self, jint filter)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set file name");
	return;
    }

    image->filter = filter;
}


/*
 * Class:     magick_MagickImage
 * Method:    getFilter
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getFilter
  (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve handle");
	return -1;
    }

    return image->filter;
}




/*
 * Class:     magick_MagickImage
 * Method:    getDimension
 * Signature: ()Ljava/awt/Dimension;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getDimension
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;
    jclass dimensionClass;
    jmethodID consMethodID;
    jobject dimension;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve handle");
	return NULL;
    }
    dimensionClass = (*env)->FindClass(env, "java/awt/Dimension");
    if (dimensionClass == 0) {
	throwMagickException(env, "Unable to locate class java.awt.Dimension");
	return NULL;
    }
    consMethodID = (*env)->GetMethodID(env, dimensionClass,
				       "<init>", "(II)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct java.awt.Dimension");
	return NULL;
    }
    dimension = (*env)->NewObject(env, dimensionClass, consMethodID,
				  image->columns, image->rows);
    if (dimension == NULL) {
	throwMagickException(env, "Unable to construct java.awt.Dimension");
	return NULL;
    }
    return dimension;
}


/*
 * Class:     magick_MagickImage
 * Method:    addNoiseImage
 * Signature: (I)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_addNoiseImage
    (JNIEnv *env, jobject self, jint noiseType)
{
    NoiseType noiseEnum;
    jobject newImage;
    Image *noisyImage;
    ExceptionInfo exception;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    switch (noiseType) {
        default: noiseEnum = UniformNoise;                break;
        case 1:  noiseEnum = GaussianNoise;               break;
        case 2:  noiseEnum = MultiplicativeGaussianNoise; break;
        case 3:  noiseEnum = ImpulseNoise;                break;
        case 4:  noiseEnum = LaplacianNoise;              break;
        case 5:  noiseEnum = PoissonNoise;                break;
    }

    GetExceptionInfo(&exception);
    noisyImage = AddNoiseImage(image, noiseEnum, &exception);
    if (noisyImage == NULL) {
	throwMagickApiException(env, "Unable to add noise", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newImage = newImageObject(env, noisyImage);
    if (newImage == NULL) {
	DestroyImages(noisyImage);
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}

/*
 * Class:     magick_MagickImage
 * Method:    getWidth
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getWidth,
    columns,
    "magickImageHandle",
    Image)

/*
 * Class:     magick_MagickImage
 * Method:    getHeight
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getHeight,
    rows,
    "magickImageHandle",
    Image)

/*
 * Class:     magick_MagickImage
 * Method:    getDepth
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getDepth,
    depth,
    "magickImageHandle",
    Image)


/*
 * Class:     magick_MagickImage
 * Method:    setDepth
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setDepth,
    depth,
    "magickImageHandle",
    Image)


/*
 * Class:     magick_MagickImage
 * Method:    blurImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_blurImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *blurredImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    blurredImage = BlurImage(image, radius, sigma, &exception);
    if (blurredImage == NULL) {
	throwMagickApiException(env, "Cannot blur image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, blurredImage);
    if (newObj == NULL) {
	DestroyImages(blurredImage);
	throwMagickException(env, "Unable to create new blurred image");
	return NULL;
    }

    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    getStorageClass
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getStorageClass
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to obtain image handle");
	return -1;
    }

    return image->storage_class;
}





/*
 * Class:     magick_MagickImage
 * Method:    annotateImage
 * Signature: (Lmagick/AnnotateInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_annotateImage
    (JNIEnv *env, jobject self, jobject drawInfo)
{
    Image *image;
    DrawInfo *dInfo;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    dInfo = (DrawInfo*) getHandle(env, drawInfo,
				  "drawInfoHandle", NULL);

    AnnotateImage(image, dInfo);
}



/*
 * Class:     magick_MagickImage
 * Method:    charcoalImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_charcoalImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *charcoalImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    charcoalImage = CharcoalImage(image, radius, sigma, &exception);
    if (charcoalImage == NULL) {
	throwMagickApiException(env, "Cannot charcoal image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, charcoalImage);
    if (newObj == NULL) {
	DestroyImages(charcoalImage);
	throwMagickException(env, "Unable to create new charcoal image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    borderImage
 * Signature: (Ljava/awt/Rectangle;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_borderImage
    (JNIEnv *env, jobject self, jobject jRect)
{
    RectangleInfo iRect;
    Image *image = NULL, *borderedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    if (!getRectangle(env, jRect, &iRect)) {
	throwMagickException(env, "Cannot retrieve rectangle information");
	return NULL;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    borderedImage = BorderImage(image, &iRect, &exception);
    if (borderedImage == NULL) {
	throwMagickApiException(env, "Cannot border image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, borderedImage);
    if (newObj == NULL) {
	DestroyImages(borderedImage);
	throwMagickException(env, "Unable to create border image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    raiseImage
 * Signature: (Ljava/awt/Rectangle;Z)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_raiseImage
    (JNIEnv *env, jobject self, jobject jRect, jboolean raise)
{
    RectangleInfo iRect;
    Image *image = NULL;

    if (!getRectangle(env, jRect, &iRect)) {
	throwMagickException(env, "Cannot retrieve rectangle information");
	return JNI_FALSE;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return JNI_FALSE;
    }

    return RaiseImage(image, &iRect, raise);
}




/*
 * Class:     magick_MagickImage
 * Method:    chopImage
 * Signature: (Ljava/awt/Rectangle;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_chopImage
    (JNIEnv *env, jobject self, jobject jRect)
{
    RectangleInfo iRect;
    Image *image = NULL, *choppedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    if (!getRectangle(env, jRect, &iRect)) {
	throwMagickException(env, "Cannot retrieve rectangle information");
	return NULL;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    choppedImage = ChopImage(image, &iRect, &exception);
    if (choppedImage == NULL) {
	throwMagickApiException(env, "Cannot chop image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, choppedImage);
    if (newObj == NULL) {
	DestroyImages(choppedImage);
	throwMagickException(env, "Unable to chop image");
	return NULL;
    }

    return newObj;
}






/*
 * Class:     magick_MagickImage
 * Method:    colorizeImage
 * Signature: (Ljava/lang/String;Lmagick/PixelPacket;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_colorizeImage
  (JNIEnv *env, jobject self, jstring opacity, jobject target)
{
    Image *image = NULL;
    Image *newImage = NULL;
    const char *cstrOpacity = NULL;
    ExceptionInfo exception;
    PixelPacket pixelPacket;
    jobject newObj;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to obtain image handle");
	return NULL;
    }

    if (!getPixelPacket(env, target, &pixelPacket)) {
	throwMagickException(env, "Unable to get PixelPacket values");
	return NULL;
    }

    cstrOpacity = (*env)->GetStringUTFChars(env, opacity, 0);
    if (cstrOpacity == NULL) {
	throwMagickException(env, "Unable to get opacity value");
	return NULL;
    }

    GetExceptionInfo(&exception);
    newImage = ColorizeImage(image, cstrOpacity, pixelPacket, &exception);
    (*env)->ReleaseStringUTFChars(env, opacity, cstrOpacity);
    if (newImage == NULL) {
	throwMagickApiException(env, "Unable to colorize image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
	DestroyImages(newImage);
	throwMagickException(env, "Unable to create colorized image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    compositeImage
 * Signature: (ILmagick/MagickImage;II)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_compositeImage
    (JNIEnv *env, jobject self, jint compOp,
     jobject compImage, jint xOffset, jint yOffset)
{
    Image *image = NULL, *comp = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve image handle");
	return JNI_FALSE;
    }

    comp = (Image*) getHandle(env, compImage, "magickImageHandle", NULL);
    if (comp == NULL) {
	throwMagickException(env, "Unable to retrieve composite image handle");
	return JNI_FALSE;
    }

    return CompositeImage(image, compOp, comp, xOffset, yOffset);
}



/*
 * Class:     magick_MagickImage
 * Method:    contrastImage
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_contrastImage
    (JNIEnv *env, jobject self, jboolean sharpen)
{
    Image *image = NULL;

    image = getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to obtain image handle");
	return JNI_FALSE;
    }

    return ContrastImage(image, sharpen);
}




/*
 * Class:     magick_MagickImage
 * Method:    cloneImage
 * Signature: (IIZ)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_cloneImage
    (JNIEnv *env, jobject self, jint columns, jint rows, jboolean clonePixels)
{
    Image *image = NULL, *clone = NULL;
    jfieldID handleFid = 0;
    jobject clonedImage;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", &handleFid);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    clone = CloneImage(image, columns, rows, clonePixels, &exception);
    if (clone == NULL) {
	throwMagickApiException(env, "Unable to clone image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    clonedImage = newImageObject(env, clone);
    if (clonedImage == NULL) {
	throwMagickException(env, "Unable to create clone image instance");
	return NULL;
    }

    return clonedImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    constituteImage
 * Signature: (IILjava/lang/String;[B)V
 */
JNIEXPORT void JNICALL
    Java_magick_MagickImage_constituteImage__IILjava_lang_String_2_3B
    (JNIEnv *env, jobject self,
     jint width, jint height,
     jstring map,
     jbyteArray pixels)
{
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    jint arraySize;
    jbyte *pixelArray;
    const char *mapStr;
    ExceptionInfo exception;

    /* Check that we really have the pixels. */
    if (pixels == NULL) {
	throwMagickException(env, "Pixels not allocated");
	return;
    }

    /* Check the array size. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return;
    }

    pixelArray = (*env)->GetByteArrayElements(env, pixels, 0);

#ifdef DIAGNOSTIC
    fprintf(stderr, "Image width is %d, height is %d\n", width, height);
#endif

    /* Create that image. */
    GetExceptionInfo(&exception);
    image = ConstituteImage(width, height, mapStr,
			    CharPixel, pixelArray, &exception);
    if (image == NULL) {
	throwMagickApiException(env, "Unable to create image", &exception);
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	(*env)->ReleaseByteArrayElements(env, pixels, pixelArray, 0);
	DestroyExceptionInfo(&exception);
	return;
    }
    DestroyExceptionInfo(&exception);

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
	DestroyImages(oldImage);
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);

    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseByteArrayElements(env, pixels, pixelArray, 0);
}

/*
 * Class:     magick_MagickImage
 * Method:    constituteImage
 * Signature: (IILjava/lang/String;[I)V
 */
JNIEXPORT void JNICALL
    Java_magick_MagickImage_constituteImage__IILjava_lang_String_2_3I
    (JNIEnv *env, jobject self,
     jint width, jint height,
     jstring map,
     jintArray pixels)
{
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    jint arraySize;
    jint *pixelArray;
    const char *mapStr;
    ExceptionInfo exception;

    /* Check that we really have the pixels. */
    if (pixels == NULL) {
	throwMagickException(env, "Pixels not allocated");
	return;
    }

    /* Check the array size. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return;
    }

    pixelArray = (*env)->GetIntArrayElements(env, pixels, 0);

    /* Create that image. */
    GetExceptionInfo(&exception);
    image = ConstituteImage(width, height, mapStr, IntegerPixel,
			    pixelArray, &exception);
    if (image == NULL) {
	throwMagickApiException(env, "Unable to create image", &exception);
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	(*env)->ReleaseIntArrayElements(env, pixels, pixelArray, 0);
	DestroyExceptionInfo(&exception);
	return;
    }
    DestroyExceptionInfo(&exception);

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
	DestroyImages(oldImage);
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);

    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseIntArrayElements(env, pixels, pixelArray, 0);
}

/*
 * Class:     magick_MagickImage
 * Method:    constituteImage
 * Signature: (IILjava/lang/String;[F)V
 */
JNIEXPORT void JNICALL
    Java_magick_MagickImage_constituteImage__IILjava_lang_String_2_3F
    (JNIEnv *env, jobject self,
     jint width, jint height,
     jstring map, jfloatArray pixels)
{
    Image *image = NULL, *oldImage = NULL;
    jfieldID fieldID = 0;
    jint arraySize;
    jfloat *pixelArray;
    const char *mapStr;
    ExceptionInfo exception;

    /* Check that we really have the pixels. */
    if (pixels == NULL) {
	throwMagickException(env, "Pixels not allocated");
	return;
    }

    /* Check the array size. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return;
    }

    pixelArray = (*env)->GetFloatArrayElements(env, pixels, 0);

    /* Create that image. */
    GetExceptionInfo(&exception);
    image = ConstituteImage(width, height, mapStr,
			    FloatPixel, pixelArray, &exception);
    if (image == NULL) {
	throwMagickApiException(env, "Unable to create image", &exception);
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	(*env)->ReleaseFloatArrayElements(env, pixels, pixelArray, 0);
	DestroyExceptionInfo(&exception);
	return;
    }
    DestroyExceptionInfo(&exception);

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
	DestroyImages(oldImage);
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);

    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseFloatArrayElements(env, pixels, pixelArray, 0);
}




/*
 * Class:     magick_MagickImage
 * Method:    cropImage
 * Signature: (Ljava/awt/Rectangle;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_cropImage
    (JNIEnv *env, jobject self, jobject jRect)
{
    RectangleInfo iRect;
    Image *image = NULL, *croppedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    if (!getRectangle(env, jRect, &iRect)) {
	throwMagickException(env, "Cannot retrieve rectangle information");
	return NULL;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    croppedImage = CropImage(image, &iRect, &exception);
    if (croppedImage == NULL) {
	throwMagickApiException(env, "Cannot crop image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, croppedImage);
    if (newObj == NULL) {
	DestroyImages(croppedImage);
	throwMagickException(env, "Unable to crop image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    cycleColormapImage
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_cycleColormapImage
    (JNIEnv *env, jobject self, jint amount)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve handle");
	return;
    }

    CycleColormapImage(image, amount);
}


/*
 * Class:     magick_MagickImage
 * Method:    edgeImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_edgeImage
  (JNIEnv *env, jobject self, jdouble radius)
{
    Image *image = NULL, *edgedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    edgedImage = EdgeImage(image, radius, &exception);
    if (edgedImage == NULL) {
	throwMagickApiException(env, "Cannot edge image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, edgedImage);
    if (newObj == NULL) {
	DestroyImages(edgedImage);
	throwMagickException(env, "Unable to create new edged image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    embossImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_embossImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *embossedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    embossedImage = EmbossImage(image, radius, sigma, &exception);
    if (embossedImage == NULL) {
	throwMagickApiException(env, "Cannot emboss image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, embossedImage);
    if (newObj == NULL) {
	DestroyImages(embossedImage);
	throwMagickException(env, "Unable to create new embossed image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    enhanceImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_enhanceImage
    (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *image, *enhancedImage;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    enhancedImage = EnhanceImage(image, &exception);
    if (enhancedImage == NULL) {
	throwMagickApiException(env, "Cannot enhance image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newImage = newImageObject(env, enhancedImage);
    if (newImage == NULL) {
	DestroyImages(enhancedImage);
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    destroyImages
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_destroyImages
    (JNIEnv *env, jobject self)
{
    jfieldID handleFid = 0;
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", &handleFid);
    if (image != NULL) {
	DestroyImages(image);
    }
    setHandle(env, self, "magickImageHandle", NULL, &handleFid);
}




/*
 * Class:     magick_MagickImage
 * Method:    drawImage
 * Signature: (Lmagick/DrawInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_drawImage
    (JNIEnv *env, jobject self, jobject drawInfoObj)
{
    DrawInfo *drawInfo;
    Image *image;

    drawInfo = (DrawInfo*) getHandle(env, drawInfoObj,
				     "drawInfoHandle", NULL);
    if (drawInfo == NULL) {
	throwMagickException(env, "Cannot obtain DrawInfo handle");
	return JNI_FALSE;
    }

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

#ifdef DIAGNOSTIC
    printf("Primitive: %s\n", drawInfo->primitive);
    printf("Font: %s\n", drawInfo->font);
    printf("encoding: %s\n", drawInfo->encoding);
#endif

    return DrawImage(image, drawInfo);
}




/*
 * Class:     magick_MagickImage
 * Method:    equalizeImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_equalizeImage
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return EqualizeImage(image);
}




/*
 * Class:     magick_MagickImage
 * Method:    flipImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_flipImage
    (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *image, *flippedImage;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    flippedImage = FlipImage(image, &exception);
    if (flippedImage == NULL) {
	throwMagickApiException(env, "Cannot flip image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newImage = newImageObject(env, flippedImage);
    if (newImage == NULL) {
	DestroyImages(flippedImage);
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    flopImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_flopImage
    (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *image, *floppedImage;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    floppedImage = FlopImage(image, &exception);
    if (floppedImage == NULL) {
	throwMagickApiException(env, "Cannot flop image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newImage = newImageObject(env, floppedImage);
    if (newImage == NULL) {
	DestroyImages(floppedImage);
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    gaussianBlurImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_gaussianBlurImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *blurredImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    blurredImage = GaussianBlurImage(image, radius, sigma, &exception);
    if (blurredImage == NULL) {
	throwMagickApiException(env, "Cannot blur image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, blurredImage);
    if (newObj == NULL) {
	DestroyImages(blurredImage);
	throwMagickException(env, "Unable to create Gaussian blurred image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    implodeImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_implodeImage
  (JNIEnv *env, jobject self, jdouble amount)
{
    Image *image = NULL, *implodedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    implodedImage = ImplodeImage(image, amount, &exception);
    if (implodedImage == NULL) {
	throwMagickApiException(env, "Cannot implode image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, implodedImage);
    if (newObj == NULL) {
	DestroyImages(implodedImage);
	throwMagickException(env, "Unable to create imploded image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    gammaImage
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_gammaImage
    (JNIEnv *env, jobject self, jstring gamma)
{
    const char *cstr;
    unsigned int result;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    cstr = (*env)->GetStringUTFChars(env, gamma, 0);
    result = GammaImage(image, (char*) cstr);
    (*env)->ReleaseStringUTFChars(env, gamma, cstr);
    return result;
}




/*
 * Class:     magick_MagickImage
 * Method:    isGrayImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_isGrayImage
    (JNIEnv *env, jobject self)
{
    int result;
    ExceptionInfo exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    GetExceptionInfo(&exception);
    result = IsGrayImage(image, &exception);
    DestroyExceptionInfo(&exception);

    return result;
}




/*
 * Class:     magick_MagickImage
 * Method:    isMonochromeImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_isMonochromeImage
    (JNIEnv *env, jobject self)
{
    ExceptionInfo exception;
    int result;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    /* Problem here is that although we have an error, how */
    /* do we know that an error has occur? */
    GetExceptionInfo(&exception);
    result = IsMonochromeImage(image, &exception);
    DestroyExceptionInfo(&exception);

    return result;
}




/*
 * Class:     magick_MagickImage
 * Method:    magnifyImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_magnifyImage
  (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *magnifiedImage;
    ExceptionInfo exception;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    magnifiedImage = MagnifyImage(image, &exception);
    if (magnifiedImage == NULL) {
	throwMagickApiException(env, "Unable to magnify image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newImage = newImageObject(env, magnifiedImage);
    if (newImage == NULL) {
	DestroyImages(magnifiedImage);
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}



/*
 * Class:     magick_MagickImage
 * Method:    matteFloodfillImage
 * Signature: (Lmagick/RunlengthPacket;IIII)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_matteFloodfillImage
  (JNIEnv *env, jobject self,
   jobject target, jint matte, jint x, jint y, jint method)
{
    PixelPacket pixPack;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return -1;
    }

    if (!getPixelPacket(env, target, &pixPack)) {
	throwMagickException(env, "Unable get target PixelPacket");
	return -1;
    }

    return MatteFloodfillImage(image, pixPack, matte, x, y, method);
}



/*
 * Class:     magick_MagickImage
 * Method:    medianFilterImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_medianFilterImage
  (JNIEnv *env, jobject self, jdouble radius)
{
    Image *image = NULL, *filteredImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    filteredImage = MedianFilterImage(image, radius, &exception);
    if (filteredImage == NULL) {
	throwMagickApiException(env, "Cannot median-filter image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, filteredImage);
    if (newObj == NULL) {
	DestroyImages(filteredImage);
	throwMagickException(env, "Unable to create median-filtered image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    colorFloodfillImage
 * Signature: (Lmagick/DrawInfo;Lmagick/PixelPacket;III)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_colorFloodfillImage
  (JNIEnv *env, jobject self, jobject drawInfo, jobject target,
   jint x, jint y, jint paintMethod)
{
    PixelPacket pixPack;
    Image *image =
        (Image*) getHandle(env, self, "magickImageHandle", NULL);
    DrawInfo *dInfo;
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return -1;
    }

    dInfo = (DrawInfo*) getHandle(env, drawInfo, "drawInfoHandle", NULL);
    if (dInfo == NULL) {
        throwMagickException(env, "Cannot obtain DrawInfo handle");
        return -1;
    }

    if (!getPixelPacket(env, target, &pixPack)) {
	throwMagickException(env, "Unable get target PixelPacket");
	return -1;
    }

    return ColorFloodfillImage(image, dInfo, pixPack, x, y, paintMethod);
}




/*
 * Class:     magick_MagickImage
 * Method:    minifyImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_minifyImage
    (JNIEnv *env, jobject self)
{
    jobject newImage;
    Image *minifiedImage;
    ExceptionInfo exception;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    minifiedImage = MinifyImage(image, &exception);
    if (minifiedImage == NULL) {
	throwMagickApiException(env, "Unable to minify image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newImage = newImageObject(env, minifiedImage);
    if (newImage == NULL) {
	DestroyImages(minifiedImage);
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    modulateImage
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_modulateImage
    (JNIEnv *env, jobject self, jstring modulate)
{
    const char *cstr;
    int result;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    cstr = (*env)->GetStringUTFChars(env, modulate, 0);
    result = ModulateImage(image, (char*) cstr);
    (*env)->ReleaseStringUTFChars(env, modulate, cstr);
    return result;
}




/*
 * Class:     magick_MagickImage
 * Method:    oilPaintImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_oilPaintImage
  (JNIEnv *env, jobject self, jdouble radius)
{
    Image *image = NULL, *paintedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    paintedImage = OilPaintImage(image, radius, &exception);
    if (paintedImage == NULL) {
	throwMagickApiException(env, "Cannot oil-paint image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, paintedImage);
    if (newObj == NULL) {
	DestroyImages(paintedImage);
	throwMagickException(env, "Unable to create oil-paint image");
	return NULL;
    }

    return newObj;
}






/*
 * Class:     magick_MagickImage
 * Method:    negateImage
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_negateImage
    (JNIEnv *env, jobject self, jint grayscale)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return NegateImage(image, grayscale);
}

/*
 * Class:     magick_MagickImage
 * Method:    reduceNoiseImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_reduceNoiseImage
  (JNIEnv *env, jobject self, jdouble radius)
{
    Image *image = NULL, *filteredImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    filteredImage = ReduceNoiseImage(image, radius, &exception);
    if (filteredImage == NULL) {
	throwMagickApiException(env, "Cannot peak-filter image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, filteredImage);
    if (newObj == NULL) {
	DestroyImages(filteredImage);
	throwMagickException(env, "Unable to create peak-filtered image");
	return NULL;
    }

    return newObj;
}





/*
 * Class:     magick_MagickImage
 * Method:    normalizeImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_normalizeImage
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return NormalizeImage(image);
}




/*
 * Class:     magick_MagickImage
 * Method:    opaqueImage
 * Signature: (Lmagick/PixelPacket;Lmagick/PixelPacket;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_opaqueImage
    (JNIEnv *env, jobject self, jobject target, jobject penColor)
{
    PixelPacket ppTarget, ppPenColor;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    if (!getPixelPacket(env, target, &ppTarget) ||
	!getPixelPacket(env, penColor, &ppPenColor)) {
	throwMagickException(env, "Unable to obtain PixelPacket values");
	return JNI_FALSE;
    }

    return OpaqueImage(image, ppTarget, ppPenColor);
}




/*
 * Class:     magick_MagickImage
 * Method:    rgbTransformImage
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_rgbTransformImage
    (JNIEnv *env, jobject self, jint colorspace)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return RGBTransformImage(image, colorspace);
}




/*
 * Class:     magick_MagickImage
 * Method:    rollImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_rollImage
    (JNIEnv *env, jobject self, jint xOffset, jint yOffset)
{
    jobject newImage;
    Image *rolledImage;
    ExceptionInfo exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    rolledImage = RollImage(image, xOffset, yOffset, &exception);
    if (rolledImage == NULL) {
	throwMagickApiException(env, "Unable to roll image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newImage = newImageObject(env, rolledImage);
    if (newImage == NULL) {
	DestroyImages(rolledImage);
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    sampleImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_sampleImage
    (JNIEnv *env, jobject self, jint cols, jint rows)
{
    jobject newImage;
    Image *sampledImage;
    ExceptionInfo exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    sampledImage = SampleImage(image, cols, rows, &exception);
    if (sampledImage == NULL) {
	throwMagickApiException(env, "Unable to sample image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newImage = newImageObject(env, sampledImage);
    if (newImage == NULL) {
	DestroyImages(sampledImage);
	throwMagickException(env, "Cannot create new MagickImage object");
	return NULL;
    }

    return newImage;
}


/*
 * Class:     magick_MagickImage
 * Method:    segmentImage
 * Signature: (IDD)I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_segmentImage
    (JNIEnv *env, jobject self, jint colorspace, jdouble cluster_threshold,
                                                 jdouble smoothing_threshold)
{
    ColorspaceType colorspaceEnum;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    switch (colorspace) {
        case  0: colorspaceEnum = UndefinedColorspace;   break;
        default: colorspaceEnum = RGBColorspace;         break;
        case  2: colorspaceEnum = GRAYColorspace;        break;
        case  3: colorspaceEnum = TransparentColorspace; break;
        case  4: colorspaceEnum = OHTAColorspace;        break;
        case  5: colorspaceEnum = XYZColorspace;         break;
        case  6: colorspaceEnum = YCbCrColorspace;       break;
        case  7: colorspaceEnum = YCCColorspace;         break;
        case  8: colorspaceEnum = YIQColorspace;         break;
        case  9: colorspaceEnum = YPbPrColorspace;       break;
        case 10: colorspaceEnum = YUVColorspace;         break;
        case 11: colorspaceEnum = CMYKColorspace;        break;
        case 12: colorspaceEnum = sRGBColorspace;        break;
    }

    return SegmentImage(image, colorspaceEnum, 0, cluster_threshold,
                                                  smoothing_threshold);
}



/*
 * Class:     magick_MagickImage
 * Method:    solarizeImage
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_solarizeImage
    (JNIEnv *env, jobject self, jdouble threshold)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

    SolarizeImage(image, threshold);
}






/*
 * Class:     magick_MagickImage
 * Method:    scaleImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_scaleImage
    (JNIEnv *env, jobject self, jint cols, jint rows)
{
    Image *image = NULL;
    Image *scaledImage = NULL;
    jobject returnedImage;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle",
			       &magickImageHandleFid);
    if (image == NULL) {
	throwMagickException(env, "No image to scale");
	return NULL;
    }

    GetExceptionInfo(&exception);
    scaledImage = ScaleImage(image,
			     (unsigned int) cols,
			     (unsigned int) rows,
			     &exception);
    if (scaledImage == NULL) {
	throwMagickApiException(env, "Unable to scale image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    returnedImage = newImageObject(env, scaledImage);
    if (returnedImage == NULL) {
	DestroyImages(scaledImage);
	throwMagickException(env, "Unable to construct magick.MagickImage");
	return NULL;
    }
    setHandle(env, returnedImage, "magickImageHandle",
	      (void*) scaledImage, &magickImageHandleFid);

    return returnedImage;
}




/*
 * Class:     magick_MagickImage
 * Method:    spreadImage
 * Signature: (I)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_spreadImage
  (JNIEnv *env, jobject self, jint radius)
{
    Image *image = NULL, *randomizedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    randomizedImage = SpreadImage(image, radius, &exception);
    if (randomizedImage == NULL) {
	throwMagickApiException(env, "Cannot spread image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, randomizedImage);
    if (newObj == NULL) {
	DestroyImages(randomizedImage);
	throwMagickException(env, "Unable to create spread image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    swirlImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_swirlImage
  (JNIEnv *env, jobject self, jdouble degrees)
{
    Image *image = NULL, *swirledImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    swirledImage = SwirlImage(image, degrees, &exception);
    if (swirledImage == NULL) {
	throwMagickApiException(env, "Cannot swirl image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, swirledImage);
    if (newObj == NULL) {
	DestroyImages(swirledImage);
	throwMagickException(env, "Unable to create swirled image");
	return NULL;
    }

    return newObj;
}





/*
 * Class:     magick_MagickImage
 * Method:    sortColormapByIntensity
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_sortColormapByIntensity
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return SortColormapByIntensity(image);
}



/*
 * Class:     magick_MagickImage
 * Method:    syncImage
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_syncImage
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

    SyncImage(image);
}




/*
 * Class:     magick_MagickImage
 * Method:    textureImage
 * Signature: (Lmagick/MagickImage;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_textureImage
  (JNIEnv *env, jobject self, jobject texture)
{
    Image *textureImage;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

    textureImage = (Image*) getHandle(env, texture, "magickImageHandle", NULL);
    if (textureImage == NULL) {
	throwMagickException(env, "Cannot obtain texture image handle");
	return;
    }

    TextureImage(image, textureImage);
}




/*
 * Class:     magick_MagickImage
 * Method:    thresholdImage
 * Signature: (D)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_thresholdImage
    (JNIEnv *env, jobject self, jdouble threshold)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return ThresholdImage(image, threshold);
}



/*
 * Class:     magick_MagickImage
 * Method:    transformImage
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_transformImage
    (JNIEnv *env, jobject self, jstring cropGeometry, jstring imageGeometry)
{
    const char *cropStr, *imageStr;
    jfieldID fieldID = 0;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return;
    }

    if (cropGeometry == NULL) {
        cropStr = NULL;
    } else {
        cropStr = (*env)->GetStringUTFChars(env, cropGeometry, 0);
    }

    if (imageGeometry == NULL) {
        imageStr = NULL;
    } else {
        imageStr = (*env)->GetStringUTFChars(env, imageGeometry, 0);
    }

    TransformImage(&image, cropStr, imageStr);

    if (imageGeometry != NULL) {
        (*env)->ReleaseStringUTFChars(env, imageGeometry, imageStr);
    }
    if (cropGeometry != NULL) {
        (*env)->ReleaseStringUTFChars(env, cropGeometry, cropStr);
    }

    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}




/*
 * Class:     magick_MagickImage
 * Method:    unsharpMaskImage
 * Signature: (DDDD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_unsharpMaskImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma,
                              jdouble amount, jdouble threshold)
{
    Image *image = NULL, *unsharpedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    #ifdef DIAGNOSTIC
        fprintf(stderr, "Kalder UnsharpMaskImage() !!\n");
    #endif
    unsharpedImage = UnsharpMaskImage(image, radius, sigma,
                                             amount, threshold, &exception);
     #ifdef DIAGNOSTIC
         fprintf(stderr, "Kalder UnsharpMaskImage() færdig!!\n");
     #endif
    if (unsharpedImage == NULL) {
	throwMagickApiException(env, "Cannot unsharp image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, unsharpedImage);
    if (newObj == NULL) {
	DestroyImages(unsharpedImage);
	throwMagickException(env, "Unable to create unsharped image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    waveImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_waveImage
  (JNIEnv *env, jobject self, jdouble amplitude, jdouble wavelength)
{
    Image *image = NULL, *wavedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    wavedImage = WaveImage(image, amplitude, wavelength, &exception);
    if (wavedImage == NULL) {
	throwMagickApiException(env, "Cannot wave image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, wavedImage);
    if (newObj == NULL) {
	DestroyImages(wavedImage);
	throwMagickException(env, "Unable to create waved image");
	return NULL;
    }

    return newObj;
}






/*
 * Class:     magick_MagickImage
 * Method:    transformRgbImage
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_transformRgbImage
    (JNIEnv *env, jobject self, jint colorspace)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return TransformRGBImage(image, colorspace);
}



/*
 * Class:     magick_MagickImage
 * Method:    transparentImage
 * Signature: (Lmagick/PixelPacket;I)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_transparentImage
    (JNIEnv *env, jobject self, jobject color, jint opacity)
{
    PixelPacket pixelPacket;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    getPixelPacket(env, color, &pixelPacket);
    return TransparentImage(image, pixelPacket, (unsigned int) opacity);
}




/*
 * Class:     magick_MagickImage
 * Method:    zoomImage
 * Signature: (II)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_zoomImage
    (JNIEnv *env, jobject self, jint cols, jint rows)
{
    jobject newObj;
    Image *newImage;
    ExceptionInfo exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    newImage = ZoomImage(image, cols, rows, &exception);
    if (newImage == NULL) {
	throwMagickApiException(env, "Unable to zoom image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
	DestroyImages(newImage);
	throwMagickException(env, "Unable to create a new MagickImage object");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    dispatchImage
 * Signature: (IIIILjava/lang/String;[B)Z
 */
JNIEXPORT jboolean JNICALL
    Java_magick_MagickImage_dispatchImage__IIIILjava_lang_String_2_3B
    (JNIEnv *env, jobject self,
     jint x, jint y, jint width, jint height,
     jstring map, jbyteArray pixels)
{
    Image *image = NULL;
    jint arraySize;
    const char *mapStr;
    jbyte *pixelArray;
    int result;
    ExceptionInfo exception;

    /* Obtain the minimum pixel array size required and check correctness. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    if (mapStr == NULL) {
	throwMagickException(env, "Unable to get component map");
	return JNI_FALSE;
    }
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the image object. */
    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the pixel storage array and store the pixels. */
    pixelArray = (*env)->GetByteArrayElements(env, pixels, 0);
    GetExceptionInfo(&exception);
    result = DispatchImage(image, x, y, width, height,
			   mapStr, CharPixel, pixelArray, &exception);

    /* Cleanup. */
    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseByteArrayElements(env, pixels, pixelArray, 0);

    if (result == JNI_FALSE) {
        throwMagickApiException(env, "Error dispatching image", &exception);
    }

    DestroyExceptionInfo(&exception);
    return result;
}


/*
 * Class:     magick_MagickImage
 * Method:    dispatchImage
 * Signature: (IIIILjava/lang/String;[I)Z
 */
JNIEXPORT jboolean JNICALL
    Java_magick_MagickImage_dispatchImage__IIIILjava_lang_String_2_3I
    (JNIEnv *env, jobject self,
     jint x, jint y, jint width, jint height,
     jstring map, jintArray pixels)
{
    Image *image = NULL;
    jint arraySize;
    const char *mapStr;
    jint *pixelArray;
    int result;
    ExceptionInfo exception;

    /* Obtain the minimum pixel array size required and check correctness. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    if (mapStr == NULL) {
	throwMagickException(env, "Unable to get component map");
	return JNI_FALSE;
    }
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the image object. */
    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the pixel storage array and store the pixels. */
    pixelArray = (*env)->GetIntArrayElements(env, pixels, 0);
    GetExceptionInfo(&exception);
    result = DispatchImage(image, x, y, width, height,
			   mapStr, IntegerPixel, pixelArray, &exception);

    /* Cleanup. */
    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseIntArrayElements(env, pixels, pixelArray, 0);

    if (result == JNI_FALSE) {
        throwMagickApiException(env, "Error dispatching image", &exception);
    }

    DestroyExceptionInfo(&exception);
    return result;
}



/*
 * Class:     magick_MagickImage
 * Method:    dispatchImage
 * Signature: (IIIILjava/lang/String;[F)Z
 */
JNIEXPORT jboolean JNICALL
    Java_magick_MagickImage_dispatchImage__IIIILjava_lang_String_2_3F
    (JNIEnv *env, jobject self,
     jint x, jint y, jint width, jint height,
     jstring map, jfloatArray pixels)
{
    Image *image = NULL;
    jint arraySize;
    const char *mapStr;
    jfloat *pixelArray;
    int result;
    ExceptionInfo exception;

    /* Obtain the minimum pixel array size required and check correctness. */
    mapStr = (*env)->GetStringUTFChars(env, map, 0);
    if (mapStr == NULL) {
	throwMagickException(env, "Unable to get component map");
	return JNI_FALSE;
    }
    arraySize = width * height * strlen(mapStr);
    if ((*env)->GetArrayLength(env, pixels) < arraySize) {
	throwMagickException(env, "Pixels size too small");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the image object. */
    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	(*env)->ReleaseStringUTFChars(env, map, mapStr);
	return JNI_FALSE;
    }

    /* Get the pixel storage array and store the pixels. */
    pixelArray = (*env)->GetFloatArrayElements(env, pixels, 0);
    GetExceptionInfo(&exception);
    result = DispatchImage(image, x, y, width, height,
			   mapStr, FloatPixel, pixelArray, &exception);

    /* Cleanup. */
    (*env)->ReleaseStringUTFChars(env, map, mapStr);
    (*env)->ReleaseFloatArrayElements(env, pixels, pixelArray, 0);

    if (result == JNI_FALSE) {
        throwMagickApiException(env, "Error dispatching image", &exception);
    }

    DestroyExceptionInfo(&exception);
    return result;
}


/*
 * Class:     magick_MagickImage
 * Method:    getMagick
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_magick_MagickImage_getMagick
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to get image format");
	return NULL;
    }

    return (*env)->NewStringUTF(env, image->magick);
}

/*
 * Class:     magick_MagickImage
 * Method:    setMagick
 * Signature: (Ljava/lang/String;)V
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setMagick
    (JNIEnv *env, jobject self, jstring imageFormat)
{
    Image *image = NULL;
    const char *cstr;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set image Format");
	return;
    }
    cstr = (*env)->GetStringUTFChars(env, imageFormat, 0);
    strcpy(image->magick, cstr);
    (*env)->ReleaseStringUTFChars(env, imageFormat, cstr);
}

/*
 * Class:     magick_MagickImage
 * Method:    getNumberColors
 * Signature: ()Ljava/lang/int;
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getNumberColors
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;
    jint numberColors=0;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to get the number of unique colors");
	return -1;
    }

    GetExceptionInfo(&exception);
    numberColors=GetNumberColors(image, (FILE *) NULL, &exception);

    if (numberColors == 0) {
        throwMagickApiException(env, "Error in GetNumberColors", &exception);
    }

    DestroyExceptionInfo(&exception);
    return numberColors;
}

/*
 * Class:     magick_MagickImage
 * Method:    setNumberColors
 * Signature: (()Ljava/lang/int)V;
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setNumberColors
    (JNIEnv *env, jobject self, jint numberColors)
{
    Image *image = NULL;
    QuantizeInfo quantize_info;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env,
                             "No image to set the number of unique colors");
	return;
    }

  GetQuantizeInfo(&quantize_info);
  quantize_info.number_colors=numberColors;
  (void) QuantizeImage(&quantize_info,image);
}

/*
 * Class:     magick_MagickImage
 * Method:    isAnimatedImage
 * Signature: ()Z
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_isAnimatedImage
    (JNIEnv *env, jobject self)
{
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    return (image->next != (Image *) NULL) ? (JNI_TRUE) : (JNI_FALSE);
}



/*
 * Class:     magick_MagickImage
 * Method:    rotateImage
 * Signature: (D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_rotateImage
  (JNIEnv *env, jobject self, jdouble degrees)
{
    jobject newObj;
    Image *newImage;
    ExceptionInfo exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    newImage = RotateImage(image, degrees, &exception);
    if (newImage == NULL) {
	throwMagickApiException(env, "Unable to rotate image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
	DestroyImages(newImage);
	throwMagickException(env, "Unable to create a new MagickImage object");
	return NULL;
    }

    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    shearImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_shearImage
  (JNIEnv *env, jobject self, jdouble x_shear, jdouble y_shear)
{
    jobject newObj;
    Image *newImage;
    ExceptionInfo exception;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    newImage = ShearImage(image, x_shear, y_shear, &exception);
    if (newImage == NULL) {
	throwMagickApiException(env, "Unable to shear image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, newImage);
    if (newObj == NULL) {
	DestroyImages(newImage);
	throwMagickException(env, "Unable to create a new MagickImage object");
	return NULL;
    }


    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    quantizeImage
 * Signature: (Lmagick/QuantizeInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_quantizeImage
  (JNIEnv *env, jobject self, jobject quantizeInfo)
{
    QuantizeInfo *qInfo;
    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    qInfo = (QuantizeInfo*) getHandle(env, quantizeInfo,
				     "quantizeInfoHandle", NULL);
    if (qInfo == NULL) {
	throwMagickException(env, "Cannot obtain QuantizeInfo handle");
	return JNI_FALSE;
    }

#ifdef DIAGNOSTIC
    fprintf(stderr, "qInfo.number_colors = %u\n", qInfo->number_colors);
    fprintf(stderr, "qInfo.tree_depth = %u\n", qInfo->tree_depth);
    fprintf(stderr, "qInfo.dither = %u\n", qInfo->dither);
    fprintf(stderr, "qInfo.colorspace = %u\n", qInfo->colorspace);
    fprintf(stderr, "qInfo.measure_error = %u\n", qInfo->measure_error);
#endif


    return QuantizeImage(qInfo, image);
}



/*
 * Class:     magick_MagickImage
 * Method:    getColorspace
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getColorspace,
	     colorspace,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    sharpenImage
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_sharpenImage
  (JNIEnv *env, jobject self, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *sharpenedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    sharpenedImage = SharpenImage(image, radius, sigma, &exception);
    if (sharpenedImage == NULL) {
	throwMagickApiException(env, "Cannot sharpen image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, sharpenedImage);
    if (newObj == NULL) {
	DestroyImages(sharpenedImage);
	throwMagickException(env, "Unable to create sharpened image");
	return NULL;
    }

    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    despeckleImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_despeckleImage
    (JNIEnv *env, jobject self)
{
    Image *image = NULL, *despeckledImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    despeckledImage = DespeckleImage(image, &exception);
    if (despeckledImage == NULL) {
	throwMagickApiException(env, "Cannot despeckle image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, despeckledImage);
    if (newObj == NULL) {
	DestroyImages(despeckledImage);
	throwMagickException(env, "Unable to create despeckle image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    convolveImage
 * Signature: (I[D)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_convolveImage
  (JNIEnv *env, jobject self, jint order, jdoubleArray kernel)
{
    Image *image = NULL, *convolvedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;
    double *karray;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    karray = (*env)->GetDoubleArrayElements(env, kernel, NULL);
    GetExceptionInfo(&exception);
    convolvedImage = ConvolveImage(image, order, karray, &exception);
    (*env)->ReleaseDoubleArrayElements(env, kernel, karray, JNI_ABORT);
    if (convolvedImage == NULL) {
	throwMagickApiException(env, "Cannot convolve image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, convolvedImage);
    if (newObj == NULL) {
	DestroyImages(convolvedImage);
	throwMagickException(env, "Unable to create convolved image");
	return NULL;
    }

    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    getImageAttribute
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_magick_MagickImage_getImageAttribute
    (JNIEnv *env, jobject self, jstring key)
{
    Image *image;
    const char *iKey;
    const ImageAttribute *attrib;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    iKey = (*env)->GetStringUTFChars(env, key, 0);
    attrib = GetImageAttribute(image, iKey);
    (*env)->ReleaseStringUTFChars(env, key, iKey);

    if (attrib == NULL || attrib->value == NULL) {
	return NULL;
    }

    return (*env)->NewStringUTF(env, attrib->value);
}


/*
 * Class:     magick_MagickImage
 * Method:    setImageAttribute
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_setImageAttribute
    (JNIEnv *env, jobject self, jstring key, jstring value)
{
    Image *image;
    const char *iKey, *iValue;
    jboolean result;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return JNI_FALSE;
    }

    if (key == NULL) {
        throwMagickException(env, "Image attribute key is null");
        return JNI_FALSE;
    }

    iKey = (*env)->GetStringUTFChars(env, key, 0);
    iValue = (value == NULL) ? NULL : (*env)->GetStringUTFChars(env, value, 0);
    result = SetImageAttribute(image, iKey, iValue);
    if (iValue != NULL) {
	(*env)->ReleaseStringUTFChars(env, value, iValue);
    }
    (*env)->ReleaseStringUTFChars(env, key, iKey);

    return result;
}



/*
 * Class:     magick_MagickImage
 * Method:    blobToImage
 * Signature: (Lmagick/ImageInfo;[B)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_blobToImage
    (JNIEnv *env, jobject self, jobject imageInfoObj, jbyteArray blob)
{
    size_t blobSiz;
    jbyte *blobMem;
    ExceptionInfo exception;
    Image *image, *oldImage;
    jfieldID fieldID = 0;
    ImageInfo *imageInfo;

    /* Obtain the ImageInfo pointer */
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
                                       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
        throwMagickException(env, "Cannot obtain ImageInfo object");
        return;
    }

    /* Check that we do have a blob */
    if (blob == NULL) {
        throwMagickException(env, "Blob is null");
        return;
    }

    /* Get the array size and array elements */
    blobSiz = (*env)->GetArrayLength(env, blob);
    blobMem = (*env)->GetByteArrayElements(env, blob, 0);

    /* Create that image. */
    GetExceptionInfo(&exception);
    image = BlobToImage(imageInfo, blobMem, blobSiz, &exception);
    (*env)->ReleaseByteArrayElements(env, blob, blobMem, 0);
    if (image == NULL) {
        throwMagickApiException(env, "Unable to convert blob to image",
                                &exception);
        DestroyExceptionInfo(&exception);
        return;
    }

    /* Get the old image handle and deallocate it (if required). */
    oldImage = (Image*) getHandle(env, self, "magickImageHandle", &fieldID);
    if (oldImage != NULL) {
        DestroyImages(oldImage);
    }

    /* Store the image into the handle. */
    setHandle(env, self, "magickImageHandle", (void*) image, &fieldID);
}



/*
 * Class:     magick_MagickImage
 * Method:    imageToBlob
 * Signature: (Lmagick/ImageInfo;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_magick_MagickImage_imageToBlob
 (JNIEnv *env, jobject self, jobject imageInfoObj)
{
  ImageInfo *imageInfo;
  Image *image;
  size_t blobSiz = 0;
  ExceptionInfo exception;
  void *blobMem = NULL;
  jbyteArray blob;

  /* Obtain the ImageInfo pointer */
  if (imageInfoObj != NULL) {
    imageInfo = (ImageInfo*) getHandle(env, imageInfoObj,
                                       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
      throwMagickException(env, "Cannot obtain ImageInfo object");
      return NULL;
    }
  }
  else {
    imageInfo = NULL;
  }

  /* Get the Image pointer */
  image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
  if (image == NULL) {
    throwMagickException(env, "No image to get file name");
    return NULL;
  }


  /* Do the conversion */
  GetExceptionInfo(&exception);
  blobMem = ImageToBlob(imageInfo, image, &blobSiz, &exception);
  if (blobMem == NULL) {
    throwMagickApiException(env, "Unable to convert image to blob", &exception);
    DestroyExceptionInfo(&exception);
    return NULL;
  }
  DestroyExceptionInfo(&exception);


  /* Create a new Java array. */
  blob = (*env)->NewByteArray(env, blobSiz);
  if (blob == NULL) {
    throwMagickException(env, "Unable to allocate array");
    return NULL;
  }
  (*env)->SetByteArrayRegion(env, blob, 0, blobSiz, blobMem);

  RelinquishMagickMemory(blobMem);

  return blob;
}


JNIEXPORT jobject JNICALL Java_magick_MagickImage_nextImage
  (JNIEnv *env, jobject self)
{
    jobject newObj;
    Image *nextImage;
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }

    if (image->next == NULL) {
        return NULL;
    }

    nextImage = image->next;
    /* unlink image from sequence */
    image->next = NULL;
    nextImage->previous = NULL;

    newObj = newImageObject(env, nextImage);
    if (newObj == NULL) {
       throwMagickException(env, "Unable to create a new MagickImage object");
       return NULL;
    }

    return newObj;
}

JNIEXPORT jboolean JNICALL Java_magick_MagickImage_hasFrames
  (JNIEnv *env, jobject self)
{
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return JNI_FALSE;
    }

    if (image->next == NULL) {
        return JNI_FALSE;
    } else {
        return JNI_TRUE;
    }
}

JNIEXPORT jint JNICALL Java_magick_MagickImage_getNumFrames
  (JNIEnv *env, jobject self)
{
    int count = 0;
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return 0;
    }

    while (image != NULL) {
        count++;
        image = image->next;
    }

    return count;
}

/*
 * Class:     magick_MagickImage
 * Method:    setUnits
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setUnits,
	     units,
	     "magickImageHandle",
	     Image)



/*
 * Class:     magick_MagickImage
 * Method:    getUnits
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getUnits,
	     units,
	     "magickImageHandle",
	     Image)




/*
 * Class:     magick_MagickImage
 * Method:    setXResolution
 * Signature: (D)V
 */
setDoubleMethod(Java_magick_MagickImage_setXResolution,
                x_resolution,
                "magickImageHandle",
                Image)



/*
 * Class:     magick_MagickImage
 * Method:    setYResolution
 * Signature: (D)V
 */
setDoubleMethod(Java_magick_MagickImage_setYResolution,
                y_resolution,
                "magickImageHandle",
                Image)


/*
 * Class:     magick_MagickImage
 * Method:    getXResolution
 * Signature: ()D
 */
getDoubleMethod(Java_magick_MagickImage_getXResolution,
                x_resolution,
                "magickImageHandle",
                Image)

/*
 * Class:     magick_MagickImage
 * Method:    getYResolution
 * Signature: ()D
 */
getDoubleMethod(Java_magick_MagickImage_getYResolution,
                y_resolution,
                "magickImageHandle",
                Image)

/*
 * Class:     magick_MagickImage
 * Method:    setColorProfile
 * Signature: (Lmagick/ProfileInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setColorProfile
  (JNIEnv *env, jobject self, jobject profileObj)
{
    unsigned char *info;
    int infoSize = 0;

    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return;
    }
    // setProfileInfo() is broken, dont use
    //setProfileInfo(env, &image->color_profile, profileObj);


    if (profileObj == NULL) {
        throwMagickException(env, "ProfileInfo cannot be null");
       return;
    }

    info = getByteArrayFieldValue(env, profileObj, "info", NULL, &infoSize);

#ifdef DIAGNOSTIC
    fprintf(stderr, "setColorProfile infoSize = %d  info = %p\n\n", infoSize, info);
#endif

    if (info==NULL) {
        RemoveImageProfile(image,"icc");
    } else {
        StringInfo* profile_info;
        profile_info = AcquireStringInfo(infoSize);
        SetStringInfoDatum(profile_info, info);
        SetImageProfile(image,"icc",profile_info);
        profile_info=DestroyStringInfo(profile_info);
    }
}

/*
 * Class:     magick_MagickImage
 * Method:    getColorProfile
 * Signature: ()Lmagick/ProfileInfo;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getColorProfile
  (JNIEnv *env, jobject self)
{
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }
    return getProfileInfo(env, &image->color_profile);
}



/*
 * Class:     magick_MagickImage
 * Method:    setIptcProfile
 * Signature: (Lmagick/ProfileInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MagickImage_setIptcProfile
  (JNIEnv *env, jobject self, jobject profileObj)
{
    unsigned char *info;
    int infoSize = 0;

    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return;
    }

    // setProfileInfo() is broken, dont use
    //setProfileInfo(env, &image->iptc_profile, profileObj);


    if (profileObj == NULL) {
        throwMagickException(env, "ProfileInfo cannot be null");
        return;
    }

    //name = getStringFieldValue(env, profileObj, "name", NULL);
    info = getByteArrayFieldValue(env, profileObj, "info", NULL, &infoSize);

#ifdef DIAGNOSTIC
    fprintf(stderr, "setIptcProfile 8BIM infoSize = %d  info = %p\n\n", infoSize, info);
#endif

    if (info==NULL) {
//        RemoveImageProfile(image,"iptc");
	RemoveImageProfile(image,"8bim");
    } else {
        StringInfo* profile_info;
        profile_info = AcquireStringInfo(infoSize);
        SetStringInfoDatum(profile_info, info);
//        SetImageProfile(image,"iptc",profile_info);
	SetImageProfile(image,"8bim",profile_info);
        profile_info=DestroyStringInfo(profile_info);
    }
}



/*
 * Class:     magick_MagickImage
 * Method:    getGenericProfileCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getGenericProfileCount
  (JNIEnv *env, jobject self)
{
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return -1;
    }

    return image->generic_profiles;
}



/*
 * Class:     magick_MagickImage
 * Method:    getGenericProfile
 * Signature: (I)Lmagick/ProfileInfo;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getGenericProfile
  (JNIEnv *env, jobject self, jint index)
{
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }

    if (image->generic_profiles >= index) {
        return NULL;
    }

    return getProfileInfo(env, &image->generic_profile[index]);
}




/*
 * Class:     magick_MagickImage
 * Method:    getIptcProfile
 * Signature: ()Lmagick/ProfileInfo;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getIptcProfile
  (JNIEnv *env, jobject self)
{
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }
    return getProfileInfo(env, &image->iptc_profile);
}



/*
 * Class:     magick_MagickImage
 * Method:    profileImage
 * Signature: (Ljava/lang/String;[B)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_profileImage
  (JNIEnv *env, jobject self, jstring profileName, jbyteArray profileData)
{
    Image *image = NULL;
    const char *cstrProfileName;
    unsigned char *cProfileData;
    size_t cProfileSize;
    unsigned int retVal;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "No image to set file name");
	return JNI_FALSE;
    }

    if (profileName == NULL) {
        cstrProfileName = NULL;
    }
    else {
        cstrProfileName = (*env)->GetStringUTFChars(env, profileName, 0);
    }

    if (profileData == NULL) {
        cProfileData = NULL;
        cProfileSize = 0;
    }
    else {
        cProfileSize = (*env)->GetArrayLength(env, profileData);
        cProfileData = (*env)->GetByteArrayElements(env, profileData, 0);
    }

    /* Note that the clone parameter in ProfileImage is always true
     * for JMagick because once the byte array is released, the memory
     * is recovered by the JVM.
     */
    retVal =
      ProfileImage(image, cstrProfileName, cProfileData, cProfileSize, 1);

    if (profileData != NULL) {
        (*env)->ReleaseByteArrayElements(env, profileData, cProfileData, 0);
    }

    if (profileName != NULL) {
        (*env)->ReleaseStringUTFChars(env, profileName, cstrProfileName);
    }

    return (retVal ? JNI_TRUE : JNI_FALSE);
}









	/*
	 * Class:     magick_MagickImage
	 * Method:    setImageProfile
	 */
	JNIEXPORT jboolean JNICALL Java_magick_MagickImage_setImageProfile
		(JNIEnv *env, jobject self, jstring profileName, jbyteArray profileData)
	{
			Image *image = NULL;
			const char *cstrProfileName;
			unsigned char *cProfileData;
			size_t cProfileSize;
			unsigned int retVal;

			image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
			if (image == NULL) {
		throwMagickException(env, "No image to set file name");
		return JNI_FALSE;
			}

			if (profileName == NULL) {
					cstrProfileName = NULL;
			}
			else {
					cstrProfileName = (*env)->GetStringUTFChars(env, profileName, 0);
			}

			if (profileData == NULL) {
					cProfileData = NULL;
					cProfileSize = 0;
			}
			else {
					cProfileSize = (*env)->GetArrayLength(env, profileData);
					cProfileData = (*env)->GetByteArrayElements(env, profileData, 0);
			}


      if (cProfileData == NULL) {
				retVal = DeleteImageProfile(image,cstrProfileName);
      } else {
					StringInfo * profile_info = NULL;
					profile_info = AcquireStringInfo(cProfileSize);
					SetStringInfoDatum(profile_info, cProfileData);

					retVal =
							SetImageProfile(image, cstrProfileName, profile_info);

					profile_info = DestroyStringInfo(profile_info);
				}

			if (profileData != NULL) {
					(*env)->ReleaseByteArrayElements(env, profileData, cProfileData, 0);
			}

			if (profileName != NULL) {
					(*env)->ReleaseStringUTFChars(env, profileName, cstrProfileName);
			}

			return (retVal ? JNI_TRUE : JNI_FALSE);
	}





/*
 * Class:     magick_MagickImage
 * Method:    getImageProfile
 */
JNIEXPORT jbyteArray JNICALL Java_magick_MagickImage_getImageProfile
	(JNIEnv *env, jobject self, jstring profileName)
{
  Image *image = NULL;
	const char * cstrProfileName;
	jbyteArray byteArray;
  StringInfo* profileInfo;
  unsigned char* byteElements;

	image = (Image * ) getHandle(env, self, "magickImageHandle", NULL);
	if (image == NULL) {
		throwMagickException(env, "No image to set file name");
		return JNI_FALSE;
	}

	if (profileName == NULL) {
		cstrProfileName = NULL;
	}
	else {
		cstrProfileName = (*env)->GetStringUTFChars(env, profileName, 0);
	}

	profileInfo = GetImageProfile(image, cstrProfileName);

	if (profileInfo != (const StringInfo*) NULL && profileInfo->length > 0) {

		/* Construct the byte array */
		byteArray = (*env)->NewByteArray(env, profileInfo -> length);
		if (byteArray == NULL) {
			throwMagickException(env, "Unable to allocate byte array "
													 "for profile info");
			return NULL;
		}

		byteElements = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);
		if (byteElements == NULL) {
			throwMagickException(env, "Unable to obtain byte array elements "
													 "for profile info");
			return NULL;
		}
		memcpy(byteElements,
					 GetStringInfoDatum(profileInfo),
					 GetStringInfoLength(profileInfo));

		(*env) -> ReleaseByteArrayElements(env, byteArray, byteElements, 0);
	}
	else {
		byteArray = NULL;
	}

	if (profileName != NULL) {
		( * env) -> ReleaseStringUTFChars(env, profileName, cstrProfileName);
	}
	return byteArray;
}




/*
 * Class:     magick_MagickImage
 * Method:    montageImages
 * Signature: (Lmagick/MontageInfo;)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_montageImages
  (JNIEnv *env, jobject self, jobject montageInfo)
{
    Image *image, *montage;
    MontageInfo *info;
    ExceptionInfo exception;
    jobject newObj;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    info = (MontageInfo*)
        getHandle(env, montageInfo, "montageInfoHandle", NULL);
    if (info == NULL) {
        throwMagickException(env, "Unable to retrieve MontageInfo handle");
        return NULL;
    }

    GetExceptionInfo(&exception);
    montage = MontageImages(image, info, &exception);
    if (montage == NULL) {
        throwMagickApiException(env, "Failed to create montage", &exception);
        DestroyExceptionInfo(&exception);
        return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, montage);
    if (newObj == NULL) {
        DestroyImages(montage);
        throwMagickException(env, "Unable to create montage");
        return NULL;
    }
    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    averageImages
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_averageImages
  (JNIEnv *env, jobject self)
{
    Image *image, *average;
    ExceptionInfo exception;
    jobject newObj;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    average = AverageImages(image, &exception);
    if (average == NULL) {
        throwMagickApiException(env, "Failed to create average image",
                                &exception);
        DestroyExceptionInfo(&exception);
        return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, average);
    if (newObj == NULL) {
        DestroyImages(average);
        throwMagickException(env, "Unable to create average image");
        return NULL;
    }
    return newObj;
}



/*
 * Class:     magick_MagickImage
 * Method:    levelImage
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_levelImage
  (JNIEnv *env, jobject self, jstring levels)
{
    Image *image = NULL;
    const char *cstr;
    jboolean retVal;

    /* Obtain the Image handle */
    image = (Image*) getHandle(env, self,
                               "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain Image handle");
	return JNI_FALSE;
    }

    cstr = (*env)->GetStringUTFChars(env, levels, 0);
    retVal = LevelImage(image, cstr);
    (*env)->ReleaseStringUTFChars(env, levels, cstr);

    return retVal;
}



/*
 * Class:     magick_MagickImage
 * Method:    sizeBlob
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_sizeBlob
  (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    /* Obtain the Image handle */
    image = (Image*) getHandle(env, self,
                               "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain Image handle");
	return -1;
    }

    return SizeBlob(image);
}


/*
 * Class:     magick_MagickImage
 * Method:    setCompression
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setCompression,
             compression,
             "magickImageHandle",
             Image)



/*
 * Class:     magick_MagickImage
 * Method:    getCompression
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getCompression,
             compression,
             "magickImageHandle",
             Image)

/*
 * Class:     magick_MagickImage
 * Method:    getImageType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_magick_MagickImage_getImageType
  (JNIEnv *env, jobject self)
{
    jint imageType;
    ExceptionInfo exception;

    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return -1;
    }
    GetExceptionInfo(&exception);
    imageType = GetImageType( image, &exception);
    DestroyExceptionInfo(&exception);
    return imageType;
}


/*
 * Class:     magick_MagickImage
 * Method:    getOnePixel
 * Signature: (II)Lmagick/PixelPacket;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getOnePixel
    (JNIEnv *env, jobject self, jint xPos, jint yPos)
{
    Image *image = NULL;
    jobject jPixelPacket = NULL;
    PixelPacket pixel;
    jclass pixelPacketClass;
    jmethodID consMethodID;

    image = (Image *) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to retrieve image");
        return NULL;
    }

    pixel = GetOnePixel(image, xPos, yPos);
    if (&pixel == NULL) {
        throwMagickException(env, "Unable to retrieve pixel");
    }

    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");
    if (pixelPacketClass == 0) {
        throwMagickException(env,
                             "Unable to locate class magick.PixelPacket");
        return NULL;
    }

    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,
                                       "<init>", "(IIII)V");
    if (consMethodID == 0) {
        throwMagickException(env, "Unable to construct magick.PixelPacket");
        return NULL;
    }

    jPixelPacket = (*env)->NewObject(env, pixelPacketClass, consMethodID,
                                     (jint) pixel.red,
                                     (jint) pixel.green,
                                     (jint) pixel.blue,
                                     (jint) pixel.opacity);
    if (jPixelPacket == NULL) {
        throwMagickException(env, "Unable to construct magick.PixelPacket");
        return NULL;
    }

    return jPixelPacket;
}


/*
 * Class:     magick_MagickImage
 * Method:    setBorderColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MagickImage_setBorderColor,
                     border_color,
                     "magickImageHandle",
                     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getBorderColor
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_MagickImage_getBorderColor,
                     border_color,
                     "magickImageHandle",
                     Image)


/*
 * Class:     magick_MagickImage
 * Method:    setBackgroundColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MagickImage_setBackgroundColor,
                     background_color,
                     "magickImageHandle",
                     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getBackgroundColor
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_MagickImage_getBackgroundColor,
                     background_color,
                     "magickImageHandle",
                     Image)

/*
 * Class:     magick_MagickImage
 * Method:    setDelay
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setDelay,
	     delay,
	     "magickImageHandle",
	     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getDelay
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getDelay,
	     delay,
	     "magickImageHandle",
	     Image)



/*
 * Class:     magick_MagickImage
 * Method:    setDispose
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setDispose,
	     dispose,
	     "magickImageHandle",
	     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getDispose
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getDispose,
	     dispose,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    setIterations
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setIterations,
	     iterations,
	     "magickImageHandle",
	     Image)

/*
 * Class:     magick_MagickImage
 * Method:    getIterations
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getIterations,
	     iterations,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    setColors
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setColors,
	     colors,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    getColors
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getColors,
	     colors,
	     "magickImageHandle",
	     Image)



/*
 * Class:     magick_MagickImage
 * Method:    getTotalColors
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getTotalColors,
	     total_colors,
	     "magickImageHandle",
	     Image)


/*
 * Class:     magick_MagickImage
 * Method:    getColormap
 * Signature: (I)Lmagick/PixelPacket;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_getColormap__I
  (JNIEnv *env, jobject self, jint index)
{
    Image *image;
    jobject jPixelPacket = NULL;
    jclass pixelPacketClass;
    jmethodID consMethodID;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain image handle");
        return NULL;
    }

    if (index >= image->colors) {
        throwMagickException(env, "Index out of range");
        return NULL;
    }

    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");
    if (pixelPacketClass == 0) {
	throwMagickException(env,
			     "Unable to locate class magick.PixelPacket");
	return NULL;
    }

    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,
				       "<init>", "(IIII)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    jPixelPacket = (*env)->NewObject(env, pixelPacketClass, consMethodID,
		                     (jint) image->colormap[index].red,
		                     (jint) image->colormap[index].green,
		                     (jint) image->colormap[index].blue,
		                     (jint) image->colormap[index].opacity);
    if (jPixelPacket == NULL) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    return jPixelPacket;
}



/*
 * Class:     magick_MagickImage
 * Method:    getColormap
 * Signature: ()[Lmagick/PixelPacket;
 */
JNIEXPORT jobjectArray JNICALL Java_magick_MagickImage_getColormap__
  (JNIEnv *env, jobject self)
{
    Image *image;
    jobject jPixelPacket = NULL;
    jclass pixelPacketClass;
    jmethodID consMethodID;
    jobjectArray jPPArray;
    int i;

    /* Get the image handle */
    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain image handle");
        return NULL;
    }

    /* Sanity check */
    if (image->colors <= 0 || image->colormap == NULL) {
        throwMagickException(env, "Image does not have a colourmap");
        return NULL;
    }

    /* Get the PixelPacket object class */
    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");
    if (pixelPacketClass == 0) {
	throwMagickException(env,
			     "Unable to locate class magick.PixelPacket");
	return NULL;
    }

    /* Get the constructor ID for PixelPacket */
    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,
				       "<init>", "(IIII)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    /* Create the PixelPacket array */
    jPPArray =
        (*env)->NewObjectArray(env, image->colors, pixelPacketClass, NULL);
    if (jPPArray == NULL) {
        throwMagickException(env, "Unable to construct PixelPacket[]");
        return NULL;
    }

    /* Construct a PixelPacket for each item in the colourmap */
    for (i = 0; i < image->colors; i++) {

        /* Create the PixelPacket */
        jPixelPacket =
            (*env)->NewObject(env, pixelPacketClass, consMethodID,
                              (jint) image->colormap[i].red,
                              (jint) image->colormap[i].green,
                              (jint) image->colormap[i].blue,
                              (jint) image->colormap[i].opacity);
        if (jPixelPacket == NULL) {
            throwMagickException(env, "Unable to construct magick.PixelPacket");
            return NULL;
        }

        /* Set the PixelPacket in the array */
        (*env)->SetObjectArrayElement(env, jPPArray, i, jPixelPacket);
    }

    return jPPArray;
}

/*
 * Class:     magick_MagickImage
 * Method:    trimImage
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_trimImage
    (JNIEnv *env, jobject self)
{
    Image *image = NULL, *trimmedImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    trimmedImage = TrimImage(image, &exception);
    if (trimmedImage == NULL) {
	throwMagickApiException(env, "Cannot trim image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, trimmedImage);
    if (newObj == NULL) {
	DestroyImages(trimmedImage);
	throwMagickException(env, "Unable to create trimmed image");
	return NULL;
    }

    return newObj;
}


/*
 * Class:     magick_MagickImage
 * Method:    blurImageChannel
 * Signature: (DD)Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_MagickImage_blurImageChannel
  (JNIEnv *env, jobject self, int channelType, jdouble radius, jdouble sigma)
{
    Image *image = NULL, *blurredImage = NULL;
    jobject newObj;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    blurredImage = BlurImageChannel(image, channelType, radius, sigma, &exception);
    if (blurredImage == NULL) {
	throwMagickApiException(env, "Cannot blur image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, blurredImage);
    if (newObj == NULL) {
	DestroyImages(blurredImage);
	throwMagickException(env, "Unable to create new blurred image");
	return NULL;
    }

    return newObj;
}




/*
 * Class:     magick_MagickImage
 * Method:    signatureImage
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_magick_MagickImage_signatureImage
    (JNIEnv *env, jobject self)
{
    Image *image = NULL;
    jboolean retVal;

    /* Obtain the Image handle */
    image = (Image*) getHandle(env, self,
                               "magickImageHandle", NULL);
    if (image == NULL) {
      throwMagickException(env, "Cannot obtain Image handle");
      return JNI_FALSE;
    }

    retVal = SignatureImage(image);
    return(retVal);
}


/*
 * Class:     magick_MagickImage
 * Method:    getQuality
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getQuality,
	     quality,
	     "magickImageHandle",
	     Image)

/*
 * Class:     magick_MagickImage
 * Method:    setRenderingIntent
 * Signature: (I)V
 */
setIntMethod(Java_magick_MagickImage_setRenderingIntent,
    rendering_intent,
    "magickImageHandle",
    Image)

/*
 * Class:     magick_MagickImage
 * Method:    getRenderingIntent
 * Signature: ()I
 */
getIntMethod(Java_magick_MagickImage_getRenderingIntent,
    rendering_intent,
    "magickImageHandle",
    Image)

/*
 * Class:     magick_MagickImage
 * Method:    setMatte
 * Signature: (Z)V
 */
setBoolMethod(Java_magick_MagickImage_setMatte,
    matte,
    "magickImageHandle",
    Image)

/*
 * Class:     magick_MagickImage
 * Method:    getMatte
 * Signature: ()Z
 */
getBoolMethod(Java_magick_MagickImage_getMatte,
    matte,
    "magickImageHandle",
    Image)
