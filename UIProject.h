#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "UIPage.h"
#include "RequirementLibrary.h"

class UIProject {
	string projectName;
	vector<UIPage*> pages;
public:
	UIProject();
	UIProject(const string& projectName);
	~UIProject();

	string getName() const;
	vector<UIPage*>& getPages();

	void addPage(UIPage* page);
	void print() const;

	void saveToFile(const string& filename) const;
	void loadFromFile(const string& filename);

	void findElementsByName(const string& query) const;
	void findRequirementsByPriority(int priority) const;

	void filterElementsByRole(const string& role) const;
	void filterRequirementsByType(int type) const;
	void filterElementsWithRequirements() const;

	void printElementsSortedByName() const;
	void printElementsSortedByOrder() const;
	void printElementsSortedByRole() const;

	void removeRequirementFromAllElements(int reqId);

	friend ostream& operator<<(ostream& os, const UIProject& p);
	friend istream& operator>>(istream& is, UIProject& p);
};