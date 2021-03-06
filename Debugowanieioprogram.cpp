#include <stdio.h>
#include <string>
#include <vector> //do dadnaia
#include <algorithm> // do dodania
//Biblioteki do kolorów:
#include <windows.h> //słabe rozwiązanie które raczej (chociaż są wyjątki) będzie działać tylko na Windowsie :/
#include <iostream>
#include <cstdlib>
//===============================================
#include <conio.h> //polskie znaki -jeszcze nie działają
#include <cctype> //Biblioteka do zmiany wielkości liter
int stan_uz = 1; //zmienna stan_uz określa czy użytkownik jest zalogowany, czy nie. Odblokowuje to nowe opcje w menu. Domyślnie ustawione na 0 - niezalogowany
int admin = 1; //Uprawnienia administratora

using namespace std;

void wyszukanie();

class Film {
	string Kategoria;
	string Nazwa_Filmu;
	string Rezyser;
	int rok;
	string stan_rezerwacji2;
	friend void wyszukanie();


public:

	Film() {};
	~Film() {};

	void Dodaj() {
		// SetConsoleTextAttribute (kolor, 15);
		cout << "\nProsze podac kategorie filmu: ";
		cin >> Kategoria;
		cout << "\nProsze podac tytul fimu: ";
		cin >> Nazwa_Filmu;
		cout << "\nProsze podac pierwsza litere i nazwisko rezysera fimu (w nastepujacym formacie A.Kowalski): ";
		cin >> Rezyser;
		cout << "\nProsze podac rok produkcji: ";
		cin >> rok;
		stan_rezerwacji2 = "Dostepny";
		//	SetConsoleTextAttribute (kolor, 10);
		system("cls");
		cout << "\nFilm zostal poprawnie dodany\n\n";
		//	SetConsoleTextAttribute (kolor, 8);
		system("pause");
		system("cls");
	}
	void wypisz() {
		// SetConsoleTextAttribute (kolor, 15);
		cout << "\nKategoria filmu: " << Kategoria << endl;
		cout << "\nTytul filmu: " << Nazwa_Filmu << endl;
		cout << "Rezyser filmu: " << Rezyser << endl;
		cout << "Rok produkcji: " << rok << endl;
		cout << "Stan rezerwacji: " << stan_rezerwacji2;
	}

	void setStan_rezerwacji(string a) {
		stan_rezerwacji2 = a;
	}

	string getTytul() {
		return	Nazwa_Filmu;
	}

	string getStan_rezerwacji() {
		return stan_rezerwacji2;
	}
	string getKategoria() {
		return Kategoria;
	}

};


class Baza_danych {
	int liczba_filmow = 0;
	vector <Film> baza_danych;
	friend void wyszukanie();
public:

	Baza_danych() {};
	~Baza_danych() {};
	void Dodaj_do_bazy(Film* film) {
		baza_danych.push_back(**&film);
		liczba_filmow++;
		return;
	}

	void Wypisz() {
		// SetConsoleTextAttribute (kolor, 15);
		cout << "Ilosc filmow w bazie to: " << liczba_filmow << endl;
		for (int i = 0; i < liczba_filmow; i++) {
			baza_danych[i].wypisz();
			cout << endl;
		}
	}

	void Dostepnosc() {
		string tytul;
		//	SetConsoleTextAttribute (kolor, 8);
		cout << "\nProsze wpisac tytul filmu: ";
		cin >> tytul;
		int pom = -1;
		for (int i = 0; i < liczba_filmow; i++) {
			if (!tytul.compare(baza_danych[i].getTytul())) {
				pom = i;
			}
		}
		if (pom == -1) {
			// SetConsoleTextAttribute (kolor, 15);
			cout << "Film obecnie niedostępny. Brak mozliwosci wypozyczenia." << endl;
			//	SetConsoleTextAttribute (kolor, 8);
			system("pause");
			system("cls");
		}
		else {
			// SetConsoleTextAttribute (kolor, 15);
			cout << "Film znajduje sie w wypozyczalni: " << endl;
			baza_danych[pom].wypisz();
			string sr = "Dostepne";
			bool stan = true;
			if (!sr.compare(baza_danych[pom].getStan_rezerwacji())) cout << "Niestety nie mozna go w tej chwili zarezerwowac" << endl;
			if (sr.compare(baza_danych[pom].getStan_rezerwacji())) {
				do {
					cout << "\nCzy chcesz zarezerwowac film?:\n\n[T] Tak; \t[N] Nie;" << endl;
					//	SetConsoleTextAttribute (kolor, 8);
					cout << "\n\nTwoj wybor: ";
					//	SetConsoleTextAttribute (kolor, 15);
					char wybor;
					stan = true;
					cin >> wybor;
					switch (toupper(wybor)) {
					case 'T':
						baza_danych[pom].setStan_rezerwacji("Zarezerwowano");
						cout << "\nPoprawnie zarezerwowano film \n";
						baza_danych[pom].wypisz();
						break;
					case 'N':
						break;
					default:
						system("cls");
						//	SetConsoleTextAttribute (kolor, 10); 
						cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
						//	SetConsoleTextAttribute (kolor, 8);
						system("pause");
						system("cls");
						stan = false;
						break;
					}
				} while (stan == false);
			}
			//SetConsoleTextAttribute (kolor, 8);
			system("pause");
			system("cls");
		}
	}

