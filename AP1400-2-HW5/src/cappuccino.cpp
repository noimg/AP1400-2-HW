#include "cappuccino.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino() : EspressoBased() {
    name = "Cappuccino";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino& cap) : EspressoBased(cap) {
    for (const auto& item : cap.side_items) {
        std::string iname = item->get_name();
        size_t units = item->get_units();
        
        if (iname == "Cinnamon") side_items.push_back(new Cinnamon(units));
        else if (iname == "Chocolate") side_items.push_back(new Chocolate(units));
        else if (iname == "Sugar") side_items.push_back(new Sugar(units));
        else if (iname == "Cookie") side_items.push_back(new Cookie(units));
        else if (iname == "Espresso") side_items.push_back(new Espresso(units));
        else if (iname == "Milk") side_items.push_back(new Milk(units));
        else if (iname == "MilkFoam") side_items.push_back(new MilkFoam(units));
        else if (iname == "Water") side_items.push_back(new Water(units));
    }
}

Cappuccino::~Cappuccino() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap) {
    if (this == &cap) return;
    EspressoBased::operator=(cap);
    
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
    
    for (const auto& item : cap.side_items) {
        std::string iname = item->get_name();
        size_t units = item->get_units();
        
        if (iname == "Cinnamon") side_items.push_back(new Cinnamon(units));
        else if (iname == "Chocolate") side_items.push_back(new Chocolate(units));
        else if (iname == "Sugar") side_items.push_back(new Sugar(units));
        else if (iname == "Cookie") side_items.push_back(new Cookie(units));
        else if (iname == "Espresso") side_items.push_back(new Espresso(units));
        else if (iname == "Milk") side_items.push_back(new Milk(units));
        else if (iname == "MilkFoam") side_items.push_back(new MilkFoam(units));
        else if (iname == "Water") side_items.push_back(new Water(units));
    }
}

std::string Cappuccino::get_name() {
    return name;
}

double Cappuccino::price() {
    double total = 0.0;
    for (const auto& i : ingredients)
        total += i->price();
    for (const auto& i : side_items)
        total += i->price();
    
    return total;
}

void Cappuccino::add_side_item(Ingredient* side) {
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items() {
    return side_items;
}