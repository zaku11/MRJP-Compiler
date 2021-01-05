Większość plików została wygenerowana przez **BNFC**. To co zostało przeze mnie dodane to **FrontEnd.cpp, FrontEnd.h**, **LLVM.cpp**, **LLVM.h** oraz zmodyfikowałem **Printer.C** i **Printer.H** w celu uzyskania lepszych komunikatów o błędach.

Na ten moment moje rozwiązanie to frontend + backend + struktury + obiekty.

Ważne informacje:

1. W funkcji *readString* zakładam że długość wczytywanego ciągu znaków nie przekracza 1048576. Jeśli string na wejściu będzie dłuższy, zostanie zczytane tylko pierwsze 1048576 znaków.

2. Porównywanie stringów odbywa się przez leksykograficzne porównywanie ich zawartości. Porównywanie klas odbywa się przez porównywanie pointerów do nich.

3. W pliku **lib/runtime.ll** znajdują się funkcje pomocnicze używane przez mój kompilator. Część z nich(*printInt*, *printString*, *readInt*, *concat*) została zapożyczona z moodla i slajdów prowadzącego.

4. Przy implementacji klas zakładam że metody przesłaniają widocznością funkcje np. 
```
void foo() {
	printString("function");
}
class X {
	void foo() {
		printString("method");
	}
	void bar() {
		foo();
	}
}
int main() {
	X x = new X;
	x.bar();
	return 0;
}   
```
Dla takiego kodu oczekiwanym wynikiem jest napis **method**

5. Używanie obiektu klasy bez wcześniejszej jego inicjalizacji uważam za `undefined behaviour` np.
```
int main() {
	X x; // By metoda została poprawnie wywołana należy zrobić X x = new X;
	x.foo();
	return 0;
}
```

6. W klasach argumentami metod nie mogą być zmienne o takich samych nazwach jak pola danej klasy(lub jej przodka). Nie mogą też nazywać się `self` jako że jest to nazwa specjalna.