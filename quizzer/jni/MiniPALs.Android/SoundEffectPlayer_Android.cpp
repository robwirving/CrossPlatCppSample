#include "SoundEffectPlayer_Android.h"
#include "quizzer-jni.h"
#include <android/log.h>

#define LOG_TAG "soundeffect-jni"
#define LOGI(...) __android_log_print (ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print (ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

SoundEffectPlayer* GetSoundEffectPlayer()
{
	return new SoundEffectPlayer_Android();
}

SoundEffectPlayer_Android::SoundEffectPlayer_Android()
{
}

SoundEffectPlayer_Android::~SoundEffectPlayer_Android()
{
}

void SoundEffectPlayer_Android::PlayEffect(std::string effect)
{
	LOGI("SoundEffectPlayer_Android::PlayEffect");
	JNIEnv* pEnv = GetJNIEnv();
	jobject jObj = GetQuizzerJObject();
	if(pEnv && jObj)
	{
		jclass jcQuizzer = pEnv->GetObjectClass(jObj);
		jmethodID jmPlaySound = pEnv->GetMethodID(jcQuizzer, "playSound", "(Ljava/lang/String;)V");
		jstring jStringArg = pEnv->NewStringUTF(effect.data());

		pEnv->CallVoidMethod(jObj, jmPlaySound, jStringArg);

		pEnv->DeleteLocalRef(jStringArg);
	}
}
