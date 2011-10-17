#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
#include "jmagick.h"



/*
 * Convenience function to help throw an MagickException.
 */
void throwMagickException(JNIEnv *env, const char *mesg)
{
    jclass magickExceptionClass;

    magickExceptionClass = (*env)->FindClass(env, "magick/MagickException");
    if (magickExceptionClass == 0) {
	fprintf(stderr, "Cannot find MagickException class\n");
	return;
    }
    (*env)->ThrowNew(env, magickExceptionClass, mesg);
}



/*
 * Convenience function to help throw an MagickApiException.
 *
 * Input:
 *   mesg       JMagick message
 *   exception  points to a ImageMagick ExceptionInfo structure
 */
void throwMagickApiException(JNIEnv *env,
			     const char *mesg,
			     const ExceptionInfo *exception)
{
    jclass magickApiExceptionClass;
    jmethodID consMethodID = 0;
    jobject newObj;
    jstring jreason, jdescription;
    int result;

    /* Find the class ID */
    magickApiExceptionClass =
	(*env)->FindClass(env, "magick/MagickApiException");
    if (magickApiExceptionClass == 0) {
	fprintf(stderr, "Cannot find MagickApiException class\n");
	return;
    }

    /* Find the constructor ID */
    consMethodID =
	(*env)->GetMethodID(env, magickApiExceptionClass,
			    "<init>",
			    "(ILjava/lang/String;Ljava/lang/String;)V");
    if (consMethodID == 0) {
	return;
    }

    /* Obtain the string objects */
    jreason = (*env)->NewStringUTF(env, exception->reason);
    if (jreason == NULL) {
#ifdef DIAGNOSTIC
	fprintf(stderr,
		"throwMagickApiException: "
		"Unable to create reason string\n");
#endif
	return;
    }

    jdescription = (*env)->NewStringUTF(env, exception->description);
    if (jdescription == NULL) {
#ifdef DIAGNOSTIC
	fprintf(stderr,
		"throwMagickApiException: "
		"Unable to create description string\n");
#endif
	return;
    }

    /* Create the MagickApiException object */
    newObj = (*env)->NewObject(env, magickApiExceptionClass, consMethodID,
			       exception->severity,
                               jreason, jdescription);
    if (newObj == NULL) {
#ifdef DIAGNOSTIC
	fprintf(stderr,
		"throwMagickApiException: "
		"Unable to create MagickApiException object\n");
#endif
	return;
    }

    /* Throw the exception. */
    result = (*env)->Throw(env, newObj);
#ifdef DIAGNOSTIC
    if (result != 0) {
	fprintf(stderr,
		"throwMagickApiException: "
		"Fail to throw MagickApiException");
    }
#endif
}



/*
 * Convenience function to retreive a handle from an object.
 *
 * Input:
 *   env         Java VM environment
 *   obj         Java object for which handle is to be retrieved
 *   handleName  name of the handle in the object
 *   fieldId     if non-null, contains the field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldId     if non-null, will contain field ID of the handle on output.
 */
void *getHandle(JNIEnv *env,
		jobject obj,
		const char *handleName,
		jfieldID *fieldId)
{
    jclass objClass;
    jfieldID handleFid;

    /* Retrieve the field ID of the handle */
    if (fieldId == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	handleFid = (*env)->GetFieldID(env, objClass, handleName, "J");
    }
    else if (*fieldId == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	handleFid = *fieldId =
	    (*env)->GetFieldID(env, objClass, handleName, "J");
    }
    else {
	handleFid = *fieldId;
    }

    return (void*) (*env)->GetLongField(env, obj, handleFid);
}




/*
 * Convenience function to set a handle in an object.
 *
 * Input:
 *   env         Java VM environment
 *   obj         Java object for which handle is to be retrieved
 *   handleName  name of the handle in the object
 *   fieldId     if non-null, contains the field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldId     if non-null, will contain field ID of the handle on output.
 *
 * Return:
 *   non-zero    if successful
 *   zero        if failure
 */
