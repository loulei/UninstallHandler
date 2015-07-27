LOCAL_PATH := $(call my-dir)  
  
include $(CLEAR_VARS)  
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_MODULE    := sock  
LOCAL_SRC_FILES := sock.c  

#LOCAL_FORCE_STATIC_EXECUTABLE := true
  
include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_EXECUTABLE)
