#include <iostream>
#include "Store.h"
#include <string>
#include <utility>
#include <iomanip>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdexcept> 
    
void Store::read_product_file()
{
    std::fstream store("product.txt", std::ios::in);
    if(!store.in)
        throw std::runtime_error("Error in opening the file");
    std::string temp;
    
    if(store.peek() != EOF)
    {
        getline(store, temp);
        int count = stoi(temp);
        for(int i = 0; i < count; ++i)
        {
            Product product;
            getline(store, temp);
            product.id = stoi(temp); 

            getline(store, temp);
            product.name = temp; 

            getline(store, temp);
            product.brand = temp; 

            getline(store, temp);
            product.price = stof(temp); 

            getline(store, temp);
            product.expire_date = temp;

            products.push_back(product);                                
        }
    }    

    store.close();

}

void Store::read_customer_file()
{
    std::fstream store("customer.txt", std::ios::in);
    if(!store.in)
        throw std::runtime_error("Error in opening the file");    
    std::string temp;

    if(store.peek() != EOF)
    {
        getline(store, temp);
        int count = stoi(temp);

        for(int i = 0; i < count; ++i)
        {
            Costumer customer;
            getline(store, temp);
            customer.id = stoi(temp); 

            getline(store, temp);
            customer.name = temp; 

            getline(store, temp);
            customer.phone_number = temp; 

            getline(store, temp);
            customer.address = temp;

            getline(store, temp);
            customer.balance = stof(temp);

            costumers.push_back(customer);
        }
    }    
    
    store.close();    
}

void Store::read_history_file()
{
    std::fstream store("history.txt", std::ios::in);
    if(!store.in)
        throw std::runtime_error("Error in opening the file");    
    std::string temp;
    if(store.peek() != EOF)
    {
        getline(store, temp);
        int count = stoi(temp);

        for(int i = 0; i < count; ++i)
        {
            getline(store, temp);
            int count_2 = stoi(temp);

                for(int i = 0; i < count_2; ++count_2)
                {
                    Receipt receipt;
                    std::string temp_2;
                    
                    getline(store, temp);
                    int count_3 = stoi(temp);
                    for(int j = 0; j < count_3; ++j)
                    {
                        getline(store, temp_2);
                        getline(store, temp);
                        receipt.items.insert(std::pair<int, int>(stoi(temp), stoi(temp_2)));
                    }
                    getline(store, temp);
                    receipt.date.setDate(stoi(temp.substr(8, 10)), stoi(temp.substr(5, 7)), stoi(temp.substr(0, 4)));
                    get_list_of_costumer()[i].history.push_back(receipt);

                }           
        }        
    }
    store.close();

}

void Store::read_stock_file()
{
    std::fstream store("customer.txt", std::ios::in);
    if(!store.in)
        throw std::runtime_error("Error in opening the file");    
    std::string temp, temp_2;
    
    if(store.peek() != EOF)
    {
        getline(store, temp);
        int count = stoi(temp);    
        
        for(int j = 0; j < count; ++j)
        {
            getline(store, temp);
            getline(store, temp_2);
            stock.Items.insert(std::pair<int, int>(stoi(temp), stoi(temp_2)));  
        }
    } 
    store.close();   
  
}

void Store::read_file()
{
    read_customer_file();
    read_product_file();    
    //read_history_file();
    //read_stock_file();
}

void Store::check_out(Costumer& costumer)
{
    for(auto it = costumer.get_cart().items.begin(); it != costumer.get_cart().items.end(); ++it)
    {
        int count = (-1 * it->second);
        stock.change_count_by(it->first, count);
    }
    
    costumer.convert_cart_to_receipt();
}