int setHandle(JNIEnv *env,
	      jobject obj,
	      const char *handleName,
	      void *handle,
	      jfieldID *fieldId)
{
    jclass objClass;
    jfieldID handleFid;

    /* Retrieve the field ID of the handle */
    if (fieldId == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	handleFid = (*env)->GetFieldID(env, objClass, handleName, "J");
    }
    else if (fieldId == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	handleFid = *fieldId =
	    (*env)->GetFieldID(env, objClass, handleName, "J");
    }
    else {
	handleFid = *fieldId;
    }
    if (handleFid == 0) {
	return 0;
    }

    (*env)->SetLongField(env, obj, handleFid, (jlong) handle);

    return 1;
}





/*
 * Retrieve the int value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   iRect      to be initilised by values in jRect.
 *   fieldID    if non-null, will contain the field ID.
 *   value      to contain the retrieved value. Must not be null.
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getIntFieldValue(JNIEnv *env,
		     jobject obj,
		     const char *fieldName,
		     jfieldID *fieldID,
		     jint *value)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = (*env)->GetFieldID(env, objClass, fieldName, "I");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "I");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return 0;
    }
    *value = (*env)->GetIntField(env, obj, objFieldID);
    return 1;
}




/*
 * Store the int value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *   value      to contain the value to be stored.
 *
 * Output:
 *   fieldID    if non-null, will contain the field ID.
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int setIntFieldValue(JNIEnv *env,
                     jobject obj,
                     const char *fieldName,
                     jfieldID *fieldID,
                     jint value)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = (*env)->GetFieldID(env, objClass, fieldName, "I");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "I");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return 0;
    }
    (*env)->SetIntField(env, obj, objFieldID, value);
    return 1;
}




/*
 * Retrieve the byte value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   iRect      to be initilised by values in jRect.
 *   fieldID    if non-null, will contain the field ID.
 *   value      to contain the retrieved value. Must not be null.
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getByteFieldValue(JNIEnv *env,
		      jobject obj,
		      const char *fieldName,
		      jfieldID *fieldID,
		      jbyte *value)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = (*env)->GetFieldID(env, objClass, fieldName, "B");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "B");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return 0;
    }
    *value = (*env)->GetByteField(env, obj, objFieldID);
    return 1;
}




/*
 * Retrieve the short value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   iRect      to be initilised by values in jRect.
 *   fieldID    if non-null, will contain the field ID.
 *   value      to contain the retrieved value. Must not be null.
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getShortFieldValue(JNIEnv *env,
		       jobject obj,
		       const char *fieldName,
		       jfieldID *fieldID,
		       jshort *value)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = (*env)->GetFieldID(env, objClass, fieldName, "S");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return 0;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "S");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return 0;
    }
    *value = (*env)->GetShortField(env, obj, objFieldID);
    return 1;
}




/*
 * Retrieve the string value of the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldID    if non-null, will contain the field ID.
 *
 * Return:
 *   The string value requested. The caller is responsible for
 *   deallocating this string.
 */
char* getStringFieldValue(JNIEnv *env,
                          jobject obj,
                          const char *fieldName,
                          jfieldID *fieldID)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;
    jobject stringObj = 0;
    char *stringVal = NULL;
    char *stringCpy = NULL;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID =
            (*env)->GetFieldID(env, objClass, fieldName, "Ljava/lang/String;");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "Ljava/lang/String;");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return NULL;
    }
    stringObj = (*env)->GetObjectField(env, obj, objFieldID);
    if (stringObj == NULL) {
        return NULL;
    }
    stringVal = (char *) (*env)->GetStringUTFChars(env, stringObj, 0);
    stringCpy = (char *) AcquireString(stringVal);
    (*env)->ReleaseStringUTFChars(env, stringObj, stringVal);
    return stringCpy;
}



/*
 * Retrieve the byte array from the specified field.
 *
 * Input:
 *   env        Java VM environment.
 *   obj        Java object for which the value is to be retrieved.
 *   fieldName  name of the field to be retrieved.
 *   fieldID    if non-null, points to field ID. 0 to request retrieval.
 *
 * Output:
 *   fieldID    if non-null, will contain the field ID.
 *   size       the size of the array is returned here. Must not be NULL.
 *
 * Return:
 *   The byte array requested. The caller is responsible for
 *   deallocating this byte array.
 */
