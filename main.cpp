/* На основе разработанной иерархии классов, реализованной в лабораторной работе «Использование потоков ввода/вывода данных», необходимо реализовать программу
для работы с данными, используя потоки ФАЙЛОВОГО ввода-вывода. Необходимо реализовать в приложении следующие функции:
1. добавления данных в файл,
2. удаления данных из файла,
3. редактирования данных в файле,
4. просмотра данных файла,
5. поиска данных по необходимым параметрам в файле.
Обязательно использовать функции open(), is_open(), bad(), good(), close(), eof(), fail(), seekg(), seekp(), tellg(),
перегрузить операторы вывода в поток << и считывания из потока >>.
Разработать набор классов (минимум 5 классов, связи между классами: агрегация, композиция, наследование) по предметной области «User Interface (UI)».
Функционал программы должен позволить указать перечень требований к пользовательскому интерфейсу. */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include "UIProject.h"
#include "RequirementLibrary.h"
using namespace std;
bool fileExists(const string& filename) {
	ifstream f(filename);
	return f.good();
}
int mainMenu() {
	int sw;
	cout << "Меню:\n";
	cout << "\t1. Библиотека требований;\n";
	cout << "\t2. Проект;\n";
	cout << "\t3. Сохранить всё;\n";
	cout << "\t4. Удалить требование (из библиотеки и всех элементов);\n";
	cout << "\t0. Выход из программы.\n";
	cout << "Ваш выбор: ";
	while (!(cin >> sw) || sw < 0 || sw > 4) {
		cout << "Введено не верное значение, повторите попытку: \n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return sw;
}
int requirementMenu() {
	int sw;
	cout << "Меню:\n";
	cout << "\t1. Показать всё\n";
	cout << "\t2. Добавить требование к цвету\n";
	cout << "\t3. Добавить требование к шрифту\n";
	cout << "\t4. Добавить требование к отступам\n";
	cout << "\t5. Найти по имени\n";
	cout << "\t6. Редактировать требование\n";
	cout << "\t7. Удалить требование\n";
	cout << "\t0. Назад\n";
	cout << "Ваш выбор: ";
	while (!(cin >> sw) || sw < 0 || sw > 7) {
		cout << "Введено не верное значение, повторите попытку: \n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return sw;
}
int searchMenu() {
	int sw;
	cout << "Поиск:\n";
	cout << "\t1. По имени\n";
	cout << "\t2. По приоритету\n";
	cout << "\t0. Назад\n";
	cout << "Ваш выбор: ";
	while (!(cin >> sw) || sw < 0 || sw > 2) {
		cout << "Введено не верное значение, повторите попытку: \n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return sw;
}
int filterMenu() {
	int sw;
	cout << "Фильтрация:\n";
	cout << "\t1. Элементы по роли\n";
	cout << "\t2. Требования по типу\n";
	cout << "\t3. Элементы с требованиями\n";
	cout << "\t0. Назад\n";
	cout << "Ваш выбор: ";
	while (!(cin >> sw) || sw < 0 || sw > 3) {
		cout << "Введено не верное значение, повторите попытку: \n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return sw;
}
int sortMenu() {
	int sw;
	cout << "Сортировка:\n";
	cout << "\t1. По имени\n";
	cout << "\t2. По порядку\n";
	cout << "\t3. По роли\n";
	cout << "\t0. Назад\n";
	cout << "Ваш выбор: ";
	while (!(cin >> sw) || sw < 0 || sw > 3) {
		cout << "Введено не верное значение, повторите попытку: \n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return sw;
}
int redMenu() {
	int sw;
	cout << "Редактировать:\n";
	cout << "\t1. Добавить требования к элементу\n";
	cout << "\t2. Удалить требования элемента\n";
	cout << "\t3. Редактировать поля элемента\n";
	cout << "\t0. Назад\n";
	cout << "Ваш выбор: ";
	while (!(cin >> sw) || sw < 0 || sw > 3) {
		cout << "Введено не верное значение, повторите попытку: \n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return sw;
}
int projectMenu() {
	int sw;
	cout << "\t1. Показать проект\n";
	cout << "\t2. Добавить страницу\n";
	cout << "\t3. Добавить элемент\n";
	cout << "\t4. Удалить элемент\n";
	cout << "\t5. Редактировать элемент\n";
	cout << "\t6. Поиск\n";
	cout << "\t7. Фильтрация\n";
	cout << "\t8. Сортировка\n";
	cout << "\t0. Назад\n";
	cout << "Ваш выбор: ";
	while (!(cin >> sw) || sw < 0 || sw > 8) {
		cout << "Введено не верное значение, повторите попытку: \n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return sw;
}
int main() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	const string libFile = "library.txt";
	const string projFile = "project.txt";
	RequirementLibrary lib;
	if (fileExists(libFile)) lib.loadFromFile(libFile);
	else lib.saveToFile(libFile);
	UIProject project("Мой проект");
	if (fileExists(projFile)) project.loadFromFile(projFile);
	else project.saveToFile(projFile);
	while (true) {
		system("cls");
		switch (mainMenu()) {
		case 1: {
			bool cont = true;
			while (cont) {
				system("cls");
				switch (requirementMenu()) {
				case 1:
				{
					lib.printAll();
					_getch();
					break;
				}
				case 2:
				{
					string name, token, usage;
					int priority;
					cout << "Введите название: ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, name);
					cout << "Введите приоритет (1-3): ";
					while (!(cin >> priority) || priority < 1 || priority > 3) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					cout << "Введите токен (primary/secondary/danger): ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, token);
					cout << "Введите вариант использования (background/text/border): ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, usage);
					lib.createColor(name, priority, token, usage);
					break;
				}
				case 3:
				{
					string name, token, weight;
					int priority;
					cout << "Введите название: ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, name);
					cout << "Введите приоритет (1-3): ";
					while (!(cin >> priority) || priority < 1 || priority > 3) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					cout << "Введите токен (heading-1/body/caption): ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, token);
					cout << "Насыщенность (bold/regular/light): ";
					if (cin.peek() == '\n') cin.ignore(); 
					getline(cin, weight);
					lib.createTypography(name, priority, token, weight);
					break;
				}
				case 4:
				{
					string name, token;
					int priority;
					cout << "Введите название: ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, name);
					cout << "Введите приоритет (1-3): ";
					while (!(cin >> priority) || priority < 1 || priority > 3) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					cout << "Введите токен (small/medium/large): ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, token);
					lib.createSpacing(name, priority, token);
					break;
				}
				case 5:
				{
					string name;
					cout << "Введите имя для поиска: "; 
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, name);
					UIRequirement* r = lib.findByName(name);
					if (r) r->print();
					else cout << "По вашему запросу ничего не найдено.\n";
					_getch();
					break;
				}
				case 6:
				{
					int id;
					cout << "Введите ID требования: ";
					cin >> id;
					UIRequirement* r = lib.findById(id);
					if (!r) { 
						cout << "По вашему запросу ничего не найдено.\n";
						continue;
					}
					cout << "Что редактировать?\n\t1. Название\n\t2. Приоритет\n";
					if (r->getType() == 1) cout << "\t3. Цветовой токен\n\t4. Использование\n";
					if (r->getType() == 2) cout << "\t3. Токен типографики\n\t4. Насыщенность\n";
					if (r->getType() == 3) cout << "\t3. Токен отступов\n";
					cout << "Ваш выбор: ";
					int sw;
					if (r->getType() == 3) {
						while (!(cin >> sw) || sw < 1 || sw > 3) {
							cout << "Введено не верное значение, повторите попытку: \n";
							cin.clear();
							cin.ignore(1000, '\n');
						}
					}
					else {
						while (!(cin >> sw) || sw < 1 || sw > 4) {
							cout << "Введено не верное значение, повторите попытку: \n";
							cin.clear();
							cin.ignore(1000, '\n');
						}
					}
					string v;
					if (sw == 1) {
						cout << "Введите новое имя: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, v);
						lib.editName(id, v);
					}
					else if (sw == 2) {
						int p;
						cout << "Введите новый приоритет: ";
						cin >> p;
						lib.editPriority(id, p);
					}
					else if (sw == 3 && r->getType() == 1) {
						cout << "Введите новый токен: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, v);
						lib.editColorToken(id, v);
					}
					else if (sw == 4 && r->getType() == 1) {
						cout << "Введите новый вариант использования: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, v);
						lib.editColorUsage(id, v);
					}
					else if (sw == 3 && r->getType() == 2) {
						cout << "Введите новый токен: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, v);
						lib.editTypographyToken(id, v);
					}
					else if (sw == 4 && r->getType() == 2) {
						cout << "Введите новую насыщенность: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, v);
						lib.editTypographyWeight(id, v);
					}
					else if (sw == 3 && r->getType() == 3) {
						cout << "Введите новый токен: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, v);
						lib.editSpacingToken(id, v);
					}
					_getch();
					break;
				}
				case 7:
				{
					int id;
					cout << "Введите ID для удаления: ";
					cin >> id;
					if (lib.removeRequirement(id)) cout << "Удалено.\n";
					else cout << "Не найдено.\n";
					_getch();
					break;
				}
				case 0:
				{
					cont = false;
					break;
				}
				}
			}
			break;
		}
		case 2: {
			bool cont = true;
			while (cont) {
				system("cls");
				switch (projectMenu()) {
				case 1:
				{
					project.print();
					_getch();
					break;
				}
				case 2:
				{
					string name;
					cout << "Введите название страницы: ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, name);
					project.addPage(new UIPage(name));
					break;
				}
				case 3:
				{
					if (project.getPages().empty()) {
						cout << "Ни одной страницы пока не создано.\n";
						break;
					}
					for (int i = 0; i < project.getPages().size(); ++i) cout << i << ". " << project.getPages()[i]->getName() << "\n";
					int idx;
					cout << "Страница: ";
					while (!(cin >> idx) || idx < 0 || idx >= project.getPages().size()) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					int type;
					cout << "Введите тип (1-Кнопка, 2-Поле, 3-Флажок): ";
					while (!(cin >> type) || type < 1 || type > 3) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					int id, order;
					string name, role;
					cout << " Введите ID: ";
					while (!(cin >> id)) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					cout << "Введите имя: ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, name);
					cout << "Введите роль (primary/secondary/navigation): ";
					if (cin.peek() == '\n') cin.ignore();
					getline(cin, role);
					cout << "Введите порядок: ";
					while (!(cin >> order)) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					UIElement* el = nullptr;
					if (type == 1) {
						string text;
						bool en;
						cout << "Введите текст на кнопке: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, text);
						cout << "Активна (1/0): ";
						while (!(cin >> en) || en < 0 || en > 1) {
							cout << "Введено не верное значение, повторите попытку: \n";
							cin.clear();
							cin.ignore(1000, '\n');
						}
						el = new Button(id, name, role, order, text, en);
					} else if (type == 2) {
						string ph;
						int ml;
						cout << "Подсказка: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, ph);
						cout << "Введите макс. длину символов: ";
						while (!(cin >> ml) || ml < 1) {
							cout << "Введено не верное значение, повторите попытку: \n";
							cin.clear();
							cin.ignore(1000, '\n');
						}
						el = new InputField(id, name, role, order, ph, ml);
					} else if (type == 3) {
						string label;
						bool ch;
						cout << "Метка: ";
						if (cin.peek() == '\n') cin.ignore();
						getline(cin, label);
						cout << "Отмечен (1/0): ";
						if (!(cin >> ch) || ch < 0 || ch > 1) {
							cout << "Введено не верное значение, повторите попытку: \n";
							cin.clear();
							cin.ignore(1000, '\n');
						}
						el = new CheckBox(id, name, role, order, label, ch);
					}
					if (el) project.getPages()[idx]->addElement(el);
					break;
				}
				case 4:
				{
					if (project.getPages().empty()) {
						cout << "Ни одной страницы не создано.\n";
						break;
					}
					for (int i = 0; i < project.getPages().size(); ++i) cout << i << ". " << project.getPages()[i]->getName() << "\n";
					int idx;
					cout << "Страница: ";
					while (!(cin >> idx) || idx < 0 || idx >= project.getPages().size()) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					int id;
					cout << "ID элемента: ";
					while (!(cin >> id)) {
						cout << "Введено не верное значение, повторите попытку: \n";
						cin.clear();
						cin.ignore(1000, '\n');
					}
					if (project.getPages()[idx]->removeElement(id)) cout << "Удалено.\n";
					else cout << "Такого элемента не найдено.\n";
					_getch();
					break;
				}
				case 5:
				{
					bool cont2 = true;
					while (cont2) {
						system("cls");
						switch (redMenu()) {
						case 1:
						{
							if (project.getPages().empty()) { cout << "Нет страниц.\n"; break; }
							for (int i = 0; i < project.getPages().size(); ++i)
								cout << i << ". " << project.getPages()[i]->getName() << "\n";
							int idx; cout << "Страница: "; cin >> idx; cin.ignore();
							if (idx >= project.getPages().size()) { cout << "Неверно.\n"; break; }

							auto& elements = project.getPages()[idx]->getElements();
							if (elements.empty()) { cout << "Нет элементов.\n"; break; }
							for (int i = 0; i < elements.size(); ++i)
								cout << i << ". " << elements[i]->getName() << "\n";
							int eidx;
							cout << "Элемент: ";
							cin >> eidx;
							cin.ignore();
							if (eidx >= elements.size()) { cout << "Неверно.\n"; break; }

							lib.printAll();
							int reqId;
							cout << "ID требования: "; cin >> reqId; cin.ignore();
							UIRequirement* r = lib.findById(reqId);
							if (r) { elements[eidx]->addRequirement(r); cout << "Привязано.\n"; } else cout << "Не найдено.\n";
							_getch();
							break;
						}
						case 2:
						{
							if (project.getPages().empty()) { cout << "Нет страниц.\n"; break; }
							for (int i = 0; i < project.getPages().size(); ++i)
								cout << i << ". " << project.getPages()[i]->getName() << "\n";
							int idx; cout << "Страница: "; cin >> idx; cin.ignore();
							if (idx >= project.getPages().size()) { cout << "Неверно.\n"; break; }
							int elId, reqId;
							cout << "ID элемента: "; cin >> elId; cin.ignore();
							cout << "ID требования: "; cin >> reqId; cin.ignore();
							if (project.getPages()[idx]->removeRequirementFromElement(elId, reqId))
								cout << "Удалено из элемента.\n";
							else cout << "Не найдено.\n";
							_getch();
							break;
						}
						case 3:
						{
							if (project.getPages().empty()) { cout << "Нет страниц.\n"; break; }
							for (int i = 0; i < project.getPages().size(); ++i)
								cout << i << ". " << project.getPages()[i]->getName() << "\n";
							int idx; cout << "Страница: "; cin >> idx; cin.ignore();
							if (idx >= project.getPages().size()) { cout << "Неверно.\n"; break; }

							auto& elements = project.getPages()[idx]->getElements();
							if (elements.empty()) { cout << "Нет элементов.\n"; break; }
							for (int i = 0; i < elements.size(); ++i)
								cout << i << ". " << elements[i]->getName() << "\n";
							int eidx; cout << "Элемент: "; cin >> eidx; cin.ignore();
							if (eidx >= elements.size()) { cout << "Неверно.\n"; break; }

							cout << "Поля: имя, роль, порядок";
							int t = elements[eidx]->getType();
							if (t == 10) cout << ", текст, активна";
							else if (t == 11) cout << ", подсказка, длина";
							else if (t == 12) cout << ", метка, отмечен";
							cout << "\nПоле: ";
							string field; getline(cin, field);
							cout << "Новое значение: ";
							string value; getline(cin, value);
							if (field == "имя") { elements[eidx]->setName(value); cout << "Готово.\n"; } else if (field == "роль") { elements[eidx]->setRole(value); cout << "Готово.\n"; } else if (field == "порядок") { elements[eidx]->setOrder(stoi(value)); cout << "Готово.\n"; } else if (elements[eidx]->editField(field, value)) cout << "Готово.\n";
							else cout << "Неизвестное поле.\n";
							_getch();
							break;
						}
						case 0:
						{
							cont2 = false;
							break;
						}
						}
					}
					break;
				}
				case 6:
				{
					bool cont2 = true;
					while (cont2) {
						switch (searchMenu()) {
						case 1:
						{
							string q; cout << "Введите имя: ";
							if (cin.peek() == '\n') cin.ignore();
							getline(cin, q);
							project.findElementsByName(q);
							_getch();
							break;
						}
						case 2:
						{
							int p;
							cout << "Введите приоритет (1-3): ";
							while (!(cin >> p) || p < 1 || p > 3) {
								cout << "Введено не верное значение, повторите попытку: \n";
								cin.clear();
								cin.ignore(1000, '\n');
							}
							project.findRequirementsByPriority(p);
							_getch();
							break;
						}
						case 0:
						{
							cont2 = false;
							break;
						}
						}
					}
					break;
				}
				case 7:
				{
					bool cont2 = true;
					while (cont2) {
						switch (filterMenu()) {
						case 1:
						{
							string r;
							cout << "Введите роль: ";
							if (cin.peek() == '\n') cin.ignore();
							getline(cin, r);
							project.filterElementsByRole(r);
							_getch();
							break;
						}
						case 2:
						{
							int t;
							cout << "Введите тип (1/2/3): ";
							while (!(cin >> t) || t < 1 || t > 3) {
								cout << "Введено не верное значение, повторите попытку: \n";
								cin.clear();
								cin.ignore(1000, '\n');
							}
							project.filterRequirementsByType(t);
							_getch();
							break;
						}
						case 3:
						{
							project.filterElementsWithRequirements();
							_getch();
							break;
						}
						case 0:
						{
							cont2 = false;
							break;
						}
						}
					}
					break;
				}
				case 8:
				{
					bool cont2 = true;
					while (cont2) {
						switch (sortMenu()) {
						case 1:
						{
							project.printElementsSortedByName();
							_getch();
							break;
						}
						case 2:
						{
							project.printElementsSortedByOrder();
							_getch();
							break;
						}
						case 3:
						{
							project.printElementsSortedByRole();
							_getch();
							break;
						}
						case 0:
						{
							cont2 = false;
							break;
						}
						}
					}
					break;
				}
				case 0:
				{
					cont = false;
					break;
				}
				}
			}
			break;
		}
		case 3: {
			lib.saveToFile(libFile);
			project.saveToFile(projFile);
			cout << "Файлы обновлены!\n";
			break;
		}
		case 4: {
			int id;
			cout << "Введите ID требования: ";
			cin >> id;
			project.removeRequirementFromAllElements(id);
			if (lib.removeRequirement(id)) cout << "Удалено.\n";
			else cout << "Не найдено в библиотеке.\n";
			_getch();
			break;
		}
		case 0: {
			lib.saveToFile(libFile);
			project.saveToFile(projFile);
			cout << "Программа завершена!";
			return 0;
		}
		}
	}
}