#include "BaseAnimal.h"
#include "Prey.h"

float nutritionalValue;

float Prey::GetNutritionalValue()
{
	return nutritionalValue;
}

void Prey::SetNutritionalValue(float value)
{
	nutritionalValue = value;
}

void Prey::Kill()
{
	BaseAnimal::Kill();
	SetNutritionalValue(0);
}