#include <iostream>
#include <thread> // std::this_thread::sleep_for()
#include <chrono> // std::chrono::milliseconds()
#include <windows.h>
#include <string>
#include <algorithm> // string.remove()
#include <cctype> // std::tolower(), std::toupper()
#include <regex>
#include <limits> // std::numeric_limits
#include "utils.h"
#include "date.h"


Exception::Exception(const std::string& message) : message(message) {}

const char* Exception::what() const noexcept{
    return this->message.c_str();
}

std::string Exception::getMessage() const{
    return this->message;
}
bool enumFormat(std::string& str){
    // usuwa wszystkie spacje z stringa
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    if(!str.empty()){
        // zmiana wszystkiego na lowercase
        for(int i = 0; i<str.size(); i++){
            if(i == 0){
                // zmiana pierwszej litery na uppercase
                str[i] = std::toupper(static_cast<unsigned char>(str[i]));
                continue;
            }
            // zmienia reszte liter na lowercase
            str[i] = std::tolower(static_cast<unsigned char>(str[i]));
        }

        // osobno poniewaz w enumie nazwa to PolAutomatyczna, a petla zmienia tylko pierwsza litere na wielka
        if(str == "Polautomatyczna"){
            str[3] = std::toupper(static_cast<unsigned char>(str[3]));
        }

        // zmienilo stringa i zwraca true
        return true;
    } else {
        // jezeli jest puste, nie zmienia stringa, a zwraca false
        return false;
    }
}

void licensePlateCheck(std::string licensePlate){
    // XX-XXXXX lub XXX-XXXXX
    std::regex pattern("\^[A-Z]{2,3}(-)[A-ZA-z0-9]{5}$");

    if(!std::regex_match(licensePlate, pattern)){
        throw Exception("Tablica rejestracyjna jest wpisana niepoprawnie - " + licensePlate);
    }
}

Date dateCheck(std::string date){
    // dd.mm.yyyy
    // \\. to jest escape na kropke
    std::regex pattern("\^[0-9]{2}(\\.)[0-9]{2}(\\.)[0-9]{4}$");
    if(!std::regex_match(date, pattern)){
        throw Exception("Data jest wpisana niepoprawnie - " + date);
    } else {
        std::string year = date.substr(6,4);
        std::string month = date.substr(3,2);
        std::string day = date.substr(0,2);
        return Date(std::stoi(year), std::stoi(month), std::stoi(day));
    }
}


void clearTerminal(){
    system("cls");
}
void wait(int ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
void waitAndClearTerminal(int ms){
    wait(ms);
    clearTerminal();
}
void clearCin(){
    // czysci pozostalosci po cin
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool checkIfStrEmpty(std::string& str){
    return (str.empty() ? true : false);
}

