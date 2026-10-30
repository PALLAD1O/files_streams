#include "UIElement.h"
#include <iostream>

UIElement::UIElement() : id(0), name(""), role("primary"), order(0) {}
UIElement::UIElement(int id, const string& name, const string& role, int order) : id(id), name(name), role(role), order(order) {}
UIElement::~UIElement() {}

int UIElement::getId() const { return id; }
string UIElement::getName() const { return name; }
string UIElement::getRole() const { return role; }
int UIElement::getOrder() const { return order; }
vector<UIRequirement*>& UIElement::getRequirements() { return requirements; }

void UIElement::setName(const string& n) { name = n; }
void UIElement::setRole(const string& r) { role = r; }
void UIElement::setOrder(int o) { order = o; }

void UIElement::addRequirement(UIRequirement* req) {
	if (req) requirements.push_back(req);
}

void UIElement::removeRequirement(int reqId) {
	for (auto it = requirements.begin(); it != requirements.end(); ++it) {
		if ((*it)->getId() == reqId) {
			requirements.erase(it);
			return;
		}
	}
}

void UIElement::print() const {
	cout << "    [Элемент] ID: " << id << " | " << name << " | Роль: " << role << " | Порядок: " << order << endl;
	if (requirements.empty()) {
		cout << "      (нет требований)" << endl;
	} else {
		for (auto req : requirements) req->print();
	}
}

void UIElement::save(ofstream& out) const {
	out << id << "\n" << name << "\n" << role << "\n" << order << "\n";
	out << requirements.size() << "\n";
	for (auto req : requirements) {
		out << req->getType() << "\n";
		req->save(out);
	}
}

ostream& operator<<(ostream& os, const UIElement& el) {
	os << el.id << " " << el.name << " " << el.role << " " << el.order;
	return os;
}

istream& operator>>(istream& is, UIElement& el) {
	is >> el.id >> el.name >> el.role >> el.order;
	return is;
}

Button::Button() : UIElement(), text("Button"), isEnabled(true) {}
Button::Button(int id, const string& name, const string& role, int order, const string& text, bool isEnabled) : UIElement(id, name, role, order), text(text), isEnabled(isEnabled) {}

int Button::getType() const { return 10; }

void Button::print() const {
	UIElement::print();
	cout << "      -> Кнопка | Текст: '" << text << "' | Активна: " << (isEnabled ? "Да" : "Нет") << endl;
}

void Button::save(ofstream& out) const {
	UIElement::save(out);
	out << text << "\n" << isEnabled << "\n";
}

void Button::load(ifstream& in) {
	in >> id;
	in.ignore();
	getline(in, name);
	getline(in, role);
	in >> order;
	in.ignore();

	requirements.clear();
	size_t count;
	in >> count;
	in.ignore();
	for (size_t i = 0; i < count; ++i) {
		int type;
		in >> type;
		in.ignore();
		UIRequirement* req = nullptr;
		if (type == 1) { auto* r = new ColorRequirement(); r->load(in); req = r; } else if (type == 2) { auto* r = new TypographyRequirement(); r->load(in); req = r; } else if (type == 3) { auto* r = new SpacingRequirement(); r->load(in); req = r; }
		if (req) requirements.push_back(req);
	}

	getline(in, text);
	in >> isEnabled;
	in.ignore();
}

bool Button::editField(const string& field, const string& value) {
	if (field == "text") { text = value; return true; }
	if (field == "enabled") { isEnabled = (value == "1" || value == "true"); return true; }
	return false;
}

ostream& operator<<(ostream& os, const Button& b) {
	os << static_cast<const UIElement&>(b) << " " << b.text << " " << b.isEnabled;
	return os;
}

istream& operator>>(istream& is, Button& b) {
	is >> static_cast<UIElement&>(b) >> b.text >> b.isEnabled;
	return is;
}

