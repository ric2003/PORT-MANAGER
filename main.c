#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define MAX_IDENTIFIER_LENGTH 20
#define MAX_CONTAINERS 100
#define MAX_PILES 6
#define MAX_CONTAINERS_PER_PILE 15
#define MAX_BERTHS 10
#define MAX_EMBARCACAO 10

typedef struct {
    char code[4];
    int weight;
} Container;

typedef struct {
    Container pileContainers[MAX_CONTAINERS_PER_PILE];
    int numContainers;
} Pile;

typedef struct {
    char matricula[5];
    Pile pilhas[MAX_PILES];
} Embarcacao;

typedef struct {
    Embarcacao embarcacoes[MAX_EMBARCACAO];
} Port;

bool isValidShipIdentifier(char *identifier) {
    // Check if the identifier has exactly 4 characters
    if (strlen(identifier) != 4)
        return false;

    // Check if each character is an uppercase letter
    for (int i = 0; i < 4; i++) {
        if (!isupper(identifier[i]))
            return false;
    }
    // All checks passed, the identifier is valid
    return true;
}

bool isValidContainerCode(const char *code) {
    // Check if the code has exactly 3 characters
    if (strlen(code) != 3)
        return false;

    // Check if the first two characters are uppercase letters
    if (!isupper(code[0]) || !isupper(code[1]))
        return false;

    // Check if the third character is a digit between 0 and 9
    if (!isdigit(code[2]) || code[2] < '0' || code[2] > '9')
      return false;

    // All checks passed, the code is valid
    return true;
}

void printMenu() {
    printf(
        "+---- MENU\n"
        "| move\t\t[-g grua] [-d ponto] [-p pilha] [-D ponto] [-P pilha] [-n numero_de_contentores]\n"
        "| show\t\t[-d ponto] [-e embarc]\n"
        "| where\t[embarc]\n"
        "| navigate\t[-e embarc] [-d ponto]\n"
        "| load\t\t[-e embarc] [-p pilha] [-c contentor:peso]\n"
        "| weight\t[embarc]\n"
        "| save\t\t[filename]\n"
        "| help\n"
        "| quit\n"
        "+----\n"
    );
}
char* removeFirstFourChars(char* str) {
    int length = strlen(str);
    
    if (length <= 4) {
        // The string has 4 or fewer characters, so return an empty string
        char* newStr = (char*)malloc(1);
        newStr[0] = '\0';
        return newStr;
    } else {
        // Create a new string without the first four characters
        char* newStr = (char*)malloc(length - 3);
        strcpy(newStr, str + 4);
        return newStr;
    }
}


