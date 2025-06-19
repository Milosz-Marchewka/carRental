# Salon Samochodowy - projekt szkolny

### DISCLAIMER: To jest projekt szkolny. Został stworzony w 2-3 dni, czas pracy  
### około 7h. Zapewne nie wszystko co znajduje się w tym projekcie jest zrobione  
### z najlepszymi praktykami, optymalnie lub przystępnie. Celem było stworzenie projektu  
### opierającego się o OOP, obsługę plików i wyjątków oraz podstawowe CLI.

---

Program jest salonem samochodowym.  
Przechowuje on wszystkie zmiany w pliku cars.txt  
Sam program działa po Polsku, tyle że kod jest napisany  
w języku angielskim.

# Daje możliwość:
- wyświetlenia wszystkich pojazdów
- dodania pojazdu
- usunięcia pojazdu
- wypożyczenia pojazdu
- zwrotu pojazdu

# Struktura plików
- main.cpp - zbiór wszystkiego, działanie programu
- dealership.cpp/.h - logika związana z obsługą wielu pojazdów
- car.cpp/.h - logika związana z obsługą pojedynczego pojazdu
- condition.cpp/.h - stan pojazdu
- fuelType.cpp/.h - rodzaj napędu/paliwa
- transmission.cpp/.h - rodzaj skrzyni biegów
- utils.cpp/.h - funkcje pomocnicze

# Uruchomienie
											
Projekt jest oryginalnie stworzony w Code::Blocks. 
Jednakże, nie załączam tutaj plików .cbp itp.
Zalecam otwarcie projektu w Visual Studio 2022
lub Visual Studio Code (z kompilatorem g++)

----------------------------------------------------------
# Pseudo-dokumentacja

## KLASY

## Plik car.h/.cpp
Plik, który zawiera klasę Car, przechowującą dane i metody powiązane z pojedynczym pojazdem. Posiada metody nadpisujące plik z danymi cars.txt.

## `Klasa Car`

### Metody prywatne:
- `string licensePlate` – tablica rejestracyjna, zainicjowana na `""`
- `string brand` – marka pojazdu, zainicjowana na `""`
- `string model` – model pojazdu, zainicjowana na `""`
- `Date prodDate` – data produkcji, zainicjowana na `0,0,0`
- `string color` – kolor pojazdu, zainicjowana na `""`
- `bool isAvailable` – dostępność pojazdu, zainicjowana na `false`
- `int mileage` – przebieg pojazdu, zainicjowany na `0`
- `FuelType fuelType` – rodzaj napędu/paliwa, zainicjowany na `Benzyna`
- `Transmission transmission` – rodzaj skrzyni biegów, zainicjowany na `Manualna`
- `Condition condition` – stan pojazdu, zainicjowany na `Nowy`

---

### Metody publiczne:

#### Konstruktory:
- `Car(string, string, string, Date, string, bool, int, FuelType, Transmission, Condition)`
- `Car(string, string, string, int, int, int, string, bool, int, string, string, string)`  
  Korzysta z poprzedniego konstruktora, łączy argumenty za pomocą konstruktora `Date()` i funkcji `stringToX()` z plików `enum`.

---

### Gettery:
- `string getLicensePlate() const`
- `string getBrand() const`
- `string getModel() const`
- `Date getProductionDate() const`
- `string getColor() const`
- `bool getAvailable() const`
- `int getMileage() const`
- `FuelType getFuelType() const`
- `Transmission getTransmission() const`
- `Condition getCondition() const`

---

### Settery:
- `void setLicensePlate(string)` – z walidacją: `licensePlateCheck()` z `utils.h`
- `void setBrand(string)`
- `void setModel(string)`
- `void setProductionDate(Date)` – waliduje datę z dzisiejszą
- `void setColor(string)`
- `void setAvailability(bool)`
- `void setMileage(int)` – walidacja: `< 0` lub `> 1_000_000`
- `void setFuelType(FuelType)`
- `void setTransmission(Transmission)`
- `void setCondition(Condition)`

---

### Inne metody:
- `string getFileFormat() const`  
  Zwraca dane w formacie do zapisu do `cars.txt`:  
  `TablicaRejestracyjna;Marka;Model;DataProdukcji;Kolor;Dostępność;Przebieg;RodzajNapędu;SkrzyniaBiegów;Stan`

