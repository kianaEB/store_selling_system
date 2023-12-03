#include <iostream>
#include "Date.h"
#include <stdexcept>
#include <string>

using namespace std;

const int Date::days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date(unsigned int y, unsigned int m, unsigned int d)
{
    setYear(y);
    setMonth(m);
    setDay(d);
}

Date::Date(string newDate)
{
    this->year = stoi(newDate.substr(0, 4));
    this->month = stoi(newDate.substr(5));
}

void Date::setYear(unsigned int y)
{
    year = y;
}

unsigned int Date::getYear() const
{
    return year;
}

void Date::setMonth(unsigned int m)
{
    if(m >= 1 && m <= 12)
        month = m;
    else
        throw std::invalid_argument("Invalid month!");
}

unsigned int Date::getMonth() const
{
    return month;
}

void Date::setDay(unsigned int d)
{
    if(checkDay(d))
        day = d;
    else
        throw std::invalid_argument("Invalid day for current month and year!");
}

unsigned int Date::getDay() const
{
    return day;
}

void Date::print() const
{
    std::cout << year << "/" << month << "/" << day << std::endl;
}

bool Date::checkDay(unsigned int testDay) const
{
    unsigned int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(testDay <= daysPerMonth[month])
        return true;
    if((month == 2 && testDay == 29) &&
       (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
        return true;
    return false;
}

void Date::setDate(int d, int m, int y)
{
    setYear(y);
    setMonth(m);
    setDay(d);
}

bool Date::operator>(Date& right)
{
    if(this->getYear() > right.getYear())
        return true;
    if(this->getYear() < right.getYear())
        return false;
    if(this->getYear() == right.getYear())
    {
        if(this->getMonth() > right.getMonth())
            return true;
        if(this->getMonth() < right.getMonth())
            return false;
        if(this->getMonth() == right.getMonth())
        {
            if(this->getDay() > right.getDay())
                return true;
            else
                return false;
        }
    }           

}

bool Date::operator<=(Date& right)
{
    return !(*this > right);            
}

istream& operator>>(istream& input, Date& date)
{
    string temp;
    input >> temp;
    
    date.setYear(stoi(temp.substr(0, 4)));
    date.setMonth(stoi(temp.substr(5, 7)));
    date.setDay(stoi(temp.substr(8, 10)));

    return input;
}

bool Date::leapYear( int testYear ) const
{
    if ( testYear % 400 == 0 ||
       ( testYear % 100 != 0 && testYear % 4 == 0 ) )
        return true;
    else
        return false; 
}

bool Date::endOfMonth( int testDay ) const
{
if ( month == 2 && leapYear( year ) )
    return testDay == 29; // last day of Feb. in leap year
else
    return testDay == days[ month ];
}

void Date::helpIncrement()
{
    if (!endOfMonth(day))
        day++;
    else
        if ( month < 12 )
        {
            month++; 
            day = 1; 
        } 
        else 
        {
            year++; 
            month = 1; 
            day = 1; 
        } 
}
Date &Date::operator++() 
{ 
    helpIncrement();    
    return *this; 
}

bool Date::operator==(Date& date)
{
    if((date.getYear() == this->getYear()) &&
        (date.getMonth() == this->getMonth()) &&
        (date.getDay() == this->getDay()) )
        return true;
    return false;    
}

Date::~Date()
{

}