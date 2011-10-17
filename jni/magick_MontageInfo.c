#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
#include "jmagick.h"
//#include "magick_MontageInfo.h"


/*
 * Class:     magick_MontageInfo
 * Method:    init
 * Signature: (Lmagick/ImageInfo;)V
 */
JNIEXPORT void JNICALL Java_magick_MontageInfo_init
  (JNIEnv *env, jobject self, jobject imageInfo)
{
    ImageInfo *info;
    MontageInfo *montageInfo;

    /* Obtain the ImageInfo */
    info = (ImageInfo*) getHandle(env, imageInfo, "imageInfoHandle", NULL);
    if (info == NULL) {
        throwMagickException(env, "Unable to obtain ImageInfo handle");
        return;
    }

    /* Initialise the MontageInfo handle, allocating memory if required */
    montageInfo =
        (MontageInfo*) getHandle(env, self, "montageInfoHandle", NULL);
    if (montageInfo == NULL) {
        montageInfo = (MontageInfo*) AcquireMemory(sizeof(MontageInfo));
        if (montageInfo == NULL) {
            throwMagickException(env,
                                 "Unable to allocate "
                                 "memory for MontageInfo");
            return;
        }
    }
    GetMontageInfo(info, montageInfo);
    setHandle(env, self, "montageInfoHandle", (void*) montageInfo, NULL);
}



/*
 * Class:     magick_MontageInfo
 * Method:    destroyMontageInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MontageInfo_destroyMontageInfo
  (JNIEnv *env, jobject self)
{
    MontageInfo *montageInfo = NULL;
    jfieldID handleFid = 0;

    montageInfo = (MontageInfo*) getHandle(env, self,
                                           "montageInfoHandle", &handleFid);

    if (montageInfo != NULL) {
	setHandle(env, self, "montageInfoHandle", NULL, &handleFid);
	DestroyMontageInfo(montageInfo);
    }
}



/*
 * Class:     magick_MontageInfo
 * Method:    setGeometry
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_MontageInfo_setGeometry,
		geometry,
		"montageInfoHandle",
		MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    getGeometry
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_MontageInfo_getGeometry,
		geometry,
		"montageInfoHandle",
		MontageInfo)


/*
 * Class:     magick_MontageInfo
 * Method:    setTile
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_MontageInfo_setTile,
		tile,
		"montageInfoHandle",
		MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    getTile
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_MontageInfo_getTile,
		tile,
		"montageInfoHandle",
		MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    setTitle
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_MontageInfo_setTitle,
		title,
		"montageInfoHandle",
		MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    getTitle
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_MontageInfo_getTitle,
		title,
		"montageInfoHandle",
		MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    setFrame
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_MontageInfo_setFrame,
		frame,
		"montageInfoHandle",
		MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    getFrame
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_MontageInfo_getFrame,
		frame,
		"montageInfoHandle",
		MontageInfo)




/*
 * Class:     magick_MontageInfo
 * Method:    setTexture
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_MontageInfo_setTexture,
		texture,
		"montageInfoHandle",
		MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    getTexture
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_MontageInfo_getTexture,
		texture,
		"montageInfoHandle",
		MontageInfo)




/*
 * Class:     magick_MontageInfo
 * Method:    setFont
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_MontageInfo_setFont,
		font,
		"montageInfoHandle",
		MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    getFont
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_MontageInfo_getFont,
		font,
		"montageInfoHandle",
		MontageInfo)


/*
 * Class:     magick_MontageInfo
 * Method:    setPointSize
 * Signature: (D)V
 */
