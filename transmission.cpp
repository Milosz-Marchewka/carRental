#include <iostream>
#include <string>
#include "transmission.h"
#include "utils.h" // Exception, enumFormat()

Transmission stringToTransmission(std::string transmission){
    // zmienia string na format jaki jest w enumie, zwraca false jezeli string jest pusty, true jezeli wszystko ok
    if(enumFormat(transmission)){
        if(transmission == "Manualna") return Transmission::Manualna;
        else if(transmission == "Automatyczna") return Transmission::Automatyczna;
        else if(transmission == "PolAutomatyczna") return Transmission::PolAutomatyczna;
        else throw Exception("Wprowadzono bledny typ skrzyni biegow.");
    } else {
        throw Exception("Nie wprowadzono rodzaju skrzyni biegow - " + transmission);
    }
}
std::string transmissionToString(Transmission transmission){
    switch(transmission){
    case Transmission::Manualna:
        return "Manualna";
    case Transmission::Automatyczna:
        return "Automatyczna";
    case Transmission::PolAutomatyczna:
        return "PolAutomatyczna";
    default:
        throw Exception("Wprowadzono niepoprawny typ skrzyni biegow.");
    }
}
