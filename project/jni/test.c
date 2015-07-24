#include <stdio.h>
#include <jni.h>
#include <malloc.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/inotify.h>
#include <fcntl.h>
#include <android/log.h>

#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

int uninstall(JNIEnv *env, jobject obj, jstring packageDir, jint sdkVersion);

static JNINativeMethod gMethods[] = {
    {"uninstall", "(Ljava/lang/String;I)I", (void*)uninstall},//绑定
};


int uninstall(JNIEnv *env, jobject obj, jstring packageDir, jint sdkVersion){
	jboolean b = JNI_FALSE;
	char *pd = (*env)->GetStringUTFChars(env, packageDir, &b);
	pid_t pid = fork();

	if(pid < 0){
		LOGD("create process fail");
	}else if(pid == 0){
		LOGD("create process success, current in child id=%d", getpid());
		int fd = inotify_init();
		if(fd < 0){
			LOGD("inotify init fail");
			exit(1);
		}

		int wd = inotify_add_watch(fd, pd, IN_DELETE);
		if(wd < 0){
			LOGD("add inotify add fail");
			exit(1);
		}

		void *p_buf = malloc(sizeof(struct inotify_event));
		if(p_buf == NULL){
			LOGD("malloc fail");
			exit(1);
		}

		LOGD("start observer");
		ssize_t readBytes = read(fd, p_buf, sizeof(struct inotify_event));
		free(p_buf);
		inotify_rm_watch(fd, IN_DELETE);

		LOGD("app uninstall, current sdk:%d", sdkVersion);
		if(sdkVersion >= 17){
			execlp("am", "am", "start", "--user", "0", "-a", "android.intent.action.VIEW", "-d", "http://www.baidu.com", (char*)NULL);
		}else{
			execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d", "http://www.baidu.com", (char*)NULL);
		}
//		while(JNI_TRUE){
//			FILE *file = fopen(pd, "rt");
//			if(file == NULL){
//				LOGD("app uninstall, current sdkversion=%d", sdkVersion);
//				if(sdkVersion >= 17){
//					execlp("am", "am", "start", "--user", "0", "-a", "android.intent.action.VIEW", "-d", "http://www.baidu.com", (char*)NULL);
//				}else{
//					execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d", "http://www.baidu.com", (char*)NULL);
//				}
//			}else{
//				LOGD("everything ok in pid:%d", getpid());
//			}
//			sleep(1);
//		}
	}else{
		LOGD("create process success, current in parent id=%d", getpid());
		return pid;
	}


}

static int registerNativeMethods(JNIEnv* env
        , const char* className
        , JNINativeMethod* gMethods, int numMethods) {
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

static int registerNatives(JNIEnv* env) {
    const char* kClassName = "com/example/uninstallhandler/NativeHandler";//指定要注册的类
    return registerNativeMethods(env, kClassName, gMethods,
            sizeof(gMethods) / sizeof(gMethods[0]));
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);

    if (!registerNatives(env)) {//注册
        return -1;
    }
    //成功
    result = JNI_VERSION_1_4;

    return result;
}




























