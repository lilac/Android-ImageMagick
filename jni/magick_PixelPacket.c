#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
#include "jmagick.h"
//#include "magick_PixelPacket.h"


/*
 * Class:     magick_PixelPacket
 * Method:    queryColorDatabase
 * Signature: (Ljava/lang/String;)Lmagick/PixelPacket;
 */
JNIEXPORT jobject JNICALL Java_magick_PixelPacket_queryColorDatabase
    (JNIEnv *env, jclass class, jstring target)
{
    PixelPacket iPixelPacket;
    const char *cstr;
    unsigned int result;
    jmethodID consMethodID;
    jobject jPixelPacket;
    ExceptionInfo exception;

    cstr = (*env)->GetStringUTFChars(env, target, 0);
    GetExceptionInfo(&exception);
    result = QueryColorDatabase(cstr, &iPixelPacket, &exception);
    (*env)->ReleaseStringUTFChars(env, target, cstr);

    if (!result) {
	throwMagickApiException(env, "Unable to locate color", &exception);
        DestroyExceptionInfo(&exception);
	return NULL;
    }

    consMethodID = (*env)->GetMethodID(env, class, "<init>", "(IIII)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

#ifdef DIAGNOSTIC
    fprintf(stderr, "Query colour %d, %d, %d, %d\n",
            iPixelPacket.red,
            iPixelPacket.green,
            iPixelPacket.blue,
            iPixelPacket.opacity);
#endif

    jPixelPacket = (*env)->NewObject(env, class, consMethodID,
				     (jint) iPixelPacket.red,
				     (jint) iPixelPacket.green,
				     (jint) iPixelPacket.blue,
				     (jint) iPixelPacket.opacity);
    if (jPixelPacket == NULL) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    return jPixelPacket;
}