- `static Car fromFileString(const string&)` – konwertuje string z pliku na obiekt `Car`

- `void setCar(...)` – ustawia wszystkie pola klasy

- `void show()` – pokazuje wszystkie dane pojazdu

- `void smallShow()` – pokazuje tylko markę, model, tablicę rejestracyjną oraz dostępność

- `void write()` – pozwala na wpisywanie wartości z klawiatury przy pomocy `std::getline` i setterów.  
  Obsługuje wyjątki przy błędnych danych. W razie błędu wraca na początek metody, a nie do głównego menu.

- `void edit(Car&)` – używa `std::getline` i setterów do edycji danych przekazanego obiektu.  
  Waliduje dane, działa jak `write()`. Użytkownik może pominąć dane, naciskając `Enter`.

---

## Plik dealership.h/.cpp
Plik, który zawiera klasę Dealership, przechowującą vector pojazdów oraz nazwę pliku, do którego zapisują się dane.

## `Klasa Dealership`

### Pola prywatne:
- `vector<Car> cars`
- `const string filename = "cars.txt"`

---

### Metody publiczne:

#### Constructors:
- `Dealership(vector<Car>)`  
  Konstruktor podmieniający vector klasy z argumentem.
- `Dealership(Car)`  
  Konstruktor dodający (`push_back`) argument do vectora klasy.

---

#### Metody wyświetlające:
- `void displayCars()`  
  Pokazuje wszystkie pojazdy z vectora klasy. Jeżeli nie ma żadnych pojazdów, powiadamia użytkownika. Sortuje auta po dostępności.
- `void sortedDisplayCars()`  
  Pokazuje wszystkie pojazdy wraz z indeksami. Wyświetla tylko markę, model, tablicę rejestracyjną oraz dostępność pojazdu. Sortuje auta po dostępności.
- `void reverseDisplayCars()`  
  Pokazuje wszystkie pojazdy wraz z indeksami. Wyświetla tylko markę, model, tablicę rejestracyjną oraz dostępność pojazdu. Sortuje auta od niedostępnych do dostępnych.

---

#### Dodawanie pojazdów:
- `void addCar(const Car&)`  
  Dodaje auto do vectora klasy (`push_back`).
- `void addCar()`  
  Tworzy obiekt `Car`, wywołuje metodę `write()` (pozwala na wpisanie danych auta), a następnie dodaje go do vectora (poprzez powyższą metodę).

---

#### Usuwanie pojazdów:
- `void removeCar(Car&)`  
  Sprawdza w pętli, czy `getFileFormat()` argumentu zgadza się z obiektem w vectorze. Jeśli tak, usuwa go za pomocą `erase(index)`.  
  **Dlaczego `getFileFormat()`?**  
  Ponieważ zawiera najwięcej unikatowych informacji o pojeździe w formacie string oddzielonym średnikami.
- `void removeCar()`  
  Wyświetla auta (`sortedDisplayCars()`), prosi użytkownika o indeks pojazdu do usunięcia.  
  Jeśli indeks jest niepoprawny lub nie jest liczbą, rzuca wyjątek.  
  Poprawny indeks wywołuje `removeCar(Car&)` z odpowiednim obiektem.

---

#### Edytowanie pojazdów:
- `void editCar()`  
  Wyświetla auta (`sortedDisplayCars()`), prosi użytkownika o indeks pojazdu do edycji.  
  Jeśli indeks jest niepoprawny lub nie jest liczbą, rzuca wyjątek.  
  Poprawny indeks wywołuje `Car::edit(Car&)` na wybranym obiekcie.

---

#### Wypożyczanie pojazdów:
- `void rentCar(Car&)`  
  Jeżeli pojazd jest dostępny (`getAvailable() == true`), zmienia dostępność na `false`.  
  Jeśli pojazd jest niedostępny, rzuca wyjątek.
- `void rentCar()`  
  Wyświetla auta (`sortedDisplayCars()`), prosi użytkownika o indeks pojazdu do wypożyczenia.  
  Jeśli indeks jest niepoprawny lub nie jest liczbą, rzuca wyjątek.  
  Poprawny indeks wywołuje `rentCar(Car&)` na wybranym obiekcie.

