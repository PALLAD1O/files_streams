#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "UIRequirement.h"

class RequirementLibrary {
	vector<UIRequirement*> requirements;
	int nextId;
public:
	RequirementLibrary();
	~RequirementLibrary();

	UIRequirement* createColor(const string& name, int priority, const string& token, const string& usage);
	UIRequirement* createTypography(const string& name, int priority, const string& token, const string& weight);
	UIRequirement* createSpacing(const string& name, int priority, const string& token);

	UIRequirement* findById(int id);
	UIRequirement* findByName(const string& name);

	bool editName(int id, const string& newName);
	bool editPriority(int id, int newPriority);
	bool editColorToken(int id, const string& token);
	bool editColorUsage(int id, const string& usage);
	bool editTypographyToken(int id, const string& token);
	bool editTypographyWeight(int id, const string& weight);
	bool editSpacingToken(int id, const string& token);

	bool removeRequirement(int id);

	void printAll() const;
	void saveToFile(const string& filename) const;
	void loadFromFile(const string& filename);

	vector<UIRequirement*>& getAll();
};