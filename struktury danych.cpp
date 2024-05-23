#include <iostream>
#include <fstream>
#include <random>
#include <locale.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
const long long rozmiar = 1500;
void generateRandomNumbers(const string& plik) {
    ofstream file(plik); //otwiera plik do zapisu
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, rozmiar-1);

    int wyjatki[rozmiar]; //tablica bez powtorzen
    int count = 0; //zlicza wygenerowane liczby

    while(count < rozmiar) { //dziala dopoki count jest mniejsze niż rozmiar
        int num = distr(gen); // tworzy losowa liczbe

        // sprawdza czy liczba jest w tablicy
        bool isDuplicate = false;
        for(int i = 0; i < count; i++) {
            if(wyjatki[i] == num) {
                isDuplicate = true;
            }
        }

        if(!isDuplicate) {
            // jesli nie to ja dodaje
            wyjatki[count] = num;
            count++;
        }
    }

    file << rozmiar << endl; //zapisuje jako pierwszy element rozmiar

    for(int i = 0; i < rozmiar; i++) {
        file << wyjatki[i] << endl; // zapisuje wszystko do pliku
    }

    file.close(); // zamyka plik
}
 
void ZapiszCzas(const string& nazwaPliku, long long czas, const string& nazwaFunkcji) {
    std::ofstream plik(nazwaPliku, ios::app);
    if (plik.is_open()) {
        plik << nazwaFunkcji << ";" << czas <<endl;
        plik.close();
    } else {
       cout << "Nie udało się otworzyć pliku";
    }
}

/////////////tablica//////////////
int* Zaladuj(const string& plik, int& n) {
    ifstream file(plik);
    n = 0;                      //n- rozmiar zawsze w tym kodzie
    int number;                //zmienna do przechowywania liczb w pliku
    while(file >> number) {
        n++;
    }
    file.clear();                //wyczysc flagi bledów strumienia
    file.seekg(0, ios::beg);    //przesun wskaźnik pliku na poczatek

    int* numbers = new int[n]; // utwoez nowa tablice o odpowiednim rozmiarze

    int i = 0; // zaczynamy od indeksu 0
    while(file >> number) {
        numbers[i++] = number;
    }
    file.close();        //zamknij plik
    return numbers;     //zwroc liczby
}

int* DodajKoniecTablicy(int* T, int& n, int elem) {
    int* newT = new int[n+1];       //stwórz nową tablice większą
    for(int i=0; i<n; i++)
        newT[i] = T[i];           //kopiuj elementy z starej tablicy do nowej
    newT[n] = elem;              //dodja nowy element na koniec tablicy
    n++;                            //zwieksz rozmiar tablicy
    delete[] T;              //usuwa stara by zwolnic pamiec
    return newT;               //zwroc tablice
}

int* DodajPoczatekTablicy(int* T, int& n, int elem) {
    int* newT = new int[n+1];   //tworzysz nowa tablice o jeden wieksza
    newT[0] = elem;            //dodajemy nowy element na poczatek
    for(int i=0; i<n; i++)
        newT[i+1] = T[i];     //przepisujemy reszte
    n++;                      //zwiekszamy rozmiar
    delete[] T;              //usuwa stara by zwolnic pamiec
    return newT;              //zwracamy nowa tablice
}

int* DodajWybranyTablica(int* T, int& n, int elem, int pos) {
    if(pos < 0 || pos > n) {
        cout << "zła pozycja" << endl;
        return T;        //zwraca bez zmian
    }
    int* newT = new int[n+1];      //stwórz nową tablice większą
    for(int i=0; i<pos; i++)
        newT[i] = T[i];           //przepisuje do podajen pozycji
    newT[pos] = elem;             //wstawia
    for(int i=pos; i<n; i++)     //przepisuje od kolejnego do konca
        newT[i+1] = T[i]; 
    n++;                        //zwieksza rozmiar
    delete[] T;                        //usuwa stara by zwolnic pamiec
    return newT;               //zwraca nowa tablice
}

