#include <iostream>
#include <string>
#include "condition.h"
#include "utils.h" // Exception, enumFormat()

Condition stringToCondition(std::string condition){
    // zmiana na format jaki jest w enumie, zwraca false jezeli string jest pusty
    if(enumFormat(condition)){
        if(condition == "Nowy") return Condition::Nowy;
        else if(condition == "Doskonaly") return Condition::Doskonaly;
        else if(condition == "Dobry") return Condition::Dobry;
        else if(condition == "Przecietny") return Condition::Przecietny;
        else if(condition == "Slaby") return Condition::Slaby;
        else if(condition == "Uszkodzony") return Condition::Uszkodzony;
        else throw Exception("Wpisano niepoprawny stan pojazdu.");
    } else {
        throw Exception("Nie wpisano stanu pojazdu - " + condition);
    }
}
std::string conditionToString(Condition condition){
    switch(condition){
    case Condition::Nowy:
        return "Nowy";
    case Condition::Doskonaly:
        return "Doskonaly";
    case Condition::Dobry:
        return "Dobry";
    case Condition::Przecietny:
        return "Przecietny";
    case Condition::Slaby:
        return "Slaby";
    case Condition::Uszkodzony:
        return "Uszkodzony";
    default:
        throw Exception("Wprowadzono niepoprawny stan pojazdu.");
    }
}
