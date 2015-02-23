# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

# shared quizzer static lib
include $(CLEAR_VARS)

LOCAL_MODULE    := minipals
LOCAL_SRC_FILES := MiniPALs.Shared/GpsPosition.cpp \
MiniPALs.Shared/SoundEffectPlayer.cpp \
MiniPALs.Shared/TTSPlayer.cpp \
MiniPALs.Android/GpsPosition_Android.cpp \
MiniPALs.Android/SoundEffectPlayer_Android.cpp \
MiniPALs.Android/TTSPlayer_Android.cpp
#LOCAL_SRC_FILES := ../../MiniPALs.Shared/GpsPosition.cpp \
../../MiniPALs.Shared/SoundEffectPlayer.cpp \
../../MiniPALs.Shared/TTSPlayer.cpp \
../../MiniPALs.Android/GpsPosition_Android.cpp \
../../MiniPALs.Android/SoundEffectPlayer_Android.cpp \
../../MiniPALs.Android/TTSPlayer_Android.cpp

#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../MiniPALs.Shared/
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../MiniPALs.Android/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/MiniPALs.Shared/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/MiniPALs.Android/

#LOCAL_STATIC_LIBRARIES := cpufeatures android_native_app_glue ndk_helper
#LOCAL_STATIC_LIBRARIES := cpufeatures android_native_app_glue ndk_helper

include $(BUILD_STATIC_LIBRARY)

################

# shared quizzer static lib
include $(CLEAR_VARS)

LOCAL_MODULE    := shared
LOCAL_SRC_FILES := SharedCode.Shared/CalculateDistance.cpp \
SharedCode.Shared/CityLocation.cpp \
SharedCode.Shared/QuizQuestion.cpp \
SharedCode.Shared/Quizzer.cpp \
SharedCode.Shared/SharedCode.cpp
#LOCAL_SRC_FILES := ../../SharedCode.Shared/CalculateDistance.cpp \
../../SharedCode.Shared/CityLocation.cpp \
../../SharedCode.Shared/QuizQuestion.cpp \
../../SharedCode.Shared/Quizzer.cpp \
../../SharedCode.Shared/SharedCode.cpp

#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../SharedCode.Shared/
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../MiniPALs.Shared/
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../MiniPALs.Android/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/SharedCode.Shared/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/MiniPALs.Shared/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/MiniPALs.Android/

LOCAL_STATIC_LIBRARIES := minipals
#LOCAL_STATIC_LIBRARIES := cpufeatures android_native_app_glue ndk_helper minipals

include $(BUILD_STATIC_LIBRARY)

################

# quizzer jni shared lib
include $(CLEAR_VARS)

LOCAL_MODULE    := quizzer-jni
LOCAL_SRC_FILES := quizzer-jni.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/SharedCode.Shared/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/MiniPALs.Shared/
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../SharedCode.Shared/
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../MiniPALs.Shared/

# for native audio
LOCAL_LDLIBS    += -lOpenSLES
# for logging
LOCAL_LDLIBS    += -llog
# for native asset manager
LOCAL_LDLIBS    += -landroid

LOCAL_STATIC_LIBRARIES := shared minipals
#LOCAL_STATIC_LIBRARIES := shared minipals
#cpufeatures android_native_app_glue ndk_helper

include $(BUILD_SHARED_LIBRARY)

NDK_MODULE_PATH := $(LOCAL_PATH) 

#$(call import-add-path,$(LOCAL_PATH))
#$(call import-module,minipals)
#$(call import-module,MiniPals.Shared/minipals)
#$(call import-module,android/ndk_helper)
#$(call import-module,android/native_app_glue)
#$(call import-module,android/cpufeatures)
