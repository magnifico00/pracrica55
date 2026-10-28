#include <iostream>
#include "Prey.h"

class Carnivore : public Prey
{
public:
	// методы
	
	/// <summary>
	/// Охота на жертву для насыщения
	/// </summary>
	/// <param name="prey">Жертва</param>
	void Hunt(Prey& prey) // реализация полиформизма - метод будет работать с любым объектом класса "Жертва"
	{
		hunger += prey.GetNutritionalValue();
		std::cout << name << " has restored " << prey.GetNutritionalValue() << " hunger." << std::endl;
		std::cout << "Current hunger = " << hunger << std::endl;
		prey.Kill();
	}

	// конструкторы
	Carnivore(std::string name, float nutritionalValue) : Prey(name, nutritionalValue)
	{
		this->nutritionalValue = nutritionalValue;
	};
};