#pragma once

#include <jni.h>

class Quizzer;

JavaVM* GetJVM();
JNIEnv* GetJNIEnv();
jobject GetQuizzerJObject();
