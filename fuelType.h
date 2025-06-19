#ifndef FUELTYPE_H_INCLUDED
#define FUELTYPE_H_INCLUDED
#include <string>

enum class FuelType{
    Benzyna,
    Diesel,
    Elektryczny,
    Hybryda
};

FuelType stringToFuelType(std::string);
std::string fuelTypeToString(FuelType);

#endif // FUELTYPE_H_INCLUDED
