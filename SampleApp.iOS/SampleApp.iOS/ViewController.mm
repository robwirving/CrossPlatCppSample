//
//  ViewController.m
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#import "ViewController.h"
#include "Quizzer.h"
#include "PlatformConversions_iOS.h"

@interface ViewController ()

@property (nonatomic, weak) IBOutlet UILabel *txtQuestion;
@property (nonatomic, weak) IBOutlet UIButton *button1;
@property (nonatomic, weak) IBOutlet UIButton *button2;
@property (nonatomic, weak) IBOutlet UIButton *button3;
@property (nonatomic, weak) IBOutlet UIButton *button4;
@property (nonatomic, weak) IBOutlet UIActivityIndicatorView *progressRing;

@end

@implementation ViewController

- (IBAction)button1_Click
{
    [self selectAnswer:0];
}

- (IBAction)button2_Click
{
    [self selectAnswer:1];
}

- (IBAction)button3_Click
{
    [self selectAnswer:2];
}

-(IBAction)button4_Click
{
    if(_quizzer.NextQuestion())
        [self displayQuestion];
}

-(void)selectAnswer:(unsigned int)answerChoice
{
    _quizzer.SelectAnswer(answerChoice);
    
    [_button4 setHidden:NO];
}

-(void)displayQuestion
{
    auto question = _quizzer.GetQuestion();
    
    _txtQuestion.text = convertToPlatformString(question.GetQuestion());
    [_button1 setTitle:convertToPlatformString(question.GetAnswers()[0]) forState:UIControlStateNormal];
    [_button2 setTitle:convertToPlatformString(question.GetAnswers()[1]) forState:UIControlStateNormal];
    [_button3 setTitle:convertToPlatformString(question.GetAnswers()[2]) forState:UIControlStateNormal];
    
    [_button4 setHidden:YES];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [_progressRing setHidesWhenStopped:YES];
    [_progressRing startAnimating];
    
    NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
        // need to do this asynchronously
        _quizzer.Load();
        
        [_progressRing stopAnimating];
        
        [self displayQuestion];
    }];
    
    [[NSOperationQueue mainQueue] addOperation:operation];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
