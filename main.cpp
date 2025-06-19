#include <iostream>
#include <chrono>
#include <thread>
#include <limits>
#include "dealership.h"
#include "car.h"
#include "utils.h" // Exception


// wypisywanie opcji na ekran
void mainMenu(){
    std::cout<<"============================";
    std::cout<<"\nWitaj w salonie samochodowym!";
    std::cout<<"\n";
    std::cout<<"\nCo chcesz zrobic?";
    std::cout<<"\n[0] - Pokaz wszystkie auta";
    std::cout<<"\n[1] - Dodaj auto";
    std::cout<<"\n[2] - Usun auto";
    std::cout<<"\n[3] - Edytuj auto";
    std::cout<<"\n[4] - Wypozycz auto";
    std::cout<<"\n[5] - Oddaj auto\n";
    std::cout<<"============================\n";
}

// wypisanie aut
void displayCars(Dealership& dealership){
    std::string _;
    dealership.displayCars();
    std::cout<<"\nNacisnij enter, aby wrocic do ekranu poczatkowego.";
    // oczyszcza buffer po jakichkolwiek poprzednich std::cin
    clearCin();
    std::getline(std::cin, _);

    waitAndClearTerminal(2000);
}
// dodanie aut
void addCar(Dealership& dealership){
    dealership.addCar();
    waitAndClearTerminal(3000);
}
// usuniecie auta
void removeCar(Dealership& dealership){
    dealership.removeCar();
    waitAndClearTerminal(3000);
}
void editCar(Dealership& dealership){
    dealership.editCar();
    waitAndClearTerminal(3000);
}
// wypozyczenie auta
void rentCar(Dealership& dealership){
    dealership.rentCar();
    waitAndClearTerminal(3000);
}
// zwrot auta
void returnCar(Dealership& dealership){
    dealership.returnCar();
    waitAndClearTerminal(3000);
}
// przetworzenie opcji
void processDecision(Dealership& dealership, int decision){
    switch(decision){
        case 0: {
            displayCars(dealership);
            break;
        }
        case 1:
            addCar(dealership);
            break;
        case 2:
            removeCar(dealership);
            break;
        case 3:
            editCar(dealership);
            break;
        case 4:
            rentCar(dealership);
            break;
        case 5:
            returnCar(dealership);
            break;
        default:
            throw Exception("Wpisales/as niepoprawna opcje.");
    }
    dealership.saveToFile();
}

int main()
{
    Dealership dealership;
    dealership.fetchFromFile();
    while(true){
        try{
            // wypisanie opcji
            mainMenu();

            int decision;
            std::cout<<">";
            std::cin>>decision;
            if(std::cin.fail()){
                clearCin();
                throw Exception("Nie wpisales liczby.");
            }
            // przetworzenie opcji
            processDecision(dealership, decision);
        }
        // catch na custom exception z moich utils.h
        catch(const Exception& e){
            std::cerr<<e.getMessage();
            waitAndClearTerminal(2000);
        }
        // catch na wpisanie niepoprawnego typu danych
        catch(std::invalid_argument&){
            std::cerr<<"Wpisano niepoprawna wartosc.";
            waitAndClearTerminal(3000);
        }
        // catch na inne wyjatki
        catch(...){
            std::cerr<<"Napotkano nieznany wyjatek.";
            waitAndClearTerminal(2000);
        }
    }
    return 0;
}
