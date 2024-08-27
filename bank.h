#ifndef BANK_MANAGEMENT
#define BANK_MANAGEMENT
char password[10]="LOTfi2002";
typedef struct info info; 
struct info {
	char CCP[11],
		first_name[15],
		family_name[15],
		date_birth[11],
		adress[60];
		
	unsigned int NIN, mony, n_tele,n_acount;
};
void view_info();
void create_new_acount();
void menu();
int existing_acount(char* nin);
bool date_(char* data);
void View_customer_list();
void update_info();
void copy_file(int choice,  char* data, int data_,int existe,int exist2);
void close();
void transaction();
int existing_acount1(unsigned int nin);
void dly(unsigned int mili);
void check_password();
#endif