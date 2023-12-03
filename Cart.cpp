#include "Cart.h"
#include "Store.h"
#include <map>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std;

Cart::Cart()
{

}

void Cart::add(int product_id, int quantity)
{
    if(items.find(product_id) != items.end())
    {
        items[product_id] += quantity;
    }
    else
        items.insert( std::pair<int, int>(product_id, quantity) );
}

void Cart::remove_item(int product_id)
{
    if(items.find(product_id) != items.end())
        items.erase(product_id);
    else
        throw invalid_argument("The product_id is invalid!");    
}

void Cart::reset()
{
    items.clear();
}

float Cart::get_total_price() const
{
    Store& store = Store::get_instance();    
    float total = 0;
    for(auto it_1 = store.products.begin(); it_1 != store.products.end(); ++it_1)
    {
        for(auto it_2 = items.begin(); it_2 != items.end(); ++it_2)
        {
            if(it_2->first == it_1->get_id())
            {
                total += (it_1->get_price() * it_2->second);
            }
        }
    }
    return total;
}

void Cart::print() const
{
    Store& store = Store::get_instance();    
    
    for(auto it_1 = store.products.begin(); it_1 != store.products.end(); ++it_1)
    {
        for(auto it_2 = items.begin(); it_2 != items.end(); ++it_2)
        {
            if(it_1->get_id() == it_2->first)
            {
                cout << "ID: " << it_1->get_id() << endl
                << "Name: " << it_1->get_name() << endl
                << "Price: " << it_1->get_price() << endl
                << "Brand: " << it_1->get_brand() << endl
                << "Expire date: " << it_1->get_date().getYear() << '/' 
                << setfill('0') << setw(2) << it_1->get_date().getMonth() << endl 
                << "In Stock: " << it_2->second <<  endl;
            }    
        }     
    }    
}

Cart::~Cart()
{

}