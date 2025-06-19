										                # Salon Samochodowy - projekt szkolny
                    ### DISCLAIMER: To jest projekt szkolny. Został stworzony w 2-3 dni, czas pracy
                    ### około 5h. Zapewne nie wszystko co znajduje się w tym projekcie jest zrobione
                    ### z najlepszymi praktykami, optymalnie lub przystępnie. Celem było stworzenie projektu
                    ### opierającego się o OOP, obsługę plików i wyjątków oraz podstawowe CLI.

											Program jest salonem samochodowym.
											Przechowuje on wszystkie zmiany w pliku cars.txt

											Daje możliwość:
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

											> Uruchomienie
											
											Najłatwiej uruchomić projekt w Codeblocksie, Open Pro-
											ject>Zaznaczyć plik cbp. Jeżeli inne pliki .cpp nie ko-
											mpilują się, trzeba na nich nacisnąć PPM>Properties>
											Build i zaznaczyć build i debug.


						----------------------------------------------------------
													Pseudo-dokumentacja


														    KLASY



													Plik car.h/.cpp


	
	Plik, który zawiera klasę Car, przechowującą dane i metody powiązane z pojedynczym pojazdem. Posiada metody nadpisujące plik z danymi cars.txt.

	> class Car
		private:
		- string licensePlate (tablica rejestracyjna), zainicjowane na ""
		- string brand (marka pojazdu), zainicjowane na ""
		- string model (model pojazdu), zainicjowane na ""
		- Date prodDate (data produkcji), zainicjowane na 0,0,0
		- string color (kolor pojazdu), zainicjowane na ""
		- bool isAvailable (dostępność pojazdu), zainicjowane na false
		- int mileage (przebieg pojazdu), zainicjowane na 0
		- FuelType fuelType (rodzaj napędu/paliwa pojazdu), zainicjowane na Benzyna
		- Transmission transmission (rodzaj skrzyni biegów pojazdu), zainicjowane na Manualna
		- Condition condition (stan pojazdu), zainicjowane na Nowy
		
		public:
		- Car(string, string, string, Date, string, bool, int, FuelType, Transmission, Condition)

		- Car(string, string, string, int, int, int, string, bool, int, string, string, string) - konstruktor, tyle że z typami prymitywnymi zamiast enum/class.
			korzysta z poprzedniego konstruktora, wiąże argumenty za pomocą konstruktora Date() i funkcji stringToX() z plików enum.

		Gettery

		- string getLicensePlate() const - zwraca tablicę rejestracyjną pojazdu

		- string getBrand() const - zwraca markę pojazdu

		- string getModel() const - zwraca model pojazdu

		- Date getProductionDate() const - zwraca datę produkcji pojazdu

		- string getColor() const - zwraca kolor pojazdu

		- bool getAvailable() const - zwraca dostępność pojazdu

		- int getMileage() const - zwraca przebieg pojazdu

		- FuelType getFuelType() const - zwraca rodzaj napędu/paliwa pojazdu

		- Transmission getTransmission() const - zwraca rodzaj skrzyni biegów pojazdu

		- Condition getCondition() const - zwraca stan pojazdu

		Settery

		- void setLicensePlate(string) - setter dla tablicy rejestracyjnej. ma walidację - licensePlateCheck() z utils.h

		- void setBrand(string) - setter dla marki pojazdu

		- void setModel(string) - setter dla modelu pojazdu

		- void setProductionDate(Date) - setter dla daty produkcji pojazdu. ma walidację - porównuje datę wpisaną z dzisiejszą.

		- void setColor(string) - setter dla koloru pojazdu

		- void setAvailability(bool) - setter dla dostępności pojazdu

		- void setMileage(int) - setter dla przebiegu pojazdu. ma walidację - sprawdza czy wartość jest < 0 lub >1'000'000

		- void setFuelType(FuelType) - setter dla rodzaju napędu/paliwa

		- void setTransmission(Transmission) - setter dla rodzaju skrzyni biegów

		- void setCondition(Condition) - setter dla stanu pojazdu

		Inne

		- string getFileFormat() const - zwraca wszystkie pola w formacie gotowym do wszczepienia do pliku cars.txt.
			TablicaRejestracyjna;Marka;Model;DataProdukcji;Kolor;Dostępność;Przebieg;RodzajNapędu;SkrzyniaBiegów;Stan

		- static Car fromFileSring(const string&) - konwertuje string z argumentu (który jest w formacie z pliku, patrz powyżej)
			na obiekt Car

		- void setCar(string, string, string, Date, string, bool, int, FuelType, Transmission, Condition) - setter dla wszystkich
			pól klasy.

		- void show() - pokazuje wszystkie dane pojazdu
		
		- void smallShow() - pokazuje tylko markę, model, tablicę rejestracyjną oraz dostępność pojazdu.

		- void write() - pozwala na wpisanie wartości z klawiatury. używa std::cin oraz setterów. tam gdzie jest to wymagane,
			obsługuje błąd, gdy ktoś wpisze string do int. Jeżeli ktoś wpisze coś niepoprawnego, catch wraca do nie do głównego
			menu, lecz do początku tej metody.

		- void edit(Car&) - użytwa std::getline oraz seterów aby edytować wartości przekazanego obiektu Car. waliduje input użytkownika.
			działa na szablonie write(), więc pętla i try-catch działają tak samo. aby zostawić stare dane, użytkownik może pominąć
			poprzez naciśnięcie enter.



												Plik dealership.h/.cpp



	Plik, który zawiera klasę Dealership, przechowującą vector pojazdów oraz nazwę pliku, do którego zapisują się dane.

	> class Dealership

		private:

		- vector<Car> cars
		- const string filename = "cars.txt"

		public:
		
		- Dealership(vector<Car>) - konstruktor podmieniający vector klasy z argumentem.

		- Dealership(Car) - konstruktor dodający (push_back) argument do vectora klasy.

		- void displayCars() - pokazuje wszystkie pojazdy z vectora klasy. jeżeli nie ma żadnych pojazdów w vektorze, powiadamia
			o tym użytkownika. Sortuje auta po dostępności.
	
		- void sortedDisplayCars() - pokazuje wszystkie pojazdy z vectora klasy wraz z ich indeksami. pokazuje tylko markę, model,
			tablicę rejestracyjną oraz dostępność pokazdu. Sortuje auta po dostępności.

		- void reverseDisplayCars() - pokazuje wszystkie pojazdu z vectora klasy wraz z ich indeksami. pokazuje tylko markę, model,
			tablicę rejestracyjną oraz dostępność pojazdu. Sortuje auta od niedostępnych do dostępnych.

		- void addCar(const Car&) - dodaje (push_back) auto do vectora klasy.

		- void addCar() - tworzy obiekt car, wywołuję funkcję write(), która pozwala wpisać wartości auta, po czym wywołuje powyższą
			metodę z wcześniej utworzonym obiektem jako argument.

		- void removeCar(Car&) - korzystając z pętli, sprawdza czy getFileFormat() obiektu w argumencie zgadza się z obecnym obiektem
			cars[index]. jeżeli się zgadza, to usuwa korzystajac z metody wektora erase(index).

			Dlaczego getFileFormat()? 
				Porównanie wykorzystuje akurat tą metodę, ponieważ zawiera ona najwięcej unikatowych informacji o pojeździe,
				gdyż jest to string, w którym wartości obiektu są oddzielone średnikami.

		- void removeCar() - wyświetla auta za pomocą metody sortedDisplayCars(). prosi użytkownika o wpisanie indeksu pojazdu, który
			chce usunąć. jeżeli użytkownik nie wpisał liczby lub indeks poza rozmiarem vectora, robi throw.
			jeżeli dobrze wpisane, wywołuje funkcje removeCar(Car&) z argumentem cars[index] (czyli obiektem Car z vectora cars,
			który występuje na indeksie index).
		
		- void editCar() - wyświetla auta za pomocą metody sortedDisplayCars(). prosi użytkownika o wpisanie indeksu pojazdu, który
			chce edytwaoć. jeżeli użytkownik nie wpisał liczby lub indeks poza rozmiarem vectora, robi throw.
			jeżeli dobrze wpisane, wywołuje funkcję car::edit(Car&) z argumentem cars[index].

		- void rentCar(Car&) - jeżeli pojazd jest dostępny (getAvailable()) to zmienia jego dostępność na false. jeżeli getAvailable()
			zwraca false, to robi throw.

		- void rentCar() - wyświetla auta za pomocą metody sortedDisplayCars(). prosi użytkownika o wpisanie indeksu pojazdu, który
			chce wypożyczyć. jeżeli użytkownik nie wpisał liczby lub indeks poza rozmiarem vectora, robi throw.
			jeżeli dobrze wpisane, wywołuje funkcje rentCar(Car&) z argumentem cars[index] (czyli obiektem Car z vectora cars,
			który występuje na indeksie index).

		- void returnCar(Car&) - jeżeli pojazd nie jest dostępny (!getAvailable()), to zmienia jego dostępność na true. jeżeli getAvailable()
			zwraca true, to robi throw.

		- void returnCar() - wyświetla auta za pomocą metody sortedDisplayCars(). prosi użytkownika o wpisanie indeksu pojazdu, który
			chce zwrócić. jeżeli użytkownik nie wpisał liczby lub indeks poza rozmiarem vectora, robi throw.
			jeżeli dobrze wpisane, wywołuje funkcję returnCar(Car&) z argumentem cars[index] (czyli obiektem Car z vectora cars,
			który występuje na indeksie index).
		
		- void sortCars() - sortuje pojazdy w vectorze od dostępnych do niedostępnych. używa metody sort() z biblioteki <algorithm>.
			w parametrze przekazuje początek vectora pojazdów, jego koniec, oraz funkcję lamba, która porównuje dwa obiekty Car
			i zwraca ten, który ma większą dostępność (a.getAvailable() > b.getAvailable()ponieważ true to 1, a false to 0).

		- void fetchFromFile() - używa ifstream z biblioteki <fstream>. czyta linię z pliku, i jeżeli nie jest pusta, to dodaje (push_back)
			linię do vectora za pomocą metody statycznej Car::fromFileString(string), która konwertuje linię w obiekt Car.

		- void saveToFile() - używa ofstream z biblioteki <fstream>. iteruje po obiektach z vectora i dodaje je do pliku.


												Plik date.h/.cpp


	Plik z klasą Date, która przechowuje rok, miesiąc oraz dzień. Posiada gettery i settery do poszczególnych
	pól, jak i metodą zwracającą pełną datę oraz metodą statyczną, która zwraca obiekt o dacie dzisiejszej.

	> Date
		- private int year, month, day; zainicjowane na 0.
	
		- Date(int, int, int)
			
		Gettery

		- int getYear() const - zwraca rok

		- int getMonth() const - zwraca miesiąc

		- string getMonthFormatted() - zwraca miesiąc w formatowaniu, jako string - miesiąc maj jako int byłby 5, a tutaj zwraca "05".
			korzysta z <ostringstream> aby ustawić szerokość stringa na 0, dopełnia '0' do tej szerokości.

		- int getDay() const - zwraca dzień

		- string getDayFormatted() -  zwraca dzień w formatowaniu, jako string - dzień jako int byłby np. 1, a tutaj zwraca "01".
			korzysta z <ostringstream> aby ustawić szerokość stringa na 0, dopełnia '0' do tej szerokości.

		- string getDate() const - zwraca datę w formatowaniu dd.mm.yyyy

		- static Date today() - zwraca obiekt Date z wartościami odpowiadającymi dacie systemowej. używa biblioteki <windows.h>.

		- static int currentYear() - zwraca int z rokiem z daty systemowej, <windows.h>
		
		- static int currentMonth() - zwraca int z miesiącem z daty systemowej, <windows.h>
		
		-static int currentDay() - zwraca int z dniem z daty systemowej, <windows.h>

		Settery

		- void setYear(int) - setter na rok
	
		- void setMonth(int) - setter na miesiąc

		- void setDay(int) - setter na dzień

		- void setDate(int, int, int) - setter dla każdej wartości

		Walidacja

		- static void validateDate(Date) - walidacja daty względem daty systemowej oraz pod względem liczbowym ( < 0, > 12, > 31, itp.)
		- static void validateDate(int, int, int) - walidacja daty względem daty systemowej oraz pod względem liczbowym ( < 0, > 12, > 31, itp.)
		(po co jest wersja z int,int,int, jeżeli w parametrze pierwszej metody można użyć konstruktora? ponieważ jest to użyte do walidowania daty
		również w konstruktorze. więc konstruktor wywołałby metodę, która wywołuje konstruktor, który wywołuje tą metodę... i czarna dziura znana 
		jako stack overflow error)




													PLIKI Z KLASAMI ENUM




												Plik fuelType.h/.cpp

	
	Plik, który zawiera enum class FuelType, która określa napęd/rodzaj paliwa pojazdu. Posiada dwie funkcje związane z jeg strukturą. 

	> enum class FuelType - Benzyna, Diesel, Elektryczny, Hybryda

	- FuelType stringToFuelType(string) - sprawdza, czy string w argumencie jest taki sam, jak nazwa któregokolwiek z członków enuma FuelType.
		wstępnie formatuje stringa używając enumFormat(string) z utils.h, następnie porównuje go z każdym członkiem enuma. Jeżeli nie znajdzie
		członków takich samych jak string, to robi throw.
	
	- string fuelTypeToString(FuelType) - odwrotność poprzedniej funkcji - switchuje argument, i zwraca odpowiedni string. Jeżeli nie znajdzie, to
		robi throw.


												Plik transmission.h/.cpp


	
	Plik, który zawiera enum class Transmission, która określa rodzaj skrzyni biegów pojazdu. Posiada dwie funkcje związane z jego strukturą.

	> enum class Transmission - Manualna, Automatyczna, PolAutomatyczna

	- Transmission stringToTransmission(string) - sprawdza, czy string w argumencie jest taki sam, jak nazwa któregokolwiek z członków enuma
		Transmission. Wstępnie formatuje stringa używając enumFormat(string) z utils.h, następnie porównuje go z każdym członkiem enuma.
		Jeżeli nie znajdzie członków takich samych jak string, to robi throw.

	- string transmissionToString(Transmission) - odwrotność poprzedniej funkcji - switchuje argument, i zwraca odpowiedni string. Jeżeli nie znajdzie,
		to robi throw.



												Plik condition.h/.cpp




	Plik, który zawiera enum class Condition, która określa stan pojazdu. Posiada dwie funkcje związane z jego strukturą.

	> enum class Condition - Nowy, Doskonaly, Dobry, Przecietny, Slaby, Uszkodzony

	- Condition stringToCondition(string) - sprawdza, czy string w argumencie jest taki sam, jak nazwa któregokolwiek z członkó enuma
		Condition. Wstępnie formatuje stringa używając enumFormat(string) z utils.h, następnie porównuje go z każdym członkiem enuma.
		Jeżeli nie znajdzie członków takich samych jak string, to robi throw.

	- string conditionToString(Condition) - odwrotność poprzedniej funkcji - switchuje argument, i zwraca odpowiedni string. Jeżeli nie znajdzie,
		to robi throw.



														    INNE



												Plik utils.h/.cpp


	Plik z funkcjami pomocniczymi i klasą Exception, która dziedziczy po std::exception

	> Exception
		- string getMessage() const - zwraca wiadomość z błędem

	- bool enumFormat(string&) - jeżeli string nie jest pusty, zwraca true i modifikuje go aby pasował do
 		formatu, który występuje w klasach enum (FuelType, Transmission, Condition) - Wielka litera na początku,
		reszta to litery małe. jeżeli string jest pusty, zwraca false.

	- void licensePlateCheck(string) - regex (biblioteka <regex>, std::regex_match), sprawdza czy tablica
 		rejestracyjna z parametru pasuje do paternu XX-XXXXX lub XXX-XXXXX. jeżeli nie pasuje, to robi throw.
	
	- Date dateCheck(string) - regex, sprawdza czy data pasuje do paternu (dd.mm.yyyy). jeżeli nie pasuje, to
		robi throw, jeżeli pasuje to zwraca obiekt Date z rozdzielonych wartości ze stringa.

	- void clearTerminal() - używa biblioteki <windows.h>, czyści terminal za pomocą system("cls"). system() 
		system() powoduje wpisanie parametru do konsoli, a "cls" to parametr, który powoduje jej wyczyszczenie.
		(czyli po prostu powoduje wpisanie cls do konsoli, co ją czyści.)
	
	- void wait(int) - parametr to ilość milisekund, ile program odczeka, przed wykonaniem dalszych czynności.
		używa bibliotki <chrono> aby uzyskać milisekundy z int, a <thread> aby czekać. 
	
	- void waitAndClear(int) - wiąże razem funckje clearTerminal() i wait(int).

	- void clearCin() - głównie użyte aby wyczyścić \n przed getline lub po std::cin.fail(), które dzieje się 
		jak ktoś w std::cin wpisze niepoprawny typ danych (np. string do int). zostawione, powoduje słabe 
		zachowanie się programu. funkcja czyści skutków std::cin z buffera, używając std::cin.clear() i 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'). korzysta z biblioteki <limits>

	- bool checkIfStrEmpty(string&) - jeżeli string jest pusty, zwraca true, jeżeli nie jest, to zwraca false.


						                    MAIN()



	Działanie:

		Na początku programu, tworzony jest obiekt klasy Dealership. Następnie, wczytywane są dane z pliku cars.txt.
		Reszta programu dzieje się w pętli.

		Wewnątrz pętli występuje try...catch(), który po błędzie powoduje powrót do ekranu głównego.
		
		Program wyświetla opcje, jakie użytkownik może wpisać za pomocą funkcji mainMenu().
		Program prosi użytkownika, aby wpisał opcję, którą chce.
		Jeżeli użytkownik wpisze nie liczbę, program robi throw.

		Następnie, program przetwarza wybór użytkownika za pomocą funkcji processDecision(Dealership&, int)
		Jeżeli użytkownik wybrał 0, pokazuje wszystkie pojazdu za pomocą funkcji pomocniczej displayCars(Dealership)
		Jeżeli użytkownik wybrał 1, daje mu możliwość dodania pojazdu za pomocą funkcji pomoczniczej addCar(Dealership&) 
		Jeżeli użytkownik wybrał 2, daje mu możliwość usunięcia pojazdu za pomocą funkcji pomoczniczej deleteCar(Dealership&)
		Jeżeli użytkownik wybrał 3, daje mu możliwość edytowania pojazdu za pomocą funkcji pomoczniczej editCar(Dealership&)
		Jeżeli użytkownik wybrał 4, daje mu możliwość wypożyczenia pojazdu za pomocą funkcji pomoczniczej rentCar(Dealership&)
		Jeżeli użytkownik wybrał 5, daje mu możliwość zwrotu pojazdu za pomocą funkcji pomocniczej returnCar(Dealership&)

		Jeżeli użytkownik wpisał liczbę poza zakresem <1;5>, program robi throw.


	Funkcje:


		- void mainMenu() - pokazuje użytkownikowi, jakie opcje może wpisać.

		- void displayCars(Dealership) - funkcja pomocnicza, która wywołuje Dealership::displayCars(), i pozwala wrócić do menu po naciśnięciu Enter.

		- void addCar(Dealership&) - funkcja pomocnicza, która wywołuje Dealership::addCar(), oraz powiadamia użytkownika o dodaniu i powraca do menu
			 po 3 sekundach od dodania.

		- void removeCar(Dealership&) - funkcja pomocnicza, która wywołuje Dealership::removeCar(), oraz powiadamia użytkownika o usunięciu i powraca
			do menu po 3 sekundach od usunięcia.

		- void rentCar(Dealership&) - funkcja pomocnicza, która wywołuje Dealership::rentCar(), oraz powiadamia użytkownika o wypożyczeniu i powraca
			do menu po 3 sekundach od wypożyczenia.

		- void returnCar(Dealership&) - funkcja pomocnicza, która wywołuje Dealership::returnCar(), oraz powiadamia użytkownika o zwrocie i powraca
			do menu po 3 sekundach od zwrotu.

		- void processDecision(Dealership&, int) - funkcja, która przetwarza wybór użytkownika. switchuje int z argumentu, jeżeli 0 to wywołuje funkcję
			displayCars(Dealership), jeżeli 1 to wywołuje funkcję addCar(Dealership&), jeżeli 2 to wywołuje funkcję removeCar(Dealership&), jeżeli
			3 to wywołuje funkcję removeCar(Dealership&), jeżeli 4 to wywołuje funkcję returnCar(Dealership&). Jeżeli otrzymał inną cyfrę, to robi
			throw. Po wykonaniu całej logiki, wywołuje Dealership::saveToFile() aby zapisać zmiany.
			
