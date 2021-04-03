#include <string>
#include <ostream>
#include <vector>
#include <fstream>

class IncorrectTransitionError : public std::exception {};

struct Item {
    std::string name;
    size_t price;

    Item(std::string name, size_t price): name(name), price(price) {}

    static std::vector<Item> load_from_file(const char* filepath) {
        auto fin = std::ifstream(filepath);
        std::vector<Item> result;
        while (!fin.eof()) {
            std::string name;
            int price;
            fin >> name >> price;
            result.emplace_back(name, price);
        }
        return result;
    }
};

static std::vector<Item> TEST_MENU = {
    {"Latte", 30},
    {"Cappuccino", 15},
    {"Hot chocolate", 20},
    {"Water", 5},
    {"Diet Mtn Dew", 999},
    {"Vesper Martini", 007}
};

std::ostream& operator<<(std::ostream& out, const Item& o) {
    out << o.name << " " << o.price;
    return out;
}
