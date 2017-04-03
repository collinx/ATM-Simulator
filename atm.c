
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

FILE *file_out, *file_atm, *file_temp, *file_card, *file_data, *file_cardless;
char ch1,ch2,ch3;
char opco[20],opc[20],card[20],temp1[20],temp2[20],temp3[20];
int bal,in=256;


int decode();
void verifypin();
void changepin();
void mobileverify();
void deposit();
void showMessage();
int cardless();
void balance();
void withdrawl();

int main()
{



file_atm = fopen("batm.txt", "r+");		 //stores balance of atm
file_card = fopen("card.txt","r");    //stores information of user card
file_data = fopen("data.txt","r+");  //stores database of user
file_out = fopen("input1.txt", "w");	//stores binary conversion of full instruction
file_cardless = fopen("cardless.txt","r");



if( (!file_out) || (!file_atm) || (!file_card) || (!file_data) || (!file_cardless))
	return 0;

printf("Welcome To ATM \n");
printf("Choose From Below:\n");
printf("1. Decode Card\n2. Cardless Withdraw\n3. Cash Deposit(Admin)\n4. Exit\n");
int choice,option;
scanf("%d",&choice);
switch(choice){
	case 1:
	option = decode();

	break;
	case 2:
	option = cardless();
	break;
	case 3:
	deposit();
	showMessage();
	exit(0);
	break;
	case 4:
	showMessage();
	exit(0);
	break;
	default:
	showMessage();
	exit(0);
	break;
}

if(option){
	printf("Choose From Below:\n");
	printf("1. Balance Enquiry\n2. Cash Withdrawl\n3. Pin Change\n4. Exit\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:
		balance();
		showMessage();
		exit(0);
		break;
		case 2:
		withdrawl();
		showMessage();
		exit(0);
		break;
		case 3:
		changepin();
		showMessage();
		exit(0);
		break;
		case 4:
		showMessage();
		exit(0);
		break;

		default:
		showMessage();
		exit(0);
		break;
	}
}





fclose(file_out);
fclose(file_atm);
fclose(file_data);
fclose(file_card);
fclose(file_cardless);

}

void showMessage(){
	printf("Thank You For Using Our Services\n");
}

int decode(){
ch1 = fscanf(file_card,"%s",opco); // scanning card number
int chh=0;
while(ch1!=EOF){
	rewind(file_data);
ch2 = fscanf(file_data,"%s",opc); // scannig card number
while(ch2!=EOF){
	if(!strcmp(opc,opco)){
		strcpy(card,opc);
		ch1 = fscanf(file_card,"%s",opco);
		ch2 = fscanf(file_data,"%s",opc);
		fprintf(file_out,"start\n");
		fprintf(file_out,"mov1 r0 %s\n",opco);
		fprintf(file_out,"mov1 r1 %s\n",opc);
		verifypin( );
		fprintf(file_out,"hlt\n");
		return 1;
	}
	ch2 = fscanf(file_data,"%s",opc);
}
}
return 0;
}
void balance(){
	rewind(file_data);
	ch2 = fscanf(file_data,"%s",temp1);
	while(ch2!=EOF){
		if(!strcmp(temp1,card)){
			ch2 = fscanf(file_data,"%s",temp1);
			ch2 = fscanf(file_data,"%s",temp1);
			ch2 = fscanf(file_data,"%s",temp1);
			fprintf(file_out,"l0:\n");
			fprintf(file_out,"mov1 r4 %s\n",temp1);
			fprintf(file_out,"hlt\n");
			printf("Your Balance is : %s\n",temp1);
			return;
		}
		ch2 = fscanf(file_data,"%s",temp1);
	}
}
void withdrawl(){
ch1 = fscanf(file_card,"%s",temp2); // scanning card number

int chh=0;
while(ch1!=EOF){
	rewind(file_data);
ch2 = fscanf(file_data,"%s",temp1); // scannig card number
while(ch2!=EOF){
	if(!strcmp(temp1,temp2)){
		int s,t;

		ch2 = fscanf(file_data,"%s",temp1);
			ch2 = fscanf(file_data,"%s",temp1);
				ch2 = fscanf(file_data,"%d",&t);
					ch1 = fscanf(file_card,"%s",temp2);
		ch1 = fscanf(file_card,"%d",&s);

		fprintf(file_out,"l0:\n");
			int bamt;
		ch1 = fscanf(file_atm,"%d",&bamt);
		bamt -= s;
		fprintf(file_out,"mov1 r5 %d\n",t);
		fprintf(file_out,"mov1 r6 %d\n",s);
		fprintf(file_out,"mov1 r7 %d\n",bamt);
		fprintf(file_out,"sub r5 r6\n");
		fprintf(file_out,"sub r7 r6\n");
		fprintf(file_out,"hlt\n");
		rewind(file_atm);
		fprintf(file_atm,"%d",bamt);
		printf("Amount Successfully Withdrawn\n");
		return;
	}
	else{
			ch2 = fscanf(file_data,"%s",temp1);
	}

}
}
}


