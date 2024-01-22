#include "myheader.h"


void steroid(struct horses* horse, int per_3, int per_5)
{
	horse->per_1 -= per_3 + per_5;
	horse->per_3 += per_3;
	horse->per_5 += per_5;
}