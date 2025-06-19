#include <iostream>
#include <string>
#include <vector>
#include "car.h"
#include "fuelType.h" // stringToFuelType(), fuelTypeToString()
#include "transmission.h" // stringToTransmission(), transmissionToString()
#include "condition.h" // stringToCondition(), conditionToString()
#include "utils.h" // Exception, wait()
#include "date.h" // walidacja

Car::Car(){}
Car::Car(std::string licensePlate,std::string brand,std::string model,Date prodDate,std::string color,bool isAvailable,int mileage,FuelType fuelType,Transmission transmission,Condition condition):
    licensePlate(licensePlate),
    brand(brand),
    model(model),
    prodDate(prodDate),
    color(color),
    isAvailable(isAvailable),
    mileage(mileage),
    fuelType(fuelType),
    transmission(transmission),
    condition(condition){}

// drugi konstruktor, przyjmuje atomowe wartosci obiektow z pierwszego, czyli rok, miesiac, dzien zamiast Date, itp.
// korzysta z pierwszego konstruktora, przekazuje mu wartosci tyle ze z konstruktorami/funkcjami
Car::Car(std::string licensePlate, std::string brand, std::string model, int year, int month, int day, std::string color, bool isAvailable, int mileage, std::string fuelType, std::string transmission, std::string condition)
    :Car(licensePlate, brand, model, Date(year, month, day), color, isAvailable, mileage, stringToFuelType(fuelType), stringToTransmission(transmission), stringToCondition(condition)){}
    // gettery
std::string Car::getLicensePlate() const{ return this->licensePlate;}
std::string Car::getBrand() const{ return this->brand; }
std::string Car::getModel() const{ return this->model; }
Date Car::getProductionDate() const{ return this->prodDate; }
std::string Car::getColor() const{ return this->color; }
bool Car::getAvailable() const{ return this->isAvailable; }
int Car::getMileage() const{ return this->mileage; }
FuelType Car::getFuelType() const{ return this->fuelType; }
Transmission Car::getTransmission() const{ return this->transmission;}
Condition Car::getCondition() const{ return this->condition; }

    // settery
void Car::setLicensePlate(std::string licensePlate){
    licensePlateCheck(licensePlate);
    this->licensePlate = licensePlate;
}
void Car::setBrand(std::string brand){ this->brand = brand;}
void Car::setModel(std::string model){ this->model = model; }
void Car::setProductionDate(Date prodDate){
    // sprawdza czy rok jest mniejszy od obecnego i wiekszy od 1950
    Date::validateDate(prodDate);
    this->prodDate = prodDate;
}
void Car::setColor(std::string color){ this->color = color;}
void Car::setAvailability(bool isAvailable){
    this->isAvailable = isAvailable;
}
void Car::setMileage(int mileage){
    // sprawdza czy przebieg jest wiekszy od 0 i mniejszy od 1'000'000
    if(mileage >= 0 && mileage < 1'000'000){
        this->mileage = mileage;
    } else {
        throw Exception("Podany przebieg jest niepoprawny - " + std::to_string(mileage));
    }
}
void Car::setFuelType(FuelType fuelType){ this->fuelType = fuelType;}
void Car::setTransmission(Transmission transmission){this->transmission = transmission;}
void Car::setCondition(Condition condition){this->condition = condition;}

