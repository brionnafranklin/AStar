#include "Node.h"

void Node::draw(float scale)
{
	//Changes the color of the node based on the node's state
	if (isStartNode)
	{
		//start
		DrawRectangle(position.x * scale, position.y * scale, 75, 75, PURPLE);
	}
	else if (isPathNode)
	{
		DrawRectangle(position.x * scale, position.y * scale, 75, 75, ORANGE);
	}
	else if (isEndNode)
	{
		//end
		DrawRectangle(position.x * scale, position.y * scale, 75, 75, LIME);
	}
	else
	{
		DrawRectangle(position.x * scale, position.y * scale, 75, 75, MAROON);
	}


	//Loop through the list of edges and draw them
	for (std::vector<Edge*>::iterator iterator = edges.begin(); iterator != edges.end(); iterator++)
	{
		//Draw edge
		(*iterator)->draw(position, scale);
	}
}