#include "Automata.h"

int main() {
    Automata a;

    a.on();
    a.coin(20);

    // not enough money
    a.choice(0);
    a.check();

    a.choice(1);
    a.check();

    a.cook();
    a.finish();
}
