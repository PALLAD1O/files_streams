#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "UIRequirement.h"

class UIElement {
protected:
	int id;
	string name;
	string role;
	int order;
	vector<UIRequirement*> requirements;
public:
	UIElement();
	UIElement(int id, const string& name, const string& role, int order);
	virtual ~UIElement();

	int getId() const;
	string getName() const;
	string getRole() const;
	int getOrder() const;
	vector<UIRequirement*>& getRequirements();

	void setName(const string& n);
	void setRole(const string& r);
	void setOrder(int o);

	void addRequirement(UIRequirement* req);
	void removeRequirement(int reqId);

	virtual int getType() const = 0;
	virtual void print() const;
	virtual void save(ofstream& out) const;
	virtual void load(ifstream& in) = 0;
	virtual bool editField(const string& field, const string& value) { return false; }

	friend ostream& operator<<(ostream& os, const UIElement& el);
	friend istream& operator>>(istream& is, UIElement& el);
};

class Button : public UIElement {
	string text;
	bool isEnabled;
public:
	Button();
	Button(int id, const string& name, const string& role, int order, const string& text, bool isEnabled);

	int getType() const override;
	void print() const override;
	void save(ofstream& out) const override;
	void load(ifstream& in) override;
	bool editField(const string& field, const string& value) override;

	friend ostream& operator<<(ostream& os, const Button& b);
	friend istream& operator>>(istream& is, Button& b);
};

class InputField : public UIElement {
	string placeholder;
	int maxLength;
public:
	InputField();
	InputField(int id, const string& name, const string& role, int order, const string& placeholder, int maxLength);

	int getType() const override;
	void print() const override;
	void save(ofstream& out) const override;
	void load(ifstream& in) override;
	bool editField(const string& field, const string& value) override;

	friend ostream& operator<<(ostream& os, const InputField& f);
	friend istream& operator>>(istream& is, InputField& f);
};

class CheckBox : public UIElement {
	string label;
	bool isChecked;
public:
	CheckBox();
	CheckBox(int id, const string& name, const string& role, int order, const string& label, bool isChecked);

	int getType() const override;
	void print() const override;
	void save(ofstream& out) const override;
	void load(ifstream& in) override;
	bool editField(const string& field, const string& value) override;

	friend ostream& operator<<(ostream& os, const CheckBox& c);
	friend istream& operator>>(istream& is, CheckBox& c);
};