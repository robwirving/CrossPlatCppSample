#include "GpsPosition_Android.h"
#include "quizzer-jni.h"
#include <android/log.h>

#define LOG_TAG "gpsposition-jni"
#define LOGI(...) __android_log_print (ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print (ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

GpsPosition* GetGpsPosition()
{
	return new GpsPosition_Android();
}

GpsPosition_Android::GpsPosition_Android()
{
}

GpsPosition_Android::~GpsPosition_Android()
{
}

void GpsPosition_Android::GetCurrentPosition()
{
	LOGI("GpsPosition_Android::GetCurrentPosition");
#if 1
	_latitude = 37.8650517;
	_longitude = -122.0838511;
#else
	JNIEnv* pEnv = GetJNIEnv();
	jobject jObj = GetQuizzerJObject();
	if(pEnv && jObj)
	{
		jclass jcQuizzer = pEnv->GetObjectClass(jObj);
		jmethodID jmGetLocation = pEnv->GetMethodID(jcQuizzer, "getLastKnownLocation", "()Landroid/location/Location;");

		jobject jLocation = pEnv->CallObjectMethod(jObj, jmGetLocation);

		LOGI("GpsPosition_Android::GetCurrentPosition called getLastKnownLocation");

		/*
		if(jLocation != nullptr)
		{
			LOGI("GpsPosition_Android::GetCurrentPosition got jLocation");
			jclass jcLocation = pEnv->GetObjectClass(jLocation);
			jmethodID jmGetLatitude = pEnv->GetMethodID(jcLocation, "getLatitude", "()F");
			jmethodID jmGetLongitude = pEnv->GetMethodID(jcLocation, "getLongitude", "()F");

			jfloat latitude = pEnv->CallFloatMethod(jLocation, jmGetLatitude);
			jfloat longitude = pEnv->CallFloatMethod(jLocation, jmGetLongitude);
			_latitude = (float)latitude;
			_longitude = (float)longitude;
		}
		*/
	}
#endif
}
