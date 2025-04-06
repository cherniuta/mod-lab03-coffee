//Copyright 2025 cherniuta

#include "Automata.h"
#include <iostream>

int main() {
    Automata machine;

    machine.on();
    machine.getMenu();
    machine.coin(100);
    machine.choice(1);
    machine.check();
    machine.cook();

    machine.coin(50);
    machine.choice(0);
    machine.check();
    machine.cook();

    machine.coin(30);
    machine.cancel();

    machine.off();

    return 0;
}