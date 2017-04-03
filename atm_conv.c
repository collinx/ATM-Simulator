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


int main()
{
	char ch1,ch2,ch3;
	char opco[20],opc[20],bin[20],reg[20],regi[20],num[20],str[1];
	int bal,in=256,line=1,instr=-1;
	FILE *file_inp, *file_opcode, *file_reg, *file_out, *file_atm, *file_temp, *file_card, *file_data, *file_label, *file_symbol;

		file_inp = fopen("input1.txt", "r");		//stores input instructions in standard form
		file_opcode = fopen("opcode.txt", "r"); 	//stores opcodes of all instructions
		file_reg = fopen("register.txt", "r");		//stores binary equivalent of all registers
		file_atm = fopen("batm.txt", "r+");		 //stores balance of atm
		file_card = fopen("card.txt","r");    //stores information of user card
		file_data = fopen("data.txt","r");  //stores database of user
		file_out = fopen("output1.txt", "w");	//stores binary conversion of full instruction
		file_label = fopen("label.txt","w");  // store label information
		file_symbol = fopen("symbol.txt","w");

		if((!file_inp) || (!file_out) || (!file_opcode) || (!file_reg) || (!file_atm) || (!file_card) || (!file_data) || (!file_label) || (!file_symbol))
			return 0;

		printf("Welcome To ATM Simulator\n");

		ch1 = fscanf(file_inp,"%s",opco); // scanning opcodes to process

		while(ch1!=EOF){

		    rewind(file_opcode);    // setting file pointer to beginning
		    rewind(file_reg);
		    ch2 = fscanf(file_opcode,"%s",opc);
		    while(ch2!=EOF){

		        if(!strcmp(opc,opco)){          // comparing opcode from input to opcode from opcode file

		        	ch2 = fscanf(file_opcode,"%s",bin);
		            fprintf(file_out,"%s ",bin);   // on successfull comparision, inserting binary value to output file
		            instr+=16;
		            break;
		        }

		        ch2 = fscanf(file_opcode,"%s",opc);
		    }

		    if(strlen(bin) == 16){
		    	char *ret;
		    	ret = strstr(opco, ":");
		    	if(ret != NULL){
		    		fprintf(file_label,"%s %d\n",opco,line);
		    		fprintf(file_symbol,"%s\n",opco);
		    	} else {
		    		if ( file_symbol != NULL) {
					   // fseek (file_symbol,0 , SEEK_END);
		    			int size = ftell(file_symbol);
		    			if ( size != 0) {
		    				fprintf(file_symbol,"%s\t|\t%d\n",bin,instr);

		    			}
		    		}
		    	}
		    	fprintf(file_out,"\n");
		    } else if(strlen(bin) == 12){
		    	if ( file_symbol != NULL) {
					   // fseek (file_symbol,0 , SEEK_END);
		    		int size = ftell(file_symbol);
		    		if ( size != 0) {
		    			fprintf(file_symbol,"%s\t|\t%d\n",bin,instr);

		    		}
		    	}
		    	ch1 = fscanf(file_inp,"%s",opco);
		    	ch2 = fscanf(file_reg,"%s",reg);
		    	while(ch2!=EOF){
		    		if(!strcmp(reg,opco)){
		    			ch2 = fscanf(file_reg,"%s",regi);
		    			fprintf(file_out,"%s ",regi);
		    			break;
		    		}
		    		ch2 = fscanf(file_reg,"%s",reg);
		    	}
		    	fprintf(file_out,"\n");

		    } else if(strlen(bin) == 8){
		    	if ( file_symbol != NULL) {
					   // fseek (file_symbol,0 , SEEK_END);
		    		int size = ftell(file_symbol);
		    		if ( size != 0) {
		    			fprintf(file_symbol,"%s\t|\t%d\n",bin,instr);

		    		}
		    	}
		    	ch1 = fscanf(file_inp,"%s",opco);
		    	if(isdigit(opco[0])){
		    		in = atoi(opco);
		    	}
		    	if(in == 0){
		    		fprintf(file_out,"%s ","00000000");
		    	} else if(in > 0 && in < 256){
		    		int digi=7;
		    		int quotient = in;
		    		int l;
		    		for(l=0;l<8;l++)
		    			num[l]=0;
		    		while(quotient!=0)
		    		{
		    			num[digi]= quotient % 2;
		    			quotient = quotient / 2;
		    			digi--;
		    		}
		    		int k=0;
		    		while(k!=8)
		    		{
		    			fprintf(file_out,"%d",num[k]);
		    			k++;
		    		}
		    	} else {
		    		ch2 = fscanf(file_reg,"%s",reg);
		    		while(ch2!=EOF){
		    			if(!strcmp(reg,opco)){
		    				ch2 = fscanf(file_reg,"%s",regi);
		    				fprintf(file_out,"%s ",regi);
		    				break;
		    			}
		    			ch2 = fscanf(file_reg,"%s",reg);
		    		}
		    		rewind(file_reg);
		    		ch1 = fscanf(file_inp,"%s",opco);
		    		ch2 = fscanf(file_reg,"%s",reg);
		    		while(ch2!=EOF){
		    			if(!strcmp(reg,opco)){
		    				ch2 = fscanf(file_reg,"%s",regi);
		    				fprintf(file_out,"%s ",regi);
		    				break;
		    			}
		    			ch2 = fscanf(file_reg,"%s",reg);
		    		}
		    	}
		    	fprintf(file_out,"\n");
		    } else if(strlen(bin) == 4){
		    	if ( file_symbol != NULL) {
					   // fseek (file_symbol,0 , SEEK_END);
		    		int size = ftell(file_symbol);
		    		if ( size != 0) {
		    			fprintf(file_symbol,"%s\t|\t%d\n",bin,instr);

		    		}
		    	}
		    	ch1 = fscanf(file_inp,"%s",opco);
		    	ch2 = fscanf(file_reg,"%s",reg);
		    	while(ch2!=EOF){
		    		if(!strcmp(reg,opco)){
		    			ch2 = fscanf(file_reg,"%s",regi);
		    			fprintf(file_out,"%s ",regi);
		    			break;
		    		}
		    		ch2 = fscanf(file_reg,"%s",reg);
		    	}
		    	ch1 = fscanf(file_inp,"%s",opco);

		    	in = atoi(opco);

		    	if(in == 0){
		    		fprintf(file_out,"%s ","00000000");
		    	} else if(in > 0 && in < 256){
		    		int digi=7;
		    		int quotient = in;
		    		int l;
		    		for(l=0;l<8;l++)
		    			num[l]=0;
		    		while(quotient!=0)
		    		{
		    			num[digi]= quotient % 2;
		    			quotient = quotient / 2;
		    			digi--;
		    		}
		    		int k=0;
		    		while(k!=8)
		    		{
		    			fprintf(file_out,"%d",num[k]);
		    			k++;
		    		}
		    	}


		    	fprintf(file_out,"\n");
		    }
		    line++;
		    ch1 = fscanf(file_inp,"%s",opco);
		}



		fclose(file_inp);
		fclose(file_out);
		fclose(file_opcode);
		fclose(file_atm);
		fclose(file_reg);
		fclose(file_data);
		fclose(file_card);

		printf("\nProgram Assembled Succefully. Open output.txt to view the results\n");
	}
