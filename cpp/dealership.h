#ifndef DEALERSHIP_H_INCLUDED
#define DEALERSHIP_H_INCLUDED
#include <vector>
#include <fstream>
#include "car.h";

class Dealership{
    std::vector<Car> cars;
    const std::string filename = "cars.txt";
public:
    Dealership();
    Dealership(std::vector<Car>);
    Dealership(Car);

    void displayCars();
    void sortedDisplayCars();
    void reverseDisplayCars();

    void addCar(const Car&);
    void addCar();

    void removeCar(Car&);
    void removeCar();

    void editCar();

    void rentCar();
    void rentCar(Car&);

    void returnCar();
    void returnCar(Car&);

    void saveToFile() const;
    void fetchFromFile();
    std::vector<Car> sortCars(std::vector<Car>&);
};

#endif // DEALERSHIP_H_INCLUDED
