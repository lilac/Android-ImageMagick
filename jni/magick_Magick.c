#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
#include "jmagick.h"
//#include "magick_Magick.h"

/*
 * Class:     magick_Magick
 * Method:    parseImageGeometry
 * Signature: (Ljava/lang/String;Ljava/awt/Rectangle;)I
 */
JNIEXPORT void JNICALL Java_magick_Magick_init
  (JNIEnv *env, jclass magickClass)
{
	MagickCoreGenesis(NULL, MagickFalse);
}

/*
 * Class:     magick_Magick
 * Method:    parseImageGeometry
 * Signature: (Ljava/lang/String;Ljava/awt/Rectangle;)I
 */
JNIEXPORT jint JNICALL Java_magick_Magick_parseImageGeometry
  (JNIEnv *env, jclass magickClass, jstring geometry, jobject rect)
{
    unsigned long x, y, width, height;
    jint flags;
    const char *cstr;

    if (!getIntFieldValue(env, rect, "width", NULL, (jint *) &width) ||
	!getIntFieldValue(env, rect, "height", NULL, (jint *) &height) ||
	!getIntFieldValue(env, rect, "x", NULL, (jint *) &x) ||
	!getIntFieldValue(env, rect, "y", NULL, (jint *) &y)) {
        throwMagickException(env, "Unable to obtain Rectangle values");
        return 0;
    }

    cstr = (const char *) (*env)->GetStringUTFChars(env, geometry, 0);
    flags = ParseImageGeometry(cstr, &x, &y, &width, &height);
    (*env)->ReleaseStringUTFChars(env, geometry, cstr);

    if (!setIntFieldValue(env, rect, "width", NULL, width) ||
	!setIntFieldValue(env, rect, "height", NULL, height) ||
	!setIntFieldValue(env, rect, "x", NULL, x) ||
	!setIntFieldValue(env, rect, "y", NULL, y)) {
        throwMagickException(env, "Unable to set Rectangle values");
        return 0;
    }

    return flags;
}

