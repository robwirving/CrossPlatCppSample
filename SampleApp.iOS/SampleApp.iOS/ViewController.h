//
//  ViewController.h
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#import <UIKit/UIKit.h>

#include "Quizzer.h"

@interface ViewController : UIViewController

-(IBAction)button1_Click;
-(IBAction)button2_Click;
-(IBAction)button3_Click;
-(IBAction)button4_Click;

-(void)selectAnswer:(unsigned int)answerChoice;
-(void)displayQuestion;

@end

Quizzer _quizzer;