	void Wypozycz() {
		//	SetConsoleTextAttribute (kolor, 8);
		cout << "Podaj tytul filmu ktory chcesz wypozyczyc: ";
		string tytul;
		cin >> tytul;
		int i = 0;
		int pom = -1;
		for (int i = 0; i < liczba_filmow; i++) {
			if (!tytul.compare(baza_danych[i].getTytul())) {
				pom = i;
			}
		}
		if (pom == -1) {
			// SetConsoleTextAttribute (kolor, 15);
			cout << "Brak filmu w bazie" << endl;
		}
		else {
			baza_danych.erase(baza_danych.begin() + pom); //do vectora
		//  SetConsoleTextAttribute (kolor, 10);
			cout << "\nFilm zostal poprawnie wypozyczony" << endl;
			//	SetConsoleTextAttribute (kolor, 8);
			system("pause");
			system("cls");
		}
	}

	void Wyszuk_Kategoria() {
		string kategoria;
		cout << "Prosze podac nazwe kategori zaczynając od wielkiej litery (np.: Horror):\n";
		//	SetConsoleTextAttribute (kolor, 8);
		cout << "\n\nTwoj wybor: ";
		int pomoc = 0;
		cin >> kategoria;
		if (liczba_filmow == 0)
		{
			cout << "Brak filmow\n";
			system("pause");
			system("cls");
			wyszukanie();
		}
		for (int i = 0; i < liczba_filmow; i++) {
			if (!kategoria.compare(baza_danych[i].getKategoria())) {
				//	SetConsoleTextAttribute (kolor, 15);
				cout << ++pomoc << ".\n";
				baza_danych[i].wypisz();
			}
			if (pomoc == 0) {
				//	SetConsoleTextAttribute (kolor, 15);
				cout << "Brak filmu w tej kategorii\n";
				//	SetConsoleTextAttribute (kolor, 8);
				system("pause");
				system("cls");
				wyszukanie();
			}
			bool stan2 = true;
			//	SetConsoleTextAttribute (kolor, 15);
			cout << "Czy chcesz zarezerwowac film?\n[T] Tak; \t[N] Nie;";
			do {
				//	SetConsoleTextAttribute (kolor, 8);
				cout << "\n\nTwoj wybor: ";
				//	SetConsoleTextAttribute (kolor, 15);
				char wybor;
				stan2 = true;
				cin >> wybor;
				switch (toupper(wybor)) {
				case 'T':
					Dostepnosc();
					break;
				case 'N':
					wyszukanie();
					break;
				default:
					system("cls");
					//	SetConsoleTextAttribute (kolor, 10); 
					cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
					//	SetConsoleTextAttribute (kolor, 8);
					system("pause");
					system("cls");
					stan2 = false;
					break;
				}
			} while (stan2 == false);

		}
	}

};
Baza_danych Baza_danych;
Film film;

void wyszukanie() {
	char wybor;
	bool stan = true;
	do {
		system("cls");
		stan = true;
		//	SetConsoleTextAttribute (kolor, 15); //domyślny kolor
		cout << "Prosze wybrac odpowiednia opcje za pomoca litery podanej w nawiasie kwadratowym:\n" << endl;
		cout << "[K] Wyszukiwanie filmu za pomoca kategorii;\n" << "[T] Wyszukiwanie filmu po tytule;\n" << "[Z] Zarezerwuj film" << endl;
		if (admin == 1) cout << "[D] Dodaj film do bazy danych;\n" << "[W] Wypozycz film;\n" << "[S] Stan filmow" << endl;
		//	SetConsoleTextAttribute (kolor, 8);
		cout << "\n\nTwoj wybor: ";
		cin >> wybor;
		system("cls");
		//	SetConsoleTextAttribute (kolor, 15);
		switch (toupper(wybor)) {
		case 'K':
			Baza_danych.Wyszuk_Kategoria();
			break;
		case 'T':
			Baza_danych.Dostepnosc();
			break;
		case 'Z':
			Baza_danych.Dostepnosc();
			break;
			if (admin == 1) {
		case 'D':
			film.Dodaj();
			Baza_danych.Dodaj_do_bazy(&film);
			break;
		case'W':
			Baza_danych.Wypozycz();
			break;
		case'S':
			Baza_danych.Wypisz();
			break;
			}
		default:
			system("cls");
			//	SetConsoleTextAttribute (kolor, 10); 
			cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
			//	SetConsoleTextAttribute (kolor, 8);
			system("pause");
			system("cls");
			stan = false;
			break;
		}
	} while (stan == false);

}


int main() {

	wyszukanie();
	wyszukanie();
	int a;
	do {
		wyszukanie();
		cout << "Czy chesz wyjsc? tak = 1; nie = 2" << endl;
		cin >> a;
	} while (a == 1);


	delete &film;
	delete &Baza_danych;
	return 0;

}
