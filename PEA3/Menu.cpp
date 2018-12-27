#include "Menu.h"
#include <iostream>


Menu::Menu()
{
	gen = new Genetic();
	graph = new Graph();
}


Menu::~Menu()
{
}

void Menu::MainMenu()
{
	int choice;
	int maxTime;
	int count;
	double mutation;
	//double cross;

	do 
	{
		std::cout << "1. Wczytaj z dane z pliku" << std::endl
			<< "2. Kryteruim stopu" << std::endl
			<< "3. Ustawienie wilekosci populacji poczatkowej" << std::endl
			<< "4. Wspolczynnik mutacji" << std::endl
			<< "5. Wspolczynnik krzyzowania" << std::endl
			<< "6. Algorytm genetyczny" << std::endl
			<< "7. Wyjscie" << std::endl;
			std::cin >> choice;

		switch (choice)
		{
		case 1:
			FileMenu();
			//gen->Display();
			break;
		case 2:
			std::cout << "Podaj kryterium stopu (w sekunach): " << std::endl;
			std::cin >> maxTime;
			gen->setTime(maxTime);
			break;
		case 3:
			std::cout << "Podaj wielkosc populacji poczatkowej: " << std::endl;
			std::cin >> count;
			gen->setPopulatinCount(count);
			gen->CreatePopulation(gen->getPopulationCount());
			break;
		case 4:
			std::cout << "Podaj wspolczynnik mutacji: " << std::endl;
			std::cin >> mutation;
			gen->setMutationCoefficient(mutation);
			gen->MutateSwap(gen->getMutationCoefficient());
			break;
		case 5:
			std::cout << "Podaj wspolczynnik krzyzowania: " << std::endl;
			//std::cin >> cross;
			//gen->setMutationCoefficient(cross);
			break;
		case 6:
			MutationType();
			break;
		case 7:
			exit(EXIT_SUCCESS);
		default:
			break;
		}

	} while (true);
}

void Menu::FileMenu()
{
	int choice;
	std::cout << "Ktory plik otworzyc?" << std::endl
		<< "1. ftv47.atsp" << std::endl
		<< "2. ftv170.atsp" << std::endl
		<< "3. rbg403.atsp" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		gen->ReadAtspFile("ftv47.atsp", 48);
		break;
	case 2:
		gen->ReadAtspFile("ftv170.atsp", 171);
		break;
	case 3:
		gen->ReadAtspFile("rbg403.atsp", 403);
		break;
	default:
		break;
	}
}

void Menu::MutationType()
{
	int choice;
	std::cout << "Wybierz metode mutacji" << std::endl
		<< "1. Swap mutation (zamiana miejsc dwoch losowych elemntow) " << std::endl
		<< "2. Scramble mutation (wymieszanie losowego podzbioru danego osobnika z populacji)" << std::endl;
	std::cin >> choice;
	switch(choice)
	{
	case 1:
		gen->MutateSwap(gen->getMutationCoefficient());
		break;
	case 2:
		gen->MutateScramble(gen->getMutationCoefficient());
		break;
	default:
		break;
	}
}
