
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define CHECK 1

struct user_details{
    int id;
    int account_no;
    char *account_name[40];
    char *address[50];
    int balance;
    char *email[50];
    char *mobile[11];
    char *pin[16];
    char status[10];
};
struct Last_Account{
    int id, account_no;
};
void title(char* text){

    printf("\033[1;92m");
    printf("%s",text);
    printf("\033[0m");
}
void warn(char* text){
    printf("\033[1;31m");
    printf("%s",text);
    printf("\033[0m");
}
void clean(){
    system("cls");
    printf("\n                     ***************************************************\n");
    printf("                     ***************************************************\n");
    printf("                     **********                          ***************\n");
    printf("                     **********");
    printf("\033[1;37m"); // Set text color to blue (escape sequence)
    printf("       Banking System");
    printf("\033[0m"); // Reset text color (escape sequence)
    printf("     ***************\n                     **********                          ***************\n");
    printf("                     ***************************************************\n");
    printf("                     ***************************************************\n\n");
}
void main_menu();
int home();
struct user_details deposit();
struct user_details withdraw();
struct user_details transfer();
void balance();
void myaccount();
void transition();
void admin_panel();
struct user_details one_to_one(struct user_details my_details, struct user_details another_details);

const char* get_line();
struct Last_Account get_last_account();
int count_line();
int verifyEmail(const char* email);
int verifyPhoneNumber(const char* phoneNumber);
char* getCurrentDate();
void transition_add(int acc_no, int to_acc, int amount, const char* type);
int main(){
    clean();
    char* currentDate = getCurrentDate();
    printf("Data : %s\n",currentDate);
    main_menu();
    return 0;
}

struct Last_Account get_last_account(){
    FILE* account_list;
    account_list=fopen("account_list.txt","r");
    int line_no = count_line();
    char line[200];
    int count = 0;
    if(account_list==NULL){
        warn("No account is here\n");
    }
    struct Last_Account last_account;
    last_account.id = 0;
    last_account.account_no = 1000;
    while(fgets(line, sizeof(line), account_list)){
        char *id = strtok(line,"|");
        char *account_no = strtok(NULL,"|");
        count++;
//        printf("%d %d\n",count,line_no);
        if(count == line_no){
            last_account.id = (int) atoi(id);
            last_account.account_no = (int) atoi(account_no);
            return  last_account;
        }
    }
    return last_account;
}
const char* get_line(int line_no){
    char line[200];
    FILE* account_list;
    account_list=fopen("account_list.txt","r");

    if(account_list==NULL){
        warn("No account is here\n");
    }

    while(fgets(line, sizeof(line), account_list)){
        char *id = strtok(line,"|");
        if((int) atoi(id) == line_no){
            return (int) atoi(id);
        }
    }
    return 0;
}

int count_line(){
    int count = 0;
    char character;
    FILE* account_list;
    account_list=fopen("account_list.txt","r");
    if(account_list == NULL){
        warn("No account is here!!!\n");
        return 0;
    }else{
        while ((character = getc(account_list)) != EOF) {
            if (character == '\n' || character == EOF) {
                count++;
            }
        }
        return count;
    }
}

