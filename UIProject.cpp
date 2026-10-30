#include "UIProject.h"
#include <iostream>
#include <algorithm>
#include <cctype>

static string toLower(const string& s) {
	string r = s;
	transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return tolower(c); });
	return r;
}

UIProject::UIProject() : projectName("") {}
UIProject::UIProject(const string& projectName) : projectName(projectName) {}
UIProject::~UIProject() {
	for (auto p : pages) delete p;
	pages.clear();
}

string UIProject::getName() const { return projectName; }
vector<UIPage*>& UIProject::getPages() { return pages; }

void UIProject::addPage(UIPage* page) {
	if (page) pages.push_back(page);
}

void UIProject::print() const {
	cout << "=== Проект: " << projectName << " ===" << endl;
	for (auto p : pages) p->print();
}

void UIProject::saveToFile(const string& filename) const {
	ofstream out(filename);
	if (!out.is_open()) {
		cerr << "Ошибка открытия файла!" << endl;
		return;
	}
	out << projectName << "\n";
	out << pages.size() << "\n";
	for (auto p : pages) p->save(out);
	out.close();
	cout << "Проект сохранён.\n";
}

void UIProject::loadFromFile(const string& filename) {
	ifstream in(filename);
	if (!in.is_open()) {
		cerr << "Файл не найден: " << filename << endl;
		return;
	}
	getline(in, projectName);
	for (auto p : pages) delete p;
	pages.clear();

	size_t count;
	in >> count;
	in.ignore();
	for (size_t i = 0; i < count; ++i) {
		auto* page = new UIPage();
		page->load(in);
		pages.push_back(page);
	}
	in.close();
	cout << "Проект загружен.\n";
}

void UIProject::findElementsByName(const string& query) const {
	cout << "\n=== Поиск элементов: '" << query << "' ===" << endl;
	string q = toLower(query);
	bool found = false;
	for (auto page : pages) {
		for (auto el : page->getElements()) {
			if (toLower(el->getName()).find(q) != string::npos) {
				cout << "Страница: " << page->getName() << endl;
				el->print();
				found = true;
			}
		}
	}
	if (!found) cout << "Ничего не найдено.\n";
}

void UIProject::findRequirementsByPriority(int priority) const {
	cout << "\n=== Требования с приоритетом " << priority << " ===" << endl;
	bool found = false;
	for (auto page : pages) {
		for (auto el : page->getElements()) {
			for (auto req : el->getRequirements()) {
				if (req->getPriority() == priority) {
					cout << "Страница: " << page->getName() << " | Элемент: " << el->getName() << endl;
					req->print();
					found = true;
				}
			}
		}
	}
	if (!found) cout << "Ничего не найдено.\n";
}

void UIProject::filterElementsByRole(const string& role) const {
	cout << "\n=== Элементы с ролью '" << role << "' ===" << endl;
	bool found = false;
	for (auto page : pages) {
		for (auto el : page->getElements()) {
			if (el->getRole() == role) {
				cout << "Страница: " << page->getName() << endl;
				el->print();
				found = true;
			}
		}
	}
	if (!found) cout << "Ничего не найдено.\n";
}

void UIProject::filterRequirementsByType(int type) const {
	cout << "\n=== Требования типа " << type << " ===" << endl;
	bool found = false;
	for (auto page : pages) {
		for (auto el : page->getElements()) {
			for (auto req : el->getRequirements()) {
				if (req->getType() == type) {
					cout << "Страница: " << page->getName()
						<< " | Элемент: " << el->getName() << endl;
					req->print();
					found = true;
				}
			}
		}
	}
	if (!found) cout << "Ничего не найдено.\n";
}

void UIProject::filterElementsWithRequirements() const {
	cout << "\n=== Элементы с требованиями ===" << endl;
	bool found = false;
	for (auto page : pages) {
		for (auto el : page->getElements()) {
			if (!el->getRequirements().empty()) {
				cout << "Страница: " << page->getName() << endl;
				el->print();
				found = true;
			}
		}
	}
	if (!found) cout << "Ничего не найдено.\n";
}

void UIProject::printElementsSortedByName() const {
	cout << "\n=== Элементы по имени ===" << endl;
	for (auto page : pages) {
		vector<UIElement*> sorted = page->getElements();
		sort(sorted.begin(), sorted.end(),
			[](UIElement* a, UIElement* b) { return a->getName() < b->getName(); });
		cout << "Страница: " << page->getName() << endl;
		for (auto el : sorted) el->print();
	}
}

void UIProject::printElementsSortedByOrder() const {
	cout << "\n=== Элементы по порядку ===" << endl;
	for (auto page : pages) {
		vector<UIElement*> sorted = page->getElements();
		sort(sorted.begin(), sorted.end(),
			[](UIElement* a, UIElement* b) { return a->getOrder() < b->getOrder(); });
		cout << "Страница: " << page->getName() << endl;
		for (auto el : sorted) el->print();
	}
}

void UIProject::printElementsSortedByRole() const {
	cout << "\n=== Элементы по роли ===" << endl;
	for (auto page : pages) {
		vector<UIElement*> sorted = page->getElements();
		sort(sorted.begin(), sorted.end(),
			[](UIElement* a, UIElement* b) { return a->getRole() < b->getRole(); });
		cout << "Страница: " << page->getName() << endl;
		for (auto el : sorted) el->print();
	}
}

void UIProject::removeRequirementFromAllElements(int reqId) {
	for (auto page : pages) {
		page->removeRequirementFromAllElements(reqId);
	}
}

ostream& operator<<(ostream& os, const UIProject& p) {
	os << p.projectName << " " << p.pages.size();
	return os;
}

istream& operator>>(istream& is, UIProject& p) {
	is >> p.projectName;
	return is;
}