void SzukajTablica(int* T, int n, int wartosc) {
    bool znalazles = false;
    for(int i=0; i<n; i++){
        if(T[i]==wartosc){        //jesli element pasuje do wartosci
            cout<<"znaleziono"<<endl;  //zwraca znaleziono
            znalazles=true;           //zmienia znalazles na tru
        }
    }
    if(!znalazles){
       cout<<"nie znaleziono"<<endl;   //jesli nie znalazles zwroc nie znalezion
    }
}

int* UsunPierwszyTablica(int* t, int& n) {
    if (n <= 0) return nullptr;      //jesli nie ma nic w tablicy zwroc 0

    int* newT = new int[n - 1];     //tworzy tablice mniejsza o 1
    for (int i = 0; i < n - 1; ++i) {
        newT[i] = t[i + 1];                         //skopiuj elementy starej do nowej
    }
    --n;                                        //zmiejsz rozmiar

    delete[] t;         //usuwa tablice by zwolnic pamiec
    return newT;        //zwraca nowa
}

int* UsunOstatniTablica(int* t, int& n) {
    if (n <= 0) return nullptr;      //jesli pusta zwraca null

    int* newT = new int[n - 1];     //tworzy tablice o jeden mniejsza
    for (int i = 0; i < n - 1; ++i) {
        newT[i] = t[i];                      //copiuje elementy
    }
    --n;                                      //zmiejsz rozmiar

    delete[] t;                 //usuwa stara by zmiejszyc rozmiar
    return newT;                //zwraca nowa tablice
}

int* UsunWybranyTablica(int* t, int& n, int poz) {
    if (poz < 0 || poz >= n) {         //jesli pozycja jest poza zakresem
        cout << "Nieprawidłowa pozycja" << endl;
        return t;                                                      //zwraca stara tablice
    }

    int* newT = new int[n - 1];            //tworzy tablice mnjesza
    for (int i = 0; i < poz; ++i) {        //przepisuje elementy przed
        newT[i] = t[i];
    }
    for (int i = poz + 1; i < n; ++i) { //przepisuje elementy po
        newT[i - 1] = t[i];
    }

    --n;                               //rozmiar
    delete[] t;                        //usuwa stara by zwolnic pamiec
    return newT;                       //zwraca nowa tablice
}


