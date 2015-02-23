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
 */

package com.example.quizzer;

import java.util.Locale;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class Quizzer extends Activity {

    //static final String TAG = "Quizzer";
	ProgressBar prgLoading;
	TextView txtQuestion;
	Button btnAnswer1;
	Button btnAnswer2;
	Button btnAnswer3;
	Button btnNextQuestion;
	
	MediaPlayer objPlayer = null;
	TextToSpeech objTTS = null;
	LocationManager objLocationManager = null;
    static AssetManager assetManager;
    
    boolean bIsTTSInitialized = false;
    String strTextToSpeakOnInit = null;

    static int numChannelsUri = 0;

    /** Called when the activity is first created. */
    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.main);

        assetManager = getAssets();
        
        objLocationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
        
        objTTS = new TextToSpeech(getApplicationContext(),
        		new TextToSpeech.OnInitListener() {
        	@Override
        	public void onInit(int iStatus) {
        		if(iStatus != TextToSpeech.ERROR){
        			Log.i("Quizzer", "TextToSpeech is ready");
        			objTTS.setLanguage(Locale.US);
        			bIsTTSInitialized = true;
        			if(strTextToSpeakOnInit != null && !strTextToSpeakOnInit.isEmpty())
        			{
        				objTTS.speak(strTextToSpeakOnInit, TextToSpeech.QUEUE_FLUSH, null);
        				strTextToSpeakOnInit = null;
        			}
                   }				
                }
        	});
                
        txtQuestion = ((TextView) findViewById(R.id.txtQuestion));
        prgLoading = ((ProgressBar) findViewById(R.id.prgLoading));
        btnAnswer1 = ((Button) findViewById(R.id.button1));
        btnAnswer2 = ((Button) findViewById(R.id.button2));
        btnAnswer3 = ((Button) findViewById(R.id.button3));
        btnNextQuestion = ((Button) findViewById(R.id.nextQuestion));

        // initialize button click handlers
        btnAnswer1.setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
            	selectQuizAnswer(0);
            }
        });

        btnAnswer2.setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
            	selectQuizAnswer(1);
            }
        });

        btnAnswer3.setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
            	selectQuizAnswer(2);
            }
        });

        btnNextQuestion.setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
                if (nextQuestion()) {
                    displayQuestion();
                }
            }
        });
        
        prgLoading.setIndeterminate(true);
        prgLoading.setVisibility(View.VISIBLE);
        
        final Quizzer objQuizzer = this;
        new Thread(new Runnable() {
        	public void run() {
        		
        		load(objQuizzer);
        		
        		runOnUiThread(new Runnable() {
            		public void run() {
            			displayQuestion();
            			prgLoading.setVisibility(View.INVISIBLE);
            		}
            	});
        		
        	}
        }).start();
        //load(this);
    }
    
    public void onJNILoad()
    {
    	runOnUiThread(new Runnable() {
    		public void run() {
    			displayQuestion();
    			prgLoading.setVisibility(View.INVISIBLE);
    		}
    	});
    }
    
    public void playSound(String sound)
    {
    	Log.i("Quizzer", "playSound: " + sound);
    	if(objPlayer != null)
    		objPlayer.stop();
    	if(sound.equals("clapping.mp3"))
    		objPlayer = MediaPlayer.create(this, R.raw.clapping);
    	else if(sound.equals("buzzer.mp3"))
    		objPlayer = MediaPlayer.create(this, R.raw.buzzer);
    	
    	if(objPlayer != null)
    		objPlayer.start();
    }
    
    public void speakText(String text)
    {
    	Log.i("Quizzer", "speakText: " + text);
    	
    	if(objTTS != null && bIsTTSInitialized)
    		objTTS.speak(text, TextToSpeech.QUEUE_FLUSH, null);
    	else
    		strTextToSpeakOnInit = text;
    }
    
    public Location getLastKnownLocation()
    {
    	Log.i("Quizzer", "getLastKnownLocation");
    	if(objLocationManager != null)
    	{
	    	Criteria crit = new Criteria();
	    	crit.setAccuracy(Criteria.ACCURACY_LOW);
	    	String provider = objLocationManager.getBestProvider(crit, true);
	    	Location locLastKnown = objLocationManager.getLastKnownLocation(provider);
	    	if(locLastKnown != null)
	    	{
		    	Log.i("Quizzer", "LastKnownLocation: " 
		    			+ String.valueOf(locLastKnown.getLatitude()) + ", " 
		    			+ String.valueOf(locLastKnown.getLongitude()));
	    		return locLastKnown;
	    	}
    	}
    	return null;
    }
    
    public void selectQuizAnswer(int answerChoice)
    {
    	selectAnswer(answerChoice);
    	
    	btnNextQuestion.setVisibility(View.VISIBLE);
    }
    
    public void displayQuestion()
    {
    	Log.i("Quizzer", "displayQuestion");
    	
    	QuizQuestion q = getQuestion();
    	
    	Log.i("Quizzer", "Displaying Question: " + q.GetQuestion());
    	
    	txtQuestion.setText(q.GetQuestion());
    	
    	btnAnswer1.setText(q.getAnswers().get(0));
    	btnAnswer2.setText(q.getAnswers().get(1));
    	btnAnswer3.setText(q.getAnswers().get(2));
    	
    	btnNextQuestion.setVisibility(View.INVISIBLE);
    }

    /** Called when the activity is about to be destroyed. */
    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        
        unload();
    }

    /** Native methods, implemented in jni folder */
    public static native void load(Object quizzerObject);
    public static native void unload();
    public static native void selectAnswer(int answerChoice);
    public static native boolean nextQuestion();
    public static native QuizQuestion getQuestion();

    /** Load jni .so on initialization */
    static {
         System.loadLibrary("quizzer-jni");
    }

}
