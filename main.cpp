#include<iostream>
#include<vector>
#include<typeinfo>
#include<iomanip>
#include "Item.h"
#include "Car.h"

// переменная для генерирования id машины
int Car::countId = 0;

// Структура склада, содержащая название(например "Теплый склад") и вектор однотипных товаров
struct Storage
{
	std::string name{ "" };
	std::vector<Item*>items;
};

//////////////////////////// Prototypes
void MainMenu(); // функция выводящая главное меню на экран
int Selected(int n); // функция проверяющая и возвращающая выбор пользователя
void MakeStorages(Storage& storage1, Storage& storage2, Storage& storage3);
void LoadCar(std::vector<Car*>& park, std::vector<Storage*>& storages);
void ReloadCar(std::vector<Car*>& park, std::vector<Storage*>& storages);
///////////////////////////////

// Заполняем склады товарами (для теста)
void MakeStorages(Storage& storage1, Storage& storage2, Storage& storage3)
{
	int count = 50; // количество каждого вида товара на складе
	// мячи
	for (size_t i = 0; i < count; i++)
	{
		storage1.items.push_back(new Ball("Футбольный мяч", 3000, 15, "Кожа"));
	}

	// телевизоры
	for (size_t i = 0; i < count; i++)
	{
		storage2.items.push_back(new TV("Телевизор Sony", 25000, 110, 20, 60, "LED"));
	}

	// сахар
	for (size_t i = 0; i < count; i++)
	{
		storage3.items.push_back(new Sugar("Сахар", 750, 15));
	}
}

void MainMenu()
{
	system("cls");
	std::cout << "Главное меню\n";
	std::cout << "1 - Загрузить товар в машину\n";
	std::cout << "2 - Разгрузить машину\n";
	std::cout << "0 - Выход\n>";
}

int Selected(int n) // n - количество вариантов выбора в меню
{
	int select;
	while (!(std::cin >> select) || std::cin.peek() != '\n' || select < 0 || select > n - 1)
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "Неверный ввод\n>";
	}
	std::cin.ignore();

	return select;
}

void LoadCar(std::vector<Car*>& park, std::vector<Storage*>& storages)
{

	system("cls");
	std::cout << "Выберите склад, с которого будет производиться погрузка\n";

	// Выводим список складов
	int n = 0;
	for (auto& storage : storages)
	{
		++n;
		std::cout << n << " - " << storage->name << "\n";
	}
	std::cout << "0 - Отмена\n>";
	int selStorage = Selected(n + 1);
	if (!selStorage)
		return;

	// Если склад пуст, выходим
	if (storages[selStorage - 1]->items.empty())
	{
		std::cout << "Склад пуст\n";
		std::cin.get();
		return;
	}

	std::cout << storages[selStorage - 1]->items[0]->getName() << " " << storages[selStorage - 1]->items.size() << "\n";

	std::cout << "Количество для погрузки: ";
	int count = Selected(storages[selStorage - 1]->items.size() + 1);

	system("cls");
	std::cout << "Выберите машину:\n";
	int carIdx = 0;
	for (auto& car : park)
	{
		carIdx++;
		std::cout << carIdx << " - " << " заполнено " << car->getVolume() << " из " << car->getCapacity() << " на сумму " << car->getCost() << "\n";
	}
	std::cout << "0 - Отмена\n>";
	int selCar = Selected(park.size() + 1);
	if (!selCar)
		return;

	int countLoaded = 0; // счетчик загруженных товаров
	double sum = 0; // стоимость погруженного товара
	for (size_t i = 0; i < count; i++)
	{
		auto& temp = storages[selStorage - 1]->items.back();
		if (!park[selCar - 1]->put(temp))
			break;
		sum += temp->getCost();
		storages[selStorage - 1]->items.pop_back();
		++countLoaded;
	}

	std::cout << "Загружено " << countLoaded << " единиц товара на сумму " << sum << "руб.\n";
	std::cout << "Машина " << park[selCar - 1]->getId() << " загружена на " << park[selCar - 1]->getVolume() << " из " << park[selCar - 1]->getCapacity() << "\n";
	std::cin.get();
}

void ReloadCar(std::vector<Car*>& park, std::vector<Storage*>& storages)
{
	if (!park.size())
	{
		std::cout << "Машин нет\n";
		return;
	}

	int nTrue = 0; // счетчик выгруженного товара
	int nFalse = 0; // счетчик невыгруженного товара
	system("cls");
	std::cout << "Какую машину разгрузить?\n";
	int carIdx = 0;
	for (auto& car : park)
	{
		++carIdx;
		std::cout << std::setw(5) << std::left << "" << std::setw(15) << "Количество"
			<< std::setw(20) << "Заполнено(куб.м.)" << std::setw(15) << "Сумма(руб.)" << "\n";

		std::cout << std::setw(5) << carIdx << std::setw(15) << car->getItems().size()
			<< std::setw(20) << car->getVolume() << car->getCost() << "\n";
	}
	std::cout << "0 - Отмена\n>";
	int selCar = Selected(park.size() + 1);
	if (!selCar)
		return;

	double sum = 0;
	if (park[selCar - 1])
	{
		for (auto temp = park[selCar - 1]->get(); temp; temp = park[selCar - 1]->get())
		{
			if (typeid(*temp) == typeid(Ball))
			{
				storages[0]->items.push_back(temp);
				nTrue++;
				sum += temp->getCost();
			}
			else if (typeid(*temp) == typeid(TV))
			{
				storages[1]->items.push_back(temp);
				nTrue++;
				sum += temp->getCost();
			}
			else if (typeid(*temp) == typeid(Sugar))
			{
				storages[2]->items.push_back(temp);
				nTrue++;
				sum += temp->getCost();
			}
			else
				nFalse++;
		}
	}

	if (nFalse)
		std::cout << "Не удалось выгрузить" << nFalse << " ед. товара\n";
	else
		std::cout << "Выгружено " << nTrue << " ед. товара на сумму " << sum << "руб.\n";

	std::cin.get();
}

void MenuSelect(int n, std::vector<Car*>& park, std::vector<Storage*>& storages)
{
	switch (n)
	{
	case 1: return LoadCar(park, storages); break;
	case 2: return ReloadCar(park, storages); break;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	// Создание складов
	Storage storageBall;
	storageBall.name = "Склад мячей";
	Storage storageTV;
	storageTV.name = "Склад телевизоров";
	Storage storageSugar;
	storageSugar.name = "Склад сахара";
	// заполняем склады
	MakeStorages(storageBall, storageTV, storageSugar);

	// объединяем все склады в один большой склад
	std::vector<Storage*> storages;
	storages.push_back(&storageBall);
	storages.push_back(&storageTV);
	storages.push_back(&storageSugar);

	// Создание Машин
	std::vector<Car*>park;
	for (size_t i = 0; i < 5; i++)
	{
		park.push_back(new Car(20));
	}

	while (true)
	{
		MainMenu();
		int select = Selected(9);
		if (!select)
			break;

		MenuSelect(select, park, storages);
	}

	return 0;
}