void switchTablica(int* tablica, int& n) {
    int robota=1, gdzie= 1, pozycja;
    auto start = high_resolution_clock::now(); auto koniec = high_resolution_clock::now();    auto duration = duration_cast<nanoseconds>(koniec-start).count();
    



    while (robota != 0) {
        cout << "Co chcesz zrobić z tablicą?: " << endl << "1. Wczytaj z pliku" << endl << "2. Wyświetl" << endl << "3. Wstaw" << endl << "4. Szukaj" << endl << "5. Usuń" << endl<< "0. Powrót" << endl;
        cin >> robota;

        switch (robota) {
            case 1:
                tablica = Zaladuj("liczby.txt", n);
                break;
            case 2:
                if (tablica != nullptr) {
                    for (int i = 0; i < n; i++) {
                        cout << tablica[i] << " ";
                    }
                    cout << endl;
                } else {
                    cout << "Tablica nie została zainicjalizowana." << endl;
                }
                break;
            case 3:
                cout << "Gdzie chcesz dodać element?: 1 - początek, 2 - sam wybiorę miejsce, 3 - koniec, 0 - powrót ";
                cin >> gdzie;
                switch (gdzie) {
                    case 1:
                         start = high_resolution_clock::now();
                        tablica = DodajPoczatekTablicy(tablica, n, 420);
                         koniec = high_resolution_clock::now();
                         duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"DodajPoczatekTablicy");
                        break;
                    case 2:
                        cout << "Wybierz pozycję: ";
                        cin >> pozycja;
                         start = high_resolution_clock::now();
                        tablica = DodajWybranyTablica(tablica, n, 2137, pozycja);
                         koniec = high_resolution_clock::now();
                         duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"DodajWybranyTablica");
                        break;
                    case 3:
                        start = high_resolution_clock::now();
                        tablica = DodajKoniecTablicy(tablica, n, 666);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"DodajKoniecTablicy");
                        break;
                    default:
                        cout << "Powrót do menu głównego." << endl;
                        break;
                }
                break;
            case 4:
                cout << "Podaj pozycję do wyszukania: ";
                cin >> pozycja;
                start = high_resolution_clock::now();
                SzukajTablica(tablica, n, pozycja);
                koniec = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(koniec-start).count();
                ZapiszCzas("wynik.txt",duration,"SzukajTablica");
                break;
            case 5:
                cout << "Który element chcesz usunąć?: 1 - początek, 2 - sam wybiorę miejsce, 3 - koniec, 0 - powrót ";
                cin >> gdzie;
                switch (gdzie) {
                    case 1:
                        start = high_resolution_clock::now();
                        tablica = UsunPierwszyTablica(tablica, n);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"UsunPierwszyTablica");
                        break;
                    case 2:
                        cout << "Wybierz pozycję: ";
                        cin >> pozycja;
                        start = high_resolution_clock::now();
                        tablica = UsunWybranyTablica(tablica, n, pozycja-1);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"UsunWybranyTablica");
                        break;
                    case 3:
                        start = high_resolution_clock::now();
                        tablica = UsunOstatniTablica(tablica, n);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"UsunOstatniTablica");
                        break;
                    default:
                        cout << "Powrót do menu głównego." << endl;
                        break;
                }
                break;
            default:
                cout << "Powrót do menu głównego." << endl;
                break;
        }
    }
}


/////////////lista liniowa//////////////
struct Wezel{                            //definicja struktury wezla
    int dane;                           //pole ktore przechowuje dane
    Wezel* kolejny;                    //wskaznik na nastepny wezel
};


Wezel* WczytajDoListy(const string& plik) {
    int n;                                 // rozmiar
    int* numbers = Zaladuj(plik, n);       // wczytanie liczb z pliku

    Wezel* head = nullptr;                 // inicjacja wskaznika na glowe
    Wezel* tail = nullptr;                 // inicjacja wskaznika na ogon
    for (int i = 0; i < n; i++) {          // iteracja przez wczytane liczby
        Wezel* newWezel = new Wezel;      // tworzenie nowego wezla
        newWezel->dane = numbers[i];      // przypisanie danych wezlowi
        newWezel->kolejny = nullptr;      // ustawienie wskaznika na kolejny wezel

        if (head == nullptr) {            // jesli lista jest pusta, ustawiamy nowy wezel jako glowe i ogon
            head = newWezel;
            tail = newWezel;
        } else {                          // w przeciwnym razie dodajemy nowy wezel na koniec listy
            tail->kolejny = newWezel;
            tail = newWezel;
        }
    }

    delete[] numbers; // zwalniamy pamięć zaalokowaną dla tablicy numbers
    return head;       // zwracamy wskaźnik na głowę listy
}

Wezel* DodajKoniecListy(Wezel* head, int elem) {
    Wezel* newWezel = new Wezel;             //tworzenie nowego wezla
    newWezel->dane = elem;                  //przypisanie danych wezlowi
    newWezel->kolejny = nullptr;           //ustawienie wskaznika na kolejny wezel

    if (head == nullptr) {                 //jesli glowa jest pusta to przypisz jej nowy wezel
        head = newWezel;
    } else {                              //w przeciwnym razie dodaj nowy wezel na koniec listy
        Wezel* temp = head;              //temp dostaje wartosc glowy
        while (temp->kolejny != nullptr) {    //przechodzi przez liste do ostatniego wezla
            temp = temp->kolejny;
        }
        temp->kolejny = newWezel;             //po przejsciu dodajemy nowy wezel na koniec listy
    }

    return head;
}

