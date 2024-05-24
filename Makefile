executer_sous_linux: compiler_sous_linux
	@echo "GO"
	./coachJOLinux


compiler_sous_linux: 
	@echo "Compilation en cours"
	gcc -Wall *.c -o coachJOLinux


