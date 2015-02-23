#include "TTSPlayer_Android.h"
#include "quizzer-jni.h"
#include <android/log.h>

#define LOG_TAG "tts-jni"
#define LOGI(...) __android_log_print (ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print (ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

TTSPlayer* GetTTSPlayer()
{
	return new TTSPlayer_Android();
}

TTSPlayer_Android::TTSPlayer_Android()
{
}

TTSPlayer_Android::~TTSPlayer_Android()
{

}

void TTSPlayer_Android::SpeakText(std::string text)
{
	LOGI("TTSPlayer_Android::SpeakText");
	JNIEnv* pEnv = GetJNIEnv();
	jobject jObj = GetQuizzerJObject();
	if(pEnv && jObj)
	{
		jclass jcQuizzer = pEnv->GetObjectClass(jObj);
		jmethodID jmPlaySound = pEnv->GetMethodID(jcQuizzer, "speakText", "(Ljava/lang/String;)V");
		jstring jStringArg = pEnv->NewStringUTF(text.data());

		pEnv->CallVoidMethod(jObj, jmPlaySound, jStringArg);

		pEnv->DeleteLocalRef(jStringArg);
	}
}
