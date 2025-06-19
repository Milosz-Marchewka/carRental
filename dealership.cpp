#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // std::sort(), std::find()
#include "dealership.h"
#include "car.h"
#include "utils.h" // Exception

Dealership::Dealership(){}
Dealership::Dealership(std::vector<Car> cars) : cars(cars){}
Dealership::Dealership(Car car){
    cars.push_back(car);
}
void Dealership::displayCars(){
    if(cars.size() == 0){
        std::cout<<"\nNarazie nie ma zadnych pojazdow.";
        return;
    }
    std::vector<Car> c = sortCars(cars);

    std::cout<<"\nZarejestrowanych pojazdow: "<<c.size()<<std::endl;
    for(int i = 0; i<c.size(); i++){
        Car& car = c[i];
        std::cout<<"------"<<i;
        car.show();
        wait(500);
        std::cout<<"\n";
    }
}
void Dealership::sortedDisplayCars(){
    if(cars.size() == 0){
        std::cout<<"\nNarazie nie ma zadnych pojazdow.";
        return;
    }
    std::vector<Car> c = sortCars(cars);
    std::cout<<"Zarejestrowanych pojazdow: "<<c.size()<<std::endl;
    for(int i = 0; i<c.size(); i++){
        Car& car = c[i];
        std::cout<<"["<<i<<"] ";
        car.smallShow();
        wait(250);
        std::cout<<"\n";
    }
}
void Dealership::reverseDisplayCars(){
    if(cars.size() == 0){
        std::cout<<"\nNarazie nie ma zadnych pojazdow.";
        return;
    }
    std::vector<Car> c = sortCars(cars);
    // sdt::reverse() odwraca kolejnosc vectora
    std::reverse(c.begin(), c.end());
    std::cout<<"Zarejestrowanych pojazdow: "<<c.size()<<std::endl;
    for(int i = 0; i<c.size(); i++){
        Car& car = c[i];
        std::cout<<"["<<i<<"] ";
        car.smallShow();
        wait(250);
        std::cout<<"\n";
    }
}
void Dealership::addCar(const Car& car){
    cars.push_back(car);
}
void Dealership::addCar(){
    Car car;
    car.write();
    addCar(car);
    std::cout<<"\nPomyslnie dodano";
}
void Dealership::removeCar(Car& car){
    // szukanie indeksu auta
    // petla dziala od konca, ze wzgledu na to,
    // ze usuwane elementy powoduja przesuwanie
    // reszty elementow po indeksach.
    for(int i = cars.size() - 1; i>=0; i--){
        // ze wzgledu, ze format pliku jest najbardziej 'unikatowym'
        // wyznacznikiem kazdego obiektu (poniewaz ma w sobie kazde
        // pole obiektu, wiec usuwa wszystkie identyczne auta)
        // to jest porownywane w ten sposob. moznaby alternatywnie w klasie
        // Car przeciazyc operator == i w nim porownac fileFormat aut.
        if(cars[i].getFileFormat() == car.getFileFormat()){
            // usuwa z vectora na indeksie i
            cars.erase(cars.begin() + i);
        }
    }
}
void Dealership::removeCar(){
    sortedDisplayCars();
    // getline zwraca tylko string
    std::string indexS;

    std::cout<<"\nWpisz indeks pojazdu, ktory chcesz usunac. Aby powrocic, nacisnij enter.\n";
    std::cout<<">";
    clearCin();
    std::getline(std::cin, indexS);
    if(checkIfStrEmpty(indexS)) throw Exception("Powracanie...");

    int index = std::stoi(indexS);
    std::vector<Car> c = sortCars(cars);
    if(index<0 || index >= c.size()){
        throw Exception("Wpisano niepoprawny indeks - " + index);
    } else {
        while(true){
            std::string decision;
            std::cout<<"\nCzy jestes pewny, ze chcesz usunac pojazd na indeksie ["<<index<<"]? [T/N]\n";
            std::cout<<">";
            std::cin>>decision;
            if(decision == "T" || decision=="t"){
                removeCar(c[index]);
                std::cout<<"\nPomyslnie usunieto.";
                break;
            } else if(decision=="N" || decision=="n"){
                return;
            } else{
                std::cout<<"\nProsze wpisac T lub N.";
                clearCin();
            }
        }
    }
}
void Dealership::editCar(){
    sortedDisplayCars();
    // getline zwraca tylko string
    std::string indexS;

    std::cout<<"\nWpisz indeks pojazdu, ktory chcesz edytowac. Aby powrocic, nacisnij enter. \n";
    std::cout<<">";
    clearCin();
    std::getline(std::cin, indexS);
    if(checkIfStrEmpty(indexS)) throw Exception("Powracanie...");

    int index = std::stoi(indexS);
    std::vector<Car> c = sortCars(cars);
    if(index<0 || index >= c.size()){
        clearCin();
        throw Exception("Wpisano niepoprawny indeks - " + index);
    } else{
        Car car = c[index];
        for(int i = cars.size() - 1; i>=0; i--){
            if(cars[i].getFileFormat() == car.getFileFormat()){
                    cars[i].edit(car);
                    std::cout<<"\nPomyslnie edytowano.";
                    return;
            }
        }
    }
}
void Dealership::rentCar(Car& car){
    for(int i = cars.size() - 1; i>=0; i--){
        // ze wzgledu, ze format pliku jest najbardziej 'unikatowym'
        // wyznacznikiem kazdego obiektu (poniewaz ma w sobie kazde
        // pole obiektu, wiec usuwa wszystkie identyczne auta)
        // to jest porownywane w ten sposob. moznaby alternatywnie w klasie
        // Car przeciazyc operator == i w nim porownac fileFormat aut.
        if(cars[i].getFileFormat() == car.getFileFormat()){
            if(!cars[i].getAvailable()) throw Exception("To auto nie jest dostepne.");
            cars[i].setAvailability(false);
        }
    }
}
void Dealership::rentCar(){
    sortedDisplayCars();
    // getline zwraca tylko string
    std::string indexS;

    std::cout<<"\nWpisz indeks pojazdu, ktory chcesz wypozyczyc. Aby powrocic, nacisnij enter.\n";
    clearCin();
    std::getline(std::cin, indexS);
    if(checkIfStrEmpty(indexS)) throw Exception("Powracanie...");

    int index = std::stoi(indexS);
    std::vector<Car> c = sortCars(cars);
    if(index<0 || index>=c.size()){
        clearCin();
        throw Exception("Wpisano niepoprawny indeks - " + index);
    } else {
        rentCar(c[index]);
        std::cout<<"\nPomyslnie wypozyczono.";
    }
}
void Dealership::returnCar(Car& car){
    for(int i = cars.size() - 1; i>=0; i--){
        // ze wzgledu, ze format pliku jest najbardziej 'unikatowym'
        // wyznacznikiem kazdego obiektu (poniewaz ma w sobie kazde
        // pole obiektu, wiec usuwa wszystkie identyczne auta)
        // to jest porownywane w ten sposob. moznaby alternatywnie w klasie
        // Car przeciazyc operator == i w nim porownac fileFormat aut.
        if(cars[i].getFileFormat() == car.getFileFormat()){
            if(cars[i].getAvailable()) throw Exception("To auto nie jest nikomu wypozyczone..");
            cars[i].setAvailability(true);
        }
    }
}
void Dealership::returnCar(){
   reverseDisplayCars();
   // getline zwraca tylko string
   std::string indexS;

   std::cout<<"\nWpisz indeks pojazdu, ktory chcesz oddac. Aby powrocic, nacisnij enter.\n";
   std::cout<<">";
   clearCin();
   std::getline(std::cin, indexS);
   if(checkIfStrEmpty(indexS)) throw Exception("Powracanie...");

   std::vector<Car> c = sortCars(cars);
   std::reverse(c.begin(), c.end());
   int index = std::stoi(indexS);
   if(index<0 || index>=c.size()){
        clearCin();
        throw Exception("Wpisano niepoprawny indeks - " + index);
   } else {
       returnCar(c[index]);
        std::cout<<"\nPomyslnie zwrocono.";
   }
}
std::vector<Car> Dealership::sortCars(std::vector<Car>& cars){
    // [](Car, Car) to funkcja lambda, porownuje dostepnosc miedzy autami,
    // zwraca te ktore sa dostepne - w efekcie czego, vector jest
    // posortowany od dostepnych do niedostepnych
    std::vector<Car>c = cars;
    std::sort(c.begin(), c.end(), [](Car& a, Car& b){
        return a.getAvailable() > b.getAvailable();
    });
    return c;
}
void Dealership::fetchFromFile(){
    std::ifstream file(filename);
    std::string line;
    while(std::getline(file, line)){
        if(!line.empty()){
            cars.push_back(Car::fromFileString(line));
        }
    }
}
void Dealership::saveToFile()const{
    std::ofstream file(filename);
    for(const Car& car : cars){
        file<<car.getFileFormat() << "\n";
    }
}

