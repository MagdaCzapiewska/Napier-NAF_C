/*
	Zadanie zaliczeniowe 3: Napier-NAF
	
	Kompilacja poleceniem:
	gcc @opcje nazwa.c napiernaf.c -o nazwa
	gdzie nazwa.c to nazwa programu testujacego, ktory korzysta z modulu napiernaf.c
	
	Modul napiernaf.c implementuje interfejs napiernaf.h
	
	autor: Magdalena Czapiewska <mc427863@students.mimuw.edu.pl>
	data: 8 stycznia 2022	
*/

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Funkcja wiecej zwraca argument powiekszony w przyblizeniu 2 razy
*/

int wiecej(int n){
	assert(n <= INT_MAX / 2);
	return n * 2 + 1;
}

/*
Funkcja zapisz zapisuje do tablicy wynik cyfre reprezentacji Napier-NAF
*/

void zapisz(int c, int *indeks, int **wynik, int *rozmiar, int wykladnik){

	if(*indeks == *rozmiar){
		(*rozmiar) = wiecej(*rozmiar);
		*wynik = realloc(*wynik, (long unsigned int)(*rozmiar) * sizeof(**wynik));
		assert(*wynik != NULL);
	}
	if(c == 1){
		(*wynik)[*indeks] = wykladnik;
	}
	else{
		(*wynik)[*indeks] = ((-1)*wykladnik - 1);
	}
	(*indeks)++;

}

/*
Funkcja iton zapisuje reprezentacje liczby x w dynamicznie utworzonej *n-elementowej tablicy *a
*/

void iton(int x, int **a, int *n){
	
	int *wynik = NULL;
	int indeks = 0;

	if(x != 0){
		int rozmiar = 0;
		int wykladnik = 0;
		while(x != 0){
			int c = 0;
			if(x % 2 == 0){
				c = 0;
			}
			else if((x - 1) % 4 == 0){
				c = 1;
				zapisz(c, &indeks, &wynik, &rozmiar, wykladnik);
			}
			else if((x + 1) % 4 == 0){
				c = -1;
				zapisz(c, &indeks, &wynik, &rozmiar, wykladnik);
			}
			wykladnik++;
			x = (x - c) / 2;
		}
	}
	
	*a = wynik;
	*n = indeks;
}

/*
Funkcja zapoczatkuj_liczenie nadaje *wynik poczatkowa wartosc (-1 lub 1) - jest pomocnicza dla ntoi
*/

void zapoczatkuj_liczenie(int *wykladnik_aktualny, int *wynik, int *a, int n){

	if(a[n-1] >= 0){
		(*wykladnik_aktualny) = a[n-1];
		(*wynik) += 1;
	}
	else{
		(*wykladnik_aktualny) = - (a[n-1] + 1);
		(*wynik) -= 1;
	}

}

/*
Funkcja sprawdz_mnozenie sprawdza, czy nie wyjdziemy poza zakres int podczas mnozenia dotychczasowego wyniku przez 2
*/

bool sprawdz_mnozenie(int wynik){

	if(wynik >= (INT_MIN / 2) && wynik <= (INT_MAX / 2)){
		return 1;
	}
	else{
		return 0;
	}

}

/*
Funkcja sprawdz_dodawanie sprawdza, czy nie wyjdziemy poza zakres int podczas dodawania do dotychczasowego wyniku liczby wybranej spośród {-1, 0, 1}
*/

