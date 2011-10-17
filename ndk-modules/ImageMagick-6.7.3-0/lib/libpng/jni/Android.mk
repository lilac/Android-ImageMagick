#
#   Copyright (c) 2007-2010 Takashi Kitao
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in
#   all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#   THE SOFTWARE.
#


LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libpng

LOCAL_SRC_FILES := \
	../libpng-1.2.40/png.c \
	../libpng-1.2.40/pngerror.c \
	../libpng-1.2.40/pngget.c \
	../libpng-1.2.40/pngmem.c \
	../libpng-1.2.40/pngpread.c \
	../libpng-1.2.40/pngread.c \
	../libpng-1.2.40/pngrio.c \
	../libpng-1.2.40/pngrtran.c \
	../libpng-1.2.40/pngrutil.c \
	../libpng-1.2.40/pngset.c \
	../libpng-1.2.40/pngtrans.c \
	../libpng-1.2.40/pngwio.c \
	../libpng-1.2.40/pngwrite.c \
	../libpng-1.2.40/pngwtran.c \
	../libpng-1.2.40/pngwutil.c

LOCAL_C_INCLUDES := apps/libpng/libpng-1.2.40 apps/zlib/zlib-1.2.3

LOCAL_CFLAGS := -DNDEBUG

include $(BUILD_STATIC_LIBRARY)
