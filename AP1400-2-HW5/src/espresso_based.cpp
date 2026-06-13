#include "espresso_based.h"
#include "sub_ingredients.h"
#include <iostream>
#include <thread>
#include <chrono>

EspressoBased::EspressoBased() : name("") {}

std::vector<Ingredient*>& EspressoBased::get_ingredients() {
    return ingredients;
}

EspressoBased::EspressoBased(const EspressoBased& esp) : name(esp.name) {
    for (const auto& i : esp.ingredients) {
        std::string ing_name = i->get_name();
        if (ing_name == "Cinnamon") ingredients.push_back(new Cinnamon(i->get_units()));
        else if (ing_name == "Chocolate") ingredients.push_back(new Chocolate(i->get_units()));
        else if (ing_name == "Sugar") ingredients.push_back(new Sugar(i->get_units()));
        else if (ing_name == "Cookie") ingredients.push_back(new Cookie(i->get_units()));
        else if (ing_name == "Espresso") ingredients.push_back(new Espresso(i->get_units()));
        else if (ing_name == "Milk") ingredients.push_back(new Milk(i->get_units()));
        else if (ing_name == "MilkFoam") ingredients.push_back(new MilkFoam(i->get_units()));
        else if (ing_name == "Water") ingredients.push_back(new Water(i->get_units()));
    }
}

void EspressoBased::operator=(const EspressoBased& esp) {
    if (this == &esp) return;

    for (const auto& i : ingredients) {
        delete i;
    }
    ingredients.clear();

    name = esp.name;

    for (const auto& i : esp.ingredients) {
        std::string ing_name = i->get_name();
        if (ing_name == "Cinnamon") ingredients.push_back(new Cinnamon(i->get_units()));
        else if (ing_name == "Chocolate") ingredients.push_back(new Chocolate(i->get_units()));
        else if (ing_name == "Sugar") ingredients.push_back(new Sugar(i->get_units()));
        else if (ing_name == "Cookie") ingredients.push_back(new Cookie(i->get_units()));
        else if (ing_name == "Espresso") ingredients.push_back(new Espresso(i->get_units()));
        else if (ing_name == "Milk") ingredients.push_back(new Milk(i->get_units()));
        else if (ing_name == "MilkFoam") ingredients.push_back(new MilkFoam(i->get_units()));
        else if (ing_name == "Water") ingredients.push_back(new Water(i->get_units()));
    }
}

void EspressoBased::brew() {
    std::cout << "\n==================================================\n";
    std::cout << "  Initiating brewing process for " << get_name() << "..." << std::endl;
    std::cout << "==================================================\n";

    for (const auto& i : ingredients) {
        std::cout << "-> Adding " << i->get_units() << " units of " << i->get_name() << ":\n   [";
        
        // Simulating the work process using delays and standard output buffer flushes
        for (int p = 0; p < 20; ++p) {
            std::cout << "#" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(30)); // Delay loop representing brewing
        }
        std::cout << "] 100% Complete!\n";
    }

    std::cout << "\n>>> " << get_name() << " is ready! Enjoy! <<<\n";
    std::cout << "==================================================\n\n";
}

EspressoBased::~EspressoBased()
{
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}
