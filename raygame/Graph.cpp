#include "Graph.h"
#include <math.h>

void Graph::initializeGraph()
{
	//Sets the farthest possible x value
	int xMaximum = (int)sqrt(nodes.size()) - 1;

	//Holds the x and y position
	float xPosition = 0.0f;
	float yPosition = 0.0f;

	for (std::vector<Node*>::iterator iteratorNode1 = nodes.begin(); iteratorNode1 != nodes.end(); iteratorNode1++)
	{
		//Set each node's positon to x and y
		(*iteratorNode1)->position = { xPosition, yPosition };

		for (std::vector<Node*>::iterator iteratorNode2 = nodes.begin(); iteratorNode2 != nodes.end(); ++iteratorNode2)
		{
			if (abs((*iteratorNode2)->position.x - (*iteratorNode1)->position.x) == 1 && abs((*iteratorNode2)->position.y - (*iteratorNode1)->position.y) == 1)
			{
				(*iteratorNode2)->edges.push_back(new Edge(*iteratorNode1, 2));
			}
			else if ((abs((*iteratorNode2)->position.y - (*iteratorNode1)->position.y) == 1 && ((*iteratorNode2)->position.x == xPosition)))
			{
				(*iteratorNode2)->edges.push_back(new Edge(*iteratorNode1, 1));
			}
			else if ((abs((*iteratorNode2)->position.x - (*iteratorNode1)->position.x) == 1 && ((*iteratorNode2)->position.y == yPosition)))
			{
				(*iteratorNode2)->edges.push_back(new Edge(*iteratorNode1, 1));
			}
			else if ((*iteratorNode2)->position.x == -2 && ((*iteratorNode2)->position.y == -2))
			{
				continue;
			}
		}

		//Set x to 0 and increase y if x is equal to the maximum
		if (xPosition == xMaximum)
		{
			xPosition = 0;
			yPosition++;
			continue;
		}

		//Otherwise increase x
		xPosition++;
	}
}

void Graph::draw(int scale)
{
	//Loop throught the list of nodes and draw each one
	for (std::vector<Node*>::iterator iterator = nodes.begin(); iterator != nodes.end(); iterator++)
	{
		(*iterator)->draw(scale);
	}
}

void Graph::createGraph(int size)
{
	//Create and add nodes to the node list
	for (int i = 0; i <= size; i++)
	{
		nodes.push_back(new Node({ -2,-2 }));
	}

	//Initialize graph to organize nodes
	initializeGraph();
}

Node* Graph::findNode(Vector2 position)
{
	//Check the position of each node
	for (std::vector<Node*>::iterator iterator = nodes.begin(); iterator != nodes.end(); iterator++)
	{
		//if the nodes position is the same as the one given in the argument list i return that node
		if ((*iterator)->position == position)
		{
			return *iterator;
		}
	}

	//Otherwise return nullptr
	return nullptr;
}

int Graph::findManhattan(Node* currentNode, Node* goal)
{
	//Calculate the manhattan distance
	return abs(goal->position.x - currentNode->position.x) + abs(goal->position.y - currentNode->position.y);
}

void Graph::reconstructPath(Node* startNode, Node* endNode)
{
	Node* iterator = endNode->parent;

	//Loop through all nodes
	for (int i = 0; i < nodes.size(); i++)
	{
		//If the iterator is equal to the starting node return
		if (iterator == startNode) 
		{
			return;
		}

		//Set the node to a path node
		iterator->isPathNode = true;
		//Set the node's parent to iterator
		iterator = iterator->parent;
	}
}

bool Graph::containsNode(std::vector<Node*>* list, Node* nodeToFind)
{
	std::vector<Node*>::iterator it = std::find(list->begin(), list->end(), nodeToFind);

	if (it != list->end())
	{
		return true;
	}

	return false;
}

void Graph::removeNode(std::vector<Node*>* list, Node* unwantedNode)
{
	auto it = std::find(list->begin(), list->end(), unwantedNode);

	int index = std::distance(list->begin(), it);

	if (index == 0)
	{
		list->erase(list->begin());
		return;
	}

	list->erase(list->begin() + (index - 1.0f));
}

void Graph::sortNodes(std::vector<Node*>* listPtr)
{
	Node* temp;

	//Use bubble sort here to iterate throught the list and organize it by the f score
	for (std::vector<Node*>::iterator iteratorNode1 = nodes.begin(); iteratorNode1 != nodes.end(); iteratorNode1++) 
	{
		for (std::vector<Node*>::iterator iteratorNode2 = nodes.begin(); iteratorNode2 != nodes.end(); iteratorNode2++) 
		{
			if ((*iteratorNode1)->fScore > (*iteratorNode2)->fScore) 
			{
				temp = (*iteratorNode2);
				(*iteratorNode2) = (*iteratorNode1);
				(*iteratorNode1) = temp;
			}
		}
	}
}

void Graph::AStarSearch(Vector2 startPosition, Vector2 endPosition)
{
	Node* startNode = findNode(startPosition);
	startNode->isStartNode = true;
	Node* endNode = findNode(endPosition);
	endNode->isEndNode = true;

	//Intialize openlist
	std::vector<Node*> openList;

	//Add the starting node to openList
	openList.push_back(startNode);

	//Create a pointer to openList
	std::vector<Node*>* openListPtr = &openList;

	//Initialize closedList
	std::vector<Node*> closedList;

	//Calculate the manhattan distance for the heuristic
	startNode->fScore = findManhattan(startNode, endNode);

	//Loop while the openList's size is greater than 0
	while (!openList.empty())
	{
		//Use the sortNodeList function to sort the open list. You can pass in the opentlistPtr as the argument
		sortNodes(&openList);
		//Create a Node* called currentNode. This will keep track of the node we are currently evaluating
		Node* currentNode = openList.front();

		//If current node is the same as the goal node call the reconstruct path function and return
		if (currentNode == endNode) 
		{
			reconstructPath(startNode, endNode);
			return;
		}

		//Call the removeNodeFromList function and use openlistPtr and currentNode as the arguments
		removeNode(openListPtr, currentNode);
		//Add current node to the closedlist
		closedList.push_back(currentNode);

		//Loop through all edges for the current node
		for (Edge* e : currentNode->edges) 
		{
			//Check if the node at the end of the edge is in either the openlist or the closed list
			if (containsNode(&closedList, e->target) || containsNode(openListPtr, e->target)) 
			{
				//If the statemnet is true continue
				continue;
			}

			else 
			{
				//Set the neighbor's gScore to be the currentNode's gScore added to the edge's cost
				e->target->gScore = currentNode->gScore + e->cost;
				//Set the h score of the neighbor to be the hueristic
				e->target->hScore = findManhattan(e->target, endNode);
				//Set the f score of the neighbor to be the g score of the neighbor added to the hueristic
				e->target->fScore = e->target->gScore + findManhattan(e->target, endNode);
				//Set the parent of the neighbor to be the current node
				e->target->parent = currentNode;
				//Add neighbor to openlist
				openList.push_back(e->target);

			}
		}
	}
}