unsigned char* getByteArrayFieldValue(JNIEnv *env,
                                      jobject obj,
                                      const char *fieldName,
                                      jfieldID *fieldID,
                                      int *size)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;
    jobject byteArrayObj = 0;
    unsigned char *byteArray = NULL;
    char *byteArrayCpy = NULL;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID =
            (*env)->GetFieldID(env, objClass, fieldName, "[B");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "[B");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return NULL;
    }

    /* Get the array object */
    byteArrayObj = (*env)->GetObjectField(env, obj, objFieldID);
    if (byteArrayObj == NULL) {
        return NULL;
    }

    /* Determine the size of the array */
    *size = (*env)->GetArrayLength(env, byteArrayObj);
    if (*size == 0) {
        return NULL;
    }

    /* Get and copy the array elements */
    byteArray = (jbyte *) (*env)->GetByteArrayElements(env, byteArrayObj, 0);
    byteArrayCpy = (unsigned char *) AcquireMemory(*size);
    if (byteArray == NULL) {
        return NULL;
    }
    memcpy(byteArrayCpy, byteArray, *size);
    (*env)->ReleaseByteArrayElements(env, byteArrayObj, byteArray, JNI_ABORT);

    return byteArrayCpy;
}



/*
 * From a java.awt.Rectangle object, construct a ImageMagick
 * RectangleInfo, as passed in from the parameter.
 *
 * Input:
 *   env        Java VM environment
 *   jRect      an instance of java.awt.Rectangle
 *
 * Output:
 *   iRect      to be initilised by values in jRect
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getRectangle(JNIEnv *env, jobject jRect, RectangleInfo *iRect)
{
	jint width, height, x, y;
    int retVal =
		getIntFieldValue(env, jRect, "width", NULL, (jint *) &width) &&
		getIntFieldValue(env, jRect, "height", NULL, (jint *) &height) &&
		getIntFieldValue(env, jRect, "x", NULL, (jint *) &x) &&
		getIntFieldValue(env, jRect, "y", NULL, (jint *) &y);
	if (retVal) {
		iRect->width = width;
		iRect->height = height;
		iRect->x = x;
		iRect->y = y;
	}
	return retVal;
}



/*
 * From a magick.PixelPacket object, construct a ImageMagick
 * PixelPacket, as passed in from the parameter.
 *
 * Input:
 *   env           Java VM environment
 *   jPixelPacket  an instance of magick.PixelPacket
 *
 * Output:
 *   iPixelPacket  to be initilised by values in jPixelPacket
 *
 * Return:
 *   non-zero   if successful
 *   zero       if failed
 */
int getPixelPacket(JNIEnv *env,
		   jobject jPixelPacket,
		   PixelPacket *iPixelPacket)
{
  jint red, green, blue, opacity;
  int successful =
	getIntFieldValue(env, jPixelPacket, "red", NULL,
                         &red) &&
	getIntFieldValue(env, jPixelPacket, "green", NULL,
                         &green) &&
        getIntFieldValue(env, jPixelPacket, "blue", NULL,
                         &blue) &&
	getIntFieldValue(env, jPixelPacket, "opacity", NULL,
                         &opacity);
  if (!successful) {
      return successful;
  }
  iPixelPacket->red = (Quantum) red;
  iPixelPacket->green = (Quantum) green;
  iPixelPacket->blue = (Quantum) blue;
  iPixelPacket->opacity = (Quantum) opacity;
  return successful;
}







/*
 * Construct a new Java magick.MagickImage object and set the
 * handle.
 *
 * Input:
 *   env     Java VM environment
 *   image   ImageMagick image handle
 *
 * Return:
 *   A new instance of magick.MagickImage object.
 *
 */
jobject newImageObject(JNIEnv *env, Image* image)
{
    jclass magickImageClass = 0;
    jmethodID consMethodID = 0;
    jobject newObj;

    magickImageClass = (*env)->FindClass(env, "magick/MagickImage");
    if (magickImageClass == 0) {
	return NULL;
    }

    consMethodID = (*env)->GetMethodID(env, magickImageClass,
				       "<init>", "()V");
    if (consMethodID == 0) {
	return NULL;
    }

    newObj = (*env)->NewObject(env, magickImageClass, consMethodID);
    if (newObj == NULL) {
	return NULL;
    }

    if (!setHandle(env, newObj, "magickImageHandle", (void*) image, NULL)) {
#ifdef DIAGNOSTIC
	fprintf(stderr, "newImageObject: Unable to set handle\n");
#endif
	return NULL;
    }

    return newObj;
}




