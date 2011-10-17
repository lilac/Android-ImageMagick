#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
#include "jmagick.h"
//#include "magick_DrawInfo.h"


/*
 * Class:     magick_DrawInfo
 * Method:    init
 * Signature: (Lmagick/ImageInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_DrawInfo_init
  (JNIEnv *env, jobject self, jobject jImageInfo)
{
    jfieldID drawInfoFieldID = 0;
    ImageInfo *imageInfo = NULL;
    DrawInfo *drawInfo = NULL;

    /* Get the ImageInfo handle. */
    imageInfo = (ImageInfo*) getHandle(env, jImageInfo,
				       "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Unable to get ImageInfo handle");
	return;
    }

    /* If the DrawInfo handle is not NULL, we destroy the old
     * handle before creating a new one.
     */
    drawInfo = (DrawInfo*) getHandle(env, self,
				     "drawInfoHandle",
				     &drawInfoFieldID);
    if (drawInfo != NULL) {
	DestroyDrawInfo(drawInfo);
    }

    /* Initialise and set the new DrawInfo handle. */
    drawInfo = (DrawInfo*) AcquireMemory(sizeof(DrawInfo));
    if (drawInfo == NULL) {
	throwMagickException(env, "Memory allocation failure");
	return;
    }
    GetDrawInfo(imageInfo, drawInfo);
    // drawInfo->encoding = (char *) AcquireString("Unicode");
    if (!setHandle(env, self, "drawInfoHandle",
		   drawInfo, &drawInfoFieldID)) {
	throwMagickException(env, "Unable to set DrawInfo handle");
	return;
    }
}


/*
 * Class:     magick_DrawInfo
 * Method:    destroyDrawInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_DrawInfo_destroyDrawInfo
  (JNIEnv *env, jobject self)
{
    DrawInfo *info = NULL;
    jfieldID fieldID = 0;

    info = (DrawInfo*) getHandle(env, self,
				 "drawInfoHandle", &fieldID);
    if (info != NULL) {
	DestroyDrawInfo(info);
	setHandle(env, self, "drawInfoHandle", NULL, &fieldID);
    }
}



/*
 * Class:     magick_DrawInfo
 * Method:    setPrimitive
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_DrawInfo_setPrimitive
    (JNIEnv *env, jobject self, jstring primitive)
{
    DrawInfo *info = NULL;
    const char *cstr = NULL;
    const jchar *jstr = NULL;
    int i, len, is8bits;

    info = (DrawInfo *) getHandle(env, self, "drawInfoHandle", NULL);
    if (info == NULL) {
	throwMagickException(env, "Unable to retrieve handle");
	return;
    }

    if (info->primitive != NULL) {
//	RelinquishMagickMemory((void**) &info->primitive);
    }

    jstr = (*env)->GetStringChars(env, primitive, 0);
    len = (*env)->GetStringLength(env, primitive);
    is8bits = JNI_TRUE;
    for (i = 0; i < len; i++) {
        if (jstr[i] > 255) {
            is8bits = JNI_FALSE;
            break;
        }
    }

    if (is8bits) {
        char *str = (char *) AcquireMemory(len+1);
        if (str == NULL) {
            throwMagickException(env, "Unable to allocate memory");
            (*env)->ReleaseStringChars(env, primitive, jstr);
            return;
        }
        for (i = 0; i < len; i++) {
            str[i] = (char) jstr[i];
        }
        str[len] = '\0';
        info->primitive = str;
        printf("String: %s\n", str);
        if (info->encoding != NULL) {
           // RelinquishMagickMemory((void **) &info->encoding);
        }
    }

    (*env)->ReleaseStringChars(env, primitive, jstr);

    if (!is8bits) {
        cstr = (*env)->GetStringUTFChars(env, primitive, 0);
        if (cstr == NULL) {
            throwMagickException(env, "Unable to retrieve Java string chars");
            return;
        }
        info->primitive = (char *) AcquireString(cstr);
        (*env)->ReleaseStringUTFChars(env, primitive, cstr);
        if (info->primitive == NULL) {
            throwMagickException(env, "Unable to allocate memory");
        }
        if (info->encoding != NULL) {
            RelinquishMagickMemory((void **) &info->encoding);
        }
        info->encoding = (char *) AcquireString("UTF-8");
        if (info->encoding == NULL) {
            throwMagickException(env, "Unable to allocate memory");
        }
    }
}



/*
 * Class:     magick_DrawInfo
 * Method:    getPrimitive
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_DrawInfo_getPrimitive,
		primitive,
		"drawInfoHandle",
		DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    setGeometry
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_DrawInfo_setGeometry,
		geometry,
		"drawInfoHandle",
		DrawInfo)




/*
 * Class:     magick_DrawInfo
 * Method:    getGeometry
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_DrawInfo_getGeometry,
		geometry,
		"drawInfoHandle",
		DrawInfo)



/*
 * Class:     magick_DrawInfo
 * Method:    setText
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_DrawInfo_setText
    (JNIEnv *env, jobject self, jstring text)
{
    DrawInfo *info = NULL;
    const char *cstr = NULL;
    const jchar *jstr = NULL;
    int i, len, is8bits;

    info = (DrawInfo *) getHandle(env, self, "drawInfoHandle", NULL);
    if (info == NULL) {
	throwMagickException(env, "Unable to retrieve handle");
	return;
    }

    if (info->text != NULL) {
//	RelinquishMagickMemory((void**) &info->text);
    }

    jstr = (*env)->GetStringChars(env, text, 0);
    len = (*env)->GetStringLength(env, text);
    is8bits = JNI_TRUE;
    for (i = 0; i < len; i++) {
        if (jstr[i] > 255) {
            is8bits = JNI_FALSE;
            break;
        }
    }

    if (is8bits) {
        char *str = (char *) AcquireMemory(len+1);
        if (str == NULL) {
            throwMagickException(env, "Unable to allocate memory");
            (*env)->ReleaseStringChars(env, text, jstr);
            return;
        }
        for (i = 0; i < len; i++) {
            str[i] = (char) jstr[i];
        }
        str[len] = '\0';
        info->text = str;
        printf("String: %s\n", str);
        if (info->encoding != NULL) {
          //  RelinquishMagickMemory((void **) &info->encoding);
        }
    }

    (*env)->ReleaseStringChars(env, text, jstr);

    if (!is8bits) {
        cstr = (*env)->GetStringUTFChars(env, text, 0);
        if (cstr == NULL) {
            throwMagickException(env, "Unable to retrieve Java string chars");
            return;
        }
        info->text = (char *) AcquireString(cstr);
        (*env)->ReleaseStringUTFChars(env, text, cstr);
        if (info->text == NULL) {
            throwMagickException(env, "Unable to allocate memory");
        }
        if (info->encoding != NULL) {
          //  RelinquishMagickMemory((void **) &info->encoding);
        }
        info->encoding = (char *) AcquireString("UTF-8");
        if (info->encoding == NULL) {
            throwMagickException(env, "Unable to allocate memory");
        }
    }
}



/*
 * Class:     magick_DrawInfo
 * Method:    getText
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_DrawInfo_getText,
		text,
		"drawInfoHandle",
		DrawInfo)


/*
 * Class:     magick_DrawInfo
 * Method:    setFont
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_DrawInfo_setFont,
		font,
		"drawInfoHandle",
		DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getFont
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_DrawInfo_getFont,
		font,
		"drawInfoHandle",
		DrawInfo)


/*
 * Class:     magick_DrawInfo
 * Method:    setStrokeAntialias
 * Signature: (Z)V
 */
