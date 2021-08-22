#include "Item.h"
#include <typeinfo>

// ������������
// ��� m_type ������ �� ��������, ������ ��� ��� ���������� ������ Item ������ ��������� �� ������ ���.
// ���� ����� ���-�� ������ � ������ Type, ��� ������ ���������� �� ���� ����������� ������ Item
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

// �������


// ������ �������
void Item::showInfo()
{
	std::cout << "������������ ������: " << m_name << "\n";
	//std::cout << "���: " << m_type->getName() << "\n";
	//std::cout << "�����: " << m_type->getVol() << "���.�." << "\n";
	std::cout << "����: " << m_cost << "\n";
}