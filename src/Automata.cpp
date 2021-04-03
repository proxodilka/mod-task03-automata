#include "Automata.h"
#include "UtilsInternal.h"

void Automata::on() {
    switch (state)
    {
    case STATE::OFF:
        init();
        state = STATE::WAIT;
        break;

    default:
        throw IncorrectTransitionError();
    }
    
}

void Automata::off() {
    switch (state)
    {
    default:
        return_coins();
        state = STATE::OFF;
    }
}

void Automata::coin(size_t coin) {
    switch (state)
    {
    case STATE::WAIT:
    case STATE::ACCEPT:
        cash += coin;
        state = STATE::ACCEPT;
        break;

    default:
        throw IncorrectTransitionError();
    }
}

void Automata::choice(size_t index) {
    switch (state)
    {
    case STATE::ACCEPT:
        CHECK(index >= 0 && index < menu.size());
        picked_item_idx = index;
        state = STATE::CHECK;
        break;
    
    default:
        throw IncorrectTransitionError();
    }
}

void Automata::check() {
    size_t price = menu[picked_item_idx].price;
    switch (state)
    {
    case STATE::CHECK:
        if (cash >= price) {
            cash -= price;
            state = STATE::TRANSACTION_APPROVED;
        }
        else {
            state = STATE::ACCEPT;
            warning("Not enough money. Transit to the ACCEPT state.");
        }
        break;
    
    default:
        throw IncorrectTransitionError();
    }
}

void Automata::cancel() {
    switch (state)
    {
    case STATE::ACCEPT:
    case STATE::CHECK:
    case STATE::TRANSACTION_APPROVED:
        return_coins();
        picked_item_idx = npos;
        state = STATE::WAIT;
        break;
    
    default:
        throw IncorrectTransitionError();
    }
}

void Automata::cook() {
    switch (state)
    {
    case STATE::TRANSACTION_APPROVED:
        state = STATE::COOK;
        break;
    
    default:
        throw IncorrectTransitionError();
    }
}

void Automata::finish() {
    switch (state)
    {
    case STATE::COOK:
        picked_item_idx = npos;
        state = STATE::WAIT;
        break;
    
    default:
        throw IncorrectTransitionError();
    }
}

void Automata::init() {
    cash = 0;
    picked_item_idx = npos;
    if (false/*const char* filepath = std::getenv("MENU_PATH")*/) {
        menu = Item::load_from_file("filepath");
    }
    else {
        menu = TEST_MENU;
    }
}
