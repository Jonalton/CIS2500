struct contact{
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
};
typedef struct contact contacts;

void freeStrings(char *firstName, char *lastName, char *companyName,char *phoneNumber, char *email);
