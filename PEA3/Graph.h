#pragma once
#include <vector>

class Graph
{
protected:
	int vertex;
	std::vector<std::vector<int>> graphData;

public:
	Graph();
	~Graph();

	void Display();
	void clearGraph();
	void ReadAtspFile(std::string filename, int number);
	void ReadFromFile(std::string filename);
	int getVertex();
	void setVertex(int number);
	std::vector<std::vector<int>> getGraph();
	void setGrpah(std::vector<std::vector<int>> vector);
};