Wezel* DodajPoczatekListy(Wezel* head, int elem) {
    Wezel* newWezel = new Wezel;         //tworzenie nowego wezla
    newWezel->dane = elem;              //przypisanie danych wezlowi
    newWezel->kolejny = head;          //ustawienie wstaznika na nastepny wezel na glowe
    return newWezel;                  //zwrocenie nowego wezla jako glowy listy
}

Wezel* DodajWybranyLista(Wezel* head, int elem, int pos) {
    Wezel* newWezel = new Wezel;            //tworzenie nowego wezla
    newWezel->dane = elem;                 //przypisanie danych wezlowi

    if (pos == 0) {                     //jesli pozycją jest 0 to doajemy na poczatek
        newWezel->kolejny = head;
        return newWezel;
    }

    Wezel* temp = head;                                          //temp dostaje wartosc glowy
    for (int i = 0; i < pos - 1 && temp != nullptr; i++) {      //przechodzimy przez liste do wybranej pozycji
        temp = temp->kolejny;
    }

    if (temp == nullptr) {                //jeśli pozycja jest nieprawidłowa
        cout << "zła pozycja" << endl;
        delete newWezel;                  //usuwamy nowy wezel
        return head;                     //zwracamy glowe
    }

    newWezel->kolejny = temp->kolejny;     //ustawienie wskaznika nowego wezla na pozycji po temp
    temp->kolejny = newWezel;             //ustawienie wstaznika temp->kolejny na wartosc nowego wezla
    return head;
}

void SzukajLista(Wezel* head, int wartosc) {
    Wezel* temp = head;      //temp dostaje wartosc glowy
    bool znalazles = false; // Stworzenie zmiennej do śledzenia, czy znaleziono szukaną wartość
    while (temp != nullptr) { // Szukamy dopóki temp nie jest puste
        if (temp->dane == wartosc) { // Jeżeli temp->dane jest równe wartości szukanej
            cout << "znaleziono" << endl;
            znalazles = true; // Zmieniamy na true
        }
        temp = temp->kolejny; // Przechodzimy do następnego węzła
    }
    if (!znalazles) { // Jeżeli nie znaleziono szukanej wartości
        cout << "nie znaleziono" << endl;
    }
}

Wezel* UsunPierwszyLista(Wezel* head) {
    if (head == nullptr) return nullptr;  //jesli lista pusta zwracamy null

    Wezel* temp = head;     //temp dostaje wartosc glowy
    head = head->kolejny;  //przesuwamy glowe listy na nastepny element
    delete temp;           //usuwamy stary pierwszy element
    return head;           //zwracamy glowe
}

Wezel* UsunOstatniLista(Wezel* head) {
    if (head == nullptr) return nullptr;    //jesli lista pusta zwracamy null

    if (head->kolejny == nullptr) {          // jesli jest tylko jeden element
        delete head;                        // usuwamy glowe
        return nullptr;                    //zwracamy null
    }

    Wezel* second_last = head;                              //tworzymy przedostatni element co dostaje wartosc head
    while (second_last->kolejny->kolejny != nullptr) {     //przechodzimy przez liste do przedostatniego elementu
        second_last = second_last->kolejny;               //ustawiamy wskaznik na kolejny
    }

    delete (second_last->kolejny);                        //usuwamy ostatni element
    second_last->kolejny = nullptr;                       //ustawiamy wskaznik na nastepny wezel przedostatniego elementu na null
    return head;                                       //zwracamy glowe
}

