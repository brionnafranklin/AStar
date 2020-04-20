#pragma once
#include "Node.h"

class Graph
{
public:
	Graph() {}

	//List of all nodes
	std::vector<Node*> nodes;

	//Sets the node's position on the graph with the proper connections
	void initializeGraph();
	//Draws the grid according to how far apart the nodes are
	void draw(int scale);
	//Creates all nodes and populates list
	void createGraph(int size);

	//Find and return the positon of a node in the graph
	Node* findNode(Vector2 position);

	//Finds the manhattan distance between two nodes
	int findManhattan(Node*, Node*);

	//Changes the color of all nodes in the path
	void reconstructPath(Node*, Node*);

	//Return whether or not a node is in a list
	bool containsNode(std::vector<Node*>*, Node*);

	//Removes a node from a list
	void removeNode(std::vector<Node*>*, Node*);

	//Sorts a list based on the f score of the nodes
	void sortNodes(std::vector<Node*>*);

	//Finds a path from the starting position given to the ending position given
	void AStarSearch(Vector2 startPosition, Vector2 endPosition);
};