void Store::add_costumer()
{
    Costumer costumer;
    std::string temp;
    int repeated = 0;

    std::cout << "ID: ";
    getline(std::cin, temp);
    costumer.id = stoi(temp);

    std::cout << "Name: ";
    getline(std::cin, temp);
    costumer.name = temp;

    std::cout << "Phone Number: ";
    getline(std::cin, temp);
    costumer.phone_number = temp;

    std::cout << "Address: ";
    getline(std::cin, temp);
    costumer.address = temp;

    std::cout << "Balance: ";
    getline(std::cin, temp);
    costumer.balance = stof(temp);

    for(auto it = costumers.begin(); it != costumers.end(); ++it)
    {
        if(costumer.id == it->id)
        {
            repeated = 1;
            break;
        }
    }
    if(repeated)
        throw std::invalid_argument("This ID is already exist"); 
    else    
        costumers.push_back(costumer);
}

void Store::add_product()
{
    Product product;
    std::string temp;
    int repeated = 0;

    std::cout << "ID: ";
    getline(std::cin, temp);
    product.id = stoi(temp);

    std::cout << "Name: ";
    getline(std::cin, product.name);

    std::cout << "Price: ";
    getline(std::cin, temp);
    product.price = stoi(temp);

    std::cout << "Brand: ";
    getline(std::cin, product.brand);

    std::cout << "Expire date: ";
    getline(std::cin, temp);
    product.expire_date = temp;

    std::cout << "In stock: ";
    getline(std::cin, temp);

    for(auto it = products.begin(); it != products.end(); ++it)
    {
        if(product.get_id() == it->get_id())
        {
            repeated = 1;
            break;
        }
    } 

    if(repeated)
    {
        this->stock.Items[product.get_id()] += stoi(temp);
    }
    else      
    {
        (this->stock).Items.insert( std::pair<int, int>(product.id, stoi(temp)) );
        products.push_back(product);
    }    
}

void Store::view_products()
{
    for(auto it = products.begin(); it != products.end(); ++it)
    {
        std::cout << "ID:          " << it->id << std::endl;
        std::cout << "Name:        " << it->name << std::endl;
        std::cout << "Price:       " << it->price << std::endl;
        std::cout << "Brand:       " << it->brand << std::endl;
        std::cout << "Expire date: " << it->expire_date.getYear() << '/'
        << std::setfill('0') << std::setw(2) << it->expire_date.getMonth() << std::endl;
        std::cout << std::endl;
    }
}

void Store::save_to_file()
{
    std::fstream store("store.txt", std::ios::trunc | std::ios::out);
    
    store << "\t\t\t\t LIST OF PRODUCTS " << std::endl;
    for(auto it = products.begin(); it != products.end(); ++it)
    {
        store << "ID:          " << it->id << std::endl;
        store << "Name:        " << it->name << std::endl;
        store << "Price:       " << it->price << std::endl;
        store << "Brand:       " << it->brand << std::endl;
        store << "Expire date: " << it->expire_date.getYear() << '/'
        << std::setfill('0') << std::setw(2) << it->expire_date.getMonth() << std::endl;
    }
    store << "----------------------------------------------------------" << std::endl;
    
    store << "\t\t\t\t LIST OF CUSTOMERS " << std::endl;  
    for(auto it = costumers.begin(); it != costumers.end(); ++it)
    {
        store << "ID:           " << it->id << std::endl;
        store << "Name:         " << it->name << std::endl;
        store << "Phone Number: " << it->phone_number << std::endl;
        store << "Address:      " << it->address << std::endl;
        store << "Balance:      " << it->balance << std::endl;
        store << "History:      " << std::endl;
        for(auto it_2 = it->history.begin(); it_2 != it->history.end(); ++it_2)
        {
            for(auto it_3 = it_2->items.begin(); it_3 != it_2->items.end(); ++it_3)
            {
                store << "   ID:       " << it_3->first << std::endl;
                store << "   Quantity: " << it_3->second << std::endl;
                store << std::endl; 
            }
            store << "Date: " << it_2->date.getYear() << '/' << std::setfill('0') << std::setw(2) 
            << it_2->date.getMonth() << std::setw(2) << it_2->date.getDay(); 
        }

    }
    store << "----------------------------------------------------------" << std::endl;
    
    store << "\t\t\t\t LIST OF STOCK " << std::endl;
    for(auto it = stock.Items.begin(); it != stock.Items.end(); ++it)
    {
        store << "ID:       " << it->first << std::endl;
        store << "Quantity: " << it->second << std::endl;        
    }
    store << "----------------------------------------------------------" << std::endl;

    save_to_product_file();
    save_to_customer_file();
    save_to_stock_file();
    save_to_history_file();

    store.close();

}

