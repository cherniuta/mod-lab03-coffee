#include "Automata.h"
#include <iostream>
#include <thread>
#include <chrono>

Automata::Automata() : cash(0), state(OFF), selectedDrink(-1) {
    loadMenu();
}

void Automata::loadMenu() {
    menu = { "Чай", "Кофе", "Молоко", "Руссиано" };
    prices = { 30, 50, 45, 40 };
}

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        std::cout << "Автомат включен" << std::endl;
    }
}

void Automata::off() {
    if (state == WAIT && cash == 0) {
        state = OFF;
        std::cout << "Автомат выключен" << std::endl;
    }
}

void Automata::coin(int amount) {
    if (state == WAIT || state == ACCEPT) {
        cash += amount;
        state = ACCEPT;
        std::cout << "Внесено: " << amount << ". Текущий баланс: " << cash << std::endl;
    }
}

void Automata::getMenu() const {
    if (state != OFF) {
        std::cout << "Меню напитков:" << std::endl;
        for (size_t i = 0; i < menu.size(); ++i) {
            std::cout << i + 1 << ". " << menu[i] << " - " << prices[i] << " руб." << std::endl;
        }
    }
}

STATES Automata::getState() const {
    return state;
}

void Automata::choice(int drinkIndex) {
    if (state == ACCEPT && drinkIndex >= 0 && static_cast<size_t>(drinkIndex) < menu.size()) {
        selectedDrink = drinkIndex;
        state = CHECK;
        std::cout << "Выбран напиток: " << menu[drinkIndex] << std::endl;
    }
}

bool Automata::check() {
    if (state == CHECK && selectedDrink != -1) {
        if (cash >= prices[selectedDrink]) {
            cash -= prices[selectedDrink];
            state = COOK;
            std::cout << "Средств достаточно. Приготовление..." << std::endl;
            return true;
        }
        else {
            std::cout << "Недостаточно средств" << std::endl;
            return false;
        }
    }
    return false;
}

void Automata::cancel() {
    if (state == WAIT || state == ACCEPT || state == CHECK) {
        std::cout << "Возврат средств: " << cash << " руб." << std::endl;
        cash = 0;
        selectedDrink = -1;
        state = WAIT;
    }
}

void Automata::cook() {
    if (state == COOK && selectedDrink != -1) {
        std::cout << "Готовим " << menu[selectedDrink] << "..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Ваш напиток готов!" << std::endl;
        finish();
    }
}

void Automata::finish() {
    if (state == COOK) {
        std::cout << "Заберите напиток. Сдача: " << cash << " руб." << std::endl;
        cash = 0;
        selectedDrink = -1;
        state = WAIT;
    }
}