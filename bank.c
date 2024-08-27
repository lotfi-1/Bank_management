#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<stdarg.h>
#include<Windows.h>
#include"bank.h"
#include<conio.h>
COORD coord = {0, 0}; // sets coordinates to 0,0
//COORD max_buffer_size = GetLargestConsoleWindowSize(hOut);
COORD max_res,cursor_size;
void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void dly(unsigned int mili){
    clock_t goal = mili + clock();
    while (goal > clock());
}
void create_new_acount() {
    FILE* pfile = NULL;
    info data;
    printf("\n First name : ");
    fgets(data.first_name, 15, stdin);
    printf("\n Last name  : ");
    fgets(data.family_name, 15, stdin);
    do {
        printf("\n Date of birth (yyyy/mm/dd) : ");
        fgets(data.date_birth, 11, stdin);
    } while (date_(data.date_birth) == false);
    printf("\n Adress : ");
    fgets(data.adress, 60, stdin);
    printf("\n National Identification Number : ");
    fscanf(stdin, "%d", &data.NIN);
    printf("\n Phone number : ");
    fscanf(stdin, "%d", &data.n_tele);
    printf("\n Enter the amount to deposit : ");
    fscanf(stdin, "%d", &data.mony);
    srand(time(NULL));
    int i = 0;
    char  c;
    while (i < 10) {
        c = (rand() % 10) + '0';
        data.CCP[i] = c;
        i++;
    }
    data.CCP[10] = '\0';

    int exist;
    exist =  existing_acount1(data.NIN);
    if (exist == -1 ) {
        printf("This acount is already exist :( ");
        close();
    }
    pfile = fopen("data.bin", "ab");
    if (!pfile) {
        printf("\n ERROR TO SAVE THIS INFORMATION :( ");
        printf("\n check your information ");
        close();
    }
    fseek(pfile,0,SEEK_END);
    
        data.n_acount = exist + 1;
        fwrite(&data, sizeof(data), 1, pfile);
        fclose(pfile);
    printf("\n Your account has been created successfuly :) ");
    close();
}
int existing_acount(char* nin) {
    FILE* pfile = NULL;
    info data1;
    int endf, a;
    pfile = fopen("data.bin", "rb");
    if (!pfile) {
        printf("unable to open \"data.bin\" ");
        close();
    }
    fseek(pfile, 0, SEEK_END);
    endf = ftell(pfile);
    rewind(pfile);

    while (ftell(pfile) != endf) {
        fread(&data1, sizeof(data1), 1, pfile);
        a = ftell(pfile);
        if (strncmp(data1.CCP, nin, 11) == 0) {
            fclose(pfile);
            return a - sizeof(data1);
        }
    }
    fclose(pfile);
    return -1;
}
int existing_acount1(unsigned int  nin) {
    FILE* pfile = NULL;
    info data1;
    int endf, a;
    pfile = fopen("data.bin", "rb");
    if (!pfile) {
        return 0;
    }
    fseek(pfile, 0, SEEK_END);
    endf = ftell(pfile);
    rewind(pfile);
    while (ftell(pfile) != endf) {
        fread(&data1, sizeof(data1), 1, pfile);
        a = ftell(pfile);
        if (data1.NIN==nin) {
            fclose(pfile);
            return -1;
        }
    }
    fclose(pfile);
    return data1.n_acount;
}
bool date_(char* data) {
    int year, month, day;
    char* end;
    year = strtod(data, &end);
    if (year < 1950 || year > 2023)
        return false;

    end++;
    month = strtod(end, &end);
    if (month < 1 || month > 12)
        return false;

    end++;
    day = strtod(end, NULL);
    if ((day < 0 || day > 31) || (month == 2 && day > 29))
        return false;

    return true;
}
void update_info() {
    char ccp1[11];
    int exist1;
    int choice;
    char adress_[60];
    unsigned int tel;
    printf("\n\n *- Enter your CCP : ");
    fgets(ccp1, 11, stdin);
    exist1 = existing_acount(ccp1);
    printf("\n loading ");
    for(int i=0;i<3;i++){
        dly(100);
        printf(".");
    }
    if (exist1 == -1) {
        printf("\n Tise acount does not existe ");
        close();
    }
    system("cls");
    system("color 6");
    printf("\n 1- phone number ");
    printf("\n 2- Adress ");
    printf("\n\n select option : ");
    fscanf(stdin, "%d", &choice);
    switch (choice)
    {
    case 1: {
        printf("\n\n     * Enter new phone number : ");
        fscanf(stdin, "%d", &tel);
        copy_file(choice, NULL,tel,exist1,-1);
        
    }
          break;
    case 2: {
        getchar();
        printf("\n\n     * Enter new Adress : ");
        fgets(adress_, 60, stdin);
        copy_file(choice, adress_,0,exist1,-1);
    }
          break;
    default: close();
        break;
    }

}
void copy_file(int choice,  char* data, int data_,int existe,int exist2) {
    FILE* pfile = NULL;
    FILE* p2file = NULL;
    int endf;
    info data2;
    pfile = fopen("data.bin", "rb");
    p2file = fopen("copy.bin", "wb");
    if (pfile == NULL && p2file == NULL) {
        printf("unable to open \"data\" ");
        close();
    }

    fseek(pfile, 0, SEEK_END);
    endf = ftell(pfile);
    rewind(pfile);
    int i=0;
   do{

    while (ftell(pfile) != existe && ftell(pfile) != exist2) {
        fread(&data2, sizeof(data2), 1, pfile);
        fwrite(&data2, sizeof(data2), 1, p2file);
    }
    
    switch (choice)
    {
    case 1 :{
        fread(&data2, sizeof(data2), 1, pfile);
        data2.n_tele = data_;
        fwrite(&data2, sizeof(data2), 1, p2file);
       
       
    }
        break;
    case 2 :{
       
        fread(&data2, sizeof(data2), 1, pfile);
        strcpy(data2.adress, data);
        fwrite(&data2, sizeof(data2), 1, p2file);
            
        }
        break;
    case 3 :{
        fread(&data2, sizeof(data2), 1, pfile);
        data2.mony = data2.mony + data_;
        fwrite(&data2, sizeof(data2), 1, p2file);
         printf("\n\n Deposit completed successfully :) ");
    }
        break;
    case 4 :{
        
        fread(&data2, sizeof(data2), 1, pfile);
        if (data_ > data2.mony -20 ) {
            printf("\n Error in the success of the operation :( ");
            printf("\n    You don't have much money");
            fclose(pfile);
            fclose(p2file);
            remove("copy.bin");
            close();
        }
        else {
            data2.mony = data2.mony - data_;
            fwrite(&data2, sizeof(data2), 1, p2file);
            printf("\n\n  Withdrawal completed successfully  :) ");
        }
    }
        break;
    case 5 :{
        if(ftell(pfile)==existe){
            fread(&data2, sizeof(data2), 1, pfile);
            if (data_ > data2.mony -20 ) {
                printf("\n Error in the success of the operation :( ");
                printf("\n    You don't have much money");
                fclose(pfile);
                fclose(p2file);
                remove("copy.bin");
                close();
            }
            else {
                data2.mony = data2.mony - data_;
                fwrite(&data2, sizeof(data2), 1, p2file);
            }
        }
        else{
            fread(&data2, sizeof(data2), 1, pfile);
            data2.mony = data2.mony + data_;
            fwrite(&data2, sizeof(data2), 1, p2file);
        }
        if(i==1){
            printf("\n\n   Sending completed successfully :) ");
        }
    }
        break;
    default:close();
        break;
    }
    i++ ; 
   }while(choice == 5 && i<2) ; 
    while (ftell(pfile) != endf) {
        fread(&data2, sizeof(data2), 1, pfile);
        fwrite(&data2, sizeof(data2), 1, p2file);
    }

    fclose(pfile);
    fclose(p2file);
    remove("data.bin");
    rename("copy.bin", "data.bin");
    close();
}
void transaction() {
    int choice;
    char ccp[11];
    int existe,mmony, send_existe;
    printf("\n\n 1- deposit ");
    printf("\n 2- withdraw");
    printf("\n 3- Send");
    printf("\n\n  ** Please select a business process : ");
    fscanf(stdin, "%d", &choice);
    getchar();
    sleep(1);
    system("cls");
    system("color 5");
    printf("\n\n *- Enter your CCP : ");
    fgets(ccp,11, stdin);
    printf("\n loading ");
    for(int i=0;i<3;i++){
        dly(100);
        printf(".");
    }
    printf("\n");
    existe = existing_acount(ccp);
    if (existe != -1) {
        switch (choice)
        {
        case 1: {
            printf("\n *- Enter the amount you want to deposit:$ ");
            fscanf(stdin, "%d", &mmony);
            copy_file(3, NULL,mmony,existe,-1);
        }
              break;
        case 2: {
            printf("\n *- Enter the amount you want to withdraw:$ ");
            fscanf(stdin, "%d", &mmony);
            copy_file(4, NULL, mmony, existe,-1);
        }
            break;
        case 3: {
            getchar();
            printf("\n *- Enter the CCP code you want to send money to : ");
            fgets(ccp, 11, stdin);
            send_existe = existing_acount(ccp);
            if (send_existe == -1) {
                printf("\n This account does not existe ");
                close();
            }
            else {
                printf("\n *- Enter the amount you want to Send:$ ");
                fscanf(stdin, "%d", &mmony);
                copy_file(5, NULL, mmony, existe,send_existe);
                
            }
        }
            break;
        default: close();
            break;
        }
    }
    else {
        printf("\n This account does not existe ");
        close();
    }
}
void close() {
    bool answer;
    printf("   \n\n Enter {1} to return to the menu  and  0 to exit : ");
    scanf("%d", &answer);
    if (answer == true)
    {
        menu();
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}
void removing_existing_account(){
    char ccp[11];
    int existe; 
    printf("\n\n  *- Enter your CCP : ");
    fgets(ccp,11, stdin);
    existe = existing_acount(ccp);
    printf("\n loading ");
    for(int i=0;i<3;i++){
        dly(100);
        printf(".");
    }
    if(existe==-1){
        printf("\n Tise acount does not existe ");
        close();
    }
    else{
        FILE *pfile=NULL ;
        FILE *pfile2 =NULL ; 
        info data ; 
        pfile=fopen("data.bin","rb");
        pfile2=fopen("copy.bin","wb");
        if(!pfile && !pfile2 ){
            printf("\n unable to open \"data file \" ");
            close();
        }
        fseek(pfile,0,SEEK_END);
        int endf = ftell(pfile);
        rewind(pfile) ;
        while(ftell(pfile) != endf){
            if(ftell(pfile)!=existe){
                fread(&data,sizeof(data),1,pfile);
                fwrite(&data,sizeof(data),1,pfile2);
            }
            else{
                fseek(pfile,sizeof(data),SEEK_CUR);
                printf("\n  Account removed successfully  ");
            }
        }
    
    fclose(pfile);
    fclose(pfile2);
    remove("data.bin");
    rename("copy.bin", "data.bin");
    close(); 
    }
}
void View_customer_list(){
    info data ; 
    FILE *pfile =NULL ; 
    int endf ;
    pfile=fopen("data.bin","rb");
    if(!pfile){
        printf("unable to open data file ");
        close();
    }
    fseek(pfile,0,SEEK_END);
    endf=ftell(pfile);
    rewind(pfile); 
    system("cls");
    printf("\n*********************************Book List*****************************");
    printf("\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2    ACCOUNT_n       NAME        NIN        PHONE        ADRESS    \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    if(ftell(pfile)==endf){
        printf("\n No customers available ");
        close();
    }
    else{
        int j=4 ; 
        while(ftell(pfile)!=endf){
            fread(&data,sizeof(data),1,pfile);
            gotoxy(13,j);
			printf("%d",data.n_acount);
			gotoxy(26,j);
			printf("%s",data.first_name);
			gotoxy(38,j);
			printf("%d",data.NIN);
			gotoxy(51,j);
			printf("%d",data.n_tele);
			gotoxy(63,j);
			printf("%s",data.adress );
			j++;
        }
        gotoxy(1,70);
        close();
    }
    

}
void menu(){
    system("cls");
    system("color 9");
	int a;
	printf("\n\n          \xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome to Lotfi \"BANK management\" \xB2\xB2\xB2\xB2\xB2\xB2\xB2 \n");
	printf("\n\n\n     * Create new acount            {1} \n");
        printf("\n     * Update information           {2} \n");
        printf("\n     * For transaction              {3} \n");
        printf("\n     * View customers list          {4} \n");
        printf("\n     * Removing existing account    {5} \n");
        printf("\n     * view account information     {6} \n");
        printf("\n     * Exit                         {7} \n");
	printf("\n\n\n        Enter your choice: ");
	scanf("%d", &a);
	fgetc(stdin); 
	system("cls"); 
	switch (a)
	{
	case 1: create_new_acount();
		break;
	case 2: update_info();
		break;
	case 3: transaction();
		break;
	case 4:View_customer_list();
		break;
	case 5: removing_existing_account();
		break;
    case 6 : view_info() ; 
        break ;
	case 7: exit(-1); 
		break;
	default:
		break;
	}
}
void view_info(){
    FILE *pfile =NULL ; 
    int exist ; 
    info data ; 
    char ccp[11];
    printf("\n\n *- Enter your CCP : ");
    fgets(ccp,11, stdin);
    printf("\n loading ");
    for(int i=0;i<3;i++){
        dly(100);
        printf(".");
    }
    system("cls");
    system("color 4");
    exist = existing_acount(ccp);
    if(exist ==-1){
        printf("\n Tise acount does not existe ");
        close();
    }else{
        pfile = fopen("data.bin","rb"); 
        if(!pfile){
             printf("unable to open \"data\" ");
            close();
        }  
        while(ftell(pfile)!=exist){
            fread(&data,sizeof(data),1,pfile);
        }
        fread(&data,sizeof(data),1,pfile);
        printf("\n First name : %s \n Family name : %s ",data.first_name,data.family_name);
        printf("\n Date of birth : %s \n Adress : %s ",data.date_birth,data.adress);
        printf("\n National Identification Number : %d \n Phone number %d ",data.NIN,data.n_tele);
        printf("\n\n Bank balance : %d \n\n account number : %d ",data.mony,data.n_acount) ; 
        close();
    }
}
void check_password(){
    char pass[10];
    char dj[]="PASSWORD PROTECTED";
    system("cls");
    system("color 5 ");
    for(int i =0;i<12;i++){
        dly(60);
        printf(" * ");
    }
     for(int i =0;i<19;i++){
        dly(70);
        printf("%c",dj[i]);
    }
    for(int i =0;i<12;i++){
        dly(60);
        printf(" * ");
    }
    gotoxy(20,7);
    int i=0;
    char ch ;
    printf("Enter Password: ");
    while(ch!=13){
        ch=getch();
        if(ch != 13 && ch != 8 ){
            pass[i]=ch;
            putchar('*');
            i++;
        }
    }
    pass[i]='\0';
    if(strcmp(pass,password)==0){
        printf("\n\n     Password match :) ");
	    gotoxy(17,10);
	    printf("Press any key to countinue.....");
	    getch();
        menu();
    }
    else{
    gotoxy(15,16);
	printf("\aWarning!! Incorrect Password");
	getch();
	 check_password();
    }
}
int main(){
   check_password();
    return 0 ; 
}