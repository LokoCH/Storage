#ifndef CAR_H
#define CAR_H

#include<iostream>
#include<vector>
#include"Item.h"

class Car
{
public:
	Car(double capacity) : m_capacity{ capacity }, m_volume{ 0 }, m_cost{ 0 }
	{
		++countId;
		m_id = countId;
	}

	bool put(Item* newItem)
	{
		if (newItem->getVol() > (m_capacity - m_volume))
			return false; // товар не поместился в машину

		m_items.push_back(newItem);
		m_volume += newItem->getVol();
		m_cost += newItem->getCost();
		return true;
	}

	Item* get()
	{
		if (!m_items.size())
		{
			return nullptr;
		}

		Item* temp = m_items.back();
		m_volume -= m_items.back()->getVol();
		m_cost -= m_items.back()->getCost();
		m_items.pop_back();

		if (!m_items.size())
			m_volume = 0;

		return temp;
	}

	double getCapacity()
	{
		return m_capacity;
	}

	double getVolume()
	{
		return m_volume;
	}

	int getId()
	{
		return m_id;
	}

	std::vector<Item*> getItems()
	{
		return m_items;
	}

	double getCost()
	{
		return m_cost;
	}

	void showInfo()
	{
		std::cout << "Номер машины: " << m_id << "\n";
		if (!m_items.size())
		{
			std::cout << "Машину пуста\n";
			return;
		}

		std::cout << "Загруженно " << m_volume << "куб.м. из " << m_capacity << "\n";
		std::cout << m_items.size() << " мест\n";
		std::cout << m_cost << "\n";
	}

private:
	static int countId;
	int m_id;
	double m_capacity; // вместимость
	double m_volume; // текущая загруженность
	double m_cost;
	std::vector<Item*>m_items; // список товаров
};

#endif//!CAR_H