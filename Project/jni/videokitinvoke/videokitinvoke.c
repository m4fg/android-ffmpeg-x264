#include <stdlib.h>
#include <dlfcn.h>
#include "videokitinvoke.h"

#include "../videokit/logjam.h"

static void* handle;

JNIEXPORT void JNICALL Java_uk_co_halfninja_videokit_VideokitInvoke_run(JNIEnv* env, jobject obj, jstring libffmpeg_path, jstring ffmpeg_args)
{
    const char* path;
    handle = 0;

    void (*Java_uk_co_halfninja_videokit_Videokit_run)(JNIEnv*, jobject, jobjectArray);

    path = (*env)->GetStringUTFChars(env, libffmpeg_path, 0);
    handle = dlopen(path, RTLD_LAZY);
    (*env)->ReleaseStringUTFChars(env, libffmpeg_path, path);
    if(!handle){
        LOGE("dlerror %s", (char *) dlerror());
        return;
    }

    Java_uk_co_halfninja_videokit_Videokit_run = dlsym(handle, "Java_uk_co_halfninja_videokit_Videokit_run");
    if(!Java_uk_co_halfninja_videokit_Videokit_run) {
        LOGE("NO FUNC[%s]\n",dlerror());
    }
    (*Java_uk_co_halfninja_videokit_Videokit_run)(env, obj, ffmpeg_args);

    LOGI("end");
    dlclose(handle);
    handle = 0;
}

JNIEXPORT void JNICALL Java_uk_co_halfninja_videokit_VideokitInvoke_stop(JNIEnv* env, jobject obj)
{
    void (*Java_uk_co_halfninja_videokit_Videokit_stop)(JNIEnv*, jobject);

    if(handle){
        LOGI("STOP!!!!!!!!!");
        Java_uk_co_halfninja_videokit_Videokit_stop = dlsym(handle, "Java_uk_co_halfninja_videokit_Videokit_stop");
        (*Java_uk_co_halfninja_videokit_Videokit_stop)(env, obj);
    }
}
