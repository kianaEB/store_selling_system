#include "Costumer.h"
#include <stdexcept>
#include <ctime> 

Costumer::Costumer()
{

}

void Costumer::convert_cart_to_receipt()
{
    Receipt new_receipt;
    
    time_t now = time(0);
    tm* tmPtr = localtime(&now);

    int year = 1900 + tmPtr->tm_year;
    int month = 1 + tmPtr->tm_mon;
    int day = tmPtr->tm_mday;

    new_receipt.date.setDate(day, month, year);    

    for(auto it = cart.items.begin(); it != cart.items.end(); ++it)
    {
        new_receipt.items.insert(std::pair<int, int>(it->first, it->second));
    }
    if(this->balance >= cart.get_total_price())
        this->balance -= cart.get_total_price();
    else
        throw std::invalid_argument("Balance is not enough");    
    cart.reset();
    
    history.push_back(new_receipt);     
}

float Costumer::get_total_purchase_amount() const
{
    float total_purchase = 0;
    for(auto it = history.begin(); it != history.end(); ++it)
    {
        total_purchase += it->get_total_price(); 
    }
    return total_purchase;
}

Costumer::~Costumer()
{

}