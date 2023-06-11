#include <iostream>
#include <locale>

class Transport {
private:
    std::wstring rodzaj_srodka_transportu; // Rodzaj środka transportu (morska, lądowa, powietrzna, kolejowa)
    std::wstring rodzaj; // Rodzaj (np. samochód, pociąg, prom)
    int liczba_osob; // Liczba osób mogących podróżować tym środkiem transportu
    double czas_100km; // Czas w jakim zostanie przebyte 100 km (w godzinach)
    double pojemnosc_paliwa; // Pojemność zbiornika paliwa (w litrach)
    double srednia_predkosc; // Średnia prędkość podróży (w km/h)
    double maksymalna_predkosc; // Maksymalna prędkość podróży (w km/h)

public:
    Transport(std::wstring rodzaj_srodka_transportu, std::wstring rodzaj, int liczba_osob, double czas_100km, double pojemnosc_paliwa, double srednia_predkosc, double maksymalna_predkosc)
        : rodzaj_srodka_transportu(rodzaj_srodka_transportu), rodzaj(rodzaj), liczba_osob(liczba_osob), czas_100km(czas_100km), pojemnosc_paliwa(pojemnosc_paliwa), srednia_predkosc(srednia_predkosc), maksymalna_predkosc(maksymalna_predkosc) {}

    void wpiszInformacje() const {
        std::wcout << L"Rodzaj środka transportu: " << rodzaj_srodka_transportu << std::endl;
        std::wcout << L"Rodzaj: " << rodzaj << std::endl;
        std::wcout << L"Liczba osób: " << liczba_osob << std::endl;
        std::wcout << L"Czas 100 km: " << czas_100km << L" godz." << std::endl;
        std::wcout << L"Pojemność zbiornika paliwa: " << pojemnosc_paliwa << L" l" << std::endl;
        std::wcout << L"Średnia prędkość podróży: " << srednia_predkosc << L" km/h" << std::endl;
        std::wcout << L"Maksymalna prędkość podróży: " << maksymalna_predkosc << L" km/h" << std::endl;
        std::wcout << std::endl;
    }

    double obliczZasieg() const {
        return srednia_predkosc * pojemnosc_paliwa;
    }

    double obliczCzasPodrozy(double odleglosc) const {
        return odleglosc / srednia_predkosc;
    }
};

class Pociag : public Transport {
private:
    int liczba_wagonow; // Liczba wagonów

public:
    Pociag(int liczba_wagonow, std::wstring rodzaj_srodka_transportu, std::wstring rodzaj, int liczba_osob, double czas_100km, double pojemnosc_paliwa, double srednia_predkosc, double maksymalna_predkosc)
        : Transport(rodzaj_srodka_transportu, rodzaj, liczba_osob, czas_100km, pojemnosc_paliwa, srednia_predkosc, maksymalna_predkosc), liczba_wagonow(liczba_wagonow) {}

    int obliczIloscPociagow(double odleglosc) const {
        return static_cast<int>(odleglosc / obliczZasieg()) + 1;
    }
};

class Prom : public Transport {
private:
    double dlugosc_promu; // Długość promu

public:
    Prom(double dlugosc_promu, std::wstring rodzaj_srodka_transportu, std::wstring rodzaj, int liczba_osob, double czas_100km, double pojemnosc_paliwa, double srednia_predkosc, double maksymalna_predkosc)
        : Transport(rodzaj_srodka_transportu, rodzaj, liczba_osob, czas_100km, pojemnosc_paliwa, srednia_predkosc, maksymalna_predkosc), dlugosc_promu(dlugosc_promu) {}

    int obliczIloscPromow(double odleglosc) const {
        return static_cast<int>(odleglosc / obliczZasieg()) + 1;
    }
};

int main() {
    setlocale(LC_ALL, ""); // Ustawienie polskiej lokalizacji

    // Tworzenie obiektu Pociag
    Pociag pociag(10, L"Pociąg", L"kolejowa", 200, 2.5, 5000, 80, 120);
    pociag.wpiszInformacje();
    std::wcout << L"Ilość potrzebnych pociągów: " << pociag.obliczIloscPociagow(15000) << std::endl;
    std::wcout << L"Czas podróży: " << pociag.obliczCzasPodrozy(15000) << L" godz." << std::endl;
    std::wcout << L"Zasięg: " << pociag.obliczZasieg() << L" km" << std::endl;

    std::wcout << std::endl;

    // Tworzenie obiektu Prom
    Prom prom(150, L"Prom", L"morska", 500, 5.0, 10000, 60, 100);
    prom.wpiszInformacje();
    std::wcout << L"Ilość potrzebnych promów: " << prom.obliczIloscPromow(15000) << std::endl;
    std::wcout << L"Czas podróży: " << prom.obliczCzasPodrozy(15000) << L" godz." << std::endl;
    std::wcout << L"Zasięg: " << prom.obliczZasieg() << L" km" << std::endl;

    // Porównanie zasięgu
    double zasieg_pociagu = pociag.obliczZasieg();
    double zasieg_promu = prom.obliczZasieg();

    if (zasieg_pociagu > zasieg_promu) {
        std::wcout << L"Pociąg ma większy zasięg niż prom." << std::endl;
    }
    else if (zasieg_pociagu < zasieg_promu) {
        std::wcout << L"Prom ma większy zasięg niż pociąg." << std::endl;
    }
    else {
        std::wcout << L"Pociąg i prom mają taki sam zasięg." << std::endl;
    }

    return 0;
}