/*COA Project
	Conversion of assembly code to Binary code
	GROUP Members
	1 Rishabh Tiwari 15ucs108
	2 Shubham Mangal 15ucs138
	3 Vishwesh Jainkuniya 15ucs161
	4 Vivek K. Tiwari 15ucs162  */


	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define countGeneralRegisters 10
	#define countFlagRegisters 4

//structure of general register
struct generalRegister {
	char name[2];
  	char *value;
  	int flag; // 0 if value is char, 1 if value is int
  	int intValue;
};

typedef struct generalRegister GeneralRegister;

//structure for flag registers
struct flagRegister{
	char name[1];
  	int intValue;
};

FILE *file_inp, *file_opcode, *file_reg, *file_out, *file_atm, *file_temp, *file_card, *file_data, *file_label, *file_symbol;
char ch1,ch2,ch3;
char temp1[20],temp2[20],temp3[20];
char reg[20],regi[20],num[20],str[1];

typedef struct flagRegister FlagRegister;

GeneralRegister generalRegisters[countGeneralRegisters];
FlagRegister flagRegisters[countFlagRegisters];

void printAllRegister();
void setGeneralRegisterValue(char* name, char* value);
char* getGeneralRegisterValue(char* name);
int getGeneralRegisterIntValue(char* name);
void initGeneralRegister();
void initFlagRegister();
void setFlagRegisterValue(char* name, int value);
int getFlagRegisterValue(char* name);
void generateControlSingnal(char* signalName);





void main(int argc, char *argv[]){
	initGeneralRegister();
	initFlagRegister();
	printAllRegister();
	
	
	
		file_inp = fopen(argv[1], "r");		//stores input instructions in standard form
		file_opcode = fopen("opcode.txt", "r"); 	//stores opcodes of all instructions
		file_reg = fopen("register.txt", "r");		//stores binary equivalent of all registers
	
	
	
	if((!file_inp)   || (!file_opcode) || (!file_reg)  ) 
			return ;
			
			ch1 = fscanf(file_inp,"%s",temp1);
			while(ch1!=EOF){
			rewind(file_opcode);  
		    rewind(file_reg);
		    char bin[20]=temp1;
		    if(strlen(bin)==16){
		    	printf("Success");
		    }
		    
			}
			
			
			
		
		
		
		
}
void generateControlSingnal(char* signalName){
	printf("Contol signal generated :- %s\n", signalName);
}

void initFlagRegister(){
	int i=0;
	for(i=0;i<countFlagRegisters;i++){
		if (i==0)
		{
			flagRegisters[i].name[0] = 'Z';
			flagRegisters[i].intValue = 0;
		}else if (i==1)
		{
			flagRegisters[i].name[0] = 'N';
			flagRegisters[i].intValue = 0;
		}else if (i==2)
		{
			flagRegisters[i].name[0] = 'C';
			flagRegisters[i].intValue = 0;
		}
		else if (i==3)
		{
			flagRegisters[i].name[0] = 'O';
			flagRegisters[i].intValue = 0;
		}
		
	}
}

void initGeneralRegister(){
	int i=0;
	for(i=0;i<countGeneralRegisters;i++){
		generalRegisters[i].name[0] = 'r';
		generalRegisters[i].name[1] = 48 + i;
		generalRegisters[i].flag = 1;
		generalRegisters[i].intValue = 0;
	}
}

void printAllRegister(){
	int i=0;
	for(i=0;i<countGeneralRegisters;i++){
		if (generalRegisters[i].flag==0)
		{
			//value is char
			printf("%s : %s \n", generalRegisters[i].name, generalRegisters[i].value);
		}else
		{
			//value is int		
			printf("%s : %d \n", generalRegisters[i].name, generalRegisters[i].intValue);
		}
	}

	i=0;
	for(i=0;i<countFlagRegisters;i++){
		printf("%s : %d \n", flagRegisters[i].name, flagRegisters[i].intValue);
	}
}

