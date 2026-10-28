// Файл реализации функционала заголовочного класса
#include "BaseAnimal.h"
#include <iostream>

// Переменные
bool isAlive;
float hunger = 100; // Шкала голода
std::string name; // Наименование животного

// функции

/// <summary>
/// Насыщение животного
/// </summary>
/// <param name="nutrition">Величина сытости</param>
void BaseAnimal::Eat(float nutrition)
{
	hunger += nutrition;
}

/// <summary>
/// Завершает жизнь зверя
/// </summary>
void BaseAnimal::Kill() // Реализация инкапсуляции - мы не даём пользователям работать с 
// переменными напрямую, вместо этого предоставляя метод, в котором предусмотрена логика
{
	hunger = 0;
	isAlive = false;
}