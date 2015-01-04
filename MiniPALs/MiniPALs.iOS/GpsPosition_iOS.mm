//
//  GpsPosition_iOS.m
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "GpsPosition_iOS.h"

@interface GpsPositionManager()
@property (nonatomic) CLLocationCoordinate2D coordinate;
@end

@implementation GpsPositionManager

CLLocationManager* locationManager;
dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);

-(id)init
{
    self = [super init];
    
    locationManager = [[CLLocationManager alloc] init];
    locationManager.delegate = self;
    locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    
    _coordinate = [[locationManager location] coordinate];
    
    return self;
}

-(void)start
{
    [locationManager startUpdatingLocation];
}

-(void)stop
{
    [locationManager stopUpdatingLocation];
}

-(void)wait
{
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
}

-(void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
    auto currentLocation = newLocation;
    
    if (currentLocation != nil) {
        _coordinate = [currentLocation coordinate];
        
        dispatch_semaphore_signal(semaphore);
    }
}
@end

GpsPosition* GetGpsPosition()
{
    return new GpsPosition_iOS();
}

GpsPosition_iOS::GpsPosition_iOS()
{
    _gpsPositionManager = [[GpsPositionManager alloc] init];
}

GpsPosition_iOS::~GpsPosition_iOS()
{
    
}

void GpsPosition_iOS::GetCurrentPosition()
{
    if(CLLocationCoordinate2DIsValid([_gpsPositionManager coordinate]))
    {
        auto coord = [_gpsPositionManager coordinate];
        _latitude = coord.latitude;
        _longitude = coord.longitude;
    }
    else
    {
        [_gpsPositionManager start];
    
        //wait for the locationManager to call didUpdateLocation
        //[_gpsPositionManager wait];
    
        auto coord = [_gpsPositionManager coordinate];
        _latitude = coord.latitude;
        _longitude = coord.longitude;
    
        [_gpsPositionManager stop];
    }
}
