#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "Date.h"

class Product
{
    friend class Store;
public:
    Product();
    int get_id() const { return id; };
    float get_price() const { return price; };
    std::string get_name() const { return name; };
    std::string get_brand() const { return brand; };
    Date get_date() const { return expire_date; };    
    ~Product();

private:
    int id;
    std::string name;
    float price;
    std::string brand;
    Date expire_date;

};

#endif