void create_account()
{
    char account_name[40], address[50], email[50], mobile[11], temp_mobile[11], pin[16], com_pin[16], status[10], temp_mail[20];
    int account_no, balance;
    title("\n\nEnter your information to Create Account\n");
    printf("Account Name : ");
    getchar();
    gets(account_name);
    while(CHECK){
        if(strlen(account_name)>=3){
            break;
        }else{
            warn("Account Name must have 3 letter. Try again\n");
            printf("Account Name : ");
            gets(account_name);
        }
    }
    printf("Address : ");
    gets(address);
    while(CHECK){
        if(strlen(account_name)>=3){
            break;
        }else{
            warn("Enter a valid Address. Try again\n");
            printf("Address : ");
            gets(address);
        }
    }
    printf("Email : ");
    //gets(email);
    scanf("%s",&email);
    while(CHECK){
        if(verifyEmail(email)){
            break;
        }else{
            warn("Email is not Valid. Try again\n");
            printf("Email : ");
//            gets(email);
              scanf("%s",&email);
        }
    }
    strcpy(temp_mail,email);
    printf("Mobile Number : ");
//    getchar();
//    gets(mobile);
    scanf("%s",&mobile);
    while(CHECK){
        if(verifyPhoneNumber(mobile)){
            break;
        }else{
            warn("Mobile Number is not Valid. Try again\n");
            printf("Mobile Number : ");
            scanf("%s",&mobile);
        }
    }
    printf("Initial Balance : ");
    scanf("%d",&balance);
    while(CHECK){
        if(balance>=100){
            break;
        }else{
            warn("Minimum Initial Balance 100tk. Try again\n");
            printf("Initial Balance : ");
            scanf("%d",&balance);
        }
    }

    int i = 0;
    char ch;
    printf("PIN : ");
    while(1){
        ch = getch();
         if(ch == 13 || ch == 9 ){
            pin[i] = '\0';
            printf("\n");
            break;
         }else if(ch == 8){
            if(i > 0){
                i--;
                printf("\b \b");
            }
         }else{
            pin[i++] = ch;
            printf("* \b");
         }
    }
    getchar();

//    printf("PIN : ");
//
//
//    getchar();
//    gets(pin);
    while(CHECK){
        if(strlen(pin)>=4){
            break;
        }else{
            warn("Minimum 4 Digit Input. Try again\n");
//            memset(pin, '\0', sizeof(pin));
            int i = 0;
            printf("PIN : ");
            while(1){
                ch = getch();
                 if(ch == 13 || ch == 9 ){
                    pin[i] = '\0';
                    printf("\n");
                    break;
                 }else if(ch == 8){
                    if(i > 0){
                        i--;
                        printf("\b \b");
                    }
                 }else{
                    pin[i++] = ch;
                    printf("* \b");
                 }
            }
//            printf("PIN : ");
//            gets(pin);

        }
    }
//    printf("\nConfirm PIN : ");
//    gets(com_pin);
    i = 0;
    printf("Confirm PIN : ");
    while(CHECK){
        ch = getch();
         if(ch == 13 || ch == 9 ){
            com_pin[i] = '\0';
            printf("\n");
            break;
         }else if(ch == 8){
            if(i > 0){
                i--;
                printf("\b \b");
            }
         }else{
            com_pin[i++] = ch;
            printf("* \b");
         }
    }
    if(strcmp(pin,com_pin))
    {
        warn("\nYour confirm PIN is not same! Try again...\n");
        while(1)
        {
//            printf("Confirm PIN : ");
//            gets(com_pin);
            i = 0;
            printf("Confirm PIN : ");
            while(1){
                ch = getch();
                 if(ch == 13 || ch == 9 ){
                    com_pin[i] = '\0';
                    printf("\n");
                    break;
                 }else if(ch == 8){
                    if(i > 0){
                        i--;
                        printf("\b \b");
                    }
                 }else{
                    com_pin[i++] = ch;
                    printf("* \b");
                 }
            }
            if(strcmp(pin,com_pin))
            {
                warn("You are wrong. Try again...\n");
            }
            else
            {
                break;
            }
        }
    }
    strcpy(temp_mobile, mobile);
    strcpy(email,temp_mail);

    struct Last_Account last_acc= get_last_account();
    FILE* account_list;
    account_list = fopen("account_list.txt","a");
    if(account_list == NULL){
        warn("Oh, No File is here!!!\n");
    }else{
        fprintf(account_list,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",last_acc.id+1,last_acc.account_no+1, account_name,address,balance,email,temp_mobile,pin,"Pending");
        clean();
        title("You successfully registered!!!\nAccount No is : ");
        printf("\033[1;92m");
        printf("%d\n",last_acc.account_no+1);
        printf("\033[0m");
        warn("Wait for activate Account By Admin. And Remember your Account No\n");
        title("Thanks for join us.\n");
    }

    fclose(account_list);
    exit(0);
}
int verifyEmail(const char* email) {
    int atCount = 0;
    int dotCount = 0;
    int length = strlen(email);

    // Check for empty email
    if (length == 0)
        return 0;

    // Check for '@' and '.' characters
    for (int i = 0; i < length; i++) {
        if (email[i] == '@')
            atCount++;
        else if (email[i] == '.')
            dotCount++;
    }

    // Check for exactly one '@' and at least one '.'
    if (atCount != 1 || dotCount < 1)
        return 0;

    // Check if the email starts or ends with '@' or '.'
    if (email[0] == '@' || email[0] == '.' || email[length - 1] == '@' || email[length - 1] == '.')
        return 0;

    // Check if the '@' character is followed by a '.'
    for (int i = 0; i < length - 1; i++) {
        if (email[i] == '@' && email[i + 1] == '.')
            return 0;
    }

    return 1;  // Email is valid
}

int verifyPhoneNumber(const char* phoneNumber) {
    int length = strlen(phoneNumber);

    // Check for a 11-digit length
    if (length != 11)
        return 0;

    // Check if the phone number starts with "01"
    if (strncmp(phoneNumber, "01", 2) != 0)
        return 0;

    // Check if all characters are digits
    for (int i = 2; i < length; i++) {
        if (phoneNumber[i] < '0' || phoneNumber[i] > '9')
            return false;
    }

    return 1;  // Phone number is valid
}

void main_menu(){
    int option;
    while(1){
        title("***Home Page***\n");
        printf("Choose any option from below : \n");
        printf("1. Login\n");
        printf("2. Sign Up\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n");
        printf("Enter a option : ");
        scanf("%d",&option);
        switch(option){
        case 1:
            clean();
            login();
            break;
        case 2:
            clean();
            create_account();
            break;
        case 3:
            clean();
            admin_login();
            break;
        case 4:
            clean();
            title("Thank you for using our banking system.\n");
            exit(0);
            break;
        default:
            clean();
            exit(0);
            break;
        }
    }
}
void login()
{

    char login_pin[16];
    int login_account_no;
    title("Enter your information to login\n");
    while(1)
    {
        printf("\nAccount No : ");
        scanf("%d",&login_account_no);
        printf("PIN : ");
        getchar();
        gets(login_pin);

        FILE* account_list;
        account_list = fopen("account_list.txt","r");
        if(account_list == NULL){
            printf("Oh, No File is here!!!\n");
        }
        char line[200];

        while(fgets(line, sizeof(line), account_list)){
            char *account_name, *address, *email, *mobile, *pin, *status;
            int id, account_no, balance;
            id = strtok(line,"|");
            account_no = strtok(NULL,"|");
            account_name = strtok(NULL,"|");
            address = strtok(NULL,"|");
            balance = strtok(NULL,"|");
            email = strtok(NULL,"|");
            mobile = strtok(NULL,"|");
            pin = strtok(NULL,"|");
            status = strtok(NULL,"|");
            if((login_account_no== atoi(account_no))  && (strcmp(pin,login_pin)== 0) && ((strcmp(status,"Pending")==0) ||  (strcmp(status,"Deactivate")==0))){
                clean();
                printf("\033[1;31m");
                printf("Your account state is : %s!\n",status);
                printf("\033[0m");
                return;
            }
            if((login_account_no== atoi(account_no))  && (strcmp(pin,login_pin)== 0))
            {
                struct user_details current_user;
                current_user.id = atoi(id);
                current_user.account_no = atoi(account_no);
                strcpy(current_user.account_name,account_name);
                strcpy(current_user.address,address);
                current_user.balance = atoi(balance);
                strcpy(current_user.email,email);
                strcpy(current_user.mobile,mobile);
                strcpy(current_user.pin,pin);
                strcpy(current_user.status,status);
                clean();
                title("You successfully Login!!!\n");
                fclose(account_list);
                home(current_user);
                return;
            }
        }
        fclose(account_list);
        warn("Your username or password is wrong!!!\n");
        printf("\n\nTry again");
    }
    printf("*****************************************\n\n");
}
int home(struct user_details my_details){
    int option;
    printf("\nWelcome %s\n",my_details.account_name);
    while(1){
        title("\n***Main MENU***\n");
        printf("1. Deposite Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Transfer Money\n");
        printf("4. Balance Inquire\n");
        printf("5. My Account\n");
        printf("6. Transition Details\n");
        printf("7. Logout\n");
        printf("Chose your option : ");
        scanf("%d",&option);
        clean();
        switch(option){
        case 1 :
            my_details = deposit(my_details);
            break;
        case 2:
            my_details = withdraw(my_details);
            break;
        case 3:
            my_details = transfer(my_details);
            break;
        case 4:
            balance(my_details);
            break;
        case 5:
            myaccount(my_details);
            break;
        case 6:
            transition(my_details);
            break;
        case 7:
            return 0;
        default :
            warn("Invalid option. Please try again.\n");
        }
    }
}

struct user_details deposit(struct user_details my_details){
    int deposit_amount;
    printf("Enter Deposit Amount : ");
    scanf("%d",&deposit_amount);
    clean();
    while(1){
        if(deposit_amount < 100){
            printf("Deposit Minimum Amount 100tk.\n");
            printf("Enter Deposit Amount : ");
            scanf("%d",&deposit_amount);
        }else{
            break;
        }
    }
    FILE *file = fopen("account_list.txt", "r+");
    if (file == NULL) {
        warn("Failed to open the file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        warn("Failed to open the temporary file.\n");
        fclose(file);
        return;
    }

    char line[200];
    int currentLine = 1;
    while (fgets(line, sizeof(line), file)) {
        if (currentLine == my_details.id) {
            my_details.balance = my_details.balance+deposit_amount;
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",my_details.id, my_details.account_no, my_details.account_name, my_details.address, my_details.balance,my_details.email,my_details.mobile,my_details.pin,my_details.status);
        } else {
            fprintf(tempFile, "%s", line);
        }
        currentLine++;
    }
    fclose(file);
    fclose(tempFile);
    remove("account_list.txt");
    rename("temp.txt", "account_list.txt");
    clean();
    title("Deposit Successfull.\n");

    //transition data
    transition_add(my_details.account_no, 000, deposit_amount,"Deposit");

    title("Your New Balance is : ");
    printf("%d\n",my_details.balance);
    return my_details;
}

struct user_details withdraw(struct user_details my_details){
    int withdraw_amount;
    printf("Enter Withdraw Amount : ");
    scanf("%d",&withdraw_amount);
    clean();
    int checkAgain = 1;
    while(checkAgain){
        while(1){
            if(withdraw_amount < 100){
                warn("Withdraw Minimum Amount 100tk.\n");
                printf("Enter amount to transfer : ");
                scanf("%d",&withdraw_amount);
            }else{
                checkAgain = 0;
                break;
            }
        }
        while(1){
            if(withdraw_amount > my_details.balance){
                warn("Insufficient Balance\n");
                printf("Enter Withdraw Amount : ");
                scanf("%d",&withdraw_amount);
                checkAgain = 1;
            }else{
                break;
            }
        }
    }

    FILE *file = fopen("account_list.txt", "r+");
    if (file == NULL) {
        warn("Failed to open the file.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        warn("Failed to open the temporary file.\n");
        fclose(file);
        return;
    }
    char line[200];
    int currentLine = 1;
    while (fgets(line, sizeof(line), file)) {
        if (currentLine == my_details.id) {
            my_details.balance = my_details.balance-withdraw_amount;
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",my_details.id, my_details.account_no, my_details.account_name, my_details.address, my_details.balance,my_details.email,my_details.mobile,my_details.pin,my_details.status);
        } else {
            fprintf(tempFile,"%s", line);
        }
        currentLine++;
    }
    fclose(file);
    fclose(tempFile);
    remove("account_list.txt");
    rename("temp.txt", "account_list.txt");
    clean();
    title("Withdraw Successful.\n");
    //transition data
    transition_add(my_details.account_no, 000, withdraw_amount,"Withdraw");
    title("Your New Balance is : ");
    printf("%d\n",my_details.balance);
    return my_details;
}

struct user_details transfer(struct user_details my_details){
    int transfer_account_no;
    int search_result = 0;
    struct user_details another_user;
    printf("Enter Account No to search : ");
    scanf("%d",&transfer_account_no);
    char line[200];
    FILE* account_list;
    account_list=fopen("account_list.txt","r");
    if(account_list==NULL){
        warn("No account is here\n");
    }

    while(fgets(line, sizeof(line), account_list)){
        char *account_name, *address, *email, *mobile, *pin, *status;
        int id, account_no, balance;
        id = strtok(line,"|");
        account_no = strtok(NULL,"|");
        account_name = strtok(NULL,"|");
        address = strtok(NULL,"|");
        balance = strtok(NULL,"|");
        email = strtok(NULL,"|");
        mobile = strtok(NULL,"|");
        pin = strtok(NULL,"|");
        status = strtok(NULL,"|");
        if(transfer_account_no == atoi(account_no)){
            search_result = 1;
            another_user.id = atoi(id);
            another_user.account_no = atoi(account_no);
            strcpy(another_user.account_name,account_name);
            strcpy(another_user.address,address);
            another_user.balance = atoi(balance);
            strcpy(another_user.email,email);
            strcpy(another_user.mobile,mobile);
            strcpy(another_user.pin,pin);
            strcpy(another_user.status,status);
        }
    }
    fclose(account_list);
    if(search_result){
        int oparation;
        printf("Account Name is : %s\n",another_user.account_name);
        printf("Do you want continue to Transfer?\n");
        printf("1. Yes.\n2. No.\n");
        printf("Enter choose : ");
        scanf("%d",&oparation);
        switch(oparation){
            case 1:
                clean();
                return one_to_one(my_details,another_user);
                break;
            case 2:
                clean();
                return;
            default:
                clean();
                return;
        }

    }else{
        clean();
        warn("No Account");
    }

}

struct user_details one_to_one(struct user_details my_details, struct user_details another_details){
    int amount_to_transfer;
    char line[200];
    int currentLine = 1;

    printf("Enter amount to transfer : ");
    scanf("%d",&amount_to_transfer);
    clean();
    int checkAgain = 1;
    while(checkAgain){
        while(1){
            if(amount_to_transfer < 100){
                warn("Transfar Minimum Amount 100tk.\n");
                printf("Enter amount to transfer : ");
                scanf("%d",&amount_to_transfer);
            }else{
                checkAgain = 0;
                break;
            }
        }
        while(1){
            if(amount_to_transfer > my_details.balance){
                warn("Insufficient Balance\n");
                printf("Enter amount to transfer : ");
                scanf("%d",&amount_to_transfer);
                checkAgain = 1;
            }else{
                break;
            }
        }
    }
    FILE *file = fopen("account_list.txt", "r+");
    if (file == NULL) {
        warn("Failed to open the file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        warn("Failed to open the temporary file.\n");
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        if (currentLine == my_details.id) {
            my_details.balance = my_details.balance-amount_to_transfer;
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",my_details.id, my_details.account_no, my_details.account_name, my_details.address, my_details.balance,my_details.email,my_details.mobile,my_details.pin,my_details.status);
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentLine++;
    }

    fclose(file);
    fclose(tempFile);
    remove("account_list.txt");
    rename("temp.txt", "account_list.txt");



    file = fopen("account_list.txt", "r+");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        warn("Failed to open the temporary file.\n");
        return;
    }
    currentLine = 1;
    while (fgets(line, sizeof(line), file)) {
        if (currentLine == another_details.id) {
            another_details.balance = another_details.balance+amount_to_transfer;
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",another_details.id, another_details.account_no, another_details.account_name, another_details.address, another_details.balance,another_details.email,another_details.mobile,another_details.pin,another_details.status);
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentLine++;
    }

    fclose(file);
    fclose(tempFile);
    remove("account_list.txt");
    rename("temp.txt", "account_list.txt");
    clean();

    title("Transfar Successful.\n");


    //transition data
    transition_add(my_details.account_no, another_details.account_no, amount_to_transfer,"Transfer");

    title("Your New Balance is : ");
    printf("%d\n",my_details.balance);
    return my_details;

};

void balance(struct user_details my_details){
    title("Your Current Balance : ");
    printf("%d\n",my_details.balance);
    warn("Enter any key for go to Home.\n");
    getchar();
    getchar();
    clean();
    return;
}

void myaccount(struct user_details my_details){
    title("***Account Details***\n");
    printf("Account Name : %s\n",my_details.account_name);
    printf("Account No : %d\n",my_details.account_no);
    printf("Address : %s\n",my_details.address);
    printf("Email : %s\n",my_details.email);
    printf("Mobile : %s\n",my_details.mobile);
    printf("Enter any key for go to Home.\n");
    getchar();
    getchar();
    clean();
    return;
}

void transition(struct user_details my_details){
    FILE* transition_list;
    transition_list = fopen("transition.txt","r");
    if(transition_list == NULL){
        printf("Oh, No File is here!!!\n");
    }
    char line[200];
    title("***Account Transition***\n");
    printf("Date \t\t To \t  From \t Amount \t Type\n");
    while(fgets(line, sizeof(line), transition_list)){
        char *date, *acc_to, *acc_from, *amount, *type;
        date = strtok(line,"|");
        acc_to = strtok(NULL,"|");
        acc_from = strtok(NULL,"|");
        amount = strtok(NULL,"|");
        type = strtok(NULL,"|");
        if(atoi(acc_to) == my_details.account_no){
           printf("%s \t %s \t %s \t %s \t %s\n\n",date, acc_to, acc_from, amount, type);
        }
    }
    fclose(transition_list);
}
void admin_login(){
    int pin;
    printf("Enter PIN : ");
    scanf("%d",&pin);
    if(pin == 1234){
        clean();
        admin_panel();
    }else{
        printf("Wrong PIN.\n");
        printf("Enter any key to exit.");
        getchar();
        getchar();
        clean();
    }
}
void admin_panel(){
    int option;
    while(1){

        title("Admin Menu \n");
        printf("Choose Your Option : \n");
        printf("1. All Account List\n");
        printf("2. Pending List\n");
        printf("3. Active List\n");
        printf("4. Active/Deactivate Account\n");
        printf("5. Exit\n");
        printf("Enter your option : ");
        scanf("%d",&option);
        switch(option){
            case 1:
                clean();
                all_account();
                break;
            case 2:
                clean();
                pending_account();
                break;
            case 3:
                clean();
                active_account();
                break;
            case 4:
                clean();
                active_deactive();
                break;
            default:
                clean();
                return;

        }
    }

}
void all_account(){
    title("***All Account List***\n\n");
    FILE* account_list;
    account_list = fopen("account_list.txt","r");
    if(account_list == NULL){
        printf("Oh, No File is here!!!\n");
    }
    char line[200];
    printf("ID \t Acc. No \t  Name \t\t Address \t Balance \t Email \t\t\t Mobile \t Status\n\n");
    while(fgets(line, sizeof(line), account_list)){
        char *account_name, *address, *email, *mobile, *pin, *status;
        int id, account_no, balance;
        id = strtok(line,"|");
        account_no = strtok(NULL,"|");
        account_name = strtok(NULL,"|");
        address = strtok(NULL,"|");
        balance = strtok(NULL,"|");
        email = strtok(NULL,"|");
        mobile = strtok(NULL,"|");
        pin = strtok(NULL,"|");
        status = strtok(NULL,"|");
        printf("%d \t %d \t\t %s \t\t %s \t\t %d \t\t %s \t %s \t %s\n\n",atoi(id),atoi(account_no),account_name,address,atoi(balance),email,mobile,status);


    }
    fclose(account_list);
}
void pending_account(){
    title("***All Pending Account List***\n\n");
    FILE* account_list;
    account_list = fopen("account_list.txt","r");
    if(account_list == NULL){
        printf("Oh, No File is here!!!\n");
    }
    char line[200];
    printf("ID \t Acc. No \t  Name \t\t Address \t Balance \t Email \t\t\t Mobile \t Status\n");
    while(fgets(line, sizeof(line), account_list)){
        char *account_name, *address, *email, *mobile, *pin, *status;
        int id, account_no, balance;
        id = strtok(line,"|");
        account_no = strtok(NULL,"|");
        account_name = strtok(NULL,"|");
        address = strtok(NULL,"|");
        balance = strtok(NULL,"|");
        email = strtok(NULL,"|");
        mobile = strtok(NULL,"|");
        pin = strtok(NULL,"|");
        status = strtok(NULL,"|");
        if(strcmp(status,"Pending")==0){
            printf("%d \t %d \t\t %s \t\t %s \t\t %d \t\t %s \t %s \t %s\n\n",atoi(id),atoi(account_no),account_name,address,atoi(balance),email,mobile,status);
        }

    }
    fclose(account_list);
}
void active_account(){
    title("***All Active Account List***\n\n");
    FILE* account_list;
    account_list = fopen("account_list.txt","r");
    if(account_list == NULL){
        printf("Oh, No File is here!!!\n");
    }
    char line[200];
    printf("ID \t Acc. No \t  Name \t\t Address \t Balance \t Email \t\t\t Mobile \t Status\n");
    while(fgets(line, sizeof(line), account_list)){
        char *account_name, *address, *email, *mobile, *pin, *status;
        int id, account_no, balance;
        id = strtok(line,"|");
        account_no = strtok(NULL,"|");
        account_name = strtok(NULL,"|");
        address = strtok(NULL,"|");
        balance = strtok(NULL,"|");
        email = strtok(NULL,"|");
        mobile = strtok(NULL,"|");
        pin = strtok(NULL,"|");
        status = strtok(NULL,"|");
        if(strcmp(status,"Active")==0){
            printf("%d \t %d \t\t %s \t\t %s \t\t %d \t\t %s \t %s \t %s\n\n",atoi(id),atoi(account_no),account_name,address,atoi(balance),email,mobile,status);
        }

    }
    fclose(account_list);
}
void active_deactive(){
    int option;
    while(1){
        printf("Choose your option : \n");
        printf("1. Deactiavte Account.\n");
        printf("2. Active Account.\n");
        printf("3. Exit.\n");
        printf("Enter your option : ");
        scanf("%d",&option);

        switch(option){
        case 1:
            clean();
            deactivate();
            break;
        case 2:
            clean();
            active();
            break;
        default:
            clean();
            return;
        }
    }

}
void deactivate(){
    int acc_no;
    printf("Enter account no to deactivate : ");
    scanf("%d",&acc_no);

    char line[200];

    FILE *file = fopen("account_list.txt", "r+");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to open the temporary file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char *account_name, *address, *email, *mobile, *pin, *status;
        int id, account_no, balance;
        id = strtok(line,"|");
        account_no = strtok(NULL,"|");
        account_name = strtok(NULL,"|");
        address = strtok(NULL,"|");
        balance = strtok(NULL,"|");
        email = strtok(NULL,"|");
        mobile = strtok(NULL,"|");
        pin = strtok(NULL,"|");
        status = strtok(NULL,"|");
        if (acc_no == atoi(account_no) && (strcmp(status,"Pending")==0)) {
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",atoi(id), atoi(account_no), account_name, address, atoi(balance),email,mobile,pin,"Deactivate");
        } else if(acc_no == atoi(account_no) &&  (strcmp(status,"Deactivate")==0)) {
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",atoi(id), atoi(account_no), account_name, address, atoi(balance),email,mobile,pin,"Deactivate");
        } else if(acc_no == atoi(account_no) && (strcmp(status,"Active")==0)) {
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",atoi(id), atoi(account_no), account_name, address, atoi(balance),email,mobile,pin,"Deactivate");
        }else{
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",atoi(id), atoi(account_no), account_name, address, atoi(balance),email,mobile,pin,status);
        }

    }

    fclose(file);
    fclose(tempFile);
    remove("account_list.txt");
    rename("temp.txt", "account_list.txt");

    //clean();

    title("Deactivate Successful.\n");


}

void active(){
    int acc_no;
    printf("Enter account no to Active : ");
    scanf("%d",&acc_no);

    char line[200];

    FILE *file = fopen("account_list.txt", "r+");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to open the temporary file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char *account_name, *address, *email, *mobile, *pin, *status;
        int id, account_no, balance;
        id = strtok(line,"|");
        account_no = strtok(NULL,"|");
        account_name = strtok(NULL,"|");
        address = strtok(NULL,"|");
        balance = strtok(NULL,"|");
        email = strtok(NULL,"|");
        mobile = strtok(NULL,"|");
        pin = strtok(NULL,"|");
        status = strtok(NULL,"|");

        if (acc_no == atoi(account_no) && (strcmp(status,"Pending")==0)) {
            printf("ggkh\n");
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",atoi(id), atoi(account_no), account_name, address, atoi(balance),email,mobile,pin,"Active");
        } else if(acc_no == atoi(account_no) &&  (strcmp(status,"Deactivate")==0)) {
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",atoi(id), atoi(account_no), account_name, address, atoi(balance),email,mobile,pin,"Active");
        } else if(acc_no == atoi(account_no) && (strcmp(status,"Active")==0)) {
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",atoi(id), atoi(account_no), account_name, address, atoi(balance),email,mobile,pin,"Active");
        }else{
            fprintf(tempFile,"%d|%d|%s|%s|%d|%s|%s|%s|%s|\n",atoi(id), atoi(account_no), account_name, address, atoi(balance),email,mobile,pin,status);
        }
    }

    fclose(file);
    fclose(tempFile);

    rename("account_list.txt", "account_list2.txt");
    remove("account_list.txt");
    rename("temp.txt", "account_list.txt");
    rename("temp.txt", "account_list.txt");
    remove("temp.txt");
    clean();

    title("Active Successful.\n");


}

char* getCurrentDate() {
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);

    static char formattedDate[11];
    strftime(formattedDate, sizeof(formattedDate), "%d-%m-%Y", localTime);

    return formattedDate;
}

void transition_add(int acc_no, int to_acc, int amount, const char* type){
    FILE *transitionFile = fopen("transition.txt", "a");
    if (transitionFile == NULL) {
        printf("Failed to open the temporary file.\n");
        fclose(transitionFile);
        return;
    }
    fprintf(transitionFile,"%s|%d|%d|%d|%s\n",getCurrentDate(), acc_no, to_acc, amount, type);
    fclose(transitionFile);
}
