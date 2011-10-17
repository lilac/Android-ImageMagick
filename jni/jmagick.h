#ifndef __JMAGICK__
#define __JMAGICK__

#include <magick/image.h>

#if MagickLibInterface >= 5
#define DestroyImages DestroyImageList
#define AllocateImage AcquireImage
#endif

/*
 * Convenience function to help throw an MagickException.
 */
void throwMagickException(JNIEnv *env, const char *mesg);


/*
 * Convenience function to help throw an MagickApiException.
 *
 * Input:
 *   mesg       JMagick message
 *   exception  points to a ImageMagick ExceptionInfo structure
 */
void throwMagickApiException(JNIEnv *env,
			     const char *mesg,
			     const ExceptionInfo *exception);

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
		jfieldID *fieldId);


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
	      jfieldID *fieldId);


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
		     jint *value);

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
                     jint value);

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
int getRectangle(JNIEnv *env, jobject jRect, RectangleInfo *iRect);


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
		   PixelPacket *iPixelPacket);

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
jobject newImageObject(JNIEnv *env, Image* image);



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
void setHandleAttribute(JNIEnv *env, char **attribVar, jstring jstr);




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
void setProfileInfo(JNIEnv *env,
                    ProfileInfo *profileInfo,
                    jobject profileObj);



/*
 * Given the C ProfileInfo structure, construct a Java ProfileInfo
 * object with values obtained from the C ProfileInfo structure.
 * Input:
 *   env           JNI environment
 *   profileInfo   C ProfileInfo structure
 * Return:
 *   Java ProfileInfo object
 */
jobject getProfileInfo(JNIEnv *env, ProfileInfo *profileInfo);



/*
 * Convenience macro to set an attribute in the object handle.
 */
#define setMethod(funcName, fieldName, handleName, handleType, fieldType)     \
JNIEXPORT void JNICALL funcName                                               \
    (JNIEnv *env, jobject self, fieldType value)                              \
{                                                                             \
    handleType *info = NULL;                                                  \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return;                                                               \
    }                                                                         \
                                                                              \
    info->fieldName = value;                                                  \
}



/*
 * Convenience macro to get an attribute of an object handle.
 */
#define getMethod(funcName, fieldName, handleName, handleType, fieldType)     \
JNIEXPORT fieldType JNICALL funcName                                          \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    handleType *info = NULL;                                                  \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return (fieldType) 0;                                                 \
    }                                                                         \
                                                                              \
    return info->fieldName;                                                   \
}


/*
 * Convenience macro to set an integer attribute in the object handle.
 */
#define setIntMethod(funcName, fieldName, handleName, handleType)             \
        setMethod(funcName, fieldName, handleName, handleType, jint)


/*
 * Convenience macro to get an integer attribute of an object handle.
 */
#define getIntMethod(funcName, fieldName, handleName, handleType)             \
        getMethod(funcName, fieldName, handleName, handleType, jint)


/*
 * Convenience macro to set an boolean attribute in the object handle.
 */
#define setBoolMethod(funcName, fieldName, handleName, handleType)            \
        setMethod(funcName, fieldName, handleName, handleType, jboolean)


/*
 * Convenience macro to get an boolean attribute of an object handle.
 */
#define getBoolMethod(funcName, fieldName, handleName, handleType)            \
        getMethod(funcName, fieldName, handleName, handleType, jboolean)


/*
 * Convenience macro to set an short attribute in the object handle.
 */
#define setShortMethod(funcName, fieldName, handleName, handleType)           \
        setMethod(funcName, fieldName, handleName, handleType, jshort)


/*
 * Convenience macro to get an byte attribute of an object handle.
 */
#define getByteMethod(funcName, fieldName, handleName, handleType)            \
        getMethod(funcName, fieldName, handleName, handleType, jbyte)


/*
 * Convenience macro to set an byte attribute in the object handle.
 */
#define setByteMethod(funcName, fieldName, handleName, handleType)            \
        setMethod(funcName, fieldName, handleName, handleType, jbyte)


/*
 * Convenience macro to get a double attribute of an object handle.
 */
#define getDoubleMethod(funcName, fieldName, handleName, handleType)          \
        getMethod(funcName, fieldName, handleName, handleType, jdouble)