InputField::InputField() : UIElement(), placeholder("..."), maxLength(50) {}
InputField::InputField(int id, const string& name, const string& role, int order,const string& placeholder, int maxLength) : UIElement(id, name, role, order), placeholder(placeholder), maxLength(maxLength) {}

int InputField::getType() const { return 11; }

void InputField::print() const {
	UIElement::print();
	cout << "      -> Поле ввода | Подсказка: '" << placeholder << "' | Макс. длина: " << maxLength << endl;
}

void InputField::save(ofstream& out) const {
	UIElement::save(out);
	out << placeholder << "\n" << maxLength << "\n";
}

void InputField::load(ifstream& in) {
	in >> id;
	in.ignore();
	getline(in, name);
	getline(in, role);
	in >> order;
	in.ignore();

	requirements.clear();
	size_t count;
	in >> count;
	in.ignore();
	for (size_t i = 0; i < count; ++i) {
		int type;
		in >> type;
		in.ignore();
		UIRequirement* req = nullptr;
		if (type == 1) { auto* r = new ColorRequirement(); r->load(in); req = r; } else if (type == 2) { auto* r = new TypographyRequirement(); r->load(in); req = r; } else if (type == 3) { auto* r = new SpacingRequirement(); r->load(in); req = r; }
		if (req) requirements.push_back(req);
	}

	getline(in, placeholder);
	in >> maxLength;
	in.ignore();
}

bool InputField::editField(const string& field, const string& value) {
	if (field == "placeholder") { placeholder = value; return true; }
	if (field == "maxLength") { maxLength = stoi(value); return true; }
	return false;
}

ostream& operator<<(ostream& os, const InputField& f) {
	os << static_cast<const UIElement&>(f) << " " << f.placeholder << " " << f.maxLength;
	return os;
}

istream& operator>>(istream& is, InputField& f) {
	is >> static_cast<UIElement&>(f) >> f.placeholder >> f.maxLength;
	return is;
}

CheckBox::CheckBox() : UIElement(), label("Check"), isChecked(false) {}
CheckBox::CheckBox(int id, const string& name, const string& role, int order, const string& label, bool isChecked) : UIElement(id, name, role, order), label(label), isChecked(isChecked) {}

int CheckBox::getType() const { return 12; }

void CheckBox::print() const {
	UIElement::print();
	cout << "      -> Флажок | Метка: '" << label << "' | Отмечен: " << (isChecked ? "Да" : "Нет") << endl;
}

void CheckBox::save(ofstream& out) const {
	UIElement::save(out);
	out << label << "\n" << isChecked << "\n";
}

void CheckBox::load(ifstream& in) {
	in >> id;
	in.ignore();
	getline(in, name);
	getline(in, role);
	in >> order;
	in.ignore();

	requirements.clear();
	size_t count;
	in >> count;
	in.ignore();
	for (size_t i = 0; i < count; ++i) {
		int type;
		in >> type;
		in.ignore();
		UIRequirement* req = nullptr;
		if (type == 1) { auto* r = new ColorRequirement(); r->load(in); req = r; } else if (type == 2) { auto* r = new TypographyRequirement(); r->load(in); req = r; } else if (type == 3) { auto* r = new SpacingRequirement(); r->load(in); req = r; }
		if (req) requirements.push_back(req);
	}

	getline(in, label);
	in >> isChecked;
	in.ignore();
}

bool CheckBox::editField(const string& field, const string& value) {
	if (field == "label") { label = value; return true; }
	if (field == "checked") { isChecked = (value == "1" || value == "true"); return true; }
	return false;
}

ostream& operator<<(ostream& os, const CheckBox& c) {
	os << static_cast<const UIElement&>(c) << " " << c.label << " " << c.isChecked;
	return os;
}

istream& operator>>(istream& is, CheckBox& c) {
	is >> static_cast<UIElement&>(c) >> c.label >> c.isChecked;
	return is;
}