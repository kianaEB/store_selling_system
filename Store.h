#ifndef STORE_H
#define STORE_H

#include <vector>
#include "Product.h"
#include "Costumer.h"
#include "Stock.h"
#include "Date.h"
#include <fstream>

class Store
{
    friend class Cart;
    friend class Receipt;
public:
    static Store& get_instance()
    {
        static Store instance;
        return instance;
    }
    void check_out(Costumer&);
    void add_costumer();
    void add_product();
    void view_products();
    void save_to_file();
    void read_file();      
    void sales_report(Date, Date);
    Costumer& get_customer(int);
    Stock& get_stock() { return stock; };
    std::ifstream& read_file(std::ifstream&);

    std::vector<Costumer>& get_list_of_costumer() { return costumers; };
    std::vector<Product>& get_list_of_product() { return products; };    




    ~Store();

private:
    Store() { };
    Store(const Store&) = delete;
    void operator=(const Store&) = delete;  
    
    std::vector<Product> products;
    Stock stock;
    std::vector<Costumer> costumers;
    void save_to_product_file();
    void save_to_customer_file();
    void save_to_stock_file();
    void save_to_history_file();

    void read_product_file();
    void read_customer_file();
    void read_stock_file();
    void read_history_file();        

};

#endif