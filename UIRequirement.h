#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class UIRequirement {
protected:
	int id;
	string name;
	int priority; // 1 - высокий, 2 - средний, 3 - низкий
public:
	UIRequirement();
	UIRequirement(int id, const string& name, int priority);
	virtual ~UIRequirement();

	int getId() const;
	string getName() const;
	int getPriority() const;

	void setName(const string& n);
	void setPriority(int p);

	virtual int getType() const = 0;
	virtual void print() const = 0;
	virtual void save(ofstream& out) const = 0;
	virtual void load(ifstream& in) = 0;

	friend ostream& operator<<(ostream& os, const UIRequirement& req);
	friend istream& operator>>(istream& is, UIRequirement& req);
};

class ColorRequirement : public UIRequirement {
	string colorToken;
	string usage;
public:
	ColorRequirement();
	ColorRequirement(int id, const string& name, int priority, const string& colorToken, const string& usage);

	void setColorToken(const string& t);
	void setUsage(const string& u);

	int getType() const override;
	void print() const override;
	void save(ofstream& out) const override;
	void load(ifstream& in) override;

	friend ostream& operator<<(ostream& os, const ColorRequirement& req);
	friend istream& operator>>(istream& is, ColorRequirement& req);
};

class TypographyRequirement : public UIRequirement {
	string typographyToken;
	string weight;
public:
	TypographyRequirement();
	TypographyRequirement(int id, const string& name, int priority, const string& typographyToken, const string& weight);

	void setTypographyToken(const string& t);
	void setWeight(const string& w);

	int getType() const override;
	void print() const override;
	void save(ofstream& out) const override;
	void load(ifstream& in) override;

	friend ostream& operator<<(ostream& os, const TypographyRequirement& req);
	friend istream& operator>>(istream& is, TypographyRequirement& req);
};

class SpacingRequirement : public UIRequirement {
	string spacingToken;
public:
	SpacingRequirement();
	SpacingRequirement(int id, const string& name, int priority, const string& spacingToken);

	void setSpacingToken(const string& t);

	int getType() const override;
	void print() const override;
	void save(ofstream& out) const override;
	void load(ifstream& in) override;

	friend ostream& operator<<(ostream& os, const SpacingRequirement& req);
	friend istream& operator>>(istream& is, SpacingRequirement& req);
};