

compiler_sous_linux: 
	@echo "Compilation en cours"
	gcc -Wall *.c -o coachJOLinux
	@echo "Pour lancer le programme faire : 'make executer_sous_linux'"

executer_sous_linux: compiler_sous_linux
	@echo "GO"
	./coachJOLinux
