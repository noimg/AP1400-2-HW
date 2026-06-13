#ifndef MOCHA_H
#define MOCHA_H

#include "espresso_based.h"
#include <string>
#include <vector>

class Mocha : public EspressoBased {
public:
    Mocha();
    Mocha(const Mocha& mc);
    virtual ~Mocha() override;
    void operator=(const Mocha& mc);

    virtual std::string get_name() override;
    virtual double price() override;

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();

private:
    std::vector<Ingredient*> side_items;
};

#endif // MOCHA_H