#ifndef RECEIPT_H
#define RECEIPT_H

#include <string>
#include <map>
#include "Date.h"

class Receipt
{
    friend class Store;
    friend class Costumer;
public:
    Receipt();
    float get_total_price() const;
    const std::map<int, int>& get_items() const { return items; };
    const Date& get_date() const { return date; };
    ~Receipt();

private:
    std::map<int, int> items;
    Date date;
};

#endif