---

#### Zwracanie pojazdów:
- `void returnCar(Car&)`  
  Jeżeli pojazd nie jest dostępny (`getAvailable() == false`), zmienia dostępność na `true`.  
  Jeśli pojazd jest już dostępny, rzuca wyjątek.
- `void returnCar()`  
  Wyświetla auta (`sortedDisplayCars()`), prosi użytkownika o indeks pojazdu do zwrotu.  
  Jeśli indeks jest niepoprawny lub nie jest liczbą, rzuca wyjątek.  
  Poprawny indeks wywołuje `returnCar(Car&)` na wybranym obiekcie.

---

#### Sortowanie:
- `void sortCars()`  
  Sortuje pojazdy w vectorze od dostępnych do niedostępnych.  
  Używa `std::sort()` z funkcją lambda:  
  ```cpp
  [](const Car& a, const Car& b) { return a.getAvailable() > b.getAvailable(); }

#### File operations:
- `void fetchFromFile()`  
  Używa `ifstream` z biblioteki `<fstream>`.  
  Czyta plik linia po linii, a jeśli linia nie jest pusta, tworzy obiekt `Car` za pomocą statycznej metody:  
  ```cpp
  Car::fromFileString(string)

- `void saveToFile()`  
  Używa `ofstream` z biblioteki `<fstream>`.  
  Iteruje po vectorze `cars` i dla każdego obiektu wywołuje metodę `getFileFormat()`.  
  Zwrócone linie zapisuje do pliku `cars.txt`.

## Plik date.h/.cpp
Plik z klasą Date, która przechowuje rok, miesiąc oraz dzień. Posiada gettery i settery do poszczególnych
pól, jak i metodą zwracającą pełną datę oraz metodą statyczną, która zwraca obiekt o dacie dzisiejszej.

## `Klasa Date`

### Pola prywatne:
- `int year = 0`
- `int month = 0`
- `int day = 0`

---

### Metody publiczne:

#### Konstruktor:
- `Date(int year, int month, int day)`  
  Konstruktor ustawiający wartości daty.

---

#### Gettery:
- `int getYear() const`  
  Zwraca rok.
- `int getMonth() const`  
  Zwraca miesiąc.
- `string getMonthFormatted()`  
  Zwraca miesiąc jako string w formacie dwucyfrowym, np. `"05"` dla maja.  
  Wykorzystuje `<ostringstream>` do dopełnienia zera i ustawienia szerokości na 2.
- `int getDay() const`  
  Zwraca dzień.
- `string getDayFormatted()`  
  Zwraca dzień jako string w formacie dwucyfrowym, np. `"01"`.  
  Wykorzystuje `<ostringstream>` do dopełnienia zera i ustawienia szerokości na 2.
- `string getDate() const`  
  Zwraca datę w formacie `"dd.mm.yyyy"`.

---

#### Statyczne metody związane z datą systemową (wymagają `<windows.h>`):
- `static Date today()`  
  Zwraca obiekt `Date` z aktualną datą systemową.
- `static int currentYear()`  
  Zwraca bieżący rok.
- `static int currentMonth()`  
  Zwraca bieżący miesiąc.
- `static int currentDay()`  
  Zwraca bieżący dzień.

---

#### Settery:
- `void setYear(int)`  
  Ustawia rok.
- `void setMonth(int)`  
  Ustawia miesiąc.
- `void setDay(int)`  
  Ustawia dzień.
- `void setDate(int, int, int)`  
  Ustawia rok, miesiąc i dzień jednocześnie.

---

#### Walidacja:
- `static void validateDate(Date)`  
  Waliduje datę względem aktualnej daty systemowej oraz pod względem wartości liczbowych (np. miesiąc < 1 lub > 12, dzień < 1 lub > 31 itp.).
- `static void validateDate(int year, int month, int day)`  
  Ta wersja przyjmuje wartości jako int i jest używana m.in. w konstruktorze, aby uniknąć rekurencji (stack overflow).  
  Zapobiega to sytuacji, w której konstruktor wywołuje metodę walidującą, która tworzy kolejny obiekt `Date` i znów wywołuje walidację — co prowadziłoby do błędu przepełnienia stosu.





