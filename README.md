# Seaport_SO2
Projekt z przedmiotu systemy operacyjne 2

Uruchamianie:
g++ main.cpp vehicles/Truck.cpp vehicles/Vehicle.cpp vehicles/Ship.cpp stoppingPlaces/Dock.cpp stoppingPlaces/TruckParkingArea.cpp view/ConsoleView.cpp view/NcursesView.cpp PortAdministrator.cpp Seaport.cpp -o main -lncurses
./main

Ogólny opis projektu:
W ramach zajęć projektowych z przedmiotu Systemy Operacyjne 2 stworzony został projekt, który jest symulacją pracy portu morskiego. W wspomnianej symulacji statki oraz samochody ciężarowe przewożą oraz przeładowują ładunki. Zademonstrowany został również proces cumowania statków oraz parkowania samochodów ciężarowych, kiedy to pojazdy wysyłają prośbę do administratora portu o pozwolenie na wykonanie operacji. Pojazdy mogą przystąpić do cumowania lub parkowania dopiero po uzyskaniu zgody. Sytuacja wygląda identycznie w przypadku opuszczania portu. Program jest aplikacją wielowątkową i w głównej mierz skupiała się na synchronizacji dostępu do zasobów współdzielonych przez wątki oraz na eliminacji zakleszczeń. Projekt został sporządzony w języku c++, z wykorzystaniem biblioteki ncorses do wizualizacji.

Założenia projektowe:
+	W porcie morskim zachodzą procesy takie jak rozładunek i załadunek statków oraz samochodów ciężarowych.
+	Port morski ma określoną liczbę miejsc do cumowania statków oraz do parkowania samochodów ciężarowych, których rozdysponowywaniem zajmuje się administrator portu.
+	Statki oraz samochody ciężarowe mają określoną maksymalną ładowność, która jest losowo przypisywana przy tworzeniu danego obiektu.
+	Statki oraz samochody ciężarowe przyjeżdżające do portu mogą być puste (bez ładunku) lub mogą zawierać określony ładunek. 
+	By wyładować ładunek z statku o dużej pojemności może być konieczne wykorzystanie kilku pustych ciężarówek o łącznej ładowności równej lub większej od ładunku na danym statku.
+	Port opuszczają tylko statki oraz samochody ciężarowe, które początkowo były puste i w porcie zostały załadowane ładunkiem lub na odwrót. Przykładowo, kiedy załadowywany statek wpływa do portu, musi najpierw zostać opróżniony.
+	Każdy statek oraz samochód ciężarowymająokreślony czas, do kiedy może pozostać w porcie. Przed upływem tego czasu musi zostać rozładowany i opuścić port.
+	Każdy z statków oraz samochodów ciężarowych jest tworzony w osobnym wątku. 
+	Statek lub samochód ciężarowy chcący wpłynąć do portu lub wypłynąć z portu wysyła prośbę o pozwolenie na tą operację do administratora portu, a następnie wyczekuje pozytywnej odpowiedzi.
+	Administrator portu odpowiada na prośby statków i samochodów ciężarowych chcących wpłynąć do portu, na podstawie wolnych miejsc do cumowania i parkowania oraz tego czy dany statek jest potrzeby w porcie (pusty / załadowny).
+	Działania administratora odbywają się w trybie ciągłym (działa w osobnym wątku).
+	Statki i samochody ciężarowe wysyłające prośbę o pozwolenie na wpłynięcie do portu przechowywane są w kolejce priorytetowej (w zależności od czasu wymaganego do opuszczenia portu), do której dostęp ma tylko administrator portu.

