all: 
	+$(MAKE) -C ./src/
	cp ./src/latc_llvm ./
