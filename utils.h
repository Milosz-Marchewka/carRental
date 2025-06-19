#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <string>
#include <exception>
#include "date.h"

class Exception: public std::exception{
    std::string message {""};
public:
    Exception(const std::string& message);
    const char* what() const noexcept override;
    std::string getMessage() const;
};

bool enumFormat(std::string&);
void licensePlateCheck(std::string);
Date dateCheck(std::string);
void clearTerminal();
void wait(int);
void waitAndClearTerminal(int);
void clearCin();
bool checkIfStrEmpty(std::string&);

#endif // UTILS_H_INCLUDED
