#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
//#include "magick_ImageInfo.h"
#include "jmagick.h"






/*
 * Class:     magick_ImageInfo
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_ImageInfo_init
    (JNIEnv *env, jobject obj)
{
    ImageInfo *imageInfo = NULL;
    jfieldID fid = 0;

    imageInfo = (ImageInfo*) getHandle(env, obj, "imageInfoHandle", &fid);

    if (imageInfo == NULL) {
	imageInfo = (ImageInfo *) AcquireMemory(sizeof(ImageInfo));
	if (imageInfo == NULL) {
	    throwMagickException(env, "Unable to allocate memory for handle");
	    return;
	}
    }
    GetImageInfo(imageInfo);

    setHandle(env, obj, "imageInfoHandle", (void*) imageInfo, &fid);
}

/*
 * Class:     magick_ImageInfo
 * Method:    setImageOption
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_ImageInfo_setImageOption
    (JNIEnv *env, jobject self, jstring option, jstring value)
{                                                                             
    ImageInfo *info = NULL;
    const char *cstr1 = NULL;
    const char *cstr2 = NULL;
                                                                              
    info = (ImageInfo *) getHandle(env, self, "imageInfoHandle", NULL);             
    if (info == NULL) {                                                       
        throwMagickException(env, "Unable to retrieve handle");               
        return;                                                               
    }                                                                         
                                                                              
    cstr1 = (*env)->GetStringUTFChars(env, option, 0);                          
    if (cstr1 == NULL) {                                                       
        throwMagickException(env, "Unable to retrieve Java string chars");    
        return;                                                               
    }                        

    cstr2 = (*env)->GetStringUTFChars(env, value, 0);                          
    if (cstr2 == NULL) {                                                       
        throwMagickException(env, "Unable to retrieve Java string chars");    
        return;                                                               
    }                        
             
    SetImageOption(info, (char *)AcquireString(cstr1), (char *)AcquireString(cstr2));
    
    (*env)->ReleaseStringUTFChars(env, option, cstr1);
    (*env)->ReleaseStringUTFChars(env, value, cstr2);                          
}


/*
 * Class:     magick_ImageInfo
 * Method:    setFileName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_magick_ImageInfo_setFileName
    (JNIEnv *env, jobject obj, jstring fileName)
{
    ImageInfo *imageInfo = NULL;
    jfieldID handleFid = 0;
    const char *cstr = NULL;

    imageInfo = (ImageInfo*) getHandle(env, obj,
				       "imageInfoHandle", &handleFid);

    if (imageInfo == NULL) {
	imageInfo = (ImageInfo *) AcquireMemory(sizeof(ImageInfo));
	if (imageInfo == NULL) {
	    throwMagickException(env, "Unable to allow memory for handle");
	    return;
	}
	GetImageInfo(imageInfo);
	setHandle(env, obj, "imageInfoHandle", (void*) imageInfo, &handleFid);
    }

    cstr = (*env)->GetStringUTFChars(env, fileName, 0);
    strcpy(imageInfo->filename, cstr);
    (*env)->ReleaseStringUTFChars(env, fileName, cstr);

#ifdef DIAGNOSTIC
    fprintf(stderr, "Set the file name in ImageInfo to %s\n",
            imageInfo->filename);
#endif
}


/*
 * Class:     magick_ImageInfo
 * Method:    getFileName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_magick_ImageInfo_getFileName
    (JNIEnv *env, jobject obj)
{
    ImageInfo *imageInfo = NULL;

    imageInfo = (ImageInfo*) getHandle(env, obj, "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Unable to retrieve ImageInfo handle");
	return NULL;
    }

    return (*env)->NewStringUTF(env, imageInfo->filename);
}




/*
 * Class:     magick_ImageInfo
 * Method:    setSubimage
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setSubimage,
	     subimage,
	     "imageInfoHandle",
	     ImageInfo)




/*
 * Class:     magick_ImageInfo
 * Method:    getSubimage
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getSubimage,
	     subimage,
	     "imageInfoHandle",
	     ImageInfo)




/*
 * Class:     magick_ImageInfo
 * Method:    setSubrange
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setSubrange,
	     subrange,
	     "imageInfoHandle",
	     ImageInfo)





/*
 * Class:     magick_ImageInfo
 * Method:    getSubrange
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getSubrange,
	     subrange,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setServerName
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_ImageInfo_setServerName,
		server_name,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getServerName
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_ImageInfo_getServerName,
		server_name,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setFont
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_ImageInfo_setFont,
		font,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getFont
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_ImageInfo_getFont,
		font,
		"imageInfoHandle",
		ImageInfo)




/*
 * Class:     magick_ImageInfo
 * Method:    setSize
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_ImageInfo_setSize,
		size,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getSize
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_ImageInfo_getSize,
		size,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setTile
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_ImageInfo_setTile,
		tile,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getTile
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_ImageInfo_getTile,
		tile,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setDensity
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_ImageInfo_setDensity,
		density,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getDensity
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_ImageInfo_getDensity,
		density,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setPage
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_ImageInfo_setPage,
		page,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getPage
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_ImageInfo_getPage,
		page,
		"imageInfoHandle",
		ImageInfo)




/*
 * Class:     magick_ImageInfo
 * Method:    setTexture
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_ImageInfo_setTexture,
		texture,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getTexture
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_ImageInfo_getTexture,
		texture,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setView
 * Signature: (Ljava/lang/String;)V
 */
