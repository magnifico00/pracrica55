#include "Carnivore.cpp"
#include <format>

/// <summary>
/// Домашняя кошка
/// </summary>
class Cat : public Carnivore
{
public:
	// Итоговые конструкторы для инициализации объектов кошек
	
	/// <summary>
	/// Просто кошка
	/// </summary>
	Cat() : Carnivore("Domestic cat", 30) {}

	/// <summary>
	/// Кошка с кличкой
	/// </summary>
	/// <param name="nickName">Кличка</param>
	Cat(std::string nickName) : Carnivore(std::format("Domestic cat ({})", nickName), 30) {}

	/// <summary>
	/// Демонстрация переопределения наследниками
	/// </summary>
	/// <param name="units"></param>
	void Move (int units) override // override - ключевое слово, маркер перегрузки
	{
		std::cout << name << " has gracefully crawled " << units << " units." << std::endl;
	}
};