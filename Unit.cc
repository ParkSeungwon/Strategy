//
//  Unit.m
//  Straegygame
//
//  Created by 승원 박 on 12. 7. 13..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//
#include "Waypoint.h"
#include "Weapon.h"
#include "Unit.h"
#include "time.h"
#include "Terrain.h"

//#include <Accelerate/Accelerate.h>


#include <string>


//#define PI 3.14159265359



/*@interface WayToGo : NSObject
@property CGPoint destination;
@property int speed;
@property CGPoint center;
@property int usedFuel;
@end
*/
@implementation Unit


string unitName;
@synthesize price;
@synthesize maxHealth;
@synthesize currentHealth;
@synthesize fuelCapacity;
@synthesize currentFuel;
@synthesize currentPosition;
@synthesize headingToward = _headingToward;
@synthesize experience;
@synthesize avoidRate;
@synthesize weaponSlot;
@synthesize minimumSpeed;
@synthesize maximumSpeed;
@synthesize intelligenceRadius;
@synthesize minimumTurnRadius;
 terrainPenaltyPercent;
 wayPoints;



Unit::Unit(string _unitName, CGPoint _currentPosition) 
{
	ifstream fin("Unit.def");
	string s;
	do {
		if (fin.eof()) throw 3; 
		fin >> s;
	}
	while (s != _unitName)
	
	unitName = _unitName;
	currentPosition = _currentPosition;
	fin >> maxHealth >> fuelCapacity >> price >> minimumSpeed ;
	fin.close();
}

void Unit::setDirectionInRadians(float direction)
{
    while (direction >= 2 * M_PI) direction -= 2 * M_PI;
    while (direction < 0) direction += 2 * M_PI;
    _headingToward = direction;   
}

bool Unit::canEquip(Weapon *weapon) 
{
    return YES;
}

CGPoint Unit::getTurnCenter(CGPoint destination) 
{
    float a = positionInfo.position.x;
    float b = positionInfo.position.y;
    float c = destination.x;
    float d = destination.y;
   
    float cota = 1/tanf(positionInfo.headingToward);
    CGPoint center;
    center.x = ( (b-d)/2+(a*a-c*c)/(2*(d-b)) ) / (cota+(a-c)/(d-b));
    center.y = cota*(a-center.x)+b;
    return center;
}

float Unit::getMovedAngleInRadian(CGPoint destination) 
{
    CGPoint center = getTurnCenter(destination);
    return atan2f(point.y - center.y, point.x - center.x) - atan2f(currentPosition.y - center.y, currentPosition.x - point.x); 
}

float Unit::getTurnRadius (CGPoint destination) 
{
    CGPoint center = getTurnCenter(destination);
    return distanceBetween(destination, center);
}


float Unit::calculateMovableDistanceForPolar(float theta) 
{
    float relativeRadius = self.headingToward + theta;
    return (2 * maximumSpeed  * cosf(relativeRadius))/ (M_PI - 2 * relativeRadius);
    
}


CGPoint Unit::where(int when) 
{
	int sec=0, i=0;
	do {sec += waypoint[i++].duration;}
	while (sec<when);
	when -= sec;	//현재 웨이포인트 내에서의 지난 시간으로 재설정
	i--;
	
	delete positionInfo;	//전에 할당한 메모리 해방
	positionInfo = waypoint[i].where(when);
}
/*- (void)calculateMovableAreaOnMap:(Map *)map
{
    int numIterations = 0;
    float * x = malloc(numIterations*sizeof(float));
    float * cosx = malloc(numIterations*sizeof(float));
    float * sinx = malloc(numIterations*sizeof(float));
    
    for(int i=0; i < numIterations; i++){
        
        x[i] = 0;//loopCalculatedValue;
    }
    
    vvsincosf(sinx,cosx,x,&numIterations);
    //vvcosf(<#float *#>, <#const float *#>, <#const int *#>)
    
    //self.currentPosition = 
}
 */

