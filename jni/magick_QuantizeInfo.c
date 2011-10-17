#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
#include "jmagick.h"
//#include "magick_ImageInfo.h"



/*
 * Class:     magick_QuantizeInfo
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_QuantizeInfo_init
  (JNIEnv *env, jobject self)
{
    QuantizeInfo *quantizeInfo = NULL;
    jfieldID fid = 0;

    quantizeInfo =
	(QuantizeInfo*) getHandle(env, self, "quantizeInfoHandle", &fid);

    if (quantizeInfo == NULL) {
	quantizeInfo = (QuantizeInfo *) AcquireMemory(sizeof(QuantizeInfo));
	if (quantizeInfo == NULL) {
	    throwMagickException(env, "Unable to allow memory for handle");
	    return;
	}
    }
    GetQuantizeInfo(quantizeInfo);

    setHandle(env, self, "quantizeInfoHandle", (void*) quantizeInfo, &fid);
}



/*
 * Class:     magick_QuantizeInfo
 * Method:    destroyQuantizeInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_QuantizeInfo_destroyQuantizeInfo
  (JNIEnv *env, jobject self)
{
    QuantizeInfo *quantizeInfo = NULL;
    jfieldID handleFid = 0;

    quantizeInfo = (QuantizeInfo*) getHandle(env, self,
				       "quantizeInfoHandle", &handleFid);

    if (quantizeInfo != NULL) {
	setHandle(env, self, "quantizeInfoHandle", NULL, &handleFid);
	DestroyQuantizeInfo(quantizeInfo);
    }
}



/*
 * Class:     magick_QuantizeInfo
 * Method:    setNumberColors
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setNumberColors,
	     number_colors,
	     "quantizeInfoHandle",
	     QuantizeInfo)

/*
 * Class:     magick_QuantizeInfo
 * Method:    getNumberColors
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getNumberColors,
	     number_colors,
	     "quantizeInfoHandle",
	     QuantizeInfo)

/*
 * Class:     magick_QuantizeInfo
 * Method:    setTreeDepth
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setTreeDepth,
	     tree_depth,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    getTreeDepth
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getTreeDepth,
	     tree_depth,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    setDither
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setDither,
	     dither,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    getDither
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getDither,
	     dither,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    setColorspace
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setColorspace,
	     colorspace,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    getColorspace
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getColorspace,
	     colorspace,
	     "quantizeInfoHandle",
	     QuantizeInfo)



/*
 * Class:     magick_QuantizeInfo
 * Method:    setMeasureError
 * Signature: (I)V
 */
setIntMethod(Java_magick_QuantizeInfo_setMeasureError,
	     measure_error,
	     "quantizeInfoHandle",
	     QuantizeInfo)


/*
 * Class:     magick_QuantizeInfo
 * Method:    getMeasureError
 * Signature: ()I
 */
getIntMethod(Java_magick_QuantizeInfo_getMeasureError,
	     measure_error,
	     "quantizeInfoHandle",
	     QuantizeInfo)

