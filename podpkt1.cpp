/*#include <iostream> // Biblioteka do obsługi strumieni wejścia/wyjścia.
#include <mutex> // Biblioteka do obsługi muteksów.
#include <shared_mutex> // Biblioteka do obsługi muteksów dzielonych.
#include <thread> // Biblioteka do obsługi wątków.
#include <vector> // Biblioteka do obsługi kontenerów wektorowych.
#include <chrono> // Biblioteka do obsługi operacji czasowych.

using namespace std; // Używanie przestrzeni nazw std.

class Singleton { // Deklaracja klasy Singleton.
private:
    static Singleton* instance; // Statyczne pole przechowujące jedyną instancję klasy.
    static mutex instanceMutex; // Statyczny muteks kontrolujący dostęp do instancji Singletona.
    string data; // Pole przechowujące dane.
    static shared_mutex dataMutex; // Statyczny muteks dzielony do synchronizacji dostępu do danych.

    Singleton() : data("Default Data") { // Prywatny konstruktor ustawiający domyślne dane.

    }

    Singleton(const Singleton&) = delete; // Usunięcie konstruktora kopiującego.
    Singleton& operator=(const Singleton&) = delete; // Usunięcie operatora przypisania.

public:
    ~Singleton() { // Dekonstruktor.

    }

    static Singleton* getInstance() { // Metoda zwracająca instancję Singletona.
        if (instance == nullptr) { // Jeśli instancja nie istnieje...
            lock_guard<mutex> lock(instanceMutex); // ...blokuj dostęp do instancji...
            if (instance == nullptr) { // ...i jeśli nadal nie istnieje...
                instance = new Singleton(); // ...utwórz nową.
            }
        }
        return instance; // Zwróć instancję.
    }

    void setData(const string& newData) { // Metoda ustawiająca nowe dane.
        unique_lock<shared_mutex> lock(dataMutex); // Blokada unikalna dla zapisu.
        cout << "Starting to set data by thread " << this_thread::get_id() << endl; // Komunikat o rozpoczęciu ustawiania danych.
        data = newData; // Ustawienie nowych danych.
        cout << "Data set to: " << data << " by " << this_thread::get_id() << endl; // Komunikat o ustawionych danych.
    }

    string getData() { // Metoda pobierająca dane.
        shared_lock<shared_mutex> lock(dataMutex); // Blokada współdzielona dla odczytu.
        cout << "Starting to read data by thread " << this_thread::get_id() << endl; // Komunikat o rozpoczęciu odczytu danych.
        cout << "Data read as: " << data << " by " << this_thread::get_id() << endl; // Komunikat o odczytanych danych.
        return data; // Zwrócenie danych.
    }
};

Singleton* Singleton::instance = nullptr; // Inicjalizacja statycznego pola instance.
mutex Singleton::instanceMutex; // Inicjalizacja statycznego muteksu kontrolującego dostęp do instancji Singletona.
shared_mutex Singleton::dataMutex; // Inicjalizacja statycznego muteksu dzielonego do synchronizacji dostępu do danych.

void writeTest(const string& newData, int delay) { // Funkcja testowa dla zapisu danych.
    this_thread::sleep_for(chrono::milliseconds(delay)); // Opóźnienie dla symulacji pracy.
    Singleton::getInstance()->setData(newData); // Ustawienie nowych danych w Singletonie.

    cout << "Reading after writing in thread " << this_thread::get_id() << endl; // Komunikat odczytu danych po zapisie.
    Singleton::getInstance()->getData(); // Odczyt danych z Singletona.
}

void readTest(int delay) { // Funkcja testowa dla odczytu danych.
    this_thread::sleep_for(chrono::milliseconds(delay)); // Opóźnienie dla symulacji pracy.
    Singleton::getInstance()->getData(); // Odczyt danych z Singletona.
}

int main() { // Funkcja główna.
    vector<thread> threads; // Wektor wątków.

    threads.emplace_back(writeTest, "Data from thread 1", 50); // Tworzenie wątku z funkcją zapisującą dane.
    threads.emplace_back(readTest, 10); // Tworzenie wątku z funkcją odczytującą dane.
    threads.emplace_back(readTest, 20); // Tworzenie kolejnego wątku z funkcją odczytującą dane.
    threads.emplace_back(writeTest, "Data from thread 4", 30); // Tworzenie kolejnego wątku z funkcją zapisującą dane.

    for (auto& th : threads) { // Pętla czekająca na zakończenie wątków.
        th.join(); // Oczekiwanie na zakończenie wątku.
    }

    return 0; // Zwrócenie wartości 0, co oznacza sukces wykonania programu.
}
*/