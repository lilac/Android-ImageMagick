
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := filters 
LOCAL_SRC_FILES := analyze.c

LOCAL_C_INCLUDES += $(LOCAL_PATH)/.. /opt/local/include /opt/local/include/freetype2 /usr/local/include/ImageMagick
LOCAL_CFLAGS += -DHAVE_CONFIG_H
LOCAL_LDLIBS += -lz
#LOCAL_LDLIBS += -L$(LOCAL_PATH)/../../lib -lfreetype -lpng -ljpeg
#LOCAL_STATIC_LIBRARIES += tiff-static
#LOCAL_SHARED_LIBRARIES += png freetype jpeg

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)
#$(call import-module,jpeg)
#$(call import-module,tiff)