setDoubleMethod(Java_magick_MontageInfo_setPointSize,
                pointsize,
                "montageInfoHandle",
                MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getPointSize
 * Signature: ()D
 */
getDoubleMethod(Java_magick_MontageInfo_getPointSize,
                pointsize,
                "montageInfoHandle",
                MontageInfo)


/*
 * Class:     magick_MontageInfo
 * Method:    setBorderWidth
 * Signature: (I)V
 */
setIntMethod(Java_magick_MontageInfo_setBorderWidth,
             border_width,
             "montageInfoHandle",
             MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getBorderWidth
 * Signature: ()I
 */
getIntMethod(Java_magick_MontageInfo_getBorderWidth,
             border_width,
             "montageInfoHandle",
             MontageInfo)


/*
 * Class:     magick_MontageInfo
 * Method:    setGravity
 * Signature: (I)V
 */
setIntMethod(Java_magick_MontageInfo_setGravity,
             gravity,
             "montageInfoHandle",
             MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getGravity
 * Signature: ()I
 */
getIntMethod(Java_magick_MontageInfo_getGravity,
             gravity,
             "montageInfoHandle",
             MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    setShadow
 * Signature: (Z)V
 */
setBoolMethod(Java_magick_MontageInfo_setShadow,
              shadow,
              "montageInfoHandle",
              MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getShadow
 * Signature: ()Z
 */
getBoolMethod(Java_magick_MontageInfo_getShadow,
              shadow,
              "montageInfoHandle",
              MontageInfo)


/*
 * Class:     magick_MontageInfo
 * Method:    setFill
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MontageInfo_setFill,
                     fill,
                     "montageInfoHandle",
                     MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getFill
 * Signature: ()Z
 */
getPixelPacketMethod(Java_magick_MontageInfo_getFill,
                     fill,
                     "montageInfoHandle",
                     MontageInfo)


/*
 * Class:     magick_MontageInfo
 * Method:    setStroke
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MontageInfo_setStroke,
                     stroke,
                     "montageInfoHandle",
                     MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getStroke
 * Signature: ()Z
 */
getPixelPacketMethod(Java_magick_MontageInfo_getStroke,
                     stroke,
                     "montageInfoHandle",
                     MontageInfo)



/*
 * Class:     magick_MontageInfo
 * Method:    setBackgroundColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MontageInfo_setBackgroundColor,
                     background_color,
                     "montageInfoHandle",
                     MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getBackgroundColor
 * Signature: ()Z
 */
getPixelPacketMethod(Java_magick_MontageInfo_getBackgroundColor,
                     background_color,
                     "montageInfoHandle",
                     MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    setBorderColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MontageInfo_setBorderColor,
                     border_color,
                     "montageInfoHandle",
                     MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getBorderColor
 * Signature: ()Z
 */
getPixelPacketMethod(Java_magick_MontageInfo_getBorderColor,
                     border_color,
                     "montageInfoHandle",
                     MontageInfo)


/*
 * Class:     magick_MontageInfo
 * Method:    setMatteColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_MontageInfo_setMatteColor,
                     matte_color,
                     "montageInfoHandle",
                     MontageInfo)

/*
 * Class:     magick_MontageInfo
 * Method:    getMatteColor
 * Signature: ()Z
 */
getPixelPacketMethod(Java_magick_MontageInfo_getMatteColor,
                     matte_color,
                     "montageInfoHandle",
                     MontageInfo)


/*
 * Class:     magick_MontageInfo
 * Method:    setFileName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_MontageInfo_setFileName
  (JNIEnv *env, jobject self, jstring fileName)
{
    MontageInfo *montageInfo = NULL;
    const char *cstr = NULL;

    montageInfo = (MontageInfo*) getHandle(env, self,
                                           "montageInfoHandle", NULL);

    if (montageInfo == NULL) {
        throwMagickException(env, "Unable to obtain MontageInfo handle");
        return;
    }

    cstr = (*env)->GetStringUTFChars(env, fileName, 0);
    strcpy(montageInfo->filename, cstr);
    (*env)->ReleaseStringUTFChars(env, fileName, cstr);
}


/*
 * Class:     magick_MontageInfo
 * Method:    getFileName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_magick_MontageInfo_getFileName
  (JNIEnv *env, jobject self)
{
    MontageInfo *montageInfo = NULL;

    montageInfo =
        (MontageInfo*) getHandle(env, self, "montageInfoHandle", NULL);
    if (montageInfo == NULL) {
	throwMagickException(env, "Unable to retrieve MontageInfo handle");
	return NULL;
    }

    return (*env)->NewStringUTF(env, montageInfo->filename);
}
