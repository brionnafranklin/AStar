#pragma once
#include "raylib.h"

struct Node;

class Edge
{
public:
	Edge() {}
	Edge(Node*, float);

	Node* target = nullptr;
	float cost = 0.0f;
	Color drawColor = BLACK;
	void draw(Vector2 startPosition, float scale);
};