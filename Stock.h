#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <map>

class Stock
{
    friend class Store;
public:
    Stock();
    void change_count_by(int, int);
    int get_count(int) const;
    const std::map<int, int>& get_items() const { return Items; };    
    ~Stock();

private:
    std::map<int, int> Items;
};

#endif