void navegar(Port *port, int doc, char* embarc ) {
  
    int encontrado = 0;
    int indice = -1;
    Embarcacao temp;
    if(doc>9||doc<0){
      printf("ERROR: invalid command\n");
      return;
    }
    // Check if Embarcacao with the given identifier exists
    for (int i = 0; i < MAX_EMBARCACAO; i++) {
        if (strcmp(port->embarcacoes[i].matricula, embarc) == 0) {
            encontrado = 1;
            indice = i;
            break;
        }
    }

    if(port->embarcacoes[doc].matricula[0] == '\0'){
      if(encontrado){
        temp = port->embarcacoes[doc];
        port->embarcacoes[doc] = port->embarcacoes[indice];
        port->embarcacoes[indice] = temp;
        printf("SUCCESS: operation concluded\n");
        
      }else{
        strcpy(port->embarcacoes[doc].matricula,embarc);
        //port.embarcacoes[doc].matricula=embarc;
        printf("SUCCESS: operation concluded\n");
      }
      
    }else{
       printf("ERROR: invalid command\n");
      return ;
    }

  return;
}
void load(Port *port,int pile, char* embarc, char* contentor, int weight){
  int numcontentors = 0;  
  int encontrado = 0;
    int indice = -1;
  if(pile<0||pile>5){
    printf("ERROR: invalid command\n");
      return;
  }
  for (int i = 0; i < MAX_EMBARCACAO; i++) {
          if (strcmp(port->embarcacoes[i].matricula, embarc) == 0) {
              encontrado = 1;
              indice = i;
              break;
          }
      }
    if(!encontrado){
      printf("ERROR: invalid command\n");
      return;
    }
    for (int i = 0; i < MAX_PILES; i++) {
      if(port->embarcacoes[indice].pilhas[i].numContainers!=0){
        for(int j =0; j<port->embarcacoes[indice].pilhas[i].numContainers;j++){
          if(strcmp(port->embarcacoes[indice].pilhas[i].pileContainers[j].code,contentor)==0){
            printf("ERROR: invalid command\n");
            return;
          }
        }
      }
    }
    numcontentors =port->embarcacoes[indice].pilhas[pile].numContainers;
    strcpy(port->embarcacoes[indice].pilhas[pile].pileContainers[numcontentors].code,contentor);
      port->embarcacoes[indice].pilhas[pile].pileContainers[numcontentors].weight=weight;
      port->embarcacoes[indice].pilhas[pile].numContainers++;
  printf("SUCCESS: operation concluded\n");
  return;
  
}
void where(Port *port, char* shipcode){ 
 
  int encontrado = 0;
  int indice = -1;
  char shipcodigo[5];
  
  for (int i = 0; i < MAX_EMBARCACAO; i++) {
          if (strcmp(port->embarcacoes[i].matricula, shipcode) == 0) {
              encontrado = 1;
              indice = i;
              break;
          }
  }
  if(!encontrado){
    printf("ERROR: invalid command\n");
    return;
  }
   strcpy(shipcodigo,port->embarcacoes[indice].matricula);
  
  printf("%d %s",indice,shipcodigo);
  return;
}
void show(Port *port){

for (int i = 0; i < MAX_EMBARCACAO; i++) {
          if (port->embarcacoes[i].matricula[0]!='\0'){
            printf("d%d %s\n",i,port->embarcacoes[i].matricula);
            for(int j = 0; j < MAX_PILES; j++){
              if(port->embarcacoes[i].pilhas[j].numContainers!=0){
                printf("\tp%d %d",j, port->embarcacoes[i].pilhas[j].numContainers);
                for(int k = 0; k < port->embarcacoes[i].pilhas[j].numContainers; k++){
                   printf(" %s:%d",port->embarcacoes[i].pilhas[j].pileContainers[k].code,port->embarcacoes[i].pilhas[j].pileContainers[k].weight);
                  if(k==port->embarcacoes[i].pilhas[j].numContainers-1){
                    printf("\n");
                  }
                }
              }
            }
          }
}
  return;
  
}
void show_ponto(Port *port,int ponto){

if (port->embarcacoes[ponto].matricula[0]!='\0'){
            printf("d%d %s\n",ponto,port->embarcacoes[ponto].matricula);
            for(int j = 0; j < MAX_PILES; j++){
              if(port->embarcacoes[ponto].pilhas[j].numContainers!=0){
                printf("\tp%d %d",j, port->embarcacoes[ponto].pilhas[j].numContainers);
                for(int k = 0; k < port->embarcacoes[ponto].pilhas[j].numContainers; k++){
                   printf(" %s:%d",port->embarcacoes[ponto].pilhas[j].pileContainers[k].code,port->embarcacoes[ponto].pilhas[j].pileContainers[k].weight);
                  if(k==port->embarcacoes[ponto].pilhas[j].numContainers-1){
                    printf("\n");
                  }
                }
              }
            }
          }

  
  return;
  
}
void show_embarc(Port *port,char* embarc){

  
  for (int i = 0; i < MAX_EMBARCACAO; i++) {
          if (strcmp(port->embarcacoes[i].matricula,embarc)==0){
            printf("d%d %s\n",i,port->embarcacoes[i].matricula);
            for(int j = 0; j < MAX_PILES; j++){
              if(port->embarcacoes[i].pilhas[j].numContainers!=0){
                printf("\tp%d %d",j, port->embarcacoes[i].pilhas[j].numContainers);
                for(int k = 0; k < port->embarcacoes[i].pilhas[j].numContainers; k++){
                   printf(" %s:%d",port->embarcacoes[i].pilhas[j].pileContainers[k].code,port->embarcacoes[i].pilhas[j].pileContainers[k].weight);
                  if(k==port->embarcacoes[i].pilhas[j].numContainers-1){
                    printf("\n");
                  }
                }
              }
            }
            break;
          } 
}
  return;
  
}
void weight(Port *port,char* embarc){
  int peso = 0;
  int existe = 0;
   for (int i = 0; i < MAX_EMBARCACAO; i++) {
          if (strcmp(port->embarcacoes[i].matricula,embarc)==0){
            for(int j = 0; j < MAX_PILES; j++){
              if(port->embarcacoes[i].pilhas[j].numContainers!=0){                
                for(int k = 0; k < port->embarcacoes[i].pilhas[j].numContainers; k++){
                  peso+=port->embarcacoes[i].pilhas[j].pileContainers[k].weight;
                }
              }
            }
            existe = 1;
            break;
          } 
}
  if(existe==0){
    printf("ERROR: invalid command\n");
  return;
  }
  printf("%s %d",embarc,peso);
  return;
  
}

