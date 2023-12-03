#ifndef COSTUMER_H
#define COSTUMER_H

#include <string>
#include <vector>
#include "Receipt.h"
#include "Cart.h"


class Costumer
{
    friend class Store;
public:
    Costumer();
    
    void convert_cart_to_receipt();
    float get_total_purchase_amount() const;
    const std::vector<Receipt>& get_history() const { return history; };
    int get_id() const { return id; };
    std::string get_name() const { return name; };
    std::string get_phone_number() const { return phone_number; };
    std::string get_address() const { return address; };
    float get_balance() const { return balance; };
    Cart& get_cart() { return cart; }
    
    ~Costumer();

private:
    int id;
    std::string name;
    std::string phone_number;
    std::vector<Receipt> history;
    std::string address;
    Cart cart;
    float balance;

};

#endif