#include "UIPage.h"
#include <iostream>

UIPage::UIPage() : pageName("") {}
UIPage::UIPage(const string& pageName) : pageName(pageName) {}
UIPage::~UIPage() {
    for (auto el : elements) delete el;
    elements.clear();
}

string UIPage::getName() const { return pageName; }
vector<UIElement*>& UIPage::getElements() { return elements; }

void UIPage::addElement(UIElement* el) {
    if (el) elements.push_back(el);
}

bool UIPage::removeElement(int id) {
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        if ((*it)->getId() == id) {
            delete* it;
            elements.erase(it);
            return true;
        }
    }
    return false;
}

UIElement* UIPage::findElement(int id) {
    for (auto el : elements) {
        if (el->getId() == id) return el;
    }
    return nullptr;
}

bool UIPage::removeRequirementFromElement(int elementId, int reqId) {
    UIElement* el = findElement(elementId);
    if (!el) return false;
    el->removeRequirement(reqId);
    return true;
}

void UIPage::removeRequirementFromAllElements(int reqId) {
    for (auto el : elements) {
        el->removeRequirement(reqId);
    }
}

void UIPage::print() const {
    cout << "  === Страница: " << pageName << " ===" << endl;
    if (elements.empty()) {
        cout << "    (нет элементов)" << endl;
    } else {
        for (auto el : elements) el->print();
    }
}

void UIPage::save(ofstream& out) const {
    out << pageName << "\n";
    out << elements.size() << "\n";
    for (auto el : elements) {
        out << el->getType() << "\n";
        el->save(out);
    }
}

void UIPage::load(ifstream& in) {
    getline(in, pageName);
    for (auto el : elements) delete el;
    elements.clear();

    size_t count;
    in >> count;
    in.ignore();
    for (size_t i = 0; i < count; ++i) {
        int type;
        in >> type;
        in.ignore();
        UIElement* el = nullptr;
        if (type == 10) { auto* b = new Button(); b->load(in); el = b; } else if (type == 11) { auto* f = new InputField(); f->load(in); el = f; } else if (type == 12) { auto* c = new CheckBox(); c->load(in); el = c; }
        if (el) elements.push_back(el);
    }
}

ostream& operator<<(ostream& os, const UIPage& p) {
    os << p.pageName << " " << p.elements.size();
    return os;
}

istream& operator>>(istream& is, UIPage& p) {
    is >> p.pageName;
    return is;
}