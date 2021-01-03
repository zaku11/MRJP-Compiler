Większość plików została wygenerowana przez **BNFC**. To co zostało przeze mnie dodane to **FrontEnd.cpp, FrontEnd.h**, **LLVM.cpp**, **LLVM.h** oraz zmodyfikowałem **Printer.C** i **Printer.H** w celu uzyskania lepszych komunikatów o błędach.

Na ten moment moje rozwiązanie to frontend + backend + struktury + obiekty.

W funkcji *readString* zakładam że długość wczytywanego ciągu znaków nie przekracza 1048576. Jeśli string na wejściu będzie dłuższy, zostanie zczytane tylko pierwsze 1048576 znaków.

Porównywanie stringów odbywa się przez leksykograficzne porównywanie ich zawartości. Porównywanie klas odbywa się przez porównywanie pointerów do nich.

W pliku **lib/runtime.ll** znajdują się funkcje pomocnicze używane przez mój kompilator. Część z nich(*printInt*, *printString*, *readInt*, *concat*) została zapożyczona z moodla i slajdów prowadzącego.  