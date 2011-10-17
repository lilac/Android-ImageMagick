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

LOCAL_MODULE := zlib

LOCAL_SRC_FILES := \
	../zlib-1.2.3/adler32.c \
	../zlib-1.2.3/compress.c \
	../zlib-1.2.3/crc32.c \
	../zlib-1.2.3/deflate.c \
	../zlib-1.2.3/gzio.c \
	../zlib-1.2.3/infback.c \
	../zlib-1.2.3/inffast.c \
	../zlib-1.2.3/inflate.c \
	../zlib-1.2.3/inftrees.c \
	../zlib-1.2.3/trees.c \
	../zlib-1.2.3/uncompr.c \
	../zlib-1.2.3/zutil.c

LOCAL_C_INCLUDES := apps/zlib/zlib-1.2.3

LOCAL_CFLAGS := -DNDEBUG

include $(BUILD_STATIC_LIBRARY)
