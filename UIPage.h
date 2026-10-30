#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "UIElement.h"

class UIPage {
    string pageName;
    vector<UIElement*> elements;
public:
    UIPage();
    UIPage(const string& pageName);
    ~UIPage();

    string getName() const;
    vector<UIElement*>& getElements();

    void addElement(UIElement* el);
    bool removeElement(int id);
    UIElement* findElement(int id);

    bool removeRequirementFromElement(int elementId, int reqId);
    void removeRequirementFromAllElements(int reqId);

    void print() const;
    void save(ofstream& out) const;
    void load(ifstream& in);

    friend ostream& operator<<(ostream& os, const UIPage& p);
    friend istream& operator>>(istream& is, UIPage& p);
};