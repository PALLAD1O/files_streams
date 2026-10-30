#include "UIRequirement.h"
#include <iostream>

UIRequirement::UIRequirement() : id(0), name(""), priority(1) {}
UIRequirement::UIRequirement(int id, const string& name, int priority) : id(id), name(name), priority(priority) {}
UIRequirement::~UIRequirement() {}

int UIRequirement::getId() const { return id; }
string UIRequirement::getName() const { return name; }
int UIRequirement::getPriority() const { return priority; }
void UIRequirement::setName(const string& n) { name = n; }
void UIRequirement::setPriority(int p) { priority = p; }

ostream& operator<<(ostream& os, const UIRequirement& req) {
	os << req.id << " " << req.name << " " << req.priority;
	return os;
}

istream& operator>>(istream& is, UIRequirement& req) {
	is >> req.id >> req.name >> req.priority;
	return is;
}

ColorRequirement::ColorRequirement() : UIRequirement(), colorToken("primary"), usage("background") {}
ColorRequirement::ColorRequirement(int id, const string& name, int priority, const string& colorToken, const string& usage) : UIRequirement(id, name, priority), colorToken(colorToken), usage(usage) {}

void ColorRequirement::setColorToken(const string& t) { colorToken = t; }
void ColorRequirement::setUsage(const string& u) { usage = u; }

int ColorRequirement::getType() const { return 1; }

void ColorRequirement::print() const {
	cout << "  [Цвет] ID: " << id << " | " << name << " | Приоритет: " << priority << " | Токен: " << colorToken << " | Использование: " << usage << endl;
}

void ColorRequirement::save(ofstream& out) const {
	out << id << "\n" << name << "\n" << priority << "\n" << colorToken << "\n" << usage << "\n";
}

void ColorRequirement::load(ifstream& in) {
	in >> id;
	in.ignore();
	getline(in, name);
	in >> priority;
	in.ignore();
	getline(in, colorToken);
	getline(in, usage);
}

ostream& operator<<(ostream& os, const ColorRequirement& req) {
	os << static_cast<const UIRequirement&>(req) << " " << req.colorToken << " " << req.usage;
	return os;
}

istream& operator>>(istream& is, ColorRequirement& req) {
	is >> static_cast<UIRequirement&>(req) >> req.colorToken >> req.usage;
	return is;
}

TypographyRequirement::TypographyRequirement() : UIRequirement(), typographyToken("body"), weight("regular") {}
TypographyRequirement::TypographyRequirement(int id, const string& name, int priority, const string& typographyToken, const string& weight) : UIRequirement(id, name, priority), typographyToken(typographyToken), weight(weight) {}

void TypographyRequirement::setTypographyToken(const string& t) { typographyToken = t; }
void TypographyRequirement::setWeight(const string& w) { weight = w; }

int TypographyRequirement::getType() const { return 2; }

void TypographyRequirement::print() const {
	cout << "  [Шрифт] ID: " << id << " | " << name << " | Приоритет: " << priority << " | Токен: " << typographyToken << " | Насыщенность: " << weight << endl;
}

void TypographyRequirement::save(ofstream& out) const {
	out << id << "\n" << name << "\n" << priority << "\n" << typographyToken << "\n" << weight << "\n";
}

void TypographyRequirement::load(ifstream& in) {
	in >> id;
	in.ignore();
	getline(in, name);
	in >> priority;
	in.ignore();
	getline(in, typographyToken);
	getline(in, weight);
}

ostream& operator<<(ostream& os, const TypographyRequirement& req) {
	os << static_cast<const UIRequirement&>(req) << " " << req.typographyToken << " " << req.weight;
	return os;
}

istream& operator>>(istream& is, TypographyRequirement& req) {
	is >> static_cast<UIRequirement&>(req) >> req.typographyToken >> req.weight;
	return is;
}

SpacingRequirement::SpacingRequirement() : UIRequirement(), spacingToken("medium") {}
SpacingRequirement::SpacingRequirement(int id, const string& name, int priority, const string& spacingToken) : UIRequirement(id, name, priority), spacingToken(spacingToken) {}

void SpacingRequirement::setSpacingToken(const string& t) { spacingToken = t; }

int SpacingRequirement::getType() const { return 3; }

void SpacingRequirement::print() const {
	cout << "  [Отступы] ID: " << id << " | " << name << " | Приоритет: " << priority << " | Токен: " << spacingToken << endl;
}

void SpacingRequirement::save(ofstream& out) const {
	out << id << "\n" << name << "\n" << priority << "\n" << spacingToken << "\n";
}

void SpacingRequirement::load(ifstream& in) {
	in >> id;
	in.ignore();
	getline(in, name);
	in >> priority;
	in.ignore();
	getline(in, spacingToken);
}

ostream& operator<<(ostream& os, const SpacingRequirement& req) {
	os << static_cast<const UIRequirement&>(req) << " " << req.spacingToken;
	return os;
}

istream& operator>>(istream& is, SpacingRequirement& req) {
	is >> static_cast<UIRequirement&>(req) >> req.spacingToken;
	return is;
}