setBoolMethod(Java_magick_DrawInfo_setStrokeAntialias,
	      stroke_antialias,
	      "drawInfoHandle",
	      DrawInfo)


/*
 * Class:     magick_DrawInfo
 * Method:    getStrokeAntialias
 * Signature: ()Z
 */
getBoolMethod(Java_magick_DrawInfo_getStrokeAntialias,
	      stroke_antialias,
	      "drawInfoHandle",
	      DrawInfo)


/*
 * Class:     magick_DrawInfo
 * Method:    setTextAntialias
 * Signature: (Z)V
 */
setBoolMethod(Java_magick_DrawInfo_setTextAntialias,
	      text_antialias,
	      "drawInfoHandle",
	      DrawInfo)


/*
 * Class:     magick_DrawInfo
 * Method:    getTextAntialias
 * Signature: ()Z
 */
getBoolMethod(Java_magick_DrawInfo_getTextAntialias,
	      text_antialias,
	      "drawInfoHandle",
	      DrawInfo)


/*
 * Class:     magick_DrawInfo
 * Method:    setGravity
 * Signature: (I)V
 */
setIntMethod(Java_magick_DrawInfo_setGravity,
	     gravity,
	     "drawInfoHandle",
	     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getGravity
 * Signature: ()I
 */
getIntMethod(Java_magick_DrawInfo_getGravity,
	     gravity,
	     "drawInfoHandle",
	     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    setOpacity
 * Signature: (I)V
 */
setIntMethod(Java_magick_DrawInfo_setOpacity,
	     opacity,
	     "drawInfoHandle",
	     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getOpacity
 * Signature: ()I
 */
getIntMethod(Java_magick_DrawInfo_getOpacity,
	     opacity,
	     "drawInfoHandle",
	     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    setDecorate
 * Signature: (I)V
 */
setIntMethod(Java_magick_DrawInfo_setDecorate,
	     decorate,
	     "drawInfoHandle",
	     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getDecorate
 * Signature: ()I
 */
getIntMethod(Java_magick_DrawInfo_getDecorate,
	     decorate,
	     "drawInfoHandle",
	     DrawInfo)


/*
 * Class:     magick_DrawInfo
 * Method:    setStrokeWidth
 * Signature: (D)V
 */
setDoubleMethod(Java_magick_DrawInfo_setStrokeWidth,
		stroke_width,
		"drawInfoHandle",
		DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getStrokeWidth
 * Signature: ()D
 */
getDoubleMethod(Java_magick_DrawInfo_getStrokeWidth,
		stroke_width,
		"drawInfoHandle",
		DrawInfo)



/*
 * Class:     magick_DrawInfo
 * Method:    setPointsize
 * Signature: (D)V
 */
setDoubleMethod(Java_magick_DrawInfo_setPointsize,
		pointsize,
		"drawInfoHandle",
		DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getPointsize
 * Signature: ()D
 */
getDoubleMethod(Java_magick_DrawInfo_getPointsize,
		pointsize,
		"drawInfoHandle",
		DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    setFill
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_DrawInfo_setFill,
		     fill,
		     "drawInfoHandle",
		     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getFill
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_DrawInfo_getFill,
		     fill,
		     "drawInfoHandle",
		     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    setStroke
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_DrawInfo_setStroke,
		     stroke,
		     "drawInfoHandle",
		     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getStroke
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_DrawInfo_getStroke,
		     stroke,
		     "drawInfoHandle",
		     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    setUnderColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_DrawInfo_setUnderColor,
		     undercolor,
		     "drawInfoHandle",
		     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getUnderColor
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_DrawInfo_getUnderColor,
		     undercolor,
		     "drawInfoHandle",
		     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    setBorderColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_DrawInfo_setBorderColor,
		     border_color,
		     "drawInfoHandle",
		     DrawInfo)

/*
 * Class:     magick_DrawInfo
 * Method:    getBorderColor
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_DrawInfo_getBorderColor,
		     border_color,
		     "drawInfoHandle",
		     DrawInfo)


/*
 * Class:     magick_DrawInfo
 * Method:    setTile
 * Signature: (Lmagick/MagickImage;)V
 */
JNIEXPORT void JNICALL Java_magick_DrawInfo_setTile
  (JNIEnv *env, jobject self, jobject tileImage)
{
    DrawInfo *drawInfo;
    Image *image, *imgCopy;
    ExceptionInfo exception;

    drawInfo = (DrawInfo*) getHandle(env, self, "drawInfoHandle", NULL);
    if (drawInfo == NULL) {
        throwMagickException(env, "Unable to obtain DrawInfo handle");
        return;
    }

    image = (Image*) getHandle(env, tileImage, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain MagickImage handle");
        return;
    }

    GetExceptionInfo(&exception);
    imgCopy = CloneImage(image, 0, 0, 1, &exception);
    if (imgCopy == NULL) {
        throwMagickApiException(env, "Unable to clone MagickImage",
                                &exception);
        DestroyExceptionInfo(&exception);
        return;
    }
    DestroyExceptionInfo(&exception);

    if (drawInfo->tile != NULL) {
        DestroyImages(drawInfo->tile);
    }
    drawInfo->tile = imgCopy;
}

/*
 * Class:     magick_DrawInfo
 * Method:    getTile
 * Signature: ()Lmagick/MagickImage;
 */
JNIEXPORT jobject JNICALL Java_magick_DrawInfo_getTile
  (JNIEnv *env, jobject self)
{
    DrawInfo *drawInfo;
    Image *image;
    ExceptionInfo exception;
    jobject imgObj;

    drawInfo = (DrawInfo*) getHandle(env, self, "drawInfoHandle", NULL);
    if (drawInfo == NULL) {
        throwMagickException(env, "Unable to obtain DrawInfo handle");
        return NULL;
    }

    GetExceptionInfo(&exception);
    image = CloneImage(drawInfo->tile, 0, 0, 1, &exception);
    if (image == NULL) {
        throwMagickApiException(env, "Unable to clone image", &exception);
        DestroyExceptionInfo(&exception);
        return NULL;
    }
    DestroyExceptionInfo(&exception);

    imgObj = newImageObject(env, image);
    if (imgObj == NULL) {
        DestroyImages(image);
        throwMagickException(env, "Unable to create image object from handle");
        return NULL;
    }
    return imgObj;
}

