#ifndef ITEM_H
#define ITEM_H

#include<string>
#include<iostream>
#include<vector>

class Item;
// Структура склада, содержащая название(например "Теплый склад") и вектор однотипных товаров
struct Storage
{
	std::string name{ "" };
	std::vector<Item*>items;
};

class Item
{
public:
	Item(std::string name, double cost, Storage* store);
	~Item();
	Item(Item& other);
	Item(Item&& other)noexcept;

	virtual void setName(std::string name)
	{
		m_name = name;
	}

	virtual std::string getName()
	{
		return m_name;
	}

	virtual void setCost(double cost)
	{
		m_cost = cost;
	}

	virtual double getCost()
	{
		return m_cost;
	}

	virtual std::string getSize() = 0;
	virtual double getVol() = 0;

	virtual void showInfo() = 0;

	Storage* getStore()const { return store; }

protected:
	std::string m_name;
	double m_cost;
	Storage* store;
};

class Ball :public Item
{
public:
	Ball(std::string name, double cost, Storage* store, int radius, std::string material) :Item(name, cost, store), m_radius{ radius }, material{ material } {}

	std::string getSize() override
	{
		return (std::to_string(m_radius) + "см");
	}

	double getVol() override
	{
		return (4 * 3.14 * std::pow(m_radius, 3) / 3.) * 0.000001;
	}

	void showInfo() override
	{
		std::cout << "Наименование: " << m_name << "\n";
		std::cout << "Размер: ";
		std::cout << getSize() << "\n";
		std::cout << "Материал: " << material << "\n";
		std::cout << "Цена: " << m_cost << "\n";
	}

private:
	int m_radius;
	std::string material;
};

class TV : public Item
{
public:
	TV(std::string name, double cost, Storage* store, int length, int width, int heigth, std::string screen) : Item(name, cost, store),
		m_length{ length },
		m_width{ width },
		m_height{ heigth },
		m_screen{ screen } {}

	std::string getSize() override
	{
		return (std::to_string(m_length) + "см x " + std::to_string(m_width) + "см x " + std::to_string(m_height) + "см");
	}

	double getVol() override
	{
		return (m_length * m_width * m_height) * 0.000001;
	}

	void showInfo() override
	{
		std::cout << "Наименование: " << m_name << "\n";
		std::cout << "Размер: ";
		std::cout << getSize() << "\n";
		std::cout << "Экран: " << m_screen << "\n";
		std::cout << "Цена: " << m_cost << "\n";
	}

private:
	int m_length;
	int m_width;
	int m_height;
	std::string m_screen;
};

class Sugar : public Item
{
public:
	Sugar(std::string name, double cost, Storage* store, int weight) :Item(name, cost, store), m_weight{ weight } {}

	std::string getSize() override
	{
		return (std::to_string(m_weight) + " кг");
	}

	double getVol() override
	{
		return  m_weight * 0.02; // предположим что мешок в 50 кг занимает 1 куб.м.	
	}

	void showInfo() override
	{
		std::cout << "Наименование: " << m_name << "\n";
		std::cout << "Вес: ";
		std::cout << getSize() << "\n";
		std::cout << "Цена: " << m_cost << "\n";
	}

private:
	int m_weight; // вес
};

class Compound :public Item
{
public:
	Compound() :Item("Компоновщик", 0, nullptr), vol{ 0 } {}

	void add(Item* item)
	{
		items.push_back(item);
		m_cost += item->getCost();
		vol += item->getVol();
	}
	void remove()
	{
		m_cost -= items.back()->getCost();
		vol -= items.back()->getVol();
		items.pop_back();
	}

	std::vector<Item*>& getItems()
	{
		return items;
	}


	double getCost() override
	{
		return m_cost;
	}

	std::string getSize()override
	{
		return std::to_string(items.size());
	}

	double getVol()override
	{
		return vol;
	}

	void showInfo() override
	{
		std::cout << "Всего мест" << items.size() << "\n";
		std::cout << "Цена: " << m_cost << "\n";
	}
private:
	std::vector<Item*>items;
	double vol;
};

#endif //!ITEM_H