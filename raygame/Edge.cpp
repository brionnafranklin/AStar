#include "Edge.h"
#include "Node.h"

//contructor
Edge::Edge(Node* newTarget, float newCost = 0)
{
	//set target cost and color
	target = newTarget;
	cost = newCost;
	drawColor = BLACK;
}
//draw lines A* can take
void Edge::draw(Vector2 startPosition, float scale)
{
	DrawLine(startPosition.x * scale, startPosition.y * scale, target->position.x * scale, target->position.y * scale, drawColor);
}