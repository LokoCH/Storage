#include "Item.h"
#include <typeinfo>

// КОНСТРУКТОРЫ
// Для m_type память не выделяем, потому что все экзкмпляры класса Item должны указывать на единый тип.
// Если будем что-то менять в классе Type, это должно отразиться на всех экземплярах класса Item
Item::Item(std::string name, double cost) :
	m_name{ name }, m_cost{ cost }
{}

Item::~Item()
{
	
}

Item::Item(Item& other)
{
	m_name = other.m_name;

	//m_type = other.m_type;

	m_cost = other.m_cost;
}

Item::Item(Item&& other)
{
	m_name = other.m_name;

	//m_type = other.m_type;
	//other.m_type = nullptr;

	m_cost = other.m_cost;
}

// СЕТТЕРЫ


// Другие функции
void Item::showInfo()
{
	std::cout << "Наименование товара: " << m_name << "\n";
	//std::cout << "Тип: " << m_type->getName() << "\n";
	//std::cout << "Объем: " << m_type->getVol() << "куб.м." << "\n";
	std::cout << "Цена: " << m_cost << "\n";
}