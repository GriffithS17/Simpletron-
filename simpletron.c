#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

void load(int memory[], int size);
int run( int memory[], int size);
void dump(int memory[], int size, int accumulator, int counter, int instruction, int operation, int operand);

int main()
{
  int  choice;
  choice = 0;
  char file[30];
  char buffer[1024] = {0};


  FILE *fPtr;
  FILE *simpletron;

  if((simpletron = fopen("asciiart.txt", "r")) == NULL){
    printf("O arquivo não pode ser aberto.\n");
  }
  else{
    while(fgets(buffer, sizeof(buffer), simpletron) != NULL){
      printf("%s", buffer);
    }
    fclose(simpletron);
  }

  printf("\n");

  while (choice != 3){
    int memory[SIZE] = {0};
    int counter = 0;
    printf("1 - Usar arquivo como entrada.\n"
           "2 - Digitar instruções.\n"
           "3 - Encerrar o programa.\n");

    printf("\nEscolha uma opção: ");
    scanf("%d", &choice);

    if( choice == 1 ){
      printf("\nDigite o nome do arquivo com sua extensão (Ex: data.txt)\n");
      while(getchar() != '\n');
      fgets( file, 30, stdin );
      file[strcspn(file, "\n")] = '\0';

      if( (fPtr = fopen(file, "r")) == NULL ){
        printf("O arquivo não pode ser aberto\n");
      }
      else {
        int instruction;

        while(!feof(fPtr)){
          if(fscanf(fPtr, "%d", &instruction) != 1){
            printf("Tipo inválido na posição %d\n", counter);
            printf("*** Execução do Simpletron encerrada de forma anormal***\n");
            fclose(fPtr);
            return 0;
          }

          if (instruction == -99999) {
            printf("\n*** Carga do programa concluída ***\n");
            printf("*** Iniciando execução do programa ***\n");
            fclose(fPtr);
            break;
          }

          if (!(instruction > 9999 || instruction < -9999)){
            memory[counter++] = instruction;
          } else {
            printf("Número fora dos limites na posição %d\n", counter);
            printf("*** Execução do Simpletron encerrada de forma anormal***\n");
            fclose(fPtr);
            return 0;
          }
        }
        run(memory, SIZE);
      }
    }
    else if ( choice == 2 ){
      printf("\n*** Insira uma instrução por vez\n"
             "*** Mostrarei o número do local e\n"
             "*** uma interrogação (?).\n"
             "*** Você deverá digitar uma intrução para esse local.\n"
             "*** Digite -99999 para terminar o carregamento do programa.\n");

      load(memory, SIZE);
      run(memory, SIZE);
    }
    printf("\n");
  }
  printf("Programa finalizado.\n");
  return 0;
}

void load(int memory[], int size) {
  int instruction;
  int counter = 0;

  while (counter < size) {
    printf("%02d ? ", counter);
    if (scanf("%d", &instruction) != 1) {
      printf("Tipo inválido na posição %d.\n", counter);
      while (getchar() != '\n'); 
    }

    if (instruction == -99999) {
      printf("\n*** Carga do programa concluída ***\n");
      printf("*** Iniciando execução do programa ***\n");
      break;
    }

    if (!(instruction > 9999 || instruction < -9999)){
      memory[counter++] = instruction;
    } else {
      printf("Número fora dos limites -9999 e 9999 na posição %d\n", counter);
    }
  }
}