std::string Car::getFileFormat()const{
    return licensePlate + ";" + brand + ";" + model + ";" + getProductionDate().getDate() + ";" + color + ";" + std::to_string(isAvailable) + ";" + std::to_string(mileage) + ";" + fuelTypeToString(fuelType) + ";" + transmissionToString(transmission) + ";" + conditionToString(condition);
}
Car Car::fromFileString(const std::string& line){
    std::vector<size_t>pos;
    size_t start = 0;

    for(int i = 1; i<=9; i++){
        size_t found = line.find(";", start);
        if(found == std::string::npos){ // jak nie znajduje, to zwraca npos
            throw Exception("Blad podczas pobierania danych z pliku");
        }
        pos.push_back(found);
        start = found+1;
    }
    std::vector<std::string>car;
    car.push_back(line.substr(0, pos[0]));

    for(int i = 1; i<9; i++){
        size_t len = pos[i] - pos[i-1] - 1;
        car.push_back((line.substr(pos[i-1] + 1, len)));
    }
    car.push_back(line.substr(pos[8]+1));

    std::string dateStr = car[3];
    if(dateStr.size() != 10){
        throw Exception("Blad z formatem daty z pliku.");
    }
    int day = std::stoi(dateStr.substr(0,2));
    int month = std::stoi(dateStr.substr(3,2));
    int year = std::stoi(dateStr.substr(6,4));
    Date date(year, month, day);
    return Car(car[0], car[1], car[2], date, car[4], std::stoi(car[5]), std::stoi(car[6]), stringToFuelType(car[7]), stringToTransmission(car[8]), stringToCondition(car[9]));
}