/*
 * Set a attribute in a generic handle to string.
 *
 * Input:
 *   env        Java VM environment
 *   attribVar  points to a C string so as to set the value
 *   jstr       Java string for which to set the attrib
 *
 * Output:
 *   attribVar  points to a new C string with content from jstr
 */
void setHandleAttribute(JNIEnv *env, char **attribVar, jstring jstr)
{
    const char *cstr = NULL;
    if (*attribVar != NULL) {
//	RelinquishMagickMemory((void**)attribVar);
    }
    cstr = (*env)->GetStringUTFChars(env, jstr, 0);
    *attribVar = (char *) AcquireString(cstr);
    (*env)->ReleaseStringUTFChars(env, jstr, cstr);
}



/*
 * Given the C ProfileInfo structure and the Java ProfileInfo object,
 * acquire the contents of the Java ProfileInfo object and store it in
 * the C ProfileInfo structure.
 *
 * Input:
 *   env            JNI environment
 *   profileObj     Java ProfileInfo object for which field values are to be
 *                  obtain to store into the C ProfileInfo structure
 * Output:
 *   profileInfo    C ProfileINfo structure to store field values
 */
void setProfileInfo(JNIEnv *env, ProfileInfo *profileInfo, jobject profileObj)
{
    char *name;
    unsigned char *info;
    int infoSize = 0;

    if (profileObj == NULL) {
        throwMagickException(env, "ProfileInfo cannot be null");
        return;
    }

    name = getStringFieldValue(env, profileObj, "name", NULL);
    info = getByteArrayFieldValue(env, profileObj, "info", NULL, &infoSize);
    if (profileInfo->name != NULL) {
       // RelinquishMagickMemory((void**) &profileInfo->name);
    }
    profileInfo->name = name;
    if (profileInfo->info != NULL) {
       // RelinquishMagickMemory((void**) &profileInfo->info);
    }
    profileInfo->info = info;
    profileInfo->length = infoSize;
}



/*
 * Given the C ProfileInfo structure, construct a Java ProfileInfo
 * object with values obtained from the C ProfileInfo structure.
 * Input:
 *   env           JNI environment
 *   profileInfo   C ProfileInfo structure
 * Return:
 *   Java ProfileInfo object
 */
jobject getProfileInfo(JNIEnv *env, ProfileInfo *profileInfo)
{
    jclass profileInfoClass;
    jmethodID consMethodID;
    jobject profileObject;
    jstring name;
    jbyteArray byteArray;
    unsigned char *byteElements;

    /* Get the ProfileInfo class ID */
    profileInfoClass = (*env)->FindClass(env, "magick/ProfileInfo");
    if (profileInfoClass == 0) {
        throwMagickException(env, "Unable to locate class "
                                   "magick.ProfileInfo");
        return NULL;
    }

    /* Get the constructor method ID */
    consMethodID = (*env)->GetMethodID(env, profileInfoClass,
                                       "<init>", "(Ljava/lang/String;[B)V");
    if (consMethodID == 0) {
        throwMagickException(env, "Unable to locate constructor "
                                  "ProfileInfo(String, byte[])");
        return NULL;
    }

    /* Construct the name */
    if (profileInfo->name != NULL) {
        name = (*env)->NewStringUTF(env, profileInfo->name);
        if (name == NULL) {
            throwMagickException(env, "Unable to allocate Java String "
                                      "for profile name");
            return NULL;
        }
    }
    else {
        name = NULL;
    }

    /* Construct the byte array */
    if (profileInfo->length > 0) {
        byteArray = (*env)->NewByteArray(env, profileInfo->length);
        if (byteArray == NULL) {
            throwMagickException(env, "Unable to allocate byte array "
                                      "for profile info");
            return NULL;
        }
        byteElements =
            (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);
        if (byteElements == NULL) {
            throwMagickException(env, "Unable to obtain byte array elements "
                                      "for profile info");
            return NULL;
        }
        memcpy(byteElements,
               profileInfo->info,
               profileInfo->length);
        (*env)->ReleaseByteArrayElements(env, byteArray, byteElements, 0);
    }
    else {
        byteArray = NULL;
    }

    /* Construct the ProfileInfo object */
    profileObject = (*env)->NewObject(env, profileInfoClass, consMethodID,
                                      name, byteArray);
    if (profileObject == NULL) {
        throwMagickException(env, "Unable to construct ProfileInfo object");
        return NULL;
    }

    return profileObject;
}
