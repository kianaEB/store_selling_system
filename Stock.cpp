#include "Stock.h"
#include <stdexcept>

Stock::Stock()
{

}

void Stock::change_count_by(int product_id, int count)
{
    if(count < 0 && this->Items.at(product_id) < (-1 * count))
        throw std::out_of_range("the product is not enough!");
    else
        this->Items.at(product_id) += count;    
}

int Stock::get_count(int product_id) const
{
    return this->Items.at(product_id);
}

Stock::~Stock()
{

}