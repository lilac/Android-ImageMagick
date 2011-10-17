#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
//#include "magick_MagickInfo.h"
#include "jmagick.h"


/*
 * Class:     magick_MagickInfo
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MagickInfo_init
  (JNIEnv *env, jobject self, jstring modname)
{
    MagickInfo *magickInfo = NULL;
    jfieldID fid = 0;
    ExceptionInfo exception;
    const char *cstr = NULL;
    
    magickInfo = (MagickInfo*) getHandle(env, self, "magickInfoHandle", &fid);

    GetExceptionInfo(&exception);

    cstr = (*env)->GetStringUTFChars(env, modname, 0);
    if (cstr == NULL)
        return; // out of memory
    
    magickInfo = (MagickInfo*) GetMagickInfo(cstr, &exception);
       
    // release the string
    (*env)->ReleaseStringUTFChars(env, modname, cstr);

    if (magickInfo == NULL) {
        throwMagickApiException(env, "Unable to read magick info", &exception);
        DestroyExceptionInfo(&exception);
        return;
    }
    DestroyExceptionInfo(&exception);

    setHandle(env, self, "magickInfoHandle", (void*) magickInfo, &fid);
}



/*
 * Class:     magick_MagickInfo
 * Method:    destroyMagickInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_magick_MagickInfo_destroyMagickInfo
  (JNIEnv *env, jobject self)
{
    MagickInfo *magickInfo = NULL;
    jfieldID handleFid = 0;

    magickInfo = (MagickInfo*) getHandle(env, self,
				       "magickInfoHandle", &handleFid);

    if (magickInfo != NULL) {
	setHandle(env, self, "magickInfoHandle", NULL, &handleFid);
	/* DestroyMagickInfo(); */
    }
}


/*
 * Class:     magick_MagickInfo
 * Method:    getDescription
 * Signature: ()Ljava/lang/String;
 */
getStringMethod(Java_magick_MagickInfo_getDescription,
		description,
		"magickInfoHandle",
		MagickInfo)
