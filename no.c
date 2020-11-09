#include <stdlib.h>// for EXIT_SUCSESS
#include <unistd.h> //for getpid
#include <string.h>//dor strcmp
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <limits.h>
//ptr = (float*) malloc(100 * sizeof(float));
const unsigned int BUF = 128;
char seq[] = { ' ', '\n', '\t'};
//char *delim = &seq;

char **tokenizeLine(char *line)

{
      unsigned int buffer = BUF;
      char **tokens =(char **) calloc(BUF , sizeof(char));
      char *token;
      unsigned int count = 0;

      if(!tokens){
          printf("malloc failed\n");
          exit(EXIT_FAILURE);
      }
    
token = strtok(line, seq);

while(token != NULL){
    tokens[count] = token;
    count++;

    if(count >= BUF){
        buffer += BUF;
        tokens = realloc(tokens, BUF * sizeof(char));

        if(!token){
            printf("realloc failed\n");
        }
    }
    token =  strtok(NULL, seq);
}
tokens[count] = NULL;


return tokens;

}



// char **tokenizeLine2(char *line, char **argv)
// {
//       while(*line != '\0'){
//           while(*line == ' ' ){

//           }
//       }
// return tokens;

// }



char *readLine(){
    size_t len = 0;
    char  *line = NULL;
   if( getline(&line,&len,stdin) == -1){
        perror("error getting line");
   }
    
     //printf("%s from readLine\n", line );
//free(line);

return line;

}
 void excuteLine(char **tokens){
     int status;
     pid_t pid;
     pid = fork();
     if(pid < 0){
//err
     }else if(pid == 0){
         //child process
        if (execvp(tokens[0], tokens) == -1) {
      perror("shell oofed");
    }
     }{
         //parent process
         waitpid(-1, &status, 0);
     } 
 }



 char **resizeTokenArr(char **tokens){
     unsigned int count = 0;
     while (tokens[count] != NULL)
     {
         /* code */
         count++;
     }
        char **tokensRet =(char **) malloc((count)* sizeof(char));

        if(!tokensRet){
          printf("malloc failed in resize token array\n");
          exit(EXIT_FAILURE);
      }

        count = 0;
  while (tokens[count] != NULL)
     {
         /* code */
         tokensRet[count] = tokens[count];
         count++;
     }
     tokensRet[count +1] = NULL;
     //printf("new arr size %d\n", count+1);


     return tokensRet;
     
 }
//  char *getLine2(void){

// //    char *buffer;
//      int pos = 0;

//     char *buffer = malloc(sizeof(char) * BUF);
//      while(1){
//          char c;
//          c = getchar();

//          if(c == EOF || c=='\n'){
//              buffer[pos] = '\0';
//              return buffer;
//          }else{
//              buffer[pos] = c;
//          }
//          pos++;
//      }
//  }
 /*

   while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;
*/
 int main(void){
     char *line_;
     char **commands_;
     char **tmp;
     while(1)
     {
         printf(">");
         line_ = readLine();
         commands_ = tokenizeLine(line_);
         tmp = resizeTokenArr(commands_);
         //sleep(2);
        // printf("%s, %s, %s \n", commands_[0],commands_[1],commands_[2]);
        // printf("%s %s %s \n", tmp[0],tmp[1],tmp[2]);
         excuteLine(commands_);
     }
     free(line_);
     free(commands_);
     free(tmp);
     
 }
