#include <iostream>
#include <string>
#include "fuelType.h"
#include "utils.h" // Exception, enumFormat()

FuelType stringToFuelType(std::string fuelType){
    // zmiana na format jaki jest w enumie, zwraca false jezeli string jest pusty
    if(enumFormat(fuelType)){
        if(fuelType == "Benzyna") return FuelType::Benzyna;
        else if(fuelType == "Diesel") return FuelType::Diesel;
        else if(fuelType == "Elektryczny") return FuelType::Elektryczny;
        else if(fuelType == "Hybryda") return FuelType::Hybryda;
        else throw Exception("Wprowadzono bledny typ paliwa");
    } else{
        throw Exception("Nie wprowadzono typu paliwa - " + fuelType);
    }
}
std::string fuelTypeToString(FuelType fuelType){
    switch(fuelType){
    case FuelType::Benzyna:
        return "Benzyna";
    case FuelType::Diesel:
        return "Diesel";
    case FuelType::Elektryczny:
        return "Elektryczny";
    case FuelType::Hybryda:
        return "Hybryda";
    default:
        throw Exception("Wprowadzono niepoprawny typ paliwa.");
    }
}
