// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.MaxPower)
{
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)  
{
}

TSet::operator TBitField()      //ПОСМОТРЕТЬ
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 && Elem >= MaxPower) throw 1;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 && Elem >= MaxPower) throw 1;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower) return 0;
	if (BitField == s.BitField)  return 1;
	else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower) return 1;
	if (BitField != s.BitField)
		return 1;
	else
		return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet res(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
	res.BitField = BitField | s.BitField;
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	//if (Elem < 0 && Elem >= MaxPower)
	//{
		//throw "Wrong data";
	//}

	if (Elem < 0 && Elem >= MaxPower) throw 1;
	TSet res(MaxPower);
	res.BitField.SetBit(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	//if (Elem > MaxPower)
	//{
		//throw "Wrong data";
	//}
	//else
	if (Elem < 0 && Elem >= MaxPower) throw 1;
	TSet res(*this);
	res.BitField.ClrBit(Elem);
	return res;
	
}

TSet TSet::operator*(const TSet &s) // пересечение !!!!!!!!!!!!!!1
{
	int size = MaxPower > s.MaxPower ? MaxPower : s.MaxPower;
	TSet res(size);
	res.BitField = BitField & s.BitField;
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