# PLIKI Z KLASAMI ENUM




## Plik fuelType.h/.cpp
Plik, który zawiera enum class FuelType, która określa napęd/rodzaj paliwa pojazdu. Posiada dwie funkcje związane z jeg strukturą. 

## `enum class FuelType`
- `Benzyna`
- `Diesel`
- `Elektryczny`
- `Hybryda`

---

## Funkcje związane z `FuelType`

### `FuelType stringToFuelType(string)`
- Przyjmuje string, formatuje go wstępnie za pomocą `enumFormat(string)` (z `utils.h`).
- Porównuje sformatowany string z nazwami członków enuma `FuelType`.
- Zwraca odpowiedni `FuelType`, jeśli znajdzie zgodność.
- Rzuca wyjątek (`throw`), jeśli nie znajdzie pasującego członka.

### `string fuelTypeToString(FuelType)`
- Przyjmuje wartość `FuelType`.
- Używa `switch` do zwrócenia odpowiadającego stringa dla każdej wartości enuma.
- Rzuca wyjątek (`throw`), jeśli wartość nie pasuje do żadnego przypadku.



## Plik transmission.h/.cpp
Plik, który zawiera enum class Transmission, która określa rodzaj skrzyni biegów pojazdu. Posiada dwie funkcje związane z jego strukturą.

## `enum class Transmission`
- `Manualna`
- `Automatyczna`
- `PolAutomatyczna`

---

## Funkcje związane z `Transmission`

### `Transmission stringToTransmission(string)`
- Przyjmuje string, formatuje go wstępnie za pomocą `enumFormat(string)` (z `utils.h`).
- Porównuje sformatowany string z nazwami członków enuma `Transmission`.
- Zwraca odpowiedni `Transmission`, jeśli znajdzie zgodność.
- Rzuca wyjątek (`throw`), jeśli nie znajdzie pasującego członka.

### `string transmissionToString(Transmission)`
- Przyjmuje wartość `Transmission`.
- Używa `switch` do zwrócenia odpowiadającego stringa dla każdej wartości enuma.
- Rzuca wyjątek (`throw`), jeśli wartość nie pasuje do żadnego przypadku.



## Plik condition.h/.cpp
Plik, który zawiera enum class Condition, która określa stan pojazdu. Posiada dwie funkcje związane z jego strukturą.

## `enum class Condition`
- `Nowy`
- `Doskonaly`
- `Dobry`
- `Przecietny`
- `Slaby`
- `Uszkodzony`

---

## Funkcje związane z `Condition`

### `Condition stringToCondition(string)`
- Przyjmuje string, formatuje go wstępnie za pomocą `enumFormat(string)` (z `utils.h`).
- Porównuje sformatowany string z nazwami członków enuma `Condition`.
- Zwraca odpowiedni `Condition`, jeśli znajdzie zgodność.
- Rzuca wyjątek (`throw`), jeśli nie znajdzie pasującego członka.

### `string conditionToString(Condition)`
- Przyjmuje wartość `Condition`.
- Używa `switch` do zwrócenia odpowiadającego stringa dla każdej wartości enuma.
- Rzuca wyjątek (`throw`), jeśli wartość nie pasuje do żadnego przypadku.




# INNE



## Plik utils.h/.cpp
Plik z funkcjami pomocniczymi i klasą Exception, która dziedziczy po std::exception

### Exception class
- `string getMessage() const`  
  Zwraca wiadomość z błędem.
  
---

## Funkcje pomocniczne

### `bool enumFormat(string&)`
- Jeżeli string nie jest pusty, modyfikuje go tak, aby miał format enuma:  
  - Pierwsza litera wielka, reszta małe.  
- Zwraca `true` jeśli string nie był pusty, `false` jeśli był pusty.

### `void licensePlateCheck(string)`
- Sprawdza, czy tablica rejestracyjna pasuje do wzorca:  
  - `XX-XXXXX` lub `XXX-XXXXX`  
- Używa `std::regex_match` z biblioteki `<regex>`.  
- Rzuca wyjątek, jeśli nie pasuje do wzorca.

