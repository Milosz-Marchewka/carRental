#ifndef CONDITION_H_INCLUDED
#define CONDITION_H_INCLUDED
#include <string>

enum class Condition{
    Nowy,
    Doskonaly,
    Dobry,
    Przecietny,
    Slaby,
    Uszkodzony
};

Condition stringToCondition(std::string);
std::string conditionToString(Condition);

#endif // CONDITION_H_INCLUDED
