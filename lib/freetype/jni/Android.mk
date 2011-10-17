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

LOCAL_MODULE := freetype

LOCAL_SRC_FILES := \
	../freetype-2.3.11/src/autofit/autofit.c \
	../freetype-2.3.11/src/base/ftbase.c \
	../freetype-2.3.11/src/base/ftbbox.c \
	../freetype-2.3.11/src/base/ftbitmap.c \
	../freetype-2.3.11/src/base/ftdebug.c \
	../freetype-2.3.11/src/base/ftfstype.c \
	../freetype-2.3.11/src/base/ftgasp.c \
	../freetype-2.3.11/src/base/ftglyph.c \
	../freetype-2.3.11/src/base/ftinit.c \
	../freetype-2.3.11/src/base/ftmm.c \
	../freetype-2.3.11/src/base/ftpfr.c \
	../freetype-2.3.11/src/base/ftstroke.c \
	../freetype-2.3.11/src/base/ftsynth.c \
	../freetype-2.3.11/src/base/ftsystem.c \
	../freetype-2.3.11/src/base/fttype1.c \
	../freetype-2.3.11/src/base/ftwinfnt.c \
	../freetype-2.3.11/src/bdf/bdf.c \
	../freetype-2.3.11/src/cache/ftcache.c \
	../freetype-2.3.11/src/cff/cff.c \
	../freetype-2.3.11/src/cid/type1cid.c \
	../freetype-2.3.11/src/gzip/ftgzip.c \
	../freetype-2.3.11/src/lzw/ftlzw.c \
	../freetype-2.3.11/src/pcf/pcf.c \
	../freetype-2.3.11/src/pfr/pfr.c \
	../freetype-2.3.11/src/psaux/psaux.c \
	../freetype-2.3.11/src/pshinter/pshinter.c \
	../freetype-2.3.11/src/psnames/psmodule.c \
	../freetype-2.3.11/src/raster/raster.c \
	../freetype-2.3.11/src/sfnt/sfnt.c \
	../freetype-2.3.11/src/smooth/smooth.c \
	../freetype-2.3.11/src/truetype/truetype.c \
	../freetype-2.3.11/src/type1/type1.c \
	../freetype-2.3.11/src/type42/type42.c \
	../freetype-2.3.11/src/winfonts/winfnt.c

LOCAL_C_INCLUDES := apps/freetype/freetype-2.3.11/include

LOCAL_CFLAGS := -DNDEBUG -DFT2_BUILD_LIBRARY

include $(BUILD_STATIC_LIBRARY)
