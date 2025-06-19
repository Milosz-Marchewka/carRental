#include <string>
#include <windows.h>
#include <iomanip> // ostringstream
#include "date.h"
#include "utils.h"

Date::Date(){}
Date::Date(int year, int month, int day){
    setDate(year, month, day);
}
int Date::getYear() const{ return this->year; }
int Date::getMonth() const{ return this->month; }
std::string Date::getMonthFormatted() const{
    std::ostringstream o;
    o<<std::setw(2)<<std::setfill('0')<<this->month; // ostawia szerokosc na 2, dopelnia '0' jezeli jest jedna cyfra
    return o.str();
}
int Date::getDay() const{ return this->day;}
std::string Date::getDayFormatted() const{
    std::ostringstream o;
    o<<std::setw(2)<<std::setfill('0')<<this->day; // ostawia szerokosc na 2, dopelnia '0' jezeli jest jedna cyfra
    return o.str();
}
std::string Date::getDate() const{ return  getDayFormatted() + "." + getMonthFormatted() + "." + std::to_string(this->year);}
Date Date::today(){
    SYSTEMTIME s; // czas systemowy
    GetLocalTime(&s); // bierze czas systemowy komputera
    return Date(s.wYear, s.wMonth, s.wDay);
}
int Date::currentYear(){
    SYSTEMTIME s;
    GetLocalTime(&s);
    return s.wYear;
}
int Date::currentMonth(){
    SYSTEMTIME s;
    GetLocalTime(&s);
    return s.wMonth;
}
int Date::currentDay(){
    SYSTEMTIME s;
    GetLocalTime(&s);
    return s.wDay;
}

void Date::setYear(int year){
    if(year<1950 || year>currentYear()){
        throw Exception("Rok musi znajdowac sie w przedziale <1950;" + std::to_string(today().getYear()) + ">");
    } else{
        this->year = year;
    }
}
void Date::setMonth(int month){
    if(month<=0 || month>12){
        throw Exception("Miesiac musi znajdowac sie w zakresie <1;12>");
    } else{
        this->month = month;
    }
}
void Date::setDay(int day){
    if(day<=0 || day>31){
        throw Exception("Dzien musi znajdowac sie w zakresie <1;31>");
    } else{
        this->day = day;
    }
}
void Date::setDate(int year, int month, int day){
    validateDate(year,month,day);
    this->year = year;
    this->month = month;
    this->day = day;
}
void Date::validateDate(Date date){
    // walidacja ogolna
    // nie ma sprawdzania czy rok jest przestepny i dokladnosci
    // dni do 28,29,30,31 poniewaz nie mam pojecia jak to efektywnie
    // zrobic.
    if(date.getDay()<=0 || date.getDay()>31){
        throw Exception("Dzien musi znajdowac sie w zakresie <1;31>");
    }
    if(date.getMonth()<=0 || date.getMonth()>12){
        throw Exception("Miesiac musi znajdowac sie w zakresie <1;12>");
    }
    if(date.getMonth() == 2 && date.getDay() > 29){
        throw Exception("Dzien musi znajdowac sie w zakresie <1;29>");
    }
    // walidacja wzgledem obecnej daty
    if(date.getYear() == currentYear()){
        if(date.getMonth() == currentMonth()){
             if(date.getDay() > currentDay()){
                throw Exception("Nie mozesz wpisac daty z przyslosci.");
             }
        } else if(date.getMonth() > currentMonth()){
            throw Exception("Nie mozesz wpisac daty z przyslosci - miesiac " + std::to_string(date.getMonth()));
        }
    } else if(date.getYear() > currentYear()){
        throw Exception("Nie mozesz wpisac daty z przyslosci - rok " + std::to_string(date.getYear()));
    } else if(date.getYear() < 1950){
        throw Exception("Przyjmujemy daty tylko od roku 1950.");
    }
}
void Date::validateDate(int year, int month, int day){
    // walidacja ogolna
    // nie ma sprawdzania czy rok jest przestepny i dokladnosci
    // dni do 28,29,30,31 poniewaz nie mam pojecia jak to efektywnie
    // zrobic.
    if(day<=0 || day>31){
        throw Exception("Dzien musi znajdowac sie w zakresie <1;31>");
    }
    if(month<=0 || month>12){
        throw Exception("Miesiac musi znajdowac sie w zakresie <1;12>");
    }
    if(month == 2 && day > 29){
        throw Exception("Dzien musi znajdowac sie w zakresie <1;29>");
    }

    if(year == currentYear()){
        if(month == currentMonth()){
             if(day > currentDay()){
                throw Exception("Nie mozesz wpisac daty z przyslosci.");
             }
        } else if(month > currentMonth()){
            throw Exception("Nie mozesz wpisac daty z przyslosci - miesiac " + std::to_string(month));
        }
    } else if(year > currentYear()){
        throw Exception("Nie mozesz wpisac daty z przyslosci - rok " + std::to_string(year));
    } else if(year < 1950){
        throw Exception("Przyjmujemy daty tylko od roku 1950.");
    }
}
