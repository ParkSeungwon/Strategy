
int randomDice(int eyes) {
	srand(time());
	return rand()%eyes;
}

int randomDice() {
	return randomDice(100);
}

float Unit::distanceBetween(CGPoint pointA, CGPoint pointB)
{
    return sqrtf(powf(pointA.x - pointB.x, 2) + powf(pointA.y - pointB.y, 2));
}

