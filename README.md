Większość plików została wygenerowana przez **BNFC**. To co zostało przeze mnie dodane to **FrontEnd.cpp, FrontEnd.h**, **LLVM.cpp**, **LLVM.h** oraz lekko zmodyfikowałem **Printer.C** i **Printer.H** w celu uzyskania lepszych komunikatów o błędach.

W obecnym stanie mój front-end jest podstawową wersją z dodaną obsługą structów bez klas.

W funkcji *readString* zakładam że długość wczytywanego ciągu znaków nie przekracza 256.