int parseCommand(Port *port,const char* command_copy) {
  
    char command[100];
    char contentorcode[4];
  
    strcpy(command, command_copy);
    strtok(command, " ");
    //strtok(NULL, " ");
    
  
    if (strcmp(command, "move") == 0) {
        // Add your code to handle the 'move' command
    }else if (strcmp(command, "show") == 0) {
      int d_value;
      char e_value[5];
      
      int res1 = sscanf(command_copy, "show -d %d",&d_value);
      int res2 = sscanf(command_copy, "show -e %s",e_value);
      if(res1==1){
       show_ponto(port,d_value);
      }else if(res2==1){
        show_embarc(port,e_value);
      }
      
        
    }else if(strncmp(command, "show", 4) == 0){
        show(port);
    } else if (strcmp(command, "where") == 0) {
      char shipcode[5];
      int res = sscanf(command_copy, "where %s",shipcode);
      if (res == 1&&isValidShipIdentifier(shipcode)){
        where(port,shipcode);
      }else{
        printf("ERROR: invalid command\n");
      }
        
    }else if(strncmp(command, "where", 5) == 0){
        printf("ERROR: invalid command\n");
          return 1;
    } else if (strcmp(command, "navigate") == 0) {
        int d_value;
        char e_value[4];
        int res = sscanf(command_copy, "navigate -d %d -e %s", &d_value, e_value);
    
        if (res != 2) {
            res = sscanf(command_copy, "navigate -e %s -d %d", e_value, &d_value);
          }

        if (res == 2&&isValidShipIdentifier(e_value)) {
            navegar(port,d_value,e_value);
        } else {
            printf("ERROR: invalid command\n");
        }
        
    } else if (strcmp(command, "load") == 0) {
        int d_value;
        char e_value[5];
        char c_value[8];
        char* newStr;
      
        int res = sscanf(command_copy, "load -c %s -p %d -e %s", c_value, &d_value,e_value);
        if (res != 3) {
            res = sscanf(command_copy, "load -p %d -e %s -c %s", &d_value,e_value,c_value);
          }
        if (res != 3) {
            res = sscanf(command_copy, "load -c %s -e %s -p %d", c_value,e_value,&d_value);
          }
        if (res != 3) {
            res = sscanf(command_copy, "load -p %d -c %s -e %s", &d_value,c_value,e_value);
          }
        if (res != 3) {
            res = sscanf(command_copy, "load -e %s -c %s -p %d", e_value,c_value,&d_value);
          }
        if (res != 3) {
            res = sscanf(command_copy, "load -e %s -p %d -c %s", e_value,&d_value,c_value);
          }
        
        if (res == 3) {
          strncpy(contentorcode, c_value, 3);
          contentorcode[3]='\0';
          newStr = removeFirstFourChars(c_value);
          //&&isdigit(newStr)&&atoi(newStr)>=500
          if(isValidContainerCode(contentorcode)&&atoi(newStr)>=500){
            load(port,d_value,e_value,contentorcode,atoi(newStr));
          }else {
            printf("ERROR: invalid command\n");
          }
        }else{
          printf("ERROR: invalid command\n");
          }
      
        // Add your code to handle the 'load' command
    } else if (strcmp(command, "weight") == 0) {
       char shipcode[5];
      int res = sscanf(command_copy, "weight %s",shipcode);
      if (res == 1&&isValidShipIdentifier(shipcode)){
        weight(port,shipcode);
      }else{
        printf("ERROR: invalid command\n");
      }
      
        // Add your code to handle the 'weight' command
    }else if(strncmp(command, "weight", 5) == 0){
        printf("ERROR: invalid command\n");
          return 1;
    } else if (strcmp(command, "save") == 0) {
        // Add your code to handle the 'save' command
    } else if (strncmp(command, "help", 4) == 0) {
        printMenu();
    } else if (strncmp(command, "quit", 4) == 0) {
        return 0;
    } else {
      printf("ERROR: invalid command\n");
        return 1;
    }
    return 1;
}
int main() {
    int result;
    char command[100];
    Port *port = (Port *)malloc(sizeof(Port));
    
    // Create 10 Embarcacao objects
    for (int i = 0; i < MAX_EMBARCACAO; i++) {
        // Initialize matricula
        //sprintf(port->embarcacoes[i].matricula, NULL, i+1);

        // Create 6 empty piles for each Embarcacao
        for (int j = 0; j < MAX_PILES; j++) {
            port->embarcacoes[i].pilhas[j].numContainers = 0; // Initialize number of containers
        }
    }
   
    printMenu();
  
    while (1) {
        printf(">");
       fgets(command, sizeof(command), stdin);
        
        result = parseCommand(port,command);
      

        if (result == 0) {
            break;
        }
    }
    return 0;
}
