#pragma once
#include "Edge.h"
#include <vector>

class Node
{
public:
	//default contructor
	Node() {}
	//default decontructor
	~Node() {}
	//contructor
	Node(Vector2 newPosition) { position = newPosition; }

	Vector2 position;

	//declare the gScore, hScore, and fScore
	float gScore = 0;
	float hScore = 0;
	float fScore = 0;

	//make bools for each type of node
	bool isStartNode;
	bool isEndNode;
	bool isPathNode;

	//set parner to null
	Node* parent = nullptr;

	//Loop through the list of edges and draw them
	std::vector<Edge*> edges;

	//draw nodes
	void draw(float scale);
};