Wezel* UsunWybranyLista(Wezel* head, int poz) {
    if (head == nullptr) return nullptr;        //jesli lista pusta zwracamy null

    Wezel* temp = head;                       //temp dostaje wartosc glowy

    if (poz == 0) {                         //jesli pozycja usuwamy pierwszy element
        head = temp->kolejny;
        delete temp;
        return head;
    }

    for (int i = 0; temp != nullptr && i < poz - 1; i++) {    //przechodzimy przez liste do wybranej pozycji
        temp = temp->kolejny;
    }

    if (temp == nullptr || temp->kolejny == nullptr) {      //jesli pozycja nieprawidlowa zwracamy glowe
        cout << "Nieprawidłowa pozycja" << endl;
        return head;
    }

    Wezel* next = temp->kolejny->kolejny;         //przesuniecie next o dwa wezly wzgledem temp
    delete temp->kolejny;                        //usuwanie wartosci wstazanej przez temp->kolejny
    temp->kolejny = next;                       //ustawienie wstaznika temp->kolejny na wartosc wskaznika next
    return head;                               // zwrocenie glowy
}

void switchLista(Wezel* head, int& n) {
    int robota=1, gdzie= 1, pozycja;    auto start = high_resolution_clock::now(); auto koniec = high_resolution_clock::now();    auto duration = duration_cast<nanoseconds>(koniec-start).count();
    Wezel* temp = nullptr;

    while (robota != 0) {
        cout << "Co chcesz zrobić z lista?: " << endl << "1. Wczytaj z pliku" << endl << "2. Wyświetl" << endl << "3. Wstaw" << endl << "4. Szukaj" << endl << "5. Usuń" << endl<< "0. Powrót" << endl;
        cin >> robota;

        switch (robota) {
            case 1:
                head = WczytajDoListy("liczby.txt");
                break;
            case 2:
                temp = head;
                while (temp != nullptr) {
                    cout << temp->dane << " ";
                    temp = temp->kolejny;
                }
                cout << endl;
                break;
            case 3:
                cout << "Gdzie chcesz dodać element?: 1 - początek, 2 - sam wybiorę miejsce, 3 - koniec, 0 - powrót ";
                cin >> gdzie;
                switch (gdzie) {
                    case 1:
                        start = high_resolution_clock::now();
                        head = DodajPoczatekListy(head, 420);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"DodajPoczatekListy");
                        break;
                    case 2:
                        cout << "Wybierz pozycję: ";
                        cin >> pozycja;
                        start = high_resolution_clock::now();
                        head = DodajWybranyLista(head, 2137, pozycja);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"DodajWybranyLista");
                        break;
                    case 3:
                        start = high_resolution_clock::now();
                        head = DodajKoniecListy(head, 666);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"DodajKoniecListy");
                        break;
                    default:
                        cout << "Powrót do menu głównego." << endl;
                        break;
                }
                break;
            case 4:
                cout << "Podaj pozycję do wyszukania: ";
                cin >> pozycja;

                start = high_resolution_clock::now();
                SzukajLista(head,pozycja);
                koniec = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(koniec-start).count();
                ZapiszCzas("wynik.txt",duration,"SzukajLista");
                break;
            case 5:
                cout << "Który element chcesz usunąć?: 1 - początek, 2 - sam wybiorę miejsce, 3 - koniec, 0 - powrót ";
                cin >> gdzie;
                switch (gdzie) {
                    case 1:
                        start = high_resolution_clock::now();
                        head = UsunPierwszyLista(head);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"UsunPierwszyLista");
                        break;
                    case 2:
                        cout << "Wybierz pozycję: ";
                        cin >> pozycja;
                        start = high_resolution_clock::now();
                        head = UsunWybranyLista(head, pozycja);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"UsunWybranyLista");
                        break;
                    case 3:
                        start = high_resolution_clock::now();
                        head = UsunOstatniLista(head);
                        koniec = high_resolution_clock::now();
                        duration = duration_cast<nanoseconds>(koniec-start).count();
                        ZapiszCzas("wynik.txt",duration,"UsunOstatniLista");
                        break;
                    default:
                        cout << "Powrót do menu głównego." << endl;
                        break;
                }
                break;
            default:
                cout << "Powrót do menu głównego." << endl;
                break;
        }
    }
}
/////////////DRZEWO BST///////////////
struct WezelBST {       //definicja struktury bst
    int data;
    WezelBST* lewy;                              //wskaznik na lewego potomka
    WezelBST* prawy;                            //wstaznik na prawego syna
};

