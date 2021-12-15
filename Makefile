OBJS = main.o  bank.o
SOURCE = main.cpp  bank.cpp
HEADER = bank.h cashier.h
PROGRAM = exe
CC = g++
CFLAGS = -Wall -W
DEBUGER = -g3

$(PROGRAM): clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM) 

main.o: main.cpp
	$(CC) $(DEBUGER) $(CFLAGS) -c main.cpp 

bank.o: bank.cpp
	$(CC) $(DEBUGER) $(CFLAGS) -c bank.cpp 

clean:
	rm -f $(OBJS) $(PROGRAM)
	
run:
	./$(PROGRAM) 5 1 15 1
	
val:
	valgrind --leak-check=full -v ./$(PROGRAM) 5 1 5 10

debug:
	gdb ./$(PROGRAM)
	
	# Usefull comands for gdb : 
	#			run program_arguments or < file_name----------> to run your program
	#			backtrace or bt-------------------------------> print all active (not finished) function calls in the calling stack,
	#									    					the most recent call is at the top, #X at the beginning of each line 
	#							    	    	    			is the position in the stack (0 == top), press enter for more
	#			backtrace full--------------------------------> same with backtrace / bt but shows the values of each local variable as well
	#			break or b------------------------------------> pause execution at certain program points (breakpoints),
	#								    	    				pause before executing the command at that point,
	#								    	   					wait there for user commands, 
	#								    	    				break fun1 → break at start of function “fun1”
	#								    	   				 	break 10 → break at line 10 (if one file only)
	#								    	    				break t1.c:5 → break at line 5 of file “t1.c”
	#			next or n-------------------------------------> after a breakpoint, execute the next program instruction,
	#								    	    				executes the whole function call
	#			step or s-------------------------------------> after a breakpoint, execute the next program instruction,
	#								    	   				 	goes inside the function and waits for more commands
	#			finish or f-----------------------------------> executes current function until it returns and then waits
	#			continue or c---------------------------------> run without a pause until the next breakpoint
	#			quit or q-------------------------------------> terminate gdb
	#			print or p------------------------------------> print the current value of a program expression
	#									    					an expression can be simple (e.g., variables, etc)
	#									    					or complicated (e.g., function calls)
	#			frame #number---------------------------------> move to position #number in the calling stack
	#	   ~! if something is 0x0 it means it is NULL !~

count:
	wc $(SOURCE) $(HEADER)