void Store::save_to_product_file()
{
    std::fstream store("product.txt", std::ios::trunc | std::ios::out); 
    int count = products.size();
    store << count << std::endl;
    
    for(auto it = products.begin(); it != products.end(); ++it)
    {
        store << it->get_id()    << std::endl;
        store << it->get_name()  << std::endl;
        store << it->get_brand() << std::endl;
        store << it->get_price() << std::endl;
        store << it->expire_date.getYear() << '/'<< std::setfill('0') 
              << std::setw(2) << it->expire_date.getMonth() << std::endl;
    }
    store.close();

}

void Store::save_to_customer_file()
{
    std::fstream store("customer.txt", std::ios::trunc | std::ios::out); 
    int count = costumers.size(); 

    store << count << std::endl;  
    
    for(auto it = costumers.begin(); it != costumers.end(); ++it)
    {
        store << it->get_id() << std::endl;
        store << it->get_name() << std::endl;
        store << it->get_phone_number() << std::endl;
        store << it->get_address() << std::endl;
        store << it->get_balance() << std::endl;
    }
    store.close();    
 
}

void Store::save_to_history_file()
{
    std::fstream store("history.txt", std::ios::trunc | std::ios::out); 
    int count = costumers.size(); 

    store << count << std::endl;  
    
    for(auto it = costumers.begin(); it != costumers.end(); ++it)
    {
        int history_count = it->get_history().size();
        store << history_count << std::endl;
        
        for(auto it_2 = it->history.begin(); it_2 != it->history.end(); ++it_2)
        {
            int items_count = it_2->get_items().size();
            store << items_count << std::endl;

            for(auto it_3 = it_2->items.begin(); it_3 != it_2->items.end(); ++it_3)
            {
                store << it_3->first << std::endl;
                store << it_3->second << std::endl;
            }
        }
    }
    store.close();     
}

void Store::save_to_stock_file()
{
    std::fstream store("stock.txt", std::ios::trunc | std::ios::out); 
    int count = stock.Items.size();
    store << count << std::endl;    
    
    for(auto it = stock.Items.begin(); it != stock.Items.end(); ++it)
    {
        store << it->first << std::endl;
        store << it->second << std::endl;        
    } 
    store.close();   
}

void Store::sales_report(Date start, Date end)
{
    float temp, total = 0, max = 0;
    Date max_date = start;
    
    for(Date date = start; date <= end; ++date) 
    {   
        for(auto it_1 = costumers.begin(); it_1 != costumers.end(); ++it_1)
        {
            for(auto it_2 = it_1->history.begin(); it_2 != it_1->history.end(); ++it_2)
            {
                if(it_2->date == date)
                {
                    temp += it_2->get_total_price();
                    total += temp;
                }
            }
        }        
            
        if(max < temp)
        {
            max_date = date;
            max = temp;
        }    
                
        std::cout << std::endl << date.getYear() << '.' << std::setfill('0')
        << std::setw(2) << date.getMonth() << '.' << std::setw(2) << 
        date.getDay() << ':';
                
        int count = (temp / 100);
        for(int i = 0; i < count; ++i)
        {
            std::cout << "++ ";
        }
        std::cout << std::endl;    

        temp = 0;

    }    
    
    std::cout << "Maximum sale date: " << max_date.getYear() << '.' << std::setfill('0')
                                       << std::setw(2) << max_date.getMonth() << '.' 
                                       << std::setw(2) << max_date.getDay()  << std::endl;
                                          
    std::cout << "Total sale: " << total << std::endl;
}

Costumer& Store::get_customer(int id)
{
    for(auto it = costumers.begin(); it != costumers.end(); ++it)
    {
        if(it->id == id)
            return (*it);
    }
    throw std::invalid_argument("There is no customer with that id");
}

Store::~Store()
{

}
