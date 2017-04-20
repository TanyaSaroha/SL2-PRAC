#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct mot{
	char mnemonic[10];
	char class[10];
	int opcode;
	int length;
}mot;

typedef struct reg{
	char name[10];
	int opcode;
}reg;

typedef struct cond{
	char name[5];
	int opcode;
}cond;

typedef struct symtab{
	char name[10];
	int addr;
	int index_no;
}symtab;

typedef struct littab{
	int index_no;
	char name[10];
	int addr;
}littab;

int check(char[],symtab[],int);
int check_literal(char[],littab[],int);
int scan_lit_table(char[],littab[],int);
int search_symbol(int,symtab[],int);
int search_lit(int,littab[],int);
int scan_sym_table(symtab[],int);
int main(){
	mot arr[17];
	reg arr2[4];
	cond arr3[6];
	FILE *fp,*fpt,*sym,*pass2,*pass1;
	char ch,s[30],c,temp[10],lit_name[10],type[10],temp_equ[10],ch1,ch2,str[1000];
	int i,lc=0,start,flag,index=0,j,found=0,num=0,lit_index=0,litnum=0,const_index=0,temp_equ_addr;
	int equ_temp=0,addr=0,temp_sym1=0,temp_sym2=0,valid;
	symtab symbol[100],*head,*symtemp;
	littab lit_table[100];
	head=NULL;
	
	strcpy(arr[0].mnemonic,"START");strcpy(arr[0].class,"AD");arr[0].opcode=1;arr[0].length=1;
	strcpy(arr[1].mnemonic,"END");strcpy(arr[1].class,"AD");arr[1].opcode=2;arr[1].length=1;
	strcpy(arr[2].mnemonic,"EQU");strcpy(arr[2].class,"AD");arr[2].opcode=3;arr[2].length=1;
	strcpy(arr[3].mnemonic,"LTORG");strcpy(arr[3].class,"AD");arr[3].opcode=4;arr[3].length=1;
	strcpy(arr[4].mnemonic,"ORIGIN");strcpy(arr[4].class,"AD");arr[4].opcode=5;arr[4].length=1;
	strcpy(arr[5].mnemonic,"STOP");strcpy(arr[5].class,"IS");arr[5].opcode=1;arr[5].length=1;
	strcpy(arr[6].mnemonic,"ADD");strcpy(arr[6].class,"IS");arr[6].opcode=2;arr[6].length=1;
	strcpy(arr[7].mnemonic,"SUB");strcpy(arr[7].class,"IS");arr[7].opcode=3;arr[7].length=1;
	strcpy(arr[8].mnemonic,"MULT");strcpy(arr[8].class,"IS");arr[8].opcode=4;arr[8].length=1;
	strcpy(arr[9].mnemonic,"MOVER");strcpy(arr[9].class,"IS");arr[9].opcode=5;arr[9].length=1;
	strcpy(arr[10].mnemonic,"MOVEM");strcpy(arr[10].class,"IS");arr[10].opcode=6;arr[10].length=1;
	strcpy(arr[11].mnemonic,"COMP");strcpy(arr[11].class,"IS");arr[11].opcode=7;arr[11].length=1;
	strcpy(arr[12].mnemonic,"BC");strcpy(arr[12].class,"IS");arr[12].opcode=8;arr[12].length=1;
	strcpy(arr[13].mnemonic,"READ");strcpy(arr[13].class,"IS");arr[13].opcode=9;arr[13].length=1;
	strcpy(arr[14].mnemonic,"PRINT");strcpy(arr[14].class,"IS");arr[14].opcode=10;arr[14].length=1;
	strcpy(arr[15].mnemonic,"DS");strcpy(arr[15].class,"DL");arr[15].opcode=1;arr[15].length=1;
	strcpy(arr[16].mnemonic,"DC");strcpy(arr[16].class,"DL");arr[16].opcode=2;arr[16].length=1;
	 
	
	strcpy(arr2[0].name,"AREG");arr2[0].opcode=1;
	strcpy(arr2[1].name,"BREG");arr2[1].opcode=2;
	strcpy(arr2[2].name,"CREG");arr2[2].opcode=3;
	strcpy(arr2[3].name,"DREG");arr2[3].opcode=4;

	
	strcpy(arr3[0].name,"LE");arr3[0].opcode=1;
	strcpy(arr3[1].name,"LT");arr3[1].opcode=2;
	strcpy(arr3[2].name,"GT");arr3[2].opcode=3;
	strcpy(arr3[3].name,"GE");arr3[3].opcode=4;
	strcpy(arr3[4].name,"EQ");arr3[4].opcode=5;
	strcpy(arr3[5].name,"ANY");arr3[5].opcode=6;
	
	
	fp=fopen("input.txt","r");
	fpt=fopen("out.txt","w");
	 
	flag=0;//assume it as symbol
	i=0;	
	
	while(1){
		ch=fgetc(fp);
		flag=0;
		
		if(ch==EOF)
			break;
			
		
			
		if(ch==' ' || ch== ',' ||ch== '\n'){
			temp[i]='\0';
			i=0;
			
			if(!strcmp(temp,"START")){
				fscanf(fp,"%d",&start);
				lc=start;
				fprintf(fpt,"\t%s,%d\t\t(c,%d)\n",arr[0].class,arr[0].opcode,lc);
				fgetc(fp);
				//fprintf(fpt,"\n%d\t",lc);
				//lc++;
				found=1;
				continue;
			}
			
			
			if(!strcmp(temp,"END")){
				fprintf(fpt,"\t%s,%d",arr[1].class,arr[1].opcode);
				found=scan_lit_table(lit_name,lit_table,litnum);
				if(found){
					for(j=(found-1);j<litnum;j++){
						lit_table[j].addr=lc;
						lc++;
					}
				}
				ch=fgetc(fp);
				break;
			}
			
			if(!strcmp(temp,"LTORG")){
				for(j=0;j<litnum;j++){
					lit_table[j].addr=lc;
					lc++;
				}
			}
			
			j=0;
			if(!strcmp(temp,"EQU")){
				while(1){
					ch=fgetc(fp);
					if(ch=='+' ||ch== '\n' || ch==' '){
						temp[j]='\0';
						j=0;
						found=check(temp,symbol,num);
						if(found){
							if(ch=='+'){
								fscanf(fp,"%d",&equ_temp);
								symbol[index-1].addr=symbol[found-1].addr+equ_temp;
								ch=fgetc(fp);
								break;
							}
							else{
								symbol[index-1].addr=symbol[found-1].addr;
								break;
							}
						}
						else{
							printf("Not found");
							break;
						}
					}
					else{
						temp[j]=ch;
						j++;
					}
				}
				fprintf(fpt,"\t%s,%d\t\t(c,%d)\n",arr[2].class,arr[2].opcode,symbol[index-1].addr);
				continue;
			}
			
			j=0;
			if(!strcmp(temp,"ORIGIN")){
				while(1){
					ch=fgetc(fp);
					if(ch=='+' ||ch== '\n' || ch==' '){
						temp[j]='\0';
						j=0;
						found=check(temp,symbol,num);
						if(found){
							if(ch=='+'){
								fscanf(fp,"%d",&equ_temp);
								lc=symbol[found-1].addr+equ_temp;
								ch=fgetc(fp);
								break;
							}
							else{
								lc=symbol[found-1].addr;
								break;
							}
						}
						else{
							printf("Not found");
							break;
						}
					}
					else{
						temp[j]=ch;
						j++;
					}
				}
				fprintf(fpt,"\t%s,%d\t\t(c,%d)\n",arr[4].class,arr[4].opcode,lc);
				continue;
			}

			if(!strcmp(temp,"DS")){
				fscanf(fp,"%d",&equ_temp);
				fprintf(fpt,"%d\t%s,%d\t\t(c,%d)\n",lc,arr[15].class,arr[15].opcode,equ_temp);
				ch=fgetc(fp);
				lc++;
				continue;
			}
			
			j=0;
			if(!strcmp(temp,"DC")){
				ch1=fgetc(fp);
				while(ch1!=ch2){
					ch2=fgetc(fp);
					temp[j]=ch2;
					j++;
				}
				temp[j-1]='\0';
				fprintf(fpt,"%d\t%s,%d\t\t(c,%s)\n",lc,arr[16].class,arr[16].opcode,temp);
				lc++;
				ch=fgetc(fp);
				continue;
			}
			
			for(j=2;j<17;j++)
			{		
				if(!strcmp(temp,arr[j].mnemonic)){
					flag=1;//found from mot
					if(strcmp("AD",arr[j].class)){
						fprintf(fpt,"%d\t%s,%d\t",lc,arr[j].class,arr[j].opcode);
						lc++;	
					}
					else{
						fprintf(fpt,"\t%s,%d\t",arr[j].class,arr[j].opcode);
					}
					
					//strcpy(type,arr[j].class);
					break;
				}
			}
				
			if(flag==0){
				for(j=0;j<4;j++){
					if(!strcmp(arr2[j].name,temp)){
						flag=2;//found from reg
						fprintf(fpt,"%d\t",arr2[j].opcode);
						//continue;
						break;
					}
				}	
			}
				
			if(flag==0){
				for(j=0;j<6;j++){
					if(!strcmp(arr3[i].name,temp)){
						flag=3;//found from BC
						fprintf(fpt,"%d\t",arr3[j].opcode);
						break;
					}
				}
			}
				
			if(flag==0 && ch=='\n'){
					
				found=check(temp,symbol,num);	
					
				if(!found){		//not in symtab
					num++;//index of symtab
					symbol[index].index_no=num;
					strcpy(symbol[index].name,temp);
					symbol[index].addr=-1;
					fprintf(fpt,"(s,%d)",num);
					index++;
				}
				else{
					fprintf(fpt,"(s,%d)",symbol[found-1].index_no);
				}
					
			}
				
				
			if(flag==0 && ch==' '){
				found=check(temp,symbol,num);
				if(found){
					symbol[found-1].addr=lc;
				}
				else{
					//printf("dd-%s\n",temp);
					num++;
					symbol[index].index_no=num;
					strcpy(symbol[index].name,temp);
					symbol[index].addr=lc;
					//fprintf(fpt,"(s,%d)",num);
					index++;
				}
			}		
		}
		
		else if(ch=='='){
			fscanf(fp,"%s",lit_name);
			found=check_literal(lit_name,lit_table,litnum);
			if(!found){
				litnum++;
				strcpy(lit_table[lit_index].name,lit_name);
				lit_table[lit_index].addr=-1;
				lit_table[lit_index].index_no=litnum;
				lit_index++;	
				fprintf(fpt,"(l,%d)",litnum);
			}
			else{
				fprintf(fpt,"(l,%d)",found);
			}
			ch=fgetc(fp);
		}
			
		else{
			temp[i]=ch;
			i++;
		}
		
		
		if(ch=='\n'){
				fprintf(fpt,"\n");
				//lc++;
		}
	}
	fclose(fpt);

	valid=scan_sym_table(symbol,index);	
	printf("SYMTAB\n");
	printf("--------------\n");
	for(i=0;i<index;i++){
		if(symbol[i].addr==-1)
			printf("%s\tNOT DEFINED\n",symbol[i].name);
		else	
			printf("%s\t%d\n",symbol[i].name,symbol[i].addr);
	}
	
	printf("\nLITTAB\n");
	printf("--------------\n");
	for(i=0;i<litnum;i++){
		printf("%s\t%d\n",lit_table[i].name,lit_table[i].addr);
	}
	
/*-------------------------------------------------------------------------------------------------
	PASS 2
	
	------------------------------------------------------------------------------------------------*/	
	
	if(valid){
	
	pass1=fopen("out.txt","r");
	pass2=fopen("pass2.txt","w");
	
	i=0;
	lc=0;
	while(1){
		ch=fgetc(pass1);
		
		if(ch==EOF)
			break;
			
		if(ch==' ' || ch== ',' ||ch== '\n' || ch=='\t' || ch=='(' || ch==')'){
			temp[i]='\0';
			i=0;
			
			//printf("%s",temp);
			if(!strcmp(temp,"AD") ){
				fscanf(pass1,"%[^\n]", str);
				//printf("%s",str);
				continue;
			}
			
			if(!strcmp(temp,"DL")){
				fscanf(pass1,"%[^\n]", str);
				//printf("%s",str);
				continue;
			}
			
			if(!strcmp(temp,"IS")){
				fscanf(pass1,"%d",&temp_sym1);
				fprintf(pass2,"\t%d\t",temp_sym1);
				ch=fgetc(pass1);
				ch=fgetc(pass1);
		
				if(ch=='('){
					ch=fgetc(pass1);
					if(ch=='s'){
						ch=fgetc(pass1); 
						fscanf(pass1,"%d",&temp_sym1);
						addr=search_symbol(temp_sym1,symbol,index);
						fprintf(pass2,"\t%d",addr);	
					}
					if(ch=='l'){
						ch=fgetc(pass1);
						fscanf(pass1,"%d",&temp_sym1);
						addr=search_lit(temp_sym1,lit_table,index);
						fprintf(pass2,"\t%d",addr);
					}
				}
				else{
					fprintf(pass2,"%c",ch);
					ch=fgetc(pass1);
					ch=fgetc(pass1);
					ch=fgetc(pass1);
					
					if(ch=='s'){
						ch=fgetc(pass1);
						fscanf(pass1,"%d",&temp_sym1);
						addr=search_symbol(temp_sym1,symbol,index);
						fprintf(pass2,"\t%d",addr);	
					}
					if(ch=='l'){
						ch=fgetc(pass1);
						fscanf(pass1,"%d",&temp_sym1);
						addr=search_lit(temp_sym1,lit_table,index);
						fprintf(pass2,"\t%d",addr);	
					}
				}
			}
			
			if(ch=='\n'){
				fprintf(pass2,"\n");
				if(fscanf(pass1,"%d",&lc))
					fprintf(pass2,"%d",lc);
				else
					fprintf(pass2,"-\t-\t-\t-");
			}
		}
		if(isalpha(ch)){
			temp[i]=ch;
			i++;
		}
	}
	}
	else{
		pass2=fopen("pass2.txt","w");
		//fprintf(pass2,"ERROR");
	}
return 0;
}