setStringMethod(Java_magick_ImageInfo_setView,
		view,
		"imageInfoHandle",
		ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getView
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_ImageInfo_getView,
		view,
		"imageInfoHandle",
		ImageInfo)




/*
 * Class:     magick_ImageInfo
 * Method:    setAdjoin
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setAdjoin,
	     adjoin,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getAdjoin
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getAdjoin,
	     adjoin,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setColorspace
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setColorspace,
	     colorspace,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getColorspace
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getColorspace,
	     colorspace,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setCompression
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setCompression,
	     compression,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getCompression
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getCompression,
	     compression,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setDither
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setDither,
	     dither,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getDither
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getDither,
	     dither,
	     "imageInfoHandle",
	     ImageInfo)


/*
 * Class:     magick_ImageInfo
 * Method:    setAntialias
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setAntialias,
	     antialias,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getAntialias
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getAntialias,
	     antialias,
	     "imageInfoHandle",
	     ImageInfo)


/*
 * Class:     magick_ImageInfo
 * Method:    setInterlace
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setInterlace,
	     interlace,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getInterlace
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getInterlace,
	     interlace,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setMonochrome
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setMonochrome,
	     monochrome,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getMonochrome
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getMonochrome,
	     monochrome,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setPointSize
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setPointSize,
	     pointsize,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getPointSize
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getPointSize,
	     pointsize,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setQuality
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setQuality,
	     quality,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getQuality
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getQuality,
	     quality,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    setVerbose
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setVerbose,
	     verbose,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getVerbose
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getVerbose,
	     verbose,
	     "imageInfoHandle",
	     ImageInfo)


/*
 * Class:     magick_ImageInfo
 * Method:    setPreviewType
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setPreviewType,
	     preview_type,
	     "imageInfoHandle",
	     ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getPreviewType
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getPreviewType,
	     preview_type,
	     "imageInfoHandle",
	     ImageInfo)




/*
 * Class:     magick_ImageInfo
 * Method:    setPing
 * Signature: (Z)V
 */
setBoolMethod(Java_magick_ImageInfo_setPing,
 	      ping,
	      "imageInfoHandle",
	      ImageInfo)



/*
 * Class:     magick_ImageInfo
 * Method:    getPing
 * Signature: ()Z
 */
getBoolMethod(Java_magick_ImageInfo_getPing,
	      ping,
	      "imageInfoHandle",
	      ImageInfo)




