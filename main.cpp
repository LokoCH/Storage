#include<iostream>
#include<vector>
#include<typeinfo>
#include<iomanip>
#include "Item.h"
#include "Car.h"

// ���������� ��� ������������� id ������
int Car::countId = 0;

// ��������� ������, ���������� ��������(�������� "������ �����") � ������ ���������� �������
struct Storage
{
	std::string name{ "" };
	std::vector<Item*>items;
};

//////////////////////////// Prototypes
void MainMenu(); // ������� ��������� ������� ���� �� �����
int Selected(int n); // ������� ����������� � ������������ ����� ������������
void MakeStorages(Storage& storage1, Storage& storage2, Storage& storage3);
void LoadCar(std::vector<Car*>& park, std::vector<Storage*>& storages);
void ReloadCar(std::vector<Car*>& park, std::vector<Storage*>& storages);
///////////////////////////////

// ��������� ������ �������� (��� �����)
void MakeStorages(Storage& storage1, Storage& storage2, Storage& storage3)
{
	int count = 50; // ���������� ������� ���� ������ �� ������
	// ����
	for (size_t i = 0; i < count; i++)
	{
		storage1.items.push_back(new Ball("���������� ���", 3000, 15, "����"));
	}

	// ����������
	for (size_t i = 0; i < count; i++)
	{
		storage2.items.push_back(new TV("��������� Sony", 25000, 110, 20, 60, "LED"));
	}

	// �����
	for (size_t i = 0; i < count; i++)
	{
		storage3.items.push_back(new Sugar("�����", 750, 15));
	}
}

void MainMenu()
{
	system("cls");
	std::cout << "������� ����\n";
	std::cout << "1 - ��������� ����� � ������\n";
	std::cout << "2 - ���������� ������\n";
	std::cout << "0 - �����\n>";
}

int Selected(int n) // n - ���������� ��������� ������ � ����
{
	int select;
	while (!(std::cin >> select) || std::cin.peek() != '\n' || select < 0 || select > n - 1)
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "�������� ����\n>";
	}
	std::cin.ignore();

	return select;
}

void LoadCar(std::vector<Car*>& park, std::vector<Storage*>& storages)
{

	system("cls");
	std::cout << "�������� �����, � �������� ����� ������������� ��������\n";

	// ������� ������ �������
	int n = 0;
	for (auto& storage : storages)
	{
		++n;
		std::cout << n << " - " << storage->name << "\n";
	}
	std::cout << "0 - ������\n>";
	int selStorage = Selected(n + 1);
	if (!selStorage)
		return;

	// ���� ����� ����, �������
	if (storages[selStorage - 1]->items.empty())
	{
		std::cout << "����� ����\n";
		std::cin.get();
		return;
	}

	std::cout << storages[selStorage - 1]->items[0]->getName() << " " << storages[selStorage - 1]->items.size() << "\n";

	std::cout << "���������� ��� ��������: ";
	int count = Selected(storages[selStorage - 1]->items.size() + 1);

	system("cls");
	std::cout << "�������� ������:\n";
	int carIdx = 0;
	for (auto& car : park)
	{
		carIdx++;
		std::cout << carIdx << " - " << " ��������� " << car->getVolume() << " �� " << car->getCapacity() << " �� ����� " << car->getCost() << "\n";
	}
	std::cout << "0 - ������\n>";
	int selCar = Selected(park.size() + 1);
	if (!selCar)
		return;

	int countLoaded = 0; // ������� ����������� �������
	double sum = 0; // ��������� ������������ ������
	for (size_t i = 0; i < count; i++)
	{
		auto& temp = storages[selStorage - 1]->items.back();
		if (!park[selCar - 1]->put(temp))
			break;
		sum += temp->getCost();
		storages[selStorage - 1]->items.pop_back();
		++countLoaded;
	}

	std::cout << "��������� " << countLoaded << " ������ ������ �� ����� " << sum << "���.\n";
	std::cout << "������ " << park[selCar - 1]->getId() << " ��������� �� " << park[selCar - 1]->getVolume() << " �� " << park[selCar - 1]->getCapacity() << "\n";
	std::cin.get();
}

void ReloadCar(std::vector<Car*>& park, std::vector<Storage*>& storages)
{
	if (!park.size())
	{
		std::cout << "����� ���\n";
		return;
	}

	int nTrue = 0; // ������� ������������ ������
	int nFalse = 0; // ������� �������������� ������
	system("cls");
	std::cout << "����� ������ ����������?\n";
	int carIdx = 0;
	for (auto& car : park)
	{
		++carIdx;
		std::cout << std::setw(5) << std::left << "" << std::setw(15) << "����������"
			<< std::setw(20) << "���������(���.�.)" << std::setw(15) << "�����(���.)" << "\n";

		std::cout << std::setw(5) << carIdx << std::setw(15) << car->getItems().size()
			<< std::setw(20) << car->getVolume() << car->getCost() << "\n";
	}
	std::cout << "0 - ������\n>";
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
		std::cout << "�� ������� ���������" << nFalse << " ��. ������\n";
	else
		std::cout << "��������� " << nTrue << " ��. ������ �� ����� " << sum << "���.\n";

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

	// �������� �������
	Storage storageBall;
	storageBall.name = "����� �����";
	Storage storageTV;
	storageTV.name = "����� �����������";
	Storage storageSugar;
	storageSugar.name = "����� ������";
	// ��������� ������
	MakeStorages(storageBall, storageTV, storageSugar);

	// ���������� ��� ������ � ���� ������� �����
	std::vector<Storage*> storages;
	storages.push_back(&storageBall);
	storages.push_back(&storageTV);
	storages.push_back(&storageSugar);

	// �������� �����
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