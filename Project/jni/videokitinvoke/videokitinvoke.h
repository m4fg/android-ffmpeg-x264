#ifndef FFMPEG_INVOKE_H_INCLUDED
#define FFMPEG_INVOKE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

// Use to safely invoke ffmpeg multiple times from the same Activity
JNIEXPORT void JNICALL Java_uk_co_halfninja_videokit_VideokitInvoke_run(JNIEnv*, jobject, jstring, jobjectArray);

#ifdef __cplusplus
}
#endif

#endif // FFMPEG_INVOKE_H_INCLUDED
