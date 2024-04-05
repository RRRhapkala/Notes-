#include <iostream> // Biblioteka do obsługi strumieni wejścia/wyjścia.
#include <thread> // Biblioteka do obsługi wątków.
#include <vector> // Biblioteka do obsługi kontenerów wektorowych.
#include <string> // Biblioteka do obsługi ciągów znaków.

using namespace std; // Używanie przestrzeni nazw std.

class Singleton { // Deklaracja klasy Singleton.
private:
    thread_local static Singleton* instance; // Pole statyczne z określeniem wątkowości, przechowujące jedyną instancję klasy.
    string data; // Pole przechowujące dane.

    Singleton() : data("Default Data") { // Prywatny konstruktor ustawiający domyślne dane.

    }

    Singleton(Singleton const&) = delete; // Usunięcie konstruktora kopiującego.
    Singleton& operator=(Singleton const&) = delete; // Usunięcie operatora przypisania.

public:
    ~Singleton() { // Dekonstruktor.

    }

    static Singleton* getInstance() { // Metoda zwracająca instancję klasy.
        if (instance == nullptr) { // Jeśli instancja nie istnieje...
            instance = new Singleton(); // ...utwórz nową.
        }
        return instance; // Zwróć instancję.
    }

    void setData(const string& newData) { // Metoda ustawiająca nowe dane.
        data = newData;
    }

    string getData() const { // Metoda zwracająca dane.
        return data;
    }


    static Singleton* getInstanceAddress() { // Metoda zwracająca adres instancji.
        return instance;
    }
};

thread_local Singleton* Singleton::instance = nullptr; // Inicjalizacja statycznego pola instance z określeniem wątkowości.

void testFunction(const int i) { // Funkcja testowa.
    Singleton::getInstance()->setData("Data from thread " + to_string(i)); // Ustawienie danych w instancji klasy dla danego wątku.
    cout << "Thread " << i << " instance address: " << Singleton::getInstanceAddress() << endl; // Wyświetlenie adresu instancji dla danego wątku.
}

int main() { // Funkcja główna.
    vector<thread> threads; // Wektor wątków.

    for (int i = 0; i < 5; i++) { // Pętla tworząca wątki.
        threads.push_back(thread(testFunction, i)); // Tworzenie wątku i dodanie go do wektora.
    }

    for (auto& th : threads) { // Pętla czekająca na zakończenie wątków.
        th.join(); // Oczekiwanie na zakończenie wątku.
    }

    return 0; // Zwrócenie wartości 0, co oznacza sukces wykonania programu.
}
