#include "eeprom.h"

void EEPROM_write(uint8_t uiAddress, uint8_t ucData)

{

	while(EECR & (1<<EEPE)) //���� ������������ ����� ��������� ��������� ��������� � �������

	{}

	EEAR = uiAddress; //������������� �����

	EEDR = ucData; //����� ������ � �������

	EECR |= (1<<EEMPE); //��������� ������

	EECR |= (1<<EEPE); //����� ���� � ������

}

uint8_t EEPROM_read(uint8_t uiAddress)

{

	while(EECR & (1<<EEPE))

	{} //���� ������������ ����� ��������� ��������� ��������� � �������

	EEAR = uiAddress; //������������� �����

	EECR |= (1<<EERE); //��������� �������� ���������� �� ������ � ������� ������

	return EEDR; //���������� ���������

}