int run( int memory[], int size){
  int counter, accumulator, Register, operation, operand;
  accumulator = counter = Register = operation = operand = 0;

  FILE *output;

  while( counter < size ){
    Register = memory[counter];

    operation = Register/100;
    operand = Register%100;

    switch(operation){
      case READ:
        printf("? ");
        scanf("%d", &memory[operand]);
        if( (output = fopen("output.txt", "a")) == NULL ){
          printf("O arquivo não pode ser aberto.\n");
        }
        else{
          fprintf(output, "? ");
          fprintf(output, "%d\n", memory[operand]);
          fclose(output);
        }
        counter++;
        break;
      case WRITE:
        printf("%d\n", memory[operand]);
        if( (output = fopen("output.txt", "a")) == NULL ){
          printf("O arquivo não pode ser aberto.\n");
        }
        else{
          fprintf(output, "%d\n", memory[operand]);
          fclose(output);
        }
        counter++;
        break;
      case LOAD:
        accumulator = memory[operand];
        counter++;
        break;
      case STORE:
        memory[operand] = accumulator; 
        counter++;
        break;
      case ADD:
        accumulator += memory[operand];
        if(accumulator > 9999 || accumulator < -9999){
          printf("Acumulador estourado.\n");
          printf("*** Execução do Simpletron encerrada de forma anormal***\n");
          dump(memory, size, accumulator, counter, Register, operation, operand);
          printf("\n");
          return 0;
        }
        counter++;
        break;
      case SUBTRACT:
        accumulator -= memory[operand];
        if(accumulator < -9999 || accumulator > 9999){
          printf("Acumulador estourado.\n");
          printf("*** Execução do Simpletron encerrada de forma anormal***\n");
          dump(memory, size, accumulator, counter, Register, operation, operand);
          printf("\n");
          return 0;
        }
        counter++;
        break;
      case DIVIDE:
        if(accumulator == 0){
          printf("*** Tentativa de divisão por zero ***\n");
          printf("*** Execução do Simpletron encerrada de forma anormal***\n");
          dump(memory, size, accumulator, counter, Register, operation, operand);
          return 0;
        }
        accumulator = memory[operand]/accumulator;
        counter++;
        break;
      case MULTIPLY:
        accumulator *= memory[operand];
        if(accumulator < -9999 || accumulator > 9999){
          printf("Acumulador estourado.\n");
          printf("*** Execução do Simpletron encerrada de forma anormal***\n");
          dump(memory, size, accumulator, counter, Register, operation, operand);
          printf("\n");
          return 0;
        }
        counter++;
        break;
      case BRANCH:
        counter = operand;
        break;
      case BRANCHNEG: 
        if (accumulator < 0){
          counter = operand;
        }
        else {
          counter++;
        }
        break;
      case BRANCHZERO: 
        if (accumulator == 0){
          counter = operand;
        }
        else {
          counter++;
        }
        break;
      case HALT: 
        printf("\n*** Execução do Simpletron encerrada ***\n");
        dump(memory, size, accumulator, counter, Register, operation, operand);
        printf("\n");
        return 1;
      default:
        counter++;
      break;
    }
  }
}

void dump(int memory[], int size, int accumulator, int instructionCounter, int instructionRegister, int operationCode, int operand){
  int i, j;
  FILE *output;

  printf("\nREGISTERS:\n");
  printf("accumulator          %+05d\n", accumulator);
  printf("instructionCounter      %02d\n", instructionCounter);
  printf("instructionRegister  %+05d\n", instructionRegister);
  printf("operationCode           %02d\n", operationCode);
  printf("operand                 %02d\n\n", operand);

  printf("MEMORY:\n  "); 

  for (i = 0; i < 10; i++) {
    printf("%9d", i);
  }
  printf("\n");

  for (i = 0; i < SIZE; i += 10) {
    printf("%02d    ", i);

    for (j = 0; j < 10; j++) {
      printf("%+05d    ", memory[i + j]);
    }
    printf("\n");
  }
  
  if( (output = fopen("output.txt", "a")) == NULL ){
    printf("O arquivo não pode ser aberto.\n");
  }
  else{
    fprintf(output, "\nREGISTERS:\n");
    fprintf(output, "accumulator          %+05d\n", accumulator);
    fprintf(output, "instructionCounter      %02d\n", instructionCounter);
    fprintf(output, "instructionRegister  %+05d\n", instructionRegister);
    fprintf(output, "operationCode           %02d\n", operationCode);
    fprintf(output, "operand                 %02d\n\n", operand);

    fprintf(output, "MEMORY:\n  "); 

    for (i = 0; i < 10; i++) {
      fprintf(output, "%9d", i);
    }
    fprintf(output, "\n");

    for (i = 0; i < SIZE; i += 10) {
      fprintf(output, "%02d    ", i);

      for (j = 0; j < 10; j++) {
        fprintf(output, "%+05d    ", memory[i + j]);
      }
      fprintf(output, "\n");
    }   
    fprintf(output, "\n");
    fclose(output);
  }
}