bool sprawdz_dodawanie(int wynik, int skladnik){

	if(skladnik == 1){
		if(wynik < INT_MAX){
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(skladnik == -1){
		if(wynik > INT_MIN){
			return 1;
		}
		else{
			return 0;
		}
	}
	return 1;

}

/*
Funkcja pozycja_w_BBR_NAF zwraca wykladnik potegi dwojki jako jedna z dwoch informacji plynacych z cyfry w reprezentacji Napier_NAF (druga informacja jest obecnosc cyfry 1 lub -1 na danej pozycji) 
*/

int pozycja_w_BBR_NAF(int cyfra_w_Napier_NAF){

	if(cyfra_w_Napier_NAF >= 0){
		return cyfra_w_Napier_NAF;
	}
	else{
		return - (cyfra_w_Napier_NAF + 1);
	}

}

/*
Funkcja zaktualizuj_wykladnik aktualizuje wykladnik dwojki w systemie addytywnym
*/

void zaktualizuj_wykladnik(int *wykladnik_poprzedni, int *wykladnik_aktualny, int *indeks, int *a){

	*wykladnik_poprzedni = *wykladnik_aktualny;
	*wykladnik_aktualny = pozycja_w_BBR_NAF(a[*indeks]);

}

/*
Funkcja mnoz_przez_potege_dwojki mnozy *wynik przez potege dwojki i zwraca 1, gdy to sie uda lub 0, gdy nie uda sie z powodu wyjscia poza zakres int
*/

bool mnoz_przez_potege_dwojki(int wykladnik_poprzedni, int wykladnik_aktualny, int *wynik){

	for(int i = wykladnik_poprzedni; i > wykladnik_aktualny; i--){
			if(sprawdz_mnozenie(*wynik)){
				(*wynik) *= 2;
			}
			else{
				return 0;
			}
	}
	return 1;

}

/*
Funkcja cyfra_w_BBR_NAF zwraca liczbe 1 lub -1 jako jedna z dwoch informacji plynacych z cyfry w reprezentacji Napier_NAF (druga informacja jest pozycja cyfry 1 lub -1 w BBR-NAF)
*/

int cyfra_w_BBR_NAF(int cyfra_w_Napier_NAF){

	if(cyfra_w_Napier_NAF >= 0){
		return 1;
	}
	else{
		return -1;
	}

}

/*
Funkcja ntoi daje jako wynik wartosc liczby reprezentowanej przez n-elementowa tablice a lub 0, jesli wartosc ta nie miesci sie w zakresie typu int
*/

int ntoi(int *a, int n){
	
	int wynik = 0;
	int wykladnik_poprzedni;
	int wykladnik_aktualny;
	zapoczatkuj_liczenie(&wykladnik_aktualny, &wynik, a, n);
	int indeks = n-2;
	while(indeks >= 0){
		zaktualizuj_wykladnik(&wykladnik_poprzedni, &wykladnik_aktualny, &indeks, a);
		if(!mnoz_przez_potege_dwojki(wykladnik_poprzedni, wykladnik_aktualny, &wynik)){
			return 0;
		}
		else{
			int skladnik = cyfra_w_BBR_NAF(a[indeks]);
			if(sprawdz_dodawanie(wynik, skladnik)){
				wynik += skladnik;
			}
			else{
				return 0;
			}
			indeks--;
		}
		
	}
	if(!mnoz_przez_potege_dwojki(wykladnik_aktualny, 0, &wynik)){
		return 0;
	}
	return wynik;
	
}

/*
Funkcja minimum zwraca mniejsza z dwoch liczb calkowitych
*/

int minimum(int a, int b){

	if(a < b){
		return a;
	}
	else{
		return b;
	}

}

/*
Funkcja zmien_znak zapisuje do tablicy wynik cyfre reprezentacji Napier-NAF "przeciwna" (w rozumieniu Napier-NAF) do tej, ktora byla w tym miejscu zapisana
*/

void zmien_znak(int indeks, int **wynik){

	(*wynik)[indeks] = ((-1)*((*wynik)[indeks]) - 1);

}

/*
Funkcja uzupelnij_info_o_wykladnikach_mniejszych_niz_wybrany uwzglednia przejscie z poprzednich operacji
*/

void uzupelnij_info_o_wykladnikach_mniejszych_niz_wybrany(int *wykladnik_przejscia, int wybieram, int *przejscie, int *indeks, int **wynik, int *rozmiar){

	int pomoc = 0;
	while(((*wykladnik_przejscia) < wybieram) && ((*przejscie) != 0)){
		if((*indeks > 0) && (*wykladnik_przejscia == (pozycja_w_BBR_NAF((*wynik)[(*indeks) - 1]) + 1))){
			if((*przejscie) % 2 == cyfra_w_BBR_NAF((*wynik)[(*indeks) - 1])){
				zmien_znak((*indeks) - 1, wynik);
				pomoc = (*przejscie) / 2;
				(*przejscie) = (*przejscie) % 2;
				(*przejscie) += pomoc;
			}
			else if((*przejscie) % 2 == (-1) * cyfra_w_BBR_NAF((*wynik)[(*indeks) - 1])){
				zmien_znak((*indeks) - 1, wynik);
				(*przejscie) = (*przejscie) / 2;
			}
			else if((*przejscie) / 2 != 0){
				(*przejscie) = (*przejscie) / 2;
			}
		}
		else{
			if((*przejscie) % 2 != 0){
				zapisz((*przejscie) % 2, indeks, wynik, rozmiar, *wykladnik_przejscia);
			}
				
			(*przejscie) = (*przejscie) / 2;
		}
		(*wykladnik_przejscia)++;
	}

}

/*
Funkcja uzupelnij_info_o_wykladniku_wybranym zapisuje do tablicy z reprezentacja Napier-NAF
*/

void uzupelnij_info_o_wykladniku_wybranym(int suma, int wybieram, int **wynik, int *indeks, int *rozmiar, int *wykladnik_przejscia, int *przejscie){

	int pomoc = 0;
	if(suma != 0){
		if(((*indeks) > 0) && (wybieram == (pozycja_w_BBR_NAF((*wynik)[(*indeks) - 1]) + 1))){
			if(suma % 2 == cyfra_w_BBR_NAF((*wynik)[(*indeks) - 1])){
				zmien_znak((*indeks) - 1, wynik);
				pomoc = suma / 2;
				(*przejscie) = suma % 2;
				(*przejscie) += pomoc;
			}
			else if(suma % 2 == (-1) * cyfra_w_BBR_NAF((*wynik)[(*indeks) - 1])){
				zmien_znak((*indeks) - 1, wynik);
				(*przejscie) = suma / 2;
			}
			else if(suma / 2 != 0){
				(*przejscie) = suma / 2;
			}
		}
		else{
			if(suma % 2 != 0){
				zapisz(suma % 2, indeks, wynik, rozmiar, wybieram);
			}
			
			(*przejscie) = suma / 2;
		}
	}
	else{
		(*przejscie) = 0;
	}
	(*wykladnik_przejscia) = (wybieram + 1);

}

/*
Funkcja nadd_or_nsub_obie_tablice to operacja wykonywane w funkcji nadd_or_nsub, gdy nie skonczylismy jeszcze przegladac zadnej z tablic
*/

void nadd_or_nsub_obie_tablice(int *a, int an, int *b, int bn, int *indeks_a, int *indeks_b, int *indeks, int **wynik, int *rozmiar, int *przejscie, int *wykladnik_przejscia, int wspolczynnik){

	while((*indeks_a < an) && (*indeks_b < bn)){
		int suma = 0;
		int wybieram = minimum(pozycja_w_BBR_NAF(a[*indeks_a]), pozycja_w_BBR_NAF(b[*indeks_b]));

		uzupelnij_info_o_wykladnikach_mniejszych_niz_wybrany(wykladnik_przejscia, wybieram, przejscie, indeks, wynik, rozmiar);
		if(pozycja_w_BBR_NAF(a[*indeks_a]) == wybieram){
			suma += cyfra_w_BBR_NAF(a[*indeks_a]);
			(*indeks_a)++;
		}
		if(pozycja_w_BBR_NAF(b[*indeks_b]) == wybieram){
			suma += (wspolczynnik * cyfra_w_BBR_NAF(b[*indeks_b]));
			(*indeks_b)++;
		}
		suma += (*przejscie);

		uzupelnij_info_o_wykladniku_wybranym(suma, wybieram, wynik, indeks, rozmiar, wykladnik_przejscia, przejscie);
	}

}

/*
Funkcja nadd_or_nsub_etap_koncowy to operacje wykonywane w funkcji nadd_or_nsub, gdy skonczyla sie juz jedna z tablic
*/

void nadd_or_nsub_etap_koncowy(int *d, int dn, int *indeks_d, int *indeks, int **wynik, int *rozmiar, int *przejscie, int *wykladnik_przejscia, int wspolczynnik){

	while(*indeks_d < dn){
		int suma = 0;
		int wybieram = pozycja_w_BBR_NAF(d[*indeks_d]);

		uzupelnij_info_o_wykladnikach_mniejszych_niz_wybrany(wykladnik_przejscia, wybieram, przejscie, indeks, wynik, rozmiar);
		suma += (wspolczynnik * cyfra_w_BBR_NAF(d[*indeks_d]));
		(*indeks_d)++;
		suma += *przejscie;

		uzupelnij_info_o_wykladniku_wybranym(suma, wybieram, wynik, indeks, rozmiar, wykladnik_przejscia, przejscie);
	}

}

/*
Funkcja pamietaj_o_przejsciu zapisuje odpowiednie cyfry reprezentacji Napier-NAF, gdy nie rozpatrujemy juz reprezentacji w tablicach (dodawanych lub odejmowanych), poniewaz cale obejrzelismy
*/

void pamietaj_o_przejsciu(int *przejscie, int *indeks, int *wykladnik_przejscia, int **wynik, int *rozmiar){

	int pomoc = 0;
	while((*przejscie) != 0){
		if((*indeks > 0) && (*wykladnik_przejscia == (pozycja_w_BBR_NAF((*wynik)[(*indeks) - 1]) + 1))){
			if((*przejscie) % 2 == cyfra_w_BBR_NAF((*wynik)[(*indeks) - 1])){
				zmien_znak((*indeks) - 1, wynik);
				pomoc = (*przejscie) / 2;
				(*przejscie) = (*przejscie) % 2;
				(*przejscie) += pomoc;
			}
			else if((*przejscie) % 2 == (-1) * cyfra_w_BBR_NAF((*wynik)[(*indeks) - 1])){
				zmien_znak((*indeks) - 1, wynik);
				(*przejscie) = (*przejscie) / 2;
			}
			else if((*przejscie) / 2 != 0){
				(*przejscie) = (*przejscie) / 2;
			}
		}
		else{
			if((*przejscie) % 2 != 0){
				zapisz((*przejscie) % 2, indeks, wynik, rozmiar, *wykladnik_przejscia);
			}
				
			(*przejscie) = (*przejscie) / 2;
		}
		(*wykladnik_przejscia)++;
	}

}


/*
Funkcja nadd_or_nsub jest funkcja nadd, gdy wpolczynnik == 1, a funkcja nsub, gdy wspolczynnik == -1
*/

void nadd_or_nsub(int *a, int an, int *b, int bn, int **c, int *cn, int wspolczynnik){

	int indeks_a = 0;
	int indeks_b = 0;

	int *wynik = NULL;
	int indeks = 0;
	int rozmiar = 0;
	int przejscie = 0;
	int wykladnik_przejscia = 0;

	nadd_or_nsub_obie_tablice(a, an, b, bn, &indeks_a, &indeks_b, &indeks, &wynik, &rozmiar, &przejscie, &wykladnik_przejscia, wspolczynnik);
	if(indeks_a < an){
		nadd_or_nsub_etap_koncowy(a, an, &indeks_a, &indeks, &wynik, &rozmiar, &przejscie, &wykladnik_przejscia, 1);
	}
	else if(indeks_b < bn){
		nadd_or_nsub_etap_koncowy(b, bn, &indeks_b, &indeks, &wynik, &rozmiar, &przejscie, &wykladnik_przejscia, wspolczynnik);
	}
	pamietaj_o_przejsciu(&przejscie, &indeks, &wykladnik_przejscia, &wynik, &rozmiar);
	
	*c = wynik;
	*cn = indeks;

}

/*
Funkcja nadd zapisuje w dynamicznie utworzonej *cn-elementowej tablicy *c sume liczb reprezentowanych przez an-elementowa tablice a i bn-elementowa tablice b
*/

void nadd(int *a, int an, int *b, int bn, int **c, int *cn){

	nadd_or_nsub(a, an, b, bn, c, cn, 1);

}

/*
Funkcja nsub zapisuje w dynamicznie utworzonej *cn-elementowej tablicy *c różnice liczb reprezentowanych przez an-elementowa tablice a i bn-elementowa tablice b
*/

void nsub(int *a, int an, int *b, int bn, int **c, int *cn){

	nadd_or_nsub(a, an, b, bn, c, cn, -1);

}

/*
Funkcja nmul zapisuje w dynamicznie utworzonej *cn-elementowej tablicy *c iloczyn liczb reprezentowanych przez an-elementowa tablice a i bn-elementowa tablice b
*/

void nmul(int *a, int an, int *b, int bn, int **c, int *cn){

	int *pomocnicza;
	pomocnicza = malloc((long unsigned int)bn * sizeof(*pomocnicza));
	int *wynikowa = NULL;
	int rozmiar_wynikowej = 0;
	int *wynik = NULL;
	int rozmiar_wyniku = 0;

	for(int i = 0; i < an; i++){
		int czynnik = cyfra_w_BBR_NAF(a[i]);
		int skladnik = pozycja_w_BBR_NAF(a[i]);
		for(int j = 0; j < bn; j++){
			int czynnik_koncowy = czynnik * cyfra_w_BBR_NAF(b[j]);
			int wykladnik = (skladnik + pozycja_w_BBR_NAF(b[j]));
			if(czynnik_koncowy == 1){
				pomocnicza[j] = wykladnik;
			}
			else{
				pomocnicza[j] = (-1) * (wykladnik + 1);
			}
		}
		nadd(pomocnicza, bn, wynikowa, rozmiar_wynikowej, &wynik, &rozmiar_wyniku);
		free(wynikowa);
		wynikowa = wynik;
		rozmiar_wynikowej = rozmiar_wyniku;
		wynik = NULL;
		rozmiar_wyniku = 0;
	}
	free(pomocnicza);

	*c = wynikowa;
	*cn = rozmiar_wynikowej;

}

/*
Funkcja nexp zapisuje w dynamicznie utworzonej *cn-elementowej tablicy *c wynik potegowania, ktorego podstawa jest reprezentowana przez
an-elementowa tablice a, a nieujemny wykladnik jest reprezentowany przez bn-elementowa tablice b
*/

void nexp(int *a, int an, int *b, int bn, int **c, int *cn){

	int *wynikowa = malloc(sizeof(*wynikowa));
	wynikowa[0] = 0;
	int rozmiar_wynikowej = 1;

	int *pomocnicza = malloc((long unsigned int)bn * sizeof(*pomocnicza));
	int rozmiar_pomocniczej = bn;
	for(int i = 0; i < bn; i++){
		pomocnicza[i] = b[i];
	}

	int *wynik = NULL;
	int rozmiar_wyniku = 0;

	int *pomoc = NULL;
	int rozmiar_pomocy = 0;

	int *jeden = malloc(sizeof(*jeden));
	jeden[0] = 0;
	int rozmiar_jeden = 1;

	while(rozmiar_pomocniczej > 0){
		nmul(wynikowa, rozmiar_wynikowej, a, an, &wynik, &rozmiar_wyniku);
		nsub(pomocnicza, rozmiar_pomocniczej, jeden, rozmiar_jeden, &pomoc, &rozmiar_pomocy);

		free(wynikowa);
		wynikowa = wynik;
		rozmiar_wynikowej = rozmiar_wyniku;
		wynik = NULL;
		rozmiar_wyniku = 0;
		
		free(pomocnicza);
		pomocnicza = pomoc;
		rozmiar_pomocniczej = rozmiar_pomocy;
		pomoc = NULL;
		rozmiar_pomocy = 0;
	}
	free(pomocnicza);
	free(jeden);

	*c = wynikowa;
	*cn = rozmiar_wynikowej;

}

/*
Funkcja nieujemna zwraca wartosc true, gdy liczba, ktorej reprezentacje Napier-NAF zawiera tablica tablica jest nieujemna, a false dla reprezentacji liczby ujemnej
*/

bool nieujemna(int *tablica, int dlugosc){

	if(dlugosc > 0){
		if(tablica[dlugosc - 1] < 0){
			return false;
		}
	}
	return true;

}


/*
Funkcja sklonuj_tablice umieszcza w tablicy pomocnicza zawartosc tablicy tablica
*/

void sklonuj_tablice(int *tablica, int dlugosc, int *pomocnicza){

	for(int i = 0; i < dlugosc; i++){
		pomocnicza[i] = tablica[i];
	}

}


/*
Funkcja pozamieniaj wykonuje operacje potrzebne po wykonaniu funkcji nadd lub nsub w celu umieszczenia wyniku w odpowiedniej tablicy, ktora stanie sie pierwszym argumentem w kolejnym wywolaniu nadd lub nsub
*/

void pozamieniaj(int **tablica, int *rozmiar_tablicy, int **tablica_pom, int *rozmiar_tablicy_pom){

	free(*tablica);
	*tablica = *tablica_pom;
	*rozmiar_tablicy = *rozmiar_tablicy_pom;
	*tablica_pom = NULL;
	*rozmiar_tablicy_pom = 0;

}

/*
Funkcja ndivmod dzieli liczbe, ktorej reprezentacja jest an-elementowa tablica a, przez niezerowa liczbe, ktorej reprezentacja jest bn-elementowa
tablica b. Iloraz zapisuje w dynamicznie utworzonej *qn-elementowej tablicy *q. Reszte z dzielenia zapisuje w dynamicznie utworzonej *rn-elementowej tablicy *r
*/

void ndivmod(int *a, int an, int *b, int bn, int **q, int *qn, int **r, int *rn){

	bool b_jest_ujemna = !nieujemna(b, bn);
	bool a_jest_ujemna = !nieujemna(a, an);

	int *pomocnicza_a = malloc((long unsigned int)an * sizeof(*pomocnicza_a));
	int rozmiar_pomocniczej_a = an;
	sklonuj_tablice(a, an, pomocnicza_a);

	int *pomoc = NULL;
	int rozmiar_pomocy = 0;

	int *iloraz  = NULL;
	int rozmiar_ilorazu = 0;

	int *iloraz_pom = NULL;
	int rozmiar_ilorazu_pom = 0;

	int *jeden = malloc(sizeof(*jeden));
	jeden[0] = 0;
	int rozmiar_jeden = 1;

	if(an == 0){
		free(pomocnicza_a);
		pomocnicza_a = NULL;
		rozmiar_pomocniczej_a = 0;
	}
	else if(a_jest_ujemna == b_jest_ujemna){
		if(!b_jest_ujemna){
			nsub(pomocnicza_a, rozmiar_pomocniczej_a, b, bn, &pomoc, &rozmiar_pomocy);
			while(nieujemna(pomoc, rozmiar_pomocy)){
				nadd(iloraz, rozmiar_ilorazu, jeden, rozmiar_jeden, &iloraz_pom, &rozmiar_ilorazu_pom);
				pozamieniaj(&pomocnicza_a, &rozmiar_pomocniczej_a, &pomoc, &rozmiar_pomocy);
				pozamieniaj(&iloraz, &rozmiar_ilorazu, &iloraz_pom, &rozmiar_ilorazu_pom);
				nsub(pomocnicza_a, rozmiar_pomocniczej_a, b, bn, &pomoc, &rozmiar_pomocy);
			}
		}
		else if(b_jest_ujemna){
			nsub(pomocnicza_a, rozmiar_pomocniczej_a, b, bn, &pomoc, &rozmiar_pomocy);
			while(!nieujemna(pomocnicza_a, rozmiar_pomocniczej_a)){
				nadd(iloraz, rozmiar_ilorazu, jeden, rozmiar_jeden, &iloraz_pom, &rozmiar_ilorazu_pom);
				pozamieniaj(&pomocnicza_a, &rozmiar_pomocniczej_a, &pomoc, &rozmiar_pomocy);
				pozamieniaj(&iloraz, &rozmiar_ilorazu, &iloraz_pom, &rozmiar_ilorazu_pom);
				nsub(pomocnicza_a, rozmiar_pomocniczej_a, b, bn, &pomoc, &rozmiar_pomocy);
			}
		}
	}
	else if(a_jest_ujemna != b_jest_ujemna){
		if(!b_jest_ujemna){
			nadd(pomocnicza_a, rozmiar_pomocniczej_a, b, bn, &pomoc, &rozmiar_pomocy);
			while(!nieujemna(pomocnicza_a, rozmiar_pomocniczej_a)){
				nsub(iloraz, rozmiar_ilorazu, jeden, rozmiar_jeden, &iloraz_pom, &rozmiar_ilorazu_pom);
				pozamieniaj(&pomocnicza_a, &rozmiar_pomocniczej_a, &pomoc, &rozmiar_pomocy);
				pozamieniaj(&iloraz, &rozmiar_ilorazu, &iloraz_pom, &rozmiar_ilorazu_pom);
				nadd(pomocnicza_a, rozmiar_pomocniczej_a, b, bn, &pomoc, &rozmiar_pomocy);
			}
		}
		else if(b_jest_ujemna){
			nadd(pomocnicza_a, rozmiar_pomocniczej_a, b, bn, &pomoc, &rozmiar_pomocy);
			while(nieujemna(pomoc, rozmiar_pomocy)){
				nsub(iloraz, rozmiar_ilorazu, jeden, rozmiar_jeden, &iloraz_pom, &rozmiar_ilorazu_pom);
				pozamieniaj(&pomocnicza_a, &rozmiar_pomocniczej_a, &pomoc, &rozmiar_pomocy);
				pozamieniaj(&iloraz, &rozmiar_ilorazu, &iloraz_pom, &rozmiar_ilorazu_pom);
				nadd(pomocnicza_a, rozmiar_pomocniczej_a, b, bn, &pomoc, &rozmiar_pomocy);
			}
		}
	}
	*q = iloraz;
	*qn = rozmiar_ilorazu;

	*r = pomocnicza_a;
	*rn = rozmiar_pomocniczej_a;

	if(pomoc != NULL){
		free(pomoc);
	}
	if(iloraz_pom != NULL){
		free(iloraz_pom);
	}
	free(jeden);

}
