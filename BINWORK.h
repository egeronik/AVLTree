#pragma once
#ifndef BINWORK
#define BINWORK
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


struct record {
	int key = 0;
	char data[20];
};
/// <summary>
/// Создание бинарного файла на базе текстового
/// </summary>
/// <param name="nametf">Имя текстового файла</param>
/// <param name="namebf">Имя бинарного файла который будет создан</param>
/// <returns></returns>
int CreateBinFile(string nametf, string namebf);

/// <summary>
/// Парсинг бинарного файла
/// </summary>
/// <param name="namebf">Имя файла</param>
/// <returns>Вектор всей информации из бинарника</returns>
vector<record> outBinFile(string namebf);

/// <summary>
/// Чтение одной записи из бинарника
/// </summary>
/// <param name="namebf">Имя файла</param>
/// <param name="pos">Номер строки начиная с 0</param>
/// <returns>Запись</returns>
record readRecordFromBin(string namebf, int pos);

/// <summary>
/// Удаление записи
/// </summary>
/// <param name="namebf">Имя файла</param>
/// <param name="pos">Позиция записи начиная с 0</param>
void deleteRecord(string namebf, int pos);

/// <summary>
/// Добавление записи в файл
/// </summary>
/// <param name="namebf">Имя бинарного файла</param>
/// <param name="r">Запись необходимая для добавления</param>
void addRecord(string namebf, record r);
#endif // !BINWORK