void Car::setCar(std::string licensePlate,std::string brand,std::string model,Date prodDate,std::string color,bool isAvailable,int mileage,FuelType fuelType,Transmission transmission,Condition condition){
    setLicensePlate(licensePlate);
    setBrand(brand);
    setModel(model);
    setProductionDate(prodDate);
    setColor(color);
    setAvailability(isAvailable);
    setMileage(mileage);
    setFuelType(fuelType);
    setTransmission(transmission);
    setCondition(condition);
}
void Car::show() const{
    std::cout<<"----------";
    std::cout<<"\n"<<getBrand()<<" "<<getModel()<<" - "<<getLicensePlate()<<" - "<<(getAvailable() ? " Dostepny" : " Niedostepny");
    std::cout<<"\nData produkcji: "<<getProductionDate().getDate();
    std::cout<<"\nTyp paliwa: "<<fuelTypeToString(getFuelType());
    std::cout<<"\nSkrzyna biegow: "<<transmissionToString(getTransmission());
    std::cout<<"\nStan: "<<conditionToString(getCondition());
    std::cout<<"\nPrzebieg: "<<getMileage()<< "km";
    std::cout<<"\nKolor: "<<getColor();
}
void Car::smallShow() const{
    std::cout<<getBrand()<<" "<<getModel()<<" - "<<getLicensePlate()<<" - "<<(getAvailable() ? "Dostepny" : "Niedostepny");
}
void Car::write(){
    while(true){
        try{
            std::string licensePlate, brand, model, color, fuelType, transmission, condition, date;
            int mileage, available;

            std::cout<<"==============";
            std::cout<<"\nPodaj tablice rejestracyjna auta (XX-XXXXX lub XXX-XXXXX): ";
            std::cout<<"\n>";
            std::cin>>licensePlate;
            clearCin();
            setLicensePlate(licensePlate);

            std::cout<<"Podaj marke auta: ";
            std::cout<<"\n>";
            std::getline(std::cin, brand);
            setBrand(brand);

            std::cout<<"Podaj model auta: ";
            std::cout<<"\n>";
            std::getline(std::cin, model);
            setModel(model);

            std::cout<<"Podaj date produkcji auta (dd.mm.rrrr): ";
            std::cout<<"\n>";
            std::cin>>date;
            clearCin();
            setProductionDate(dateCheck(date));

            std::cout<<"Podaj kolor auta: ";
            std::cout<<"\n>";
            std::getline(std::cin, color);
            setColor(color);

            std::cout<<"Podaj dostepnosc auta";
            std::cout<<"\n[0] - Niedostepny";
            std::cout<<"\n[1] - Dostepny";
            std::cout<<"\nDostepnosc: ";
            std::cout<<"\n>";
            std::cin>>available;
            // jezeli wpisano cos innego niz liczba, i nie jest 0 lub 1
            if(std::cin.fail() || (available != 0 && available != 1)){
                // wyczyszczenie std::cin i throw
                clearCin();
                throw Exception("Nie wpisales/as poprawnej wartosci");
            }
            clearCin();
            setAvailability(available);

            std::cout<<"Podaj przebieg auta(km): ";
            std::cout<<"\n>";
            std::cin>>mileage;
            clearCin();
            setMileage(mileage);

            std::cout<<"Podaj naped auta";
            std::cout<<"\n - Benzyna";
            std::cout<<"\n - Diesel";
            std::cout<<"\n - Elektryczny";
            std::cout<<"\n - Hybryda";
            std::cout<<"\nNaped: ";
            std::cout<<"\n>";
            std::cin>>fuelType;
            clearCin();
            setFuelType(stringToFuelType(fuelType));

            std::cout<<"Podaj rodzaj skrzyni biegow auta";
            std::cout<<"\n - Manualna";
            std::cout<<"\n - Automatyczna";
            std::cout<<"\n - Pol automatyczna";
            std::cout<<"\nSkrzynia biegow: ";
            std::cout<<"\n>";
            std::getline(std::cin, transmission);
            setTransmission(stringToTransmission(transmission));

            std::cout<<"Podaj stan pojazdu";
            std::cout<<"\n - Nowy";
            std::cout<<"\n - Doskonaly";
            std::cout<<"\n - Dobry";
            std::cout<<"\n - Przecietny";
            std::cout<<"\n - Slaby";
            std::cout<<"\n - Uszkodzony";
            std::cout<<"\nStan: ";
            std::cout<<"\n>";
            std::cin>>condition;
            clearCin();
            setCondition(stringToCondition(condition));
            break;
        }
        catch(Exception& e){
            std::cout<<e.getMessage()<<std::endl;
            wait(2000);
            system("cls");
            std::cout<<"Wpisz ponownie.\n";
        }
    }
}
void Car::edit(Car& car){
    while(true){
        try{
            std::string licensePlate, brand, model, color, fuelType, transmission, condition, date, mileageS, availableS;

            std::cout<<"==============";
            std::cout<<"\nAktualna tablica rejestracyjna: "<<car.getLicensePlate();
            std::cout<<"\nPodaj tablice rejestracyjna auta (XX-XXXXX lub XXX-XXXXX), lub enter aby zachowac stara wartosc: ";
            std::cout<<"\n>";
            std::getline(std::cin, licensePlate);
            if(checkIfStrEmpty(licensePlate)) std::cout<<"Zachowanie starej wartosci.\n";
            else setLicensePlate(licensePlate);

            std::cout<<"\nAktualna marka auta: "<<car.getBrand();
            std::cout<<"\nPodaj marke auta, lub enter aby zachowac stara wartosc: ";
            std::cout<<"\n>"<<std::flush;
            std::getline(std::cin, brand);
            if(checkIfStrEmpty(brand)) std::cout<<"Zachowanie starej wartosci.\n";
            else setBrand(brand);

            std::cout<<"\nAktualny model auta: "<<car.getModel();
            std::cout<<"\nPodaj model auta, lub enter aby zachowac stara wartosc: ";
            std::cout<<"\n>";
            std::getline(std::cin, model);
            if(checkIfStrEmpty(model)) std::cout<<"Zachowanie starej wartosci.\n";
            else setModel(model);

            std::cout<<"\nAktualna data produkcji auta: "<<car.getProductionDate().getDate();
            std::cout<<"\nPodaj date produkcji auta (dd.mm.rrrr), lub enter aby zachowac stara wartosc: ";
            std::cout<<"\n>";
            std::getline(std::cin, date);
            if(checkIfStrEmpty(date)) std::cout<<"Zachowanie starej wartosci.\n";
            else setProductionDate(dateCheck(date));

            std::cout<<"\nAktualny kolor auta: "<<car.getColor();
            std::cout<<"\nPodaj kolor auta, lub enter aby zachowac stara wartosc: ";
            std::cout<<"\n>";
            std::getline(std::cin, color);
            if(checkIfStrEmpty(color)) std::cout<<"Zachowanie starej wartosci.\n";
            else setColor(color);

            std::cout<<"\nAktualna dostepnosc auta: "<<(car.getAvailable() ? "Dostepny" : "Niedostepny");
            std::cout<<"\nPodaj dostepnosc auta, lub enter aby zachowac stara wartosc";
            std::cout<<"\n[0] - Niedostepny";
            std::cout<<"\n[1] - Dostepny";
            std::cout<<"\nDostepnosc: ";
            std::cout<<"\n>";
            std::getline(std::cin, availableS);
            if(checkIfStrEmpty(availableS)) std::cout<<"Zachowanie starej wartosci.\n";
            else{
                int available = std::stoi(availableS);
                if(available != 0 && available != 1){
                throw Exception("Nie wpisales/as poprawnej wartosci");
                } else{
                    setAvailability(available);
                }
            }

            std::cout<<"\nAktualny przebieg auta: "<<car.getMileage()<<" km";
            std::cout<<"\nPodaj przebieg auta(km), lub enter aby zachowac stara wartosc: ";
            std::cout<<"\n>";
            std::getline(std::cin, mileageS);
            if(checkIfStrEmpty(mileageS)) std::cout<<"Zachowanie starej wartosci.\n";
            else{
                int mileage = std::stoi(mileageS);
                if(mileage < 0 || mileage > 1'000'000){
                    throw Exception("Wpisano niepoprawna wartosc.");
                } else{
                    setMileage(mileage);
                }
            }

            std::cout<<"\nAktualny naped auta: "<<fuelTypeToString(car.getFuelType());
            std::cout<<"\nPodaj naped auta, lub enter aby zachowac stara wartosc";
            std::cout<<"\n - Benzyna";
            std::cout<<"\n - Diesel";
            std::cout<<"\n - Elektryczny";
            std::cout<<"\n - Hybryda";
            std::cout<<"\nNaped: ";
            std::cout<<"\n>";
            std::getline(std::cin, fuelType);
            if(checkIfStrEmpty(fuelType)) std::cout<<"Zachowanie starej wartosci.\n";
            else setFuelType(stringToFuelType(fuelType));

            std::cout<<"\nAktualny rodzaj skrzyni biegow auta: "<<transmissionToString(car.getTransmission());
            std::cout<<"\nPodaj rodzaj skrzyni biegow auta, lub enter aby zachowac stara wartosc";
            std::cout<<"\n - Manualna";
            std::cout<<"\n - Automatyczna";
            std::cout<<"\n - Pol automatyczna";
            std::cout<<"\nSkrzynia biegow: ";
            std::cout<<"\n>";
            std::getline(std::cin, transmission);
            if(checkIfStrEmpty(transmission)) std::cout<<"Zachowanie starej wartosci.\n";
            else setTransmission(stringToTransmission(transmission));

            std::cout<<"\nAktualny stan pojazdu: "<<conditionToString(car.getCondition());
            std::cout<<"\nPodaj stan pojazdu, lub enter aby zachowac stara wartosc";
            std::cout<<"\n - Nowy";
            std::cout<<"\n - Doskonaly";
            std::cout<<"\n - Dobry";
            std::cout<<"\n - Przecietny";
            std::cout<<"\n - Slaby";
            std::cout<<"\n - Uszkodzony";
            std::cout<<"\nStan: ";
            std::cout<<"\n>";
            std::getline(std::cin, condition);
            if(checkIfStrEmpty(condition)) std::cout<<"Zachowanie starej wartosci.\n";
            else setCondition(stringToCondition(condition));
            break;
        }
        catch(Exception& e){
            std::cout<<e.getMessage()<<std::endl;
            wait(2000);
            system("cls");
            std::cout<<"Wpisz ponownie.\n";
        }
    }
}
