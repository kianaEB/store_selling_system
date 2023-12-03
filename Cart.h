#ifndef CART_H
#define CART_H

#include <map>

class Cart
{
    friend class Store;
    friend class Costumer;
public:
    Cart();
    void add(int, int);
    void remove_item(int);
    void check_out();
    void reset();
    float get_total_price() const;
    void print() const;
    const std::map<int, int>& get_items() const { return items; };
    ~Cart();

private:
    std::map<int, int> items;

};

#endif