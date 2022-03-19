CC=cl.exe

LINK=link.exe

build: Main.o HashMap.o PreProcesare.o DefineIf.o Garzi.o Include.o
	$(LINK) /OUT:so-cpp.exe Main.o HashMap.o PreProcesare.o DefineIf.o Garzi.o Include.o

Main.o: Main.c
	$(CC) /c Main.c /FoMain.o

Include.o: Include.c
	$(CC) /c Include.c /FoInclude.o

Garzi.o: Garzi.c
	$(CC) /c Garzi.c /FoGarzi.o

DefineIf.o: DefineIf.c
	$(CC) /c DefineIf.c /FoDefineIf.o

HashMap.o: HashMap.c
	$(CC) /c HashMap.c /FoHashMap.o

PreProcesare.o: PreProcesare.c
	$(CC) /c PreProcesare.c /FoPreProcesare.o

.PHONY : clean
clean :
	del Main.o HashMap.o PreProcesare.o DefineIf.o Garzi.o Include.o so-cpp.exe