WezelBST* WstawBST(WezelBST* korzen,int data){
    if(korzen==NULL){                                     //sprawdza czy korzen jest pusty
        WezelBST* newWezelBST = new WezelBST();          //tworzy nowy wezel na stercie
        newWezelBST->data = data;                       //przypisuje wartosc daty do pola data nowego wezla
        newWezelBST->lewy = newWezelBST->prawy=NULL;   //inicjuje wstazniki lewy i prawy na null czyli brak potomkow
        return newWezelBST;                           //zwraca wskaznik nowego
    }
    else if (data <= korzen->data){                  //jesli data jest mniejsze lub rowne wartosci data korzenia
        korzen->lewy = WstawBST(korzen->lewy, data);   //rekurencja wstawia wezel do lewego poddrzewa
    }
    else{
        korzen->prawy = WstawBST(korzen->prawy, data); //wstawai do prawego podrzewa
    }
    return korzen;                                           //zwraca korzen
}

WezelBST* ZnajdzMinBST(WezelBST* korzen) {
    while (korzen->lewy != NULL) korzen = korzen->lewy;     //wykonuje sie dopoki istnieje lewy potomek drzewa
    return korzen;                                         //zwraca korzen
}

WezelBST* WczytajBST(const string& plik){
    ifstream file(plik);
    if(!file){
        throw std::runtime_error("Nie mozna odczytac pliku");
    }
    WezelBST* korzen=NULL;                               //ustawia wartosc korzenia na pusta
    int data;
    while (file>>data){                                 //dziala dopoki da sie czytac z pliku
        korzen = WstawBST(korzen, data);                //wstawia nowy wezel o wartosci data do drzewa
    }
    return korzen;                                     //zwraca korzen
}

WezelBST* UsunBST(WezelBST* korzen, int data) {
    if (korzen == NULL)                               //jesli korzen jest pusty
        return NULL;                                  //zwraca nic
    else if (data < korzen->data)
        korzen->lewy = UsunBST(korzen->lewy, data);       //jesli data jest mniejsza od taty korzenia, usuwa wezel z lewego poddrzewa
    else if (data > korzen->data)
        korzen->prawy = UsunBST(korzen->prawy, data);    //jesli data jest wieksza od daty korzenia, usuwa z prawego poddrzewa
    else {                                                         //jesli wartosc jest  rowna wartosci korzenia
        if (korzen->lewy == NULL && korzen->prawy == NULL) {      //jesli nie ma potomkow
            delete korzen;                                        //usun korzen
            korzen = NULL;
        }
        else if (korzen->prawy == NULL) {                        //jesli nie ma prawego korzenia
            WezelBST* temp = korzen;                             //przypisuje wartosc korzenia do temp
            korzen = korzen->lewy;                               //daje korzen na lewego potomka
            delete temp;                                         //usuwa temp
        }
        else if (korzen->lewy == NULL) {                         //adekwatnie co wyżej
            WezelBST* temp = korzen;
            korzen = korzen->prawy;
            delete temp;
        }
        else {
            WezelBST* temp = ZnajdzMinBST(korzen->prawy);        //gdy ma dwoje potomkow  szuka minimalnego w prawym  i zapisuje do temp
            korzen->data = temp->data;                                 //zapisuje korzeniowi date temp
            korzen->prawy = UsunBST(korzen->prawy, temp->data); //rekurencja usuwa znaleziony wezel z prawego poddrzewa
        }
    }
    return korzen;                                                    //zwraca korzen
}

