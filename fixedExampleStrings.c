/**
 *  
 * The student needs to compile, test and comment the source code file.
 * 
 * Enumerate those Rules and Recommendation associated that are broken in the previous source code file.
 * Enumerate he compilation tools and paramenters (gcc vs g++), -Wall ...
 * Enumerate the standard associated  -std=c99, -std=c11
 * 
 * There are several variants. You should choose at least two.
 * At the end the source code  should compile without warnings to the variant selected (you can remove/change instructions).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

char array1[] = "Foo" "bar";
char array2[] = { 'F', 'o', 'o', 'b', 'a', 'r', '\0' };
 
enum { BUFFER_MAX_SIZE = 1024 };
 
const char* s1 = "foo( \
Hello \
World \
)foo";
const char* s2 = "\nHello\nWorld\n";

//void gets_example_func(void) {
//  char buf[BUFFER_MAX_SIZE];
// 
//  if (fgets(buf, sizeof(buf), stdin) == NULL) {
//        return 1; Is a void function
//  }
//  buf[strlen(buf) - 1] = '\0';
//}

void get_dirname(void) {
  //char *slash;
  //slash = strrchr(pathname, '/');
  //if (slash) {
    //*slash = '\0'; /* Undefined behavior */
  //}
  //return pathname;

  char cwd[50];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Current working dir: %s\n", cwd);
  } else {
      printf("Getcwd: Error.");
  }
}
 

void get_y_or_n(void) {  
	char response[8];

	printf("Continue? [y] n: ");  
	//gets(response);
	fgets(response, sizeof(response), stdin);

	if (response[0] == 'n') 
		exit(0);  

	return;
}

 
int main(int argc, char *argv[])
{
    // Comprobación de que se necesitan exactamente dos argumentos
    if (argc != 3) {
  	printf("Missing arguments, you need to insert 2 arguments. \n");
  	exit(-1);
    }


    char key[24];
    //char response[8];
    char array3[18];
    char array4[18];
    char array5 []  = "01234567890123456";
    //char *ptr_char  = "new string literal";
    //char ptr_char[]  = "new string literal";
    //int size_array1 = strlen("аналитик");
    //int size_array2 = 100;
    
    //char analitic1[size_array1]="аналитик";
    //char analitic2[size_array2]="аналитик";
    //char analitic3[100]="аналитик";

    get_dirname();

        
    //strcpy(key, argv[1]);  
    //strcpy_s(key, sizeof(key), argv[1]);  
    snprintf(key, sizeof(key), "%s", argv[1]);  
    //strcat(key, " = ");  
    strncat(key, " = ", 24 - strlen(key) - 1);  
    //strcat(key, argv[2]);
    strncat(key, argv[2], 24 - strlen(key) - 1);


    //fgets(response,sizeof(response),stdin);
    
    get_y_or_n();

    printf ("%s",array1);
    printf ("\n");
    printf ("%s",array2);
    printf ("\n");
 
    puts (s1);
    printf ("\n");
    puts (s2);
    printf ("\n");
    
    //strncpy(array3, array5, sizeof(array3));  
    snprintf(array3, sizeof(array3), "%s",  array5);  
    //strncpy(array4, array3, strlen(array3));
    snprintf(array4, sizeof(array4), "%s",  array3);  
    
    array5 [0] = 'M';
    //ptr_char [0] = 'N';
    
    array3[sizeof(array3)-1]='\0';
    
    
    return 0;
}