### `Date dateCheck(string)`
- Sprawdza, czy data pasuje do wzorca `dd.mm.yyyy` za pomocą regex.  
- Jeśli nie pasuje, rzuca wyjątek.  
- Jeśli pasuje, zwraca obiekt `Date` z rozdzielonych wartości stringa.

### `void clearTerminal()`
- Czyści terminal.  
- Używa `system("cls")` z `<windows.h>`.  
- Wpisuje do konsoli polecenie `cls`, które ją czyści.

### `void wait(int)`
- Czeka określoną ilość milisekund.  
- Parametr: czas w ms (int).  
- Używa `<chrono>` i `<thread>`.

### `void waitAndClear(int)`
- Najpierw czeka określony czas (`wait(int)`),  
- Następnie czyści terminal (`clearTerminal()`).

### `void clearCin()`
- Czyści bufor wejściowy `std::cin` po błędnym wejściu.  
- Używa `std::cin.clear()` i `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')`.  
- Korzysta z `<limits>`.

### `bool checkIfStrEmpty(string&)`
- Zwraca `true`, jeśli string jest pusty,  
- Zwraca `false` w przeciwnym przypadku.



# MAIN() - Przebieg programu i funkcje

## Działanie programu:

- Na początku programu tworzony jest obiekt klasy `Dealership`.
- Następnie wczytywane są dane z pliku `cars.txt`.
- Reszta programu działa w pętli.

### Wewnątrz pętli:

- Blok `try...catch()` obsługuje błędy i powoduje powrót do ekranu głównego w przypadku wyjątku.
- Program wyświetla opcje użytkownika za pomocą funkcji `mainMenu()`.
- Prosi użytkownika o wybór opcji.
- Jeśli użytkownik wpisze coś innego niż liczba, rzucany jest wyjątek (`throw`).
- Wybór użytkownika jest przetwarzany przez funkcję `processDecision(Dealership&, int)`:
  - `0` — pokazuje wszystkie pojazdy (`displayCars(Dealership)`)
  - `1` — dodaje pojazd (`addCar(Dealership&)`)
  - `2` — usuwa pojazd (`removeCar(Dealership&)`)
  - `3` — edytuje pojazd (`editCar(Dealership&)`)
  - `4` — wypożycza pojazd (`rentCar(Dealership&)`)
  - `5` — zwraca pojazd (`returnCar(Dealership&)`)
- Jeśli wpisana liczba jest poza zakresem `<0;5>`, rzucany jest wyjątek (`throw`).

---

## Funkcje:

### `void mainMenu()`
- Wyświetla użytkownikowi dostępne opcje.

### `void displayCars(Dealership)`
- Wywołuje `Dealership::displayCars()`.
- Pozwala użytkownikowi wrócić do menu po naciśnięciu Enter.

### `void addCar(Dealership&)`
- Wywołuje `Dealership::addCar()`.
- Powiadamia użytkownika o dodaniu pojazdu.
- Wraca do menu po 3 sekundach.

### `void removeCar(Dealership&)`
- Wywołuje `Dealership::removeCar()`.
- Powiadamia użytkownika o usunięciu pojazdu.
- Wraca do menu po 3 sekundach.

### `void rentCar(Dealership&)`
- Wywołuje `Dealership::rentCar()`.
- Powiadamia użytkownika o wypożyczeniu pojazdu.
- Wraca do menu po 3 sekundach.

### `void returnCar(Dealership&)`
- Wywołuje `Dealership::returnCar()`.
- Powiadamia użytkownika o zwrocie pojazdu.
- Wraca do menu po 3 sekundach.

### `void processDecision(Dealership&, int)`
- Przetwarza wybór użytkownika:
  - `0` → wywołuje `displayCars(Dealership)`
  - `1` → wywołuje `addCar(Dealership&)`
  - `2` → wywołuje `removeCar(Dealership&)`
  - `3` → wywołuje `editCar(Dealership&)`
  - `4` → wywołuje `rentCar(Dealership&)`
  - `5` → wywołuje `returnCar(Dealership&)`
  - Inna wartość → rzuca wyjątek (`throw`)
- Po wykonaniu akcji wywołuje `Dealership::saveToFile()` aby zapisać zmiany.