void setGeneralRegisterValue(char* name, char* value){
	int i=0;
	for(i=0;i<countGeneralRegisters;i++){
		if (generalRegisters[i].name[0]==name[0])
		{
			//set char value
			generalRegisters[i].value= value;
			generalRegisters[i].flag = 0;
			break;
		}
	}
}

void setGeneralRegisterIntValue(char* name, int intValue){
	int i=0;
	for(i=0;i<countGeneralRegisters;i++){
		if (generalRegisters[i].name==name)
		{
			//set char value
			generalRegisters[i].intValue= intValue;
			generalRegisters[i].flag = 1;
			break;
		}
	}
}

int getGeneralRegisterIntValue(char* name){
	int i=0;
	for(i=0;i<countGeneralRegisters;i++){
		if (generalRegisters[i].name==name && generalRegisters[i].flag==1)
		{
			return generalRegisters[i].intValue;
		}
	}
}

char* getGeneralRegisterValue(char* name){
	int i=0;
	for(i=0;i<countGeneralRegisters;i++){
		if (generalRegisters[i].name==name && generalRegisters[i].flag==0)
		{
			return generalRegisters[i].value;
		}
	}
}


//1 for opcode (16)
//2 for opcode (12)
//3 for opcode (8)
//4 for opcode (4)

void setFlagRegisterValue(char* name, int value){
	int i=0;
	for(i=0;i<countFlagRegisters;i++){
		if (flagRegisters[i].name[0]==name[0])
		{
			//set char value
			flagRegisters[i].intValue= value;
			break;
		}
	}
}

int getFlagRegisterValue(char* name){
	int i=0;
	for(i=0;i<countFlagRegisters;i++){
		if (flagRegisters[i].name[0]==name[0])
		{
			//set char value
			return flagRegisters[i].intValue;
		}
	}
}
int getInstructionType(){
	int i=0;
	ch1 = fscanf(file_inp,"%s",opco);
	while(ch1!=EOF){
		
		    rewind(file_opcode);    // setting file pointer to beginning
		    rewind(file_reg);
		    ch2 = fscanf(file_opcode,"%s",opc);

		    //case 1 
		    //opcode is of length 16
		    char opcode16[16];

		    //get opcode in opcode16
		    for(i=0;i<16;i++)
		    {
		    	opcode16[i] = opc[i];
		    }

		    //check in opocode table
		    if(isOpcodeExist(opcode16)==1)
		    {
		    	return 1;
		    }


		    //case 2
		    //opcode is of length 12
		    char opcode12[12];

		    //get opcode in opcode16
		    for(i=0;i<12;i++)
		    {
		    	opcode16[i] = opc[i];
		    }

		    //check in opocode table
		    if(isOpcodeExist(opcode12)==1)
		    {
		    	return 2;
		    }

		    //case 3
		    //opcode is of length 8
		    char opcode8[8];

		    //get opcode in opcode16
		    for(i=0;i<8;i++)
		    {
		    	opcode8[i] = opc[i];
		    }

		    //check in opocode table
		    if(isOpcodeExist(opcode8)==1)
		    {
		    	return 3;
		    }


		    //case 4
		    //opcode is of length 4
		    char opcode4[4];

		    //get opcode in opcode16
		    for(i=0;i<4;i++)
		    {
		    	opcode8[i] = opc[i];
		    }

		    //check in opocode table
		    if(isOpcodeExist(opcode8)==1)
		    {
		    	return 4;
		    }
		   	
		ch1 = fscanf(file_inp,"%s",opco);  //get next binary instruction
	}
}


int isOpcodeExist(char opcode[], char opco[]){
	//loop over opcode table
    while(ch2!=EOF){
    	  
        if(!strcmp(opcode16,opco)){          // comparing opcode from input to opcode from opcode file
             
            ch2 = fscanf(file_opcode,"%s",bin);
            fprintf(file_out,"%s ",bin);   // on successfull comparision, inserting binary value to output file
            	instr+=16;
            return 1;
        } 
       
         ch2 = fscanf(file_opcode,"%s",opc);
    }	
}