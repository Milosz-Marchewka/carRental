#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include "date.h"
#include "fuelType.h"
#include "transmission.h"
#include "condition.h"

class Car{
    std::string licensePlate {""}; // rejestracja
    std::string brand {""}; // marka
    std::string model {""};
    Date prodDate; // data produkcji
    std::string color {""};
    bool isAvailable = false; // czy jest dostepny
    int mileage = 0; // przebieg
    FuelType fuelType = FuelType::Benzyna; // enum - rodzaj paliwa {Benzyna, Diesel, Elektryczny, Hybryda
    Transmission transmission = Transmission::Manualna; // enum - rodzaj skrzyni biegow {Manualna, Automatyczna, PolAutomatyczna}
    Condition condition = Condition::Nowy; // enum - stan pojazdu {Nowy, Doskonaly, Dobry, Przecietny, Slaby, Uszkodzony}
public:
    Car();
    Car(std::string, std::string, std::string, Date, std::string, bool, int, FuelType, Transmission, Condition);
    Car(std::string, std::string, std::string, int, int, int, std::string, bool, int, std::string, std::string, std::string);

    std::string getLicensePlate() const;
    std::string getBrand() const;
    std::string getModel() const;
    Date getProductionDate() const;
    std::string getColor() const;
    bool getAvailable() const;
    int getMileage() const;
    FuelType getFuelType() const;
    Transmission getTransmission() const;
    Condition getCondition() const;

    void setLicensePlate(std::string);
    void setBrand(std::string);
    void setModel(std::string);
    void setProductionDate(Date);
    void setColor(std::string);
    void setAvailability(bool);
    void setMileage(int);
    void setFuelType(FuelType);
    void setTransmission(Transmission);
    void setCondition(Condition);

    std::string getFileFormat() const;
    static Car fromFileString(const std::string&);
    void setCar(std::string, std::string, std::string, Date, std::string, bool, int, FuelType, Transmission, Condition);
    void show() const;
    void smallShow() const;
    void write();
    void edit(Car&);
};

#endif // CAR_H_INCLUDED