/*
 * Class:     magick_ImageInfo
 * Method:    destroyImageInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_ImageInfo_destroyImageInfo
    (JNIEnv *env, jobject obj)
{
    ImageInfo *imageInfo = NULL;
    jfieldID handleFid = 0;

    imageInfo = (ImageInfo*) getHandle(env, obj,
				       "imageInfoHandle", &handleFid);

    if (imageInfo != NULL) {
	setHandle(env, obj, "imageInfoHandle", NULL, &handleFid);
	DestroyImageInfo(imageInfo);
    }
}


/*
 * Class:     magick_ImageInfo
 * Method:    setMagick
 * Signature: (Ljava/lang/String;)V
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT void JNICALL Java_magick_ImageInfo_setMagick
    (JNIEnv *env, jobject obj, jstring magick)
{
    ImageInfo *imageInfo = NULL;
    jfieldID handleFid = 0;
    const char *cstr = NULL;

    imageInfo = (ImageInfo*) getHandle(env, obj,
				       "imageInfoHandle", &handleFid);

    if (imageInfo == NULL) {
	imageInfo = (ImageInfo *) AcquireMemory(sizeof(ImageInfo));
	if (imageInfo == NULL) {
	    throwMagickException(env, "Unable to allocate memory for handle");
	    return;
	}
	GetImageInfo(imageInfo);
	setHandle(env, obj, "imageInfoHandle", (void*) imageInfo, &handleFid);
    }

    cstr = (*env)->GetStringUTFChars(env, magick, 0);
    strcpy(imageInfo->magick, cstr);
    (*env)->ReleaseStringUTFChars(env, magick, cstr);

#ifdef DIAGNOSTIC
    fprintf(stderr, "Set the magick member in ImageInfo to %s\n",
            imageInfo->magick);
#endif
}

/*
 * Class:     magick_ImageInfo
 * Method:    getMagick
 * Signature: ()Ljava/lang/String;
 *
 * Contributed by Abdulbaset Gaddah <agaddah@yahoo.com>
 */
JNIEXPORT jstring JNICALL Java_magick_ImageInfo_getMagick
    (JNIEnv *env, jobject obj)
{
    ImageInfo *imageInfo = NULL;

    imageInfo = (ImageInfo*) getHandle(env, obj, "imageInfoHandle", NULL);
    if (imageInfo == NULL) {
	throwMagickException(env, "Unable to retrieve ImageInfo handle");
	return NULL;
    }

    return (*env)->NewStringUTF(env, imageInfo->magick);
}


/*
 * Class:     magick_ImageInfo
 * Method:    setUnits
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setUnits,
	     units,
	     "imageInfoHandle",
	     ImageInfo)


/*
 * Class:     magick_ImageInfo
 * Method:    getUnits
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getUnits,
	     units,
	     "imageInfoHandle",
	     ImageInfo)





/*
 * Class:     magick_ImageInfo
 * Method:    setBorderColor
 * Signature: (Lmagick/PixelPacket;)V
 */
setPixelPacketMethod(Java_magick_ImageInfo_setBorderColor,
                     border_color,
                     "imageInfoHandle",
                     ImageInfo)

/*
 * Class:     magick_ImageInfo
 * Method:    getBorderColor
 * Signature: ()Lmagick/PixelPacket;
 */
getPixelPacketMethod(Java_magick_ImageInfo_getBorderColor,
                     border_color,
                     "imageInfoHandle",
                     ImageInfo)

/*
 * Class:     magick_ImageInfo
 * Method:    getDepth
 * Signature: ()I
 */
getIntMethod(Java_magick_ImageInfo_getDepth,
	     depth,
	     "imageInfoHandle",
	     ImageInfo)

/*
 * Class:     magick_ImageInfo
 * Method:    setDepth
 * Signature: (I)V
 */
setIntMethod(Java_magick_ImageInfo_setDepth,
	     depth,
	     "imageInfoHandle",
	     ImageInfo)