int check(char temp[],symtab arr[],int n){
	int i;
	
	for(i=0;i<n;i++){
		if(!strcmp(temp,arr[i].name)){
			return (arr[i].index_no);//found,not insert
		}
	}
	return 0;//not in symtab,insert new
}

int check_literal(char lit_name[],littab arr[],int litnum){
	int i;
	
	for(i=0;i<litnum;i++){
		if((!strcmp(lit_name,arr[i].name) && (arr[i].addr==-1))){
			return arr[i].index_no;//found in litttab 
		}
	}
	return 0;//not in littab
}

int scan_lit_table(char lit_name[],littab arr[],int litnum){
	int i;
	
	for(i=0;i<litnum;i++){
		if(arr[i].addr==-1){
			return arr[i].index_no;//found (addr not defined) 
		}
	}
	return 0;//addr defined
}

int search_symbol(int index,symtab arr[],int n){
	int i;
	
	for(i=0;i<n;i++){
		if(arr[i].index_no==index){
			return arr[i].addr;
		}
	}
}

int search_lit(int index,littab arr[],int n){
	int i;
	
	for(i=0;i<n;i++){
		if(arr[i].index_no==index){
			return arr[i].addr;
		}
	}
}

int scan_sym_table(symtab arr[],int n){
	int i;
	
	for(i=0;i<n;i++){
		if(arr[i].addr==-1)
			return 0;
	}
	return 1;
}
