#include <iostream> // Biblioteka do obsługi strumieni wejścia/wyjścia.
#include <fstream> // Biblioteka do obsługi operacji plikowych.
#include <string> // Biblioteka do obsługi ciągów znaków.
#include <cassert> // Biblioteka do asercji.

using namespace std; // Używanie przestrzeni nazw std.

class Singleton { // Deklaracja klasy Singleton.
private:
    static Singleton* instance; // Pole statyczne przechowujące jedyną instancję klasy.
    string data; // Pole przechowujące dane.

    Singleton() : data("Default Data") { // Prywatny konstruktor ustawiający domyślne dane.

    }

    Singleton(Singleton const&) = delete; // Usunięcie konstruktora kopiującego.
    Singleton& operator=(Singleton const&) = delete; // Usunięcie operatora przypisania.

public:
    ~Singleton() { // Destruktor.

    }

    static Singleton* getInstance() { // Metoda zwracająca instancję klasy.
        if (instance == nullptr) { // Jeśli instancja nie istnieje...
            instance = new Singleton(); // ...utwórz nową.
        }
        return instance; // Zwróć instancję.
    }

    void serialize(const string& filename) { // Metoda serializacji.
        ofstream outFile(filename); // Tworzenie strumienia wyjścia do pliku.
        if (outFile.is_open()) { // Jeśli plik jest otwarty...
            outFile << data; // ...zapisz dane.
            outFile.close(); // Zamknij plik.
            cout << "Serialization successful: Data \"" << data << "\" written to " << filename << endl; // Komunikat o sukcesie.
        }
        else { // Jeśli plik nie jest otwarty...
            cerr << "Unable to open file for writing." << endl; // ...wyświetl komunikat o błędzie.
        }
    }

    void deserialize(const string& filename) { // Metoda deserializacji.
        ifstream inFile(filename); // Tworzenie strumienia wejścia do pliku.
        if (inFile.is_open()) { // Jeśli plik jest otwarty...
            getline(inFile, data); // Odczytaj dane z pliku i zapisz w polu data.
            inFile.close(); // Zamknij plik.
            cout << "Deserialization successful: Data \"" << data << "\" read from " << filename << endl; // Komunikat o sukcesie.
        }
        else { // Jeśli plik nie jest otwarty...
            cerr << "Unable to open file for reading." << endl; // ...wyświetl komunikat o błędzie.
        }
    }

    void setData(const string& newData) { // Metoda ustawiająca nowe dane.
        data = newData;
    }

    string getData() const { // Metoda zwracająca dane.
        return data;
    }
};

Singleton* Singleton::instance = nullptr; // Inicjalizacja statycznego pola instance.

int main() { // Funkcja główna.

    string originalData = "Data before serialization"; // Pierwotne dane.
    Singleton::getInstance()->setData(originalData); // Ustawienie danych w instancji klasy.
    cout << "Setting data to: \"" << originalData << "\"" << endl; // Wyświetlenie pierwotnych danych.

    string filename = "singleton.txt"; // Nazwa pliku.
    Singleton::getInstance()->serialize(filename); // Serializacja danych do pliku.

    Singleton::getInstance()->deserialize(filename); // Deserializacja danych z pliku.

    string deserializedData = Singleton::getInstance()->getData(); // Pobranie zdeserializowanych danych.

    cout << "Original data: \"" << originalData << "\"" << endl; // Wyświetlenie pierwotnych danych.
    cout << "Deserialized data: \"" << deserializedData << "\"" << endl; // Wyświetlenie zdeserializowanych danych.

    assert(originalData == deserializedData); // Asercja, że pierwotne i zdeserializowane dane są takie same.
    cout << "Assertion successful: Original data is equal to deserialized data." << endl; // Komunikat o powodzeniu asercji.

    return 0; // Zwrócenie wartości 0, co oznacza sukces wykonania programu.
}
