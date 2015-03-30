
/* 

The project is developed as part of Computer Architecture class
Project Name: Functional Simulator for subset of ARM Processor

Developer's Name: Varun Jain, Varun Bansal
Developer's Email id: varun14170@iiitd.ac.in, varun13168@iiitd.ac.in
Date: 27th March 2015

*/


/* myARMSim.cpp
   Purpose of this file: implementation file for myARMSim
*/

#include "myARMSim.h"
#include <stdlib.h>
#include <stdio.h>


//Register file
static unsigned int R[16];
//flags
static int N,C,V,Z;
//memory
static unsigned char MEM[4000];

//intermediate datapath and control path signals
static unsigned int instruction_word;
static unsigned int operand1;
static unsigned int operand2;

//gloabl var for nos of instr (including exit)
int nosInstr = 0;
//new array of operand1, operand2, resultx


void run_armsim() {
  while(1) {
    fetch();
    decode();
    execute();
    mem();
    write_back();
  }
}

// it is used to set the reset values
//reset all registers and memory content to 0
void reset_proc() {

}

//load_program_memory reads the input memory, and pupulates the instruction 
// memory
void load_program_memory(char *file_name) {
  FILE *fp;
  unsigned int address, instruction;
  fp = fopen("../test/simple_add.mem", "r");                             // changed
  if(fp == NULL) {
    printf("Error opening input mem file\n");
    exit(1);
  }
  while(fscanf(fp, "%x %x", &address, &instruction) != EOF) {
    //printf("%x\n", address);                                          // for testing
    //printf("%x\n", instruction);                                      // for testing
    write_word(MEM, address, instruction);
  }
  fclose(fp);
}

//writes the data memory in "data_out.mem" file
void write_data_memory() {
  FILE *fp;
  unsigned int i;
  fp = fopen("../test/simple_add_out.mem", "w");
  if(fp == NULL) {
    printf("Error opening dataout.mem file for writing\n");
    return;
  }
  
  for(i=0; i < 4000; i = i+4){
    fprintf(fp, "%x %x\n", i, read_word(MEM, i));
  }
  fclose(fp);
}

//should be called when instruction is swi_exit
void swi_exit() {
  write_data_memory();
  exit(0);
}


//reads from the instruction memory and updates the instruction register

void fetch() {
  instruction_word=read_word(MEM,R[15]);
  if(instruction_word == 0xEF000011)
  {
    swi_exit();
  } 
  printf("FETCH:Fetch instruction 0x%x from address 0x%x\n",instruction_word,R[15]);
  printf("Operand2: %llu\n", instruction_word&4095);        //get operand2
  printf("Operand1: %llu\n", (instruction_word>>16)&15);    //get operand1
  printf("Opcode  : %llu\n", (instruction_word>>21)&15);    //get opcode
  printf("DestReg : %llu\n", (instruction_word>>12)&15);    //get destReg
  printf("Immediat: %llu\n", (instruction_word>>25)&1);   // immediate
  printf("InstForm: %llu\n", (instruction_word>>26)&3);
  swi_exit();
}

//reads the instruction register, reads operand1, operand2 fromo register file, decides the operation to be performed in execute stage
void decode() {
}
//executes the ALU operation based on ALUop
void execute() {
}
//perform the memory operation
void mem() {
}
//writes the results back to register file
void write_back() {
}


int read_word(char *mem, unsigned int address) {
  int *data;
  data =  (int*) (mem + address);
  return *data;
}

void write_word(char *mem, unsigned int address, unsigned int data) {
  int *data_p;
  data_p = (int*) (mem + address);
  *data_p = data;
  //printf("%x\n", *data_p);

  nosInstr++;
}
