#ifndef TRANSMISSION_H_INCLUDED
#define TRANSMISSION_H_INCLUDED
#include <string>

enum class Transmission{
    Manualna,
    Automatyczna,
    PolAutomatyczna
};

Transmission stringToTransmission(std::string);
std::string transmissionToString(Transmission);

#endif // TRANSMISSION_H_INCLUDED
