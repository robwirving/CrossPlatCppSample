//
//  GpsPosition_iOS.h
//  SampleApp.iOS
//
//  Created by Rob Irving on 1/3/15.
//  Copyright (c) 2015 Rob Irving. All rights reserved.
//

#ifndef SampleApp_iOS_GpsPosition_iOS_h
#define SampleApp_iOS_GpsPosition_iOS_h

#import <CoreLocation/CoreLocation.h>

class GpsPosition_iOS;

@interface GpsPositionManager : NSObject<CLLocationManagerDelegate>

-(id)init;
-(void)start;
-(void)stop;
-(void)wait;
-(const CLLocationCoordinate2D)getCoordinate;
@end

#include "GpsPosition.h"

class GpsPosition_iOS : public GpsPosition
{
public:
    GpsPosition_iOS();
    virtual ~GpsPosition_iOS();
    
    void GetCurrentPosition() override;
    
private:
    GpsPositionManager* _gpsPositionManager;
};

#endif
