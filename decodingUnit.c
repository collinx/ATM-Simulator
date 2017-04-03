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
  	char name;
  	int intValue;
  };

  FILE *file_inp, *file_opcode, *file_reg, *file_out, *file_atm, *file_temp, *file_card, *file_data, *file_label, *file_symbol;
  char ch1,ch2,ch3;

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
  void setFlagRegisterValue(char name, int value);
  int getFlagRegisterValue(char name);
  void generateControlSingnal(char* signalName);
  int convertBinaryToDecimal(long long n);
  void setGeneralRegisterIntValue(char* name, int intValue);



  void main(){
  	initGeneralRegister();
  	initFlagRegister();
  	printAllRegister();



		file_inp = fopen("output.txt", "r");		//stores input instructions in standard form
		file_opcode = fopen("opcode.txt", "r"); 	//stores opcodes of all instructions
		file_reg = fopen("register.txt", "r");		//stores binary equivalent of all registers



		if((!file_inp)   || (!file_opcode) || (!file_reg)  )
			return ;
		char temp1[20];
		ch1 = fscanf(file_inp,"%s",temp1);
		while(ch1!=EOF){
			char temp2[20],temp3[20];
			rewind(file_opcode);
			rewind(file_reg);
			char bin[20],prev[20];
			strcpy(bin,temp1);
			if(strlen(bin)==16){
				ch2 = fscanf(file_opcode,"%s",temp2);
				while(ch2!=EOF){

					if(!strcmp(temp1,temp2)){

						if(prev[0]=='l'){
							printf("Label %s \n",prev);
						}else{
							printf("%s sequence\n",prev);
						}
						break;
					} else{
						strcpy(prev,temp2);
						ch2 = fscanf(file_opcode,"%s",temp2);
					}
				}

			}else  if(strlen(bin)==12){
			}else  if(strlen(bin)==8){
				char last[20];
				ch2 = fscanf(file_opcode,"%s",temp2);
				while(ch2!=EOF){

					if(!strcmp(temp1,temp2)){

						if(!strcmp(prev,"add")){
							generateControlSingnal("Select ADD");
							ch1 = fscanf(file_inp,"%s",temp1);
							rewind(file_reg);
							ch3 = fscanf(file_reg,"%s",temp3);
							while(ch3!=EOF){
								char prev1[20];
								if(!strcmp(temp1,temp3)){



									strcpy(last,prev1);

									break;
								} else{
									strcpy(prev1,temp3);
									ch3 = fscanf(file_reg,"%s",temp3);
								}
							}

							ch1 = fscanf(file_inp,"%s",temp1);
							rewind(file_reg);
							ch3 = fscanf(file_reg,"%s",temp3);
							while(ch3!=EOF){
								char prev1[20];
								if(!strcmp(temp1,temp3)){




									setGeneralRegisterIntValue(last,getGeneralRegisterIntValue(last)+getGeneralRegisterIntValue(prev1));
									break;
								} else{
									strcpy(prev1,temp3);
									ch3 = fscanf(file_reg,"%s",temp3);
								}
							}
							printf("Contol signal generated :- %s IN\n", last);
							printAllRegister();
						}else if(!strcmp(prev,"sub")){
							generateControlSingnal("Select SUB");
							ch1 = fscanf(file_inp,"%s",temp1);
							rewind(file_reg);
							ch3 = fscanf(file_reg,"%s",temp3);
							while(ch3!=EOF){
								char prev1[20];
								if(!strcmp(temp1,temp3)){



									strcpy(last,prev1);
									break;
								} else{
									strcpy(prev1,temp3);
									ch3 = fscanf(file_reg,"%s",temp3);
								}
							}

							ch1 = fscanf(file_inp,"%s",temp1);
							rewind(file_reg);
							ch3 = fscanf(file_reg,"%s",temp3);
							while(ch3!=EOF){
								char prev1[20];
								if(!strcmp(temp1,temp3)){



									setGeneralRegisterIntValue(last,getGeneralRegisterIntValue(last)-getGeneralRegisterIntValue(prev1));
									break;
								} else{
									strcpy(prev1,temp3);
									ch3 = fscanf(file_reg,"%s",temp3);
								}
							}


							printAllRegister();
						}else{
							generateControlSingnal("Select CMP");
							ch1 = fscanf(file_inp,"%s",temp1);
							rewind(file_reg);
							ch3 = fscanf(file_reg,"%s",temp3);
							while(ch3!=EOF){
								char prev1[20];
								if(!strcmp(temp1,temp3)){



									strcpy(last,prev1);
									break;
								} else{
									strcpy(prev1,temp3);
									ch3 = fscanf(file_reg,"%s",temp3);
								}
							}

							ch1 = fscanf(file_inp,"%s",temp1);
							rewind(file_reg);
							ch3 = fscanf(file_reg,"%s",temp3);
							while(ch3!=EOF){
								char prev1[20];
								if(!strcmp(temp1,temp3)){



									int diff = getGeneralRegisterIntValue(last)-getGeneralRegisterIntValue(prev1);
									if(diff==0){
										setFlagRegisterValue('Z',1);
										setFlagRegisterValue('N',0);
										setFlagRegisterValue('O',0);
										setFlagRegisterValue('C',0);
									}else if(diff <0){
										setFlagRegisterValue('Z',0);
										setFlagRegisterValue('N',1);
										setFlagRegisterValue('O',0);
										setFlagRegisterValue('C',0);

									}
									break;
								} else{
									strcpy(prev1,temp3);
									ch3 = fscanf(file_reg,"%s",temp3);
								}
							}
							printAllRegister();


						}
						break;
					} else{
						strcpy(prev,temp2);
						ch2 = fscanf(file_opcode,"%s",temp2);
					}
				}

			}else  if(strlen(bin)==4){


				ch2 = fscanf(file_opcode,"%s",temp2);
				while(ch2!=EOF){
					char last[20];
					if(!strcmp(temp1,temp2)){

						if(!strcmp(prev,"mov1")){
							ch1 = fscanf(file_inp,"%s",temp1);
							rewind(file_reg);
							ch3 = fscanf(file_reg,"%s",temp3);
							while(ch3!=EOF){
								char prev1[20];
								if(!strcmp(temp1,temp3)){



									strcpy(last,prev1);
									break;
								} else{
									strcpy(prev1,temp3);
									ch3 = fscanf(file_reg,"%s",temp3);
								}
							}
							long long int num=0;
							ch1 = fscanf(file_inp,"%lld",&num);
							int valv =  convertBinaryToDecimal(num);


							setGeneralRegisterIntValue(last,valv);


							printAllRegister();
						}
						break;
					} else{
						strcpy(prev,temp2);
						ch2 = fscanf(file_opcode,"%s",temp2);
					}
				}
			}

			ch1 = fscanf(file_inp,"%s",temp1);
		}


		fclose(file_inp);

		fclose(file_opcode);

		fclose(file_reg);






	}

	int ipow(int base, int exp)
	{
		int result = 1;
		while (exp)
		{
			if (exp & 1)
				result *= base;
			exp >>= 1;
			base *= base;
		}

		return result;
	}
	int convertBinaryToDecimal(long long n)
	{
		int decimalNumber = 0, i = 0, remainder;
		while (n!=0)
		{
			remainder = n%10;
			n /= 10;
			decimalNumber += remainder*ipow(2,i);
			++i;
		}
		return decimalNumber;
	}
	void generateControlSingnal(char* signalName){
		printf("Contol signal generated :- %s\n", signalName);
	}

	void initFlagRegister(){
		int i=0;
		for(i=0;i<countFlagRegisters;i++){
			if (i==0)
			{
				flagRegisters[i].name = 'Z';
				flagRegisters[i].intValue = 0;
			}else if (i==1)
			{
				flagRegisters[i].name = 'N';
				flagRegisters[i].intValue = 0;
			}else if (i==2)
			{
				flagRegisters[i].name = 'C';
				flagRegisters[i].intValue = 1;
			}
			else if (i==3)
			{
				flagRegisters[i].name = 'O';
				flagRegisters[i].intValue = 0;
			}

		}
	}

	void initGeneralRegister(){
		int i=0;
		for(i=0;i<countGeneralRegisters;i++){
			generalRegisters[i].name[0] = 'r';
			generalRegisters[i].name[1] = '0' + i;
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
			printf("%c : %d \n", flagRegisters[i].name, flagRegisters[i].intValue);
		}

		printf("\n");
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
			if (generalRegisters[i].name[1]==name[1])
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
			if (generalRegisters[i].name[1]==name[1] && generalRegisters[i].flag==1)
			{
                    return generalRegisters[i].intValue;
			}
		}
	}

	char* getGeneralRegisterValue(char* name){
		int i=0;
		for(i=0;i<countGeneralRegisters;i++){
			if (strcmp(generalRegisters[i].name,name) && generalRegisters[i].flag==0)
			{
				return generalRegisters[i].value;
			}
		}
	}


//1 for opcode (16)
//2 for opcode (12)
//3 for opcode (8)
//4 for opcode (4)

	void setFlagRegisterValue(char name, int value){
		int i=0;
		for(i=0;i<countFlagRegisters;i++){
			if (flagRegisters[i].name==name)
			{
			//set char value
				flagRegisters[i].intValue= value;
				break;
			}
		}
	}

	int getFlagRegisterValue(char name){
		int i=0;
		for(i=0;i<countFlagRegisters;i++){
			if (flagRegisters[i].name==name)
			{
			//set char value
				return flagRegisters[i].intValue;
			}
		}
	}
