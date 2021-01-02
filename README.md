Większość plików została wygenerowana przez **BNFC**. To co zostało przeze mnie dodane to **FrontEnd.cpp, FrontEnd.h**, **LLVM.cpp**, **LLVM.h** oraz lekko zmodyfikowałem **Printer.C** i **Printer.H** w celu uzyskania lepszych komunikatów o błędach.

Na ten moment moje rozwiązanie to frontend + backend + struktury + obiekty + metody wirtualne.

W funkcji *readString* zakładam że długość wczytywanego ciągu znaków nie przekracza 256.

Porównywanie stringów odbywa się przez leksykograficzne porównywanie ich zawartości. Porównywanie klas odbywa się przez porównywanie pointerów do nich