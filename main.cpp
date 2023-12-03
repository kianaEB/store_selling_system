#include <iostream>
#include <string>
#include "Cart.cpp"
#include "Costumer.cpp"
#include "Date.cpp"
#include "Product.cpp"
#include "Receipt.cpp"
#include "Stock.cpp"
#include "Store.cpp"
#include <fstream>
#include <iomanip>

using namespace std;
void customer_menu();
void main_menu();
void cart_menu();
void stock_menu();

int main()
{
    Store& store = Store::get_instance();
    store.read_file();
    
    cout << "Please enter your choice: " << endl;
    main_menu();

    int choice;
    cout << ">>";
    cin >> choice;      

    while(choice != 8)
    {
        switch(choice)
        {
            case 1:
                system("clear");
                main_menu();
                
                cin.ignore();
                store.add_product();
                cout << "A new product has been added successfully" << endl;
                cout << "Next choice: " << endl << ">>";
                cin >> choice; 
                break;
            
            case 2:
                system("clear");
                main_menu();            
                
                cin.ignore();        
                store.add_costumer();
                cout << "A new customer has been added successfully" << endl; 
                cout << "Next choice: " << endl << ">>";
                cin >> choice;
                break;               

            case 3:
                system("clear");
                main_menu();                     
                        
                store.view_products();
                cout << "Next choice: " << endl << ">>";
                cin >> choice;

            case 4:
                system("clear");
                cout << "Please enter the customer's id" << endl << ">>"; 
                int id;
                cin >> id;

                cout << "Please enter your choice: " << endl; 
                customer_menu();
                int select;
                cout << ">>";
                cin >> select;

                while(select != 5)
                {    
                    switch (select)
                    {
                    case 1:
                        system("clear");
                        customer_menu();

                        store.check_out(store.get_customer(id));
                        cout << "Customer checked out successfully" << endl;
                        cout << "Next choice: " << endl << ">>";
                        cin >> select;                        
                        break;
                    
                    case 2:
                        system("clear");
                        customer_menu();

                        cout << "The total purchase amount: " << store.get_customer(id).get_total_purchase_amount() << endl;
                        cout << "Next choice: " << endl << ">>";
                        cin >> select;
                        break;

                    case 3:
                        system("clear");
                        customer_menu();
                        
                        for(auto it = store.get_customer(id).get_history().begin(); it != store.get_customer(id).get_history().end(); ++it)
                        {
                            cout << it->get_date().getYear() << "/" << setfill('0') << setw(2) 
                                 << it->get_date().getMonth() << "/" << setw(2) << it->get_date().getDay() << endl;

                            for(auto it_2 = it->get_items().begin(); it_2 != it->get_items().end(); ++it_2)
                            {
                                cout << "   ID:       " << it_2->first << endl;
                                cout << "   Quantity: " << it_2->second << endl;
                                cout << endl;                                 
                            }
                            cout << "Customer total purchase: " << store.get_customer(id).get_total_purchase_amount() << endl;
                                 
                        }
                            cout << "Next choice: " << endl << ">>";
                            cin >> select;                       

                        break;
                    case 4:
                        system("clear");
                        cout << "Please enter your choice: " << endl;                        
                        cart_menu();

                        int c_select;
                        cout << ">>";
                        cin >> c_select;
                        
                        while(c_select != 6)
                        {
                            switch(c_select)
                            {
                                case 1:
                                    system("clear");
                                    cart_menu();
                                    
                                    int p_id, quantity;
                                    cout << "Product ID: " << endl;
                                    cout << ">>";
                                    cin >> p_id; 
                                    cout << "Quantity: " << endl;
                                    cout << ">>";
                                    cin >> quantity;

                                    store.get_customer(id).get_cart().add(p_id, quantity);
                                    cout << "The product added to the cart successfully" << endl;

                                    cout << "Next choice: " << endl << ">>";
                                    cin >> c_select;
                                    break;

                                case 2:
                                    system("clear");
                                    cart_menu();

                                    int product_id;
                                    cout << "Please insert the product ID that you want to remove: " << endl;
                                    cout << ">>";
                                    cin >> product_id;
                                    cout << ">>";
                                    store.get_customer(id).get_cart().remove_item(product_id);
                                    
                                    cout << "Next choice: " << endl << ">>";
                                    cin >> c_select;
                                    break;

                                case 3:
                                    system("clear");
                                    cart_menu();
                                    store.get_customer(id).get_cart().print();
                                    
                                    cout << "Next choice: " << endl << ">>";
                                    cin >> c_select;
                                    break;

                                case 4:
                                    system("clear");
                                    cart_menu();
                                    store.get_customer(id).get_cart().reset();
                                    cout << "The cart has been reset successfully" << endl;
                                    
                                    cout << "Next choice: " << endl << ">>";
                                    cin >> c_select;
                                    break;

                                case 5:
                                    system("clear");
                                    cart_menu();
                                    cout << "The total price is: " << store.get_customer(id).get_cart().get_total_price() << endl;
                                    
                                    cout << "Next choice: " << endl << ">>";
                                    cin >> c_select;
                                    break;                                                                                                               

                            }
                        }
                        system("clear");
                        customer_menu();
                        cout << "Next choice: " << endl << ">>";
                        cin >> select;                        

                        break;
                    }
                                        
                }
                system("clear");
                main_menu();
                cout << "Next choice: " << endl << ">>";
                cin >> choice;
                 
                break;

            case 5:
                system("clear");
                stock_menu();
                int s_select;
                cout << ">>";
                cin >> s_select;

                while(s_select != 3)
                {
                    switch(s_select)
                    {
                        case 1:
                            system("clear");
                            stock_menu();
                            cout << "Please enter the ID of a product that you want it's count:" << endl;
                            int pr_id;
                            cout << ">>";
                            cin >> pr_id;
                            cout << "amount: " << store.get_stock().get_count(pr_id) << endl;

                            cout << "Next choice: " << endl;
                            cout << ">>";
                            cin >> s_select;
                            break;

                        case 2:
                            system("clear");
                            stock_menu();
                            for(auto it = store.get_stock().get_items().begin(); it != store.get_stock().get_items().end(); ++it)
                            {
                                cout << "   ID:       " << it->first << endl;
                                cout << "   Quantity: " << it->second << endl;
                                cout << endl;                                 
                            }
                            
                            cout << "Next choice: " << endl;
                            cout << ">>";
                            cin >> s_select;
                            break;                                                                                

                    }   
                }
                system("clear");
                main_menu();    
                cout << "Next choice: " << endl << ">>";
                cin >> choice;

            case 6:
                system("clear");
                main_menu(); 
                store.save_to_file();
                cout << "Data has been saved successfully" << endl; 

                cout << "Next choice: " << endl << ">>";
                cin >> choice;
                break;

            case 7:
                system("clear");
                main_menu();

                cout << "Please write the start date and end date: " << endl;
                Date start, end;
                cout << "Start: " << endl;
                cout << ">>";
                cin >> start;
                cout << "End: " << endl;
                cout << ">>";
                cin >> end; 
                
                store.sales_report(start, end);

                cout << "Next choice: " << endl << ">>";
                cin >> choice;
                break;                                           

        }
    }
    store.save_to_file();
    return 0;     

}

void customer_menu()
{
    cout << "\t\t\t\t CUSTOMER PANEL" << endl 
         << "1) Check out customer"        << endl
         << "2) Get total purchase amount" << endl
         << "3) History of receipts "      << endl
         << "4) Cart"                      << endl
         << "5) Back to main menu"         << endl;
}

void main_menu()
{
    cout << "\t\t\t\t MAIN MENU"    << endl;
    cout << "1) Add product"        << endl
         << "2) Add customer"       << endl
         << "3) View product"       << endl
         << "4) Customer profile"   << endl
         << "5) Stock profile"      << endl
         << "6) Save to file"       << endl
         << "7) Sales report"       << endl
         << "8) Exit"               << endl;
}

void cart_menu()
{
    cout << "\t\t\t\t CART MENU"       << endl;
    cout << "1) Add"                    << endl
         << "2) Remove item"            << endl
         << "3) Print"                  << endl
         << "4) Reset"                  << endl
         << "5) Get total price"        << endl
         << "6) Back to customer menu" << endl;   
}

void stock_menu()
{
    cout << "\t\t\t\t STOCK MENU"      << endl
         << "1) Get count of a product" << endl
         << "2) List of product"        << endl
         << "3) Back to main menu"      << endl;
}