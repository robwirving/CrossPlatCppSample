/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* This is a JNI example where we use native methods to play sounds
 * using OpenSL ES. See the corresponding Java source file located at:
 *
 *   src/com/example/quizzer/Quizzer/Quizzer.java
 */
#include "quizzer-jni.h"
#include <assert.h>
#include <jni.h>
#include <android/log.h>
#include <pthread.h>
#include <string.h>
#include <memory>

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "Quizzer.h"

#define LOG_TAG "quizzer-jni"
#define LOGI(...) __android_log_print (ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print (ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

JavaVM* g_pJVM = nullptr;

JavaVM* GetJVM()
{
	return g_pJVM;
}

JNIEnv* GetJNIEnv()
{
	JNIEnv* pEnv = nullptr;

	if(g_pJVM)
	{
		g_pJVM->GetEnv((void**)(&pEnv), JNI_VERSION_1_6);

		if(pEnv == nullptr)
			g_pJVM->AttachCurrentThread(&pEnv, nullptr);
	}

	return pEnv;
}

Quizzer* g_Quizzer = nullptr;

Quizzer* GetQuizzer()
{
	if(g_Quizzer == nullptr)
		g_Quizzer = new Quizzer();

	return g_Quizzer;
}

jobject g_jObj = nullptr;

jobject GetQuizzerJObject()
{
	return g_jObj;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* pJVM, void* reserved)
{
	LOGI("JNI_OnLoad++");

	g_pJVM = pJVM;

	jint jiRet = -1;
	JNIEnv *pEnv = nullptr;
	jclass jcQuizzer = nullptr;
	jmethodID jmidOnLoad = nullptr;

	if(pJVM->GetEnv((void**)&pEnv, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGE("JNI Check Failure");
		return jiRet;
	}

	if(pEnv == nullptr)
	{
		LOGE("pEnv is nullptr");
		return jiRet;
	}

	jcQuizzer = pEnv->FindClass("com/example/quizzer/Quizzer");
	if(jcQuizzer == nullptr)
	{
		LOGE("Find Class returns nullptr");
		return jiRet;
	}

	jmidOnLoad = pEnv->GetMethodID(jcQuizzer, "onJNILoad", "()V");
	if(jmidOnLoad == nullptr)
	{
		LOGE("GetMethodID returns nullptr");
		return jiRet;
	}

	//pEnv->CallVoidMethod(jcQuizzer, jmidOnLoad);

	return JNI_VERSION_1_6;
}

/*
void* quizzerLoadThread(void*)
{
	LOGI("quizzerLoadThread++");
	if(GetQuizzer())
	{
		GetQuizzer()->Load();
	}

	JNIEnv* pEnv = GetJNIEnv();
	if(pEnv)
	{
		jclass jcQuizzer = pEnv->GetObjectClass(g_jObj);
		if(!jcQuizzer)
			LOGE("FindClass failed");
		jmethodID jmOnLoad = pEnv->GetMethodID(jcQuizzer, "onJNILoad", "()V");
		if(!jmOnLoad)
			LOGE("GetMethodID Failed");
		pEnv->CallVoidMethod(g_jObj, jmOnLoad);
	}

	LOGI("quizzerLoadThread--");

	return nullptr;
}
*/

extern "C"
{
void Java_com_example_quizzer_Quizzer_load(JNIEnv* pEnv, jclass clazz, jobject jQuizzer)
{
	LOGI("Java_com_example_quizzer_Quizzer_load");

	g_jObj = pEnv->NewGlobalRef(jQuizzer);

	if(GetQuizzer())
		GetQuizzer()->Load();
}

void Java_com_example_quizzer_Quizzer_unload(JNIEnv* pEnv, jclass clazz)
{
	LOGI("Java_com_example_quizzer_Quizzer_unload");

	if(g_Quizzer)
	{
		delete g_Quizzer;
		g_Quizzer = nullptr;
	}

	if(g_jObj)
	{
		pEnv->DeleteGlobalRef(g_jObj);
		g_jObj = nullptr;
	}
}

void Java_com_example_quizzer_Quizzer_selectAnswer(JNIEnv* pEnv, jclass clazz, jint jiAnswer)
{
	LOGI("Java_com_example_quizzer_Quizzer_selectAnswer");
	if(GetQuizzer())
		GetQuizzer()->SelectAnswer((int)jiAnswer);
}

jboolean Java_com_example_quizzer_Quizzer_nextQuestion(JNIEnv* pEnv, jclass clazz)
{
	LOGI("Java_com_example_quizzer_Quizzer_nextQuestion");
	if(GetQuizzer())
		return GetQuizzer()->NextQuestion();

	return false;
}

jobject Java_com_example_quizzer_Quizzer_getQuestion(JNIEnv* pEnv, jclass clazz)
{
	LOGI("Java_com_example_quizzer_Quizzer_getQuestion");

	jobject jobjQuestion = nullptr;
	jclass jcQuestion = pEnv->FindClass("com/example/quizzer/QuizQuestion");
	if(jcQuestion != nullptr)
	{
		LOGI("Java_com_example_quizzer_Quizzer_getQuestion found QuizQuestion class");
		jmethodID jmQuestionCtr = pEnv->GetMethodID(jcQuestion, "<init>", "(Ljava/lang/String;[Ljava/lang/String;)V");

		auto q = GetQuizzer()->GetQuestion();
		jstring strArgQuestion = pEnv->NewStringUTF(q.GetQuestion().data());
		jobjectArray joaAnswers = (jobjectArray)pEnv->NewObjectArray(3, pEnv->FindClass("java/lang/String"), pEnv->NewStringUTF(""));

		for(int i = 0; i < 3; i++)
			pEnv->SetObjectArrayElement(joaAnswers, i, pEnv->NewStringUTF(q.GetAnswers()[i].data()));

		jobjQuestion = pEnv->NewObject(jcQuestion, jmQuestionCtr, strArgQuestion, joaAnswers);
	}

	return jobjQuestion;
}

} // extern "C"
