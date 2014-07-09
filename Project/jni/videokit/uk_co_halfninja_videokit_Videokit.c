

#include <android/log.h>
#include "logjam.h"
#include "uk_co_halfninja_videokit_Videokit.h"

#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv);
extern int received_sigterm;

JavaVM *sVm = NULL;

#define LOG_ERROR(message) __android_log_write(ANDROID_LOG_ERROR, "VideoKit", message)
#define LOG_INFO(message) __android_log_write(ANDROID_LOG_INFO, "VideoKit", message)

JNIEXPORT void JNICALL Java_uk_co_halfninja_videokit_Videokit_run(JNIEnv *env, jobject obj, jobjectArray args)
{
	int i = 0;
	int argc = 0;
	char **argv = NULL;
	jstring *strr = NULL;

	char *tmp = NULL;

	if (args != NULL) {
		argc = (*env)->GetArrayLength(env, args);
		argv = (char **) malloc(sizeof(char *) * argc);
		strr = (jstring *) malloc(sizeof(jstring) * argc);

		for(i=0;i<argc;i++)
		{
			strr[i] = (jstring)(*env)->GetObjectArrayElement(env, args, i);
			tmp = (char *)(*env)->GetStringUTFChars(env, strr[i], 0);
			argv[i] = (char *)malloc(sizeof(char) * strlen(tmp));
			strcpy(argv[i], tmp);
			(*env)->ReleaseStringUTFChars(env, strr[i], tmp);
		}
	}	

	main(argc, argv);
	
	for(i=0;i<argc;i++)
	{
		//(*env)->ReleaseStringUTFChars(env, strr[i], argv[i]);
		free(argv[i]);
	}
	free(argv);
	free(strr);

}

JNIEXPORT void JNICALL Java_uk_co_halfninja_videokit_Videokit_stop(JNIEnv *env, jobject obj)
{
	received_sigterm++;
}
