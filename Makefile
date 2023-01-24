CC = gcc
LDFLAGS = -pthread 
LIBS=-lm

all: thrNthr noThread

	$(info *********************************************************)
	$(info the generic file creates at least one thread) 
	$(info Call it "./thrNthr <number_of_integers> <number_threads>")
	$(info Output: "output2.txt" or "output1.txt" for 1 thread) 
	$(info )
	$(info the special function will execute the task directily)
	$(info taking advantage of dependencys)  
	$(info Call it "./noThread <number_of_integers>" )
	$(info Output saved in "output1.txt")    
	$(info **********************************************************)      

thrNthr: thrNthr.c
	$(CC) $(LDFLAGS) thrNthr.c -o thrNthr $(LIBS)

noThread: noThread.c
	$(CC) $(LDFLAGS) noThread.c -o noThread $(LIBS)




clean:
	rm thrNthr noThread output1.txt output2.txt