void verifypin( ){
	fprintf(file_out,"cmp r0 r1\n");
	fprintf(file_out,"jeq l0\n");
}

void changepin(){

			ch2 = fscanf(file_card,"%s",temp1);
			ch2 = fscanf(file_card,"%s",temp1);
			 	printf("Enter New Pin!!\n");
			 	char neww[20];
			 	scanf("%s",neww);
			fprintf(file_out,"l0:\n");
			fprintf(file_out,"mov1 r8 %s\n",temp1);
			fprintf(file_out,"mov1 r8 %s\n",neww);
			fprintf(file_out,"hlt\n");
			printf("Pin Changed\n");
			return;

}
void mobileverify( ){

	fprintf(file_out,"cmp r0 r1\n");
	fprintf(file_out,"jeq l0\n");

}
void deposit(){
	printf("Enter Admin Pin!!\n");
	int apin,bamt,camt;
	scanf("%d",&apin);
	if(apin==805){
		ch1 = fscanf(file_atm,"%d",&bamt);
		printf("Enter Amount Deposit!!\n");

		fprintf(file_out,"start\n");
		scanf("%d",&camt);
		fprintf(file_out,"mov1 r2 %d\n",bamt%256);
		bamt +=camt;
		fprintf(file_out,"mov1 r3 %d\n",camt%256);
		fprintf(file_out,"add r2 r3\n");
		fprintf(file_out,"hlt\n");
		printf("ATM Balance %d\n",bamt);
		rewind(file_atm);
		fprintf(file_atm,"%d",bamt);


	}
	else{
		printf("Wrong Pin!!\n");
	}
}
int cardless(){
ch1 = fscanf(file_card,"%s",opco); // scanning mobile number
int chh=0;
while(ch1!=EOF){
	rewind(file_data);
	ch2 = fscanf(file_data,"%s",opc);
	ch2 = fscanf(file_data,"%s",opc);
	ch2 = fscanf(file_data,"%s",opc);
	while(ch2!=EOF){
		if(!strcmp(opc,opco)){
			strcpy(card,opc);
			ch1 = fscanf(file_card,"%s",opco);
			ch2 = fscanf(file_data,"%s",opc);
			fprintf(file_out,"start\n");
			fprintf(file_out,"mov1 r0 %s\n",opco);
			fprintf(file_out,"mov1 r1 %s\n",opc);
			mobileverify();
			fprintf(file_out,"hlt\n");
			return 1;
		}
		else{
			ch2 = fscanf(file_data,"%s",opc);
			ch2 = fscanf(file_data,"%s",opc);
			ch2 = fscanf(file_data,"%s",opc);
			ch2 = fscanf(file_data,"%s",opc);
		}

	}
}
printf("No User Found!!");
return 0;
}

