/* чтобы избежать ошибок компиляции и вызывать данные классов больше одного раза в проекте,
в С++ прибегают к раздельной инициализации класса - заголовочные файлы и реализация. */
// В заголовки переносят инициализацию переменных и конструкторов и объявление функций.
#pragma once
#include <iostream>
#include "BaseAnimal.h"

class Prey :
    public BaseAnimal
{
protected:
	float nutritionalValue;

	Prey(std::string name) : BaseAnimal(name)
	{
		nutritionalValue = 40;
	};

	Prey(std::string name, float nutritionalValue) : BaseAnimal(name)
	{
		this->nutritionalValue = nutritionalValue;
	};

public:
	// другой пример ИНКАПСУЛЯЦИИ - структура геттер-сеттер, функции-инструменты доступа к данным.
	// внутри них может быть зашита особая логика, которую требуется учитывать для логики работы с объектом.
	float GetNutritionalValue();
	void SetNutritionalValue(float value);
	void Kill() override;
	/// <summary>
	/// Виртуальная функция. Её задача в том, чтобы быть маркером, что она должна быть у каждого наследника,
	/// и наследники сами должны определять её функционал.
	/// </summary>
	virtual void Move(int units) = 0;
};