bool SzukajBST(WezelBST* korzen, int data) {
    if (korzen == NULL) {                        //jesli nie ma korzenia zwroc false
        return false;
    }
    else if (korzen->data == data) {                                                //jesli korzen jest rowny szukanej zwroc prawede
        return true;
    }
    else if (data <= korzen->data) {
        return SzukajBST(korzen->lewy, data);                               //rekurencja szuka w lewym poddrzewie
    }
    else {
        return SzukajBST(korzen->prawy, data);                              //rekurencja szuka w prawym poddrzewie
    }
}
void WyswietlBST(WezelBST* korzen)
{
    if (korzen != NULL)                                                   //jesli korzen nie jest pusty
    {
        WyswietlBST(korzen->lewy);                                 //wyswietl lewe poddrzewo rekurencyjnie
        cout << korzen->data << "  ";                                     //wyswietla wartosc poddrzewa
        WyswietlBST(korzen->prawy);                                 //wyswietl prawe poddrzewo rekurencyjnie
    }
}

void switchBST(WezelBST* korzen, int& n) {
    int robota=1, gdzie= 1, pozycja;            auto start = high_resolution_clock::now(); auto koniec = high_resolution_clock::now();    auto duration = duration_cast<nanoseconds>(koniec-start).count();
    WezelBST* temp = nullptr;

    while (robota != 0) {
        cout << "Co chcesz zrobić z BST?: " << endl << "1. Wczytaj z pliku" << endl << "2. Wyświetl" << endl << "3. Wstaw" << endl << "4. Szukaj" << endl << "5. Usuń" << endl<< "0. Powrót" << endl;
        cin >> robota;

        switch (robota) {
            case 1:
                korzen = WczytajBST("liczby.txt");
                break;
            case 2:
                WyswietlBST(korzen);
                break;
            case 3:
                cout << "Podaj wartość do wstawienia: ";
                cin >> pozycja;
                start = high_resolution_clock::now();
                korzen = WstawBST(korzen, pozycja);
                koniec = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(koniec-start).count();
                ZapiszCzas("wynik.txt",duration,"WstawBST");
                break;
            case 4:
                cout << "Podaj wartość do wyszukania: ";
                cin >> pozycja;
                start = high_resolution_clock::now();

                if (SzukajBST(korzen, pozycja)) {
                    cout << "Znaleziono wartość " << pozycja << " w drzewie.\n";
                } else {
                    cout << "Nie znaleziono wartości " << pozycja << " w drzewie.\n";
                }
                koniec = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(koniec-start).count();
                ZapiszCzas("wynik.txt",duration,"SzukajBST");
                break;
            case 5:
                cout << "Podaj wartość do usunięcia: ";
                cin >> pozycja;
                start = high_resolution_clock::now();
                korzen = UsunBST(korzen, pozycja);
                koniec = high_resolution_clock::now();
                duration = duration_cast<nanoseconds>(koniec-start).count();
                ZapiszCzas("wynik.txt",duration,"UsunBST");
                break;
                break;
            default:
                cout << "Powrót do menu głównego." << endl;
                break;
        }
    }
}
int main() {
    setlocale(LC_COLLATE,"Polish");
    const string plik = "liczby.txt";
    generateRandomNumbers(plik);
    int n = rozmiar;
    int typ = 1;

    int* tablica = nullptr;
    Wezel* head = nullptr;
    WezelBST* korzen = nullptr;


    while (typ != 0) {
        cout << "Wybierz, na czym chcesz operować: " << endl << "1. Tablica" << endl << "2. Lista liniowa" << endl << "3. Drzewo BST" << endl << "0. Koniec" << endl;
        cin >> typ;

        switch (typ) {
            case 1:
                switchTablica(tablica, n);
                break;
            case 2:
                switchLista(head,n);
                break;
            case 3:
                switchBST(korzen, n);
                break;
            default:
                cout << "Koniec programu." << endl;
                break;
        }
    }

    delete[] tablica;
    return 0;
}