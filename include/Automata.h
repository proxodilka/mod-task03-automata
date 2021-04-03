#include "Utils.h"

#include <vector>
#include <ostream>
#include <iostream>
#include <string>

enum class STATE {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    TRANSACTION_APPROVED,
    COOK
};

const size_t npos = -1;

class Automata {
private:
    size_t cash;
    std::vector<Item> menu;
    size_t picked_item_idx;
    STATE state;

    const bool is_fixed_menu;
    std::string menu_filepath;

    void warning(std::string message="incorrect transition") {
        std::cout << "WARNING: " << message << std::endl;
    }

    void init();
    void return_coins() {
        cash = 0;
        std::cout << "Here is your coins, I don't need them anymore..." << std::endl;
    }

    Automata(bool is_fixed_menu): cash(0), picked_item_idx(npos), state(STATE::OFF), is_fixed_menu(is_fixed_menu) { }

public:
    Automata(): Automata(false) {}
    Automata(const std::vector<Item>& menu): Automata(true) { this->menu = menu; }
    Automata(std::vector<Item>&& menu): Automata(true) { this->menu = std::move(menu); }
    Automata(std::string menu_filepath): Automata(false) { this->menu_filepath = menu_filepath; }                              
    ~Automata() { off(); }

    void on();
    void off();
    void coin(size_t);
    void choice(size_t);
    void check();
    void cancel();
    void cook();
    void finish();

    const std::vector<Item>& get_menu() {return menu; }
    STATE get_state() { return state; }
    size_t get_cash() { return cash; }

};
