#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <string>
#include <iostream>

class Date
{
    friend std::istream& operator>>(std::istream&, Date&);  
public:
    explicit Date(unsigned int = 1900, unsigned int = 1, unsigned int = 1);
    Date(std::string);
   
    void setYear(unsigned int);
    unsigned int getYear() const;
    void setMonth(unsigned int);
    unsigned int getMonth() const;
    void setDay(unsigned int);
    unsigned int getDay() const;
    void setDate(int, int, int);
    void print() const;

    bool operator> (Date&);
    bool operator<= (Date&);
    bool endOfMonth(int) const; 
    bool leapYear(int) const ;
    void helpIncrement(); 
    Date& operator++(); 
    bool operator==(Date&);            

    ~Date();

private:
    unsigned int year;
    unsigned int month;
    unsigned int day;
    static const int days[13];

    bool checkDay(unsigned int) const;
};

#endif // DATE_H_INCLUDED