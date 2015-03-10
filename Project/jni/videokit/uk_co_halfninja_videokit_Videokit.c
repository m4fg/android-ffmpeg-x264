

#include <android/log.h>
#include "logjam.h"
#include "uk_co_halfninja_videokit_Videokit.h"

#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

int main(int argc, char **argv);
extern int received_sigterm;

int g_argc;
char** g_argv;
JNIEnv* g_env;
jstring g_argstring;
const char* g_jstr;

#define LOG_ERROR(message) __android_log_write(ANDROID_LOG_ERROR, "VideoKit", message)
#define LOG_INFO(message) __android_log_write(ANDROID_LOG_INFO, "VideoKit", message)

int split (const char *str, char c, char ***arr)
{
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }
    *t = '\0';

    return count;
}

static void sigsegvSignalHandler(int sig)
{
    int i;
    for(i=0;i<g_argc;i++)
    {
        free(g_argv[i]);
    }
    free(g_argv);
    (*g_env)->ReleaseStringUTFChars(g_env, g_argstring, g_jstr);
}

JNIEXPORT void JNICALL Java_uk_co_halfninja_videokit_Videokit_run(JNIEnv *env, jobject obj, jstring argstring)
{
	int i = 0;
	int argc = 0;
	char **argv = NULL;

	const char *jstr;
	jstr = (*env)->GetStringUTFChars(env, argstring, 0);

	argc = split(jstr, '\n', &argv);
    signal(SIGSEGV , &sigsegvSignalHandler);
    g_argc = argc;
    g_argv = argv;
    g_env = env;
    g_argstring = argstring;
    g_jstr = jstr;

	main(argc, argv);
    
    sigsegvSignalHandler(0);

    /*
	for(i=0;i<argc;i++)
	{
		free(argv[i]);
	}
	free(argv);
	(*env)->ReleaseStringUTFChars(env, argstring, jstr);
    */
	/*
	jstring *strr = NULL;

	if (args != NULL) {
		argc = (*env)->GetArrayLength(env, args);
		argv = (char **) malloc(sizeof(char *) * argc);
		strr = (jstring *) malloc(sizeof(jstring) * argc);

		for(i=0;i<argc;i++)
		{
			strr[i] = (jstring)(*env)->GetObjectArrayElement(env, args, i);
			argv[i] = (char *)(*env)->GetStringUTFChars(env, strr[i], 0);
		}
	}	

	main(argc, argv);
	
	for(i=0;i<argc;i++)
	{
		(*env)->ReleaseStringUTFChars(env, strr[i], argv[i]);
	}
	free(argv);
	free(strr);
	*/
}

JNIEXPORT void JNICALL Java_uk_co_halfninja_videokit_Videokit_stop(JNIEnv *env, jobject obj)
{
	received_sigterm++;
}
