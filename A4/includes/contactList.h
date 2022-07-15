struct contact{
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
};
typedef struct contact contacts;

struct strings{
    char *firstName;
    char *lastName;
    char *companyName;
    char *email;
    unsigned long phoneNumber;
};
typedef struct strings strings;

int sort_lastName(const void *a,const void *b);
void readStrings(contacts *record,strings *info,int i,FILE *fptr);
int writeContact(FILE *fptr,contacts *record,int i);
int editContact(FILE *fptr,contacts *record,strings *info,int i,int maxContacts);
int deleteContact(FILE *fptr,contacts *record,strings *info,int i,int maxContacts);
