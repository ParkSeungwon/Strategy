CGPoint Unit::getTurnCenterByRadiusAndTheta(float radius, float theta) 
{
    CGPoint center;
    float x, y;
    float cota = 1 / tanf(self.headingToward);
    float rootPart = sqrtf(radius*radius/(1+pow(cota,2)));
    float a = currentPosition.x;
    float b = currentPosition.y;
   
    if (headingToward <= M_PI) {
        if (theta >=0) {
            x = a - rootPart;//counterclockwise
        } 
        else {
            x = a + rootPart;//clockwise
        }
    }
    else {
        if (theta >= 0) {
            x = a + rootPart;
        }
        else {
            x = a - rootPart;
        }
    }
    
    y = b - cota * ( x-a);
    center.x = x;
    center.y = y;
    
    return center;
}

CGPoint Unit::getMovedPointByRadiusAndTheta(float r,float theta) 
{
    CGPoint center = getTurnCenterByRadiusAndTheta(r,theta);
    CGPoint movedPoint;
    movedPoint.x = center.x + r * cosf(theta + headingToward - M_PI/2);
    movedPoint.y = center.y + r * sinf(theta + headingToward - M_PI/2);  
    return movedPoint;
}
CGPoint Unit::getMovedPoint(CGPoint turnCenter, CGPoint currentPosition, float theta)
{
	int r = distanceBetween(turnCenter, currentPosition);
	CGPoint movedPoint;
    movedPoint.x = center.x + r * cosf(theta + headingToward - M_PI/2);
    movedPoint.y = center.y + r * sinf(theta + headingToward - M_PI/2);  
    return movedPoint;
	
}
/*void Unit::moveToAtSpeed(CGPoint destination,int speed) 
{
    if(speed >= minimumSpeed && speed <= maximumSpeed) {
        float theta = getMovedAngleInRadian(destination);
        float r = getTurnRadius(destination);
        currentPosition = destination;
        currentFuel -= r * theta;
        headingToward += theta;
    }
}

void Unit::moveByRadiusAndTheta(float radius,float theta) 
{
    currentFuel -= radius * theta;
    headingToward += theta;
    currentPosition = getMovedPointByRadiusAndTheta(radius, theta);  
}

void followOtherUnit:(Unit *)otherUnit toAttackWithWeapon:(Weapon *)weapon
{
    [self getTurnCenterByRadius:self.minimumTurnRadius andTheta:<#(float)#>
    [self moveByRadius:self.minimumTurnRadius andTheta:self.headingToward];
    [self moveTo:otherUnit.currentPosition atSpeed:self.maximumSpeed];
}*/