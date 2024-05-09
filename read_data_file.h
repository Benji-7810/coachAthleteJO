#ifndef READ_DATA_FILES_H // FILENAME
#define READ_DATA_FILES_H


#define MAX_LINE_LENGTH 1024
#define NB_MAX_DATA_BY_LINE 10
#define MAX_DATA_LENGTH 100


// return the number of lines with at least 1 character
int nbLinesNotEmpty(const char* nomFichier);


// read a "data files" and return an array of lines like this
// separator example : ";"
/*
a;bbb;cccccccccccc                tab_lines[0][0] : a
ddd                               tab_lines[0][1] : bbb   
e;s;                  ==>         tab_lines[0][2] : cccccccccccc      
zzzz                              tab_lines[0][3] : NULL

                                  tab_lines[1][0] : ddd
                                  tab_lines[1][1] : NULL
                                  
                                  tab_lines[2][0] : e
                                  tab_lines[2][1] : s
                                  tab_lines[2][2] : NULL
                                  
                                  tab_lines[3][0] : zzzz
                                  tab_lines[3][1] : NULL
*/
char*** readDataFile(const char* nomFichier, const char* separator, int* nbLines);


// print an array of "data Lines"
void printDataLines(char*** tab_lines, int nbLines);



#endif