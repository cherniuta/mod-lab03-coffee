#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <vector>

enum STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
private:
    int cash;
    std::vector<std::string> menu;
    std::vector<int> prices;
    STATES state;
    int selectedDrink;

    void loadMenu();

public:
    Automata();
    void on();
    void off();
    void coin(int amount);
    void getMenu() const;
    STATES getState() const;
    void choice(int drinkIndex);
    bool check();
    void cancel();
    void cook();
    void finish();
};

#endif // AUTOMATA_H