#include "BaseAnimal.h"
#include <iostream>

/// <summary>
/// Класс со статическими функциями. В отличие от других классов, чтобы пользоваться статическими функциями,
/// не нужно создавать объект класса - можно обратиться напрямую
/// </summary>
class ForceOfNature
{
	// пример ПОЛИМОРФИЗМА - данный метод будет работать с животным любого типа, кошка/мышка/др.
	public:
	static void SuddenDeath(BaseAnimal poorFella)
	{
		poorFella.isAlive = false;
		std::cout << "Oh no! " << poorFella.name << " is dead!" << std::endl;
	}
};