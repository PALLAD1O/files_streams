#include "RequirementLibrary.h"
#include <iostream>
#include <algorithm>
#include <cctype>

static string toLower(const string& s) {
	string r = s;
	transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return tolower(c); });
	return r;
}

RequirementLibrary::RequirementLibrary() : nextId(1) {}
RequirementLibrary::~RequirementLibrary() {
	for (auto r : requirements) delete r;
	requirements.clear();
}

UIRequirement* RequirementLibrary::createColor(const string& name, int priority,
	const string& token, const string& usage) {
	auto* r = new ColorRequirement(nextId++, name, priority, token, usage);
	requirements.push_back(r);
	return r;
}

UIRequirement* RequirementLibrary::createTypography(const string& name, int priority, const string& token, const string& weight) {
	auto* r = new TypographyRequirement(nextId++, name, priority, token, weight);
	requirements.push_back(r);
	return r;
}

UIRequirement* RequirementLibrary::createSpacing(const string& name, int priority, const string& token) {
	auto* r = new SpacingRequirement(nextId++, name, priority, token);
	requirements.push_back(r);
	return r;
}

UIRequirement* RequirementLibrary::findById(int id) {
	for (auto r : requirements) if (r->getId() == id) return r;
	return nullptr;
}

UIRequirement* RequirementLibrary::findByName(const string& name) {
	string q = toLower(name);
	for (auto r : requirements) if (toLower(r->getName()).find(q) != string::npos) return r;
	return nullptr;
}

bool RequirementLibrary::editName(int id, const string& newName) {
	UIRequirement* r = findById(id);
	if (!r) return false;
	r->setName(newName);
	return true;
}

bool RequirementLibrary::editPriority(int id, int newPriority) {
	UIRequirement* r = findById(id);
	if (!r) return false;
	r->setPriority(newPriority);
	return true;
}

bool RequirementLibrary::editColorToken(int id, const string& token) {
	auto* c = dynamic_cast<ColorRequirement*>(findById(id));
	if (!c) return false;
	c->setColorToken(token);
	return true;
}

bool RequirementLibrary::editColorUsage(int id, const string& usage) {
	auto* c = dynamic_cast<ColorRequirement*>(findById(id));
	if (!c) return false;
	c->setUsage(usage);
	return true;
}

bool RequirementLibrary::editTypographyToken(int id, const string& token) {
	auto* t = dynamic_cast<TypographyRequirement*>(findById(id));
	if (!t) return false;
	t->setTypographyToken(token);
	return true;
}

bool RequirementLibrary::editTypographyWeight(int id, const string& weight) {
	auto* t = dynamic_cast<TypographyRequirement*>(findById(id));
	if (!t) return false;
	t->setWeight(weight);
	return true;
}

bool RequirementLibrary::editSpacingToken(int id, const string& token) {
	auto* s = dynamic_cast<SpacingRequirement*>(findById(id));
	if (!s) return false;
	s->setSpacingToken(token);
	return true;
}

bool RequirementLibrary::removeRequirement(int id) {
	for (auto it = requirements.begin(); it != requirements.end(); ++it) {
		if ((*it)->getId() == id) {
			delete* it;
			requirements.erase(it);
			return true;
		}
	}
	return false;
}

void RequirementLibrary::printAll() const {
	cout << "=== Библиотека требований ===" << endl;
	if (requirements.empty()) {
		cout << "(пусто)" << endl;
		return;
	}
	for (auto r : requirements) r->print();
}

void RequirementLibrary::saveToFile(const string& filename) const {
	ofstream out(filename);
	if (!out.is_open()) {
		cerr << "Ошибка открытия файла!" << endl;
		return;
	}
	out << nextId << "\n";
	out << requirements.size() << "\n";
	for (auto r : requirements) {
		out << r->getType() << "\n";
		r->save(out);
	}
	out.close();
}

void RequirementLibrary::loadFromFile(const string& filename) {
	ifstream in(filename);
	if (!in.is_open()) {
		cerr << "Файл не найден: " << filename << endl;
		return;
	}
	for (auto r : requirements) delete r;
	requirements.clear();

	in >> nextId;
	size_t count;
	in >> count;
	in.ignore();
	for (size_t i = 0; i < count; ++i) {
		int type;
		in >> type;
		in.ignore();
		UIRequirement* r = nullptr;
		if (type == 1) { auto* c = new ColorRequirement(); c->load(in); r = c; } else if (type == 2) { auto* t = new TypographyRequirement(); t->load(in); r = t; } else if (type == 3) { auto* s = new SpacingRequirement(); s->load(in); r = s; }
		if (r) requirements.push_back(r);
	}
	in.close();
}

vector<UIRequirement*>& RequirementLibrary::getAll() { return requirements; }