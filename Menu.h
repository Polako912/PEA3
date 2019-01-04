#pragma once
#include "Genetic.h"

class Menu
{
private:
	Genetic* gen;
	Graph* graph;
public:
	Menu();
	~Menu();
	void MainMenu();
	void FileMenu();
	void MutationType();
};

