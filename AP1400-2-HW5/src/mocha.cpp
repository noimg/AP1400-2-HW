#include "mocha.h"
#include "sub_ingredients.h"

Mocha::Mocha() : EspressoBased() {
    name = "Mocha";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& mc) : EspressoBased(mc) {
    for (const auto& item : mc.side_items) {
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

Mocha::~Mocha() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

void Mocha::operator=(const Mocha& mc) {
    if (this == &mc) return;
    EspressoBased::operator=(mc);
    
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
    
    for (const auto& item : mc.side_items) {
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

std::string Mocha::get_name() {
    return name;
}

double Mocha::price() {
    double total = 0.0;
    for (const auto& i : ingredients)
        total += i->price();
    for (const auto& i : side_items)
        total += i->price();
    
    return total;
}

void Mocha::add_side_item(Ingredient* side) {
    side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items() {
    return side_items;
}