/*
 * Convenience macro to set an double attribute in the object handle.
 */
#define setDoubleMethod(funcName, fieldName, handleName, handleType)          \
        setMethod(funcName, fieldName, handleName, handleType, jdouble)


/*
 * Convenience macro to set a string attribute in the object handle.
 */
#define setStringMethod(funcName, fieldName, handleName, handleType)          \
JNIEXPORT void JNICALL funcName                                               \
    (JNIEnv *env, jobject self, jstring value)                                \
{                                                                             \
    handleType *info = NULL;                                                  \
    const char *cstr = NULL;                                                  \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return;                                                               \
    }                                                                         \
                                                                              \
    if (info->fieldName != NULL) {                                            \
	RelinquishMagickMemory((void**) &info->fieldName);                            \
	info->fieldName = NULL;                                               \
    }                                                                         \
                                                                              \
    cstr = (*env)->GetStringUTFChars(env, value, 0);                          \
    if (cstr == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve Java string chars");    \
	return;                                                               \
    }                                                                         \
    info->fieldName = (char *) AcquireString(cstr);                           \
    if (info->fieldName == NULL) {                                            \
	throwMagickException(env, "Unable to allocate memory");               \
    }                                                                         \
    (*env)->ReleaseStringUTFChars(env, value, cstr);                          \
}


/*
 * Convenience macro to get a string attribute in the object handle.
 */
#define getStringMethod(funcName, fieldName, handleName, handleType)          \
JNIEXPORT jstring JNICALL funcName                                            \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    handleType *info = NULL;                                                  \
    jstring jstr = NULL;                                                      \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    if (info->fieldName == NULL) {                                            \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    jstr = (*env)->NewStringUTF(env, info->fieldName);                        \
    if (jstr == NULL) {                                                       \
	throwMagickException(env, "Unable to construct new string");          \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    return jstr;                                                              \
}


/*
 * Convenience macro to set a PixelPacket attribute in the object handle.
 */
#define setPixelPacketMethod(funcName, fieldName, handleName, handleType)     \
JNIEXPORT void JNICALL funcName                                               \
    (JNIEnv *env, jobject self, jobject jPixelPacket)                         \
{                                                                             \
    handleType *info = NULL;                                                  \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return;                                                               \
    }                                                                         \
                                                                              \
    if (!getPixelPacket(env, jPixelPacket, &info->fieldName)) {               \
	throwMagickException(env, "Unable to set PixelPacket");               \
	return;                                                               \
    }                                                                         \
}



/*
 * Convenience macro to get a PixelPacket attribute in the object handle.
 */
#define getPixelPacketMethod(funcName, fieldName, handleName, handleType)     \
JNIEXPORT jobject JNICALL funcName                                            \
    (JNIEnv *env, jobject self)                                               \
{                                                                             \
    handleType *info = NULL;                                                  \
    jobject jPixelPacket = NULL;                                              \
    jclass pixelPacketClass;                                                  \
    jmethodID consMethodID;                                                   \
                                                                              \
    info = (handleType *) getHandle(env, self, handleName, NULL);             \
    if (info == NULL) {                                                       \
	throwMagickException(env, "Unable to retrieve handle");               \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");          \
    if (pixelPacketClass == 0) {                                              \
	throwMagickException(env,                                             \
			     "Unable to locate class magick.PixelPacket");    \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,                 \
				       "<init>", "(IIII)V");                  \
    if (consMethodID == 0) {                                                  \
	throwMagickException(env, "Unable to construct magick.PixelPacket");  \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    jPixelPacket = (*env)->NewObject(env, pixelPacketClass, consMethodID,     \
		                     (jint) info->fieldName.red,              \
		                     (jint) info->fieldName.green,            \
		                     (jint) info->fieldName.blue,             \
		                     (jint) info->fieldName.opacity);         \
    if (jPixelPacket == NULL) {                                               \
	throwMagickException(env, "Unable to construct magick.PixelPacket");  \
	return NULL;                                                          \
    }                                                                         \
                                                                              \
    return jPixelPacket;                                                      \
}




#endif /* __JMAGICK__ */
