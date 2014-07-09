LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := avdevice
LOCAL_SRC_FILES := ffmpeg/libavdevice/libavdevice.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avformat
LOCAL_SRC_FILES := ffmpeg/libavformat/libavformat.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avfilter
LOCAL_SRC_FILES := ffmpeg/libavfilter/libavfilter.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avcodec
LOCAL_SRC_FILES := ffmpeg/libavcodec/libavcodec.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swscale
LOCAL_SRC_FILES := ffmpeg/libswscale/libswscale.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avutil
LOCAL_SRC_FILES := ffmpeg/libavutil/libavutil.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swresample
LOCAL_SRC_FILES := ffmpeg/libswresample/libswresample.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := postproc
LOCAL_SRC_FILES := ffmpeg/libpostproc/libpostproc.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := x264
LOCAL_SRC_FILES := x264/libx264.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE  := videokit
# These need to be in the right order
FFMPEG_LIBS := $(addprefix ffmpeg/, \
 libavdevice/libavdevice.a \
 libavformat/libavformat.a \
 libavfilter/libavfilter.a \
 libavcodec/libavcodec.a \
 libswscale/libswscale.a \
 libavutil/libavutil.a \
 libswresample/libswresample.a \
 libpostproc/libpostproc.a )
# ffmpeg uses its own deprecated functions liberally, so turn off that annoying noise
LOCAL_CFLAGS += -g -Iffmpeg -Ivideokit -Wno-deprecated-declarations 
LOCAL_LDLIBS += -llog -lz
LOCAL_STATIC_LIBRARIES := avdevice avformat avfilter avcodec swscale avutil swresample postproc x264
LOCAL_SRC_FILES :=  videokit/cmdutils.c videokit/ffmpeg.c ffmpeg/ffmpeg_opt.c ffmpeg/ffmpeg_filter.c videokit/uk_co_halfninja_videokit_Videokit.c
include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := videokitinvoke
LOCAL_SRC_FILES := videokitinvoke/videokitinvoke.c
LOCAL_LDLIBS    := -ldl -llog
include $(BUILD_SHARED_LIBRARY)




