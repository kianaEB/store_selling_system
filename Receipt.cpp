#include "Receipt.h"
#include "Store.h"

Receipt::Receipt()
{

}

float Receipt::get_total_price() const
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

Receipt::~Receipt()
{

}