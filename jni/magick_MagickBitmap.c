#include <jni.h>
#include <assert.h>
#include <stdlib.h>

JNIEXPORT jintArray JNICALL
    Java_magick_util_MagickBitmap_bytesToInts(JNIEnv *env, jclass cls, jbyteArray bytes) {
	jintArray result;
	jbyte *bytePtr;
	//jint *intPtr;
	int size;
	int byteLen;
	byteLen = (*env)->GetArrayLength(env, bytes);
	assert(byteLen % 4 == 0);
	size = byteLen / 4;
	result = (*env)->NewIntArray(env, size);
	if (result == NULL) return NULL;
	bytePtr = (*env)->GetByteArrayElements(env, bytes, 0);
	(*env)->SetIntArrayRegion(env, result, 0, size, (jint *)bytePtr);
	// cleanup
    (*env)->ReleaseByteArrayElements(env, bytes, bytePtr, 0);
	return result;
	}

