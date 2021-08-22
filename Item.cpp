#include "Item.h"
#include <typeinfo>

// ÊÎÍÑÒÐÓÊÒÎÐÛ
Item::Item(std::string name, double cost, Storage* store) :
	m_name{ name }, m_cost{ cost }, store{ nullptr } {this->store = store; }

Item::~Item()
{
	store = nullptr;
}

Item::Item(Item& other)
{
	m_name = other.m_name;
	m_cost = other.m_cost;
	store = other.store;
}

Item::Item(Item&& other) noexcept
{
	m_name = other.m_name;
	m_cost = other.m_cost;
	store = other.store;
	other.store = nullptr;
}