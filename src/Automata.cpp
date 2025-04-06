//Copyright 2025 cherniuta

#include "Automata.h"
#include <iostream>
#include <thread>
#include <chrono>

Automata::Automata() : cash(0), state(OFF), selectedDrink(-1) {
    loadMenu();
}

void Automata::loadMenu() {
    menu = { "Tea", "Coffe", "Milk", "Russiano" };
    prices = { 30, 50, 45, 40 };
}

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        std::cout << "Automata turned on" << std::endl;
    }
}

void Automata::off() {
    if (state == WAIT && cash == 0) {
        state = OFF;
        std::cout << "Automata turned off" << std::endl;
    }
}

void Automata::coin(int amount) {
    if (state == WAIT || state == ACCEPT) {
        cash += amount;
        state = ACCEPT;
        std::cout << "Deposited: " << amount <<
            ". Current balance: " << cash << std::endl;
    }
}

void Automata::getMenu() const {
    if (state != OFF) {
        std::cout << "Menu:" << std::endl;
        for (size_t i = 0; i < menu.size(); ++i) {
            std::cout << i + 1 << ". " << menu[i] <<
                " - " << prices[i] << " rub." << std::endl;
        }
    }
}

STATES Automata::getState() const {
    return state;
}

void Automata::choice(int drinkIndex) {
    if (state == ACCEPT && drinkIndex >= 0 &&
        static_cast<size_t>(drinkIndex) < menu.size()) {
        selectedDrink = drinkIndex;
        state = CHECK;
        std::cout << "Choose a drink: " << menu[drinkIndex] << std::endl;
    }
}

bool Automata::check() {
    if (state == CHECK && selectedDrink != -1) {
        if (cash >= prices[selectedDrink]) {
            cash -= prices[selectedDrink];
            state = COOK;
            std::cout << "Making the drink..." << std::endl;
            return true;
        } else {
            std::cout << "Not enough money" << std::endl;
            return false;
        }
    }
    return false;
}

void Automata::cancel() {
    if (state == WAIT || state == ACCEPT || state == CHECK) {
        std::cout << "Return money: " << cash << " rub." << std::endl;
        cash = 0;
        selectedDrink = -1;
        state = WAIT;
    }
}

void Automata::cook() {
    if (state == COOK && selectedDrink != -1) {
        std::cout << "Making " << menu[selectedDrink] << "..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "The drink is ready sir!" << std::endl;
        finish();
    }
}

void Automata::finish() {
    if (state == COOK) {
        std::cout << "Get the drink. Change: " << cash << " rub." << std::endl;
        cash = 0;
        selectedDrink = -1;
        state = WAIT;
    }
}
