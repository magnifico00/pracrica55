#include "Prey.h"

/// <summary>
/// Итоговый класс Мыши, с которым можно работать
/// </summary>
class Mouse : public Prey
{
public:
	// Конструкторы объектов
	Mouse() : Prey("Country mouse", 10) {}
	Mouse(float nutritionalValue) : Prey("Country mouse", nutritionalValue) {}

	/// <summary>
	/// Демонстрация переопределения наследниками
	/// </summary>
	/// <param name="units"></param>
	void Move(int units) override // override - ключевое слово, маркер перегрузки
	{
		std::cout << name << " has moved " << units << " units." << std::endl;
	}
};