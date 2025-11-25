#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int arr[100];//to store index

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria

    //addressbook epmty case
    if(addressBook -> contactCount == 0)
    {
        printf("\n------------------------------------\n");
        printf(" No contacts found in addres book!!");
        printf("\n------------------------------------\n");

        return;
    }

    Contact temp;//temp structure for swapping

    do
    {
        printf("\nSort by:\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email\n");
        printf("4. No sort\n");

        printf("Enter your choice: ");
        scanf("%d",&sortCriteria);

        switch(sortCriteria)
        {
            case 1://sort by name using bubble sort
            {
                for(int i=0 ; i<addressBook -> contactCount-1 ; i++)
                {
                    for(int j=0; j<addressBook -> contactCount-1-i ; j++)
                    {
                        if(strcmp(addressBook -> contacts[j].name , addressBook -> contacts[j+1].name) >0 )
                        {
                            temp = addressBook -> contacts[j];
                            addressBook -> contacts[j] = addressBook -> contacts[j+1];
                            addressBook -> contacts[j+1] = temp;
                        }
                    }
                }

                break;
            }

            case 2://sort by phone
            {
                for(int i=0 ; i<addressBook -> contactCount-1 ; i++)
                {
                    for(int j=0; j<addressBook -> contactCount-1-i ; j++)
                    {
                        if(strcmp(addressBook -> contacts[j].phone , addressBook -> contacts[j+1].phone) >0 )
                        {
                            temp = addressBook -> contacts[j];
                            addressBook -> contacts[j] = addressBook -> contacts[j+1];
                            addressBook -> contacts[j+1] = temp;
                        }
                    }
                }

                break;
            }

            case 3://sort by email
            {
                for(int i=0 ; i<addressBook -> contactCount-1 ; i++)
                {
                    for(int j=0; j<addressBook -> contactCount-1-i ; j++)
                    {
                        if(strcmp(addressBook -> contacts[j].email , addressBook -> contacts[j+1].email) >0 )
                        {
                            temp = addressBook -> contacts[j];
                            addressBook -> contacts[j] = addressBook -> contacts[j+1];
                            addressBook -> contacts[j+1] = temp;
                        }
                    }
                }

                break;
            }

            case 4://no sort
            {
                break;
            }

            default :
            {
                printf("Invalid choice. Please try again.\n");
                continue;//invalid case - need prompt message again
            }
        }
        break;//exit do while loop for valid occurance

    }while(1);

    //table format
    printf("\n----------------------------------------------------------------------------------\n");
    printf("|%34s%12s%34s|","","ADDRESS BOOK","");
    printf("\n----------------------------------------------------------------------------------\n");
    printf("| %-3s| %-20s| %-15s| %-35s|\n","No","Name","Phone","Email");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0;i<addressBook -> contactCount;i++)
    {
        printf("| %-3d| %-20.20s| %-15s| %-35.35s|\n",i+1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
    }
    printf("----------------------------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[50],phone[11],email[50];
    int valid,unique;

    //Name
    do
    {
        printf("Name: ");
        getchar();
        scanf("%[^\n]",name);

        //checking name valid or not
        valid = valid_name(name);
        if(!valid)
        printf("Invalid Name!\n");

    }while(!valid);
    //if success,copy to structure contact
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);

    //Phone
    do
    {
        printf("Ph_No: ");
        getchar();
        scanf("%[^\n]",phone);

        valid = valid_num(phone);
        unique = unique_num(phone,addressBook);

        if(!valid)
        {
            printf("Invalid phone number!\n");
        }
        if(!unique)
        {
            printf("Phone number already exists!\n");
        }
    }while(!valid || !unique);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    
    //Email
    do
    {   
        printf("Email: ");
        getchar();
        scanf("%[^\n]",email);

        valid = valid_email(email);
        unique = unique_email(email,addressBook);

        if(!valid)
        {
            printf("Invalid email!\n");
        }
        if(!unique)
        {
            printf("Email already exists!\n");
        }
    }while(!valid || !unique);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);

    addressBook -> contactCount++;//incrementing contact count
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    while(1)
    {
        printf("\nSearch by:\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email\n");
        printf("4. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char name[50],phone[11],mail[50];
        int flag = 0,count = 0;
        getchar();

        switch(choice)
        {
            case 1 :
            {
                printf("Enter name : ");
                scanf("%[^\n]",name);

                for(int i=0;i<addressBook -> contactCount ; i++)
                {
                    if(strstr(addressBook -> contacts[i].name,name) != NULL)
                    {
                        flag = 1;
                        printf("%d. %-25s\t%s\t%-35s\n",count+1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
                        arr[count++]=i;
                    }
                }
                if(flag==0)
                {
                    printf("Contact not found\n");
                    continue;
                }
                return count;
            }

            case 2:
            {
                printf("Enter phone no : ");
                scanf("%[^\n]",phone);

                for(int i=0;i<addressBook -> contactCount ; i++)
                {
                    if(strcmp(addressBook -> contacts[i].phone,phone) == 0 )
                    {
                        flag = 1;
                        printf("%d. %-20s\t%s\t%-35s\n",count+1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
                        arr[count++]=i;
                    }
                }

                if(flag==0)
                {
                    printf("Contact not found\n");
                    continue;
                }
                return count;
            }

            case 3:
            {
                printf("Enter email : ");
                scanf("%[^\n]",mail);

                for(int i=0;i<addressBook -> contactCount ; i++)
                {
                    if(strcmp(addressBook -> contacts[i].email,mail) == 0 )
                    {
                        flag = 1;
                        printf("%d. %-20s\t%s\t%-35s\n",count+1,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
                        arr[count++]=i;
                    }
                }

                if(flag==0)
                {
                    printf("Contact not found\n");
                    continue;
                }

                return count;
            }

            case 4:
            {
                return 0;
            }

            default :
            {
                printf("Invalid choice\n");
                continue;
            }
        }
    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int count = searchContact(addressBook);
    if(count ==  0)//exit case from search fun
    return;

    int ind;
    int i;
    if(count>1)//multiple search present case
    {
    start :
        printf("Enter index: ");
        scanf("%d",&ind);
        if(ind>count)
        {
            printf("Invalid option. Please try again.\n");
            goto start;
        }
        i = arr[ind-1];
        printf("%s\t\t%s\t\t%s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
    }
    else//single search case
    {
        i=arr[0];
    }
label :
    printf("\nEdit by :\n");
    printf("1. Name\n");
    printf("2. Phone No\n");
    printf("3. Email\n");
    printf("4. Exit\n");

    int choice;
    printf("Enter your choice : ");
    scanf("%d", &choice);

    char name[50];
    char phone[11];
    char mail[50];
    int valid,unique;
    switch(choice)
    {
        case 1:
            do
            {
                getchar();
                printf("Enter name:");
                scanf("%[^\n]",name);

                valid = valid_name(name);
                if(!valid)
                printf("Invalid Name!\n");
            }while(!valid);
            strcpy(addressBook->contacts[i].name,name);
            break;
        case 2:
            do
            {
                printf("Enter Ph_num: ");
                getchar();
                scanf("%[^\n]",phone);

                valid = valid_num(phone);
                unique = unique_num(phone,addressBook);
                if(!valid)
                printf("Invalid phone number!\n");
                if(!unique)
                printf("Phone number already exists!\n");
            } while (!valid || !unique);
            strcpy(addressBook->contacts[i].phone,phone);
            break;
        case 3:
            do
            {
                printf("Enter email id: ");
                getchar();
                scanf("%[^\n]",mail);

                valid = valid_email(mail);
                unique = unique_email(mail,addressBook);
                if(!valid)
                printf("Invalid email!\n");
                if(!unique)
                printf("Email already exists!\n");
            }while(!valid || !unique);
            strcpy(addressBook->contacts[i].email,mail);
            break;
        case 4:
            {
                return;//exit from edit fun
            }
        default :
            printf("Invalid choice\n");
            goto label;

    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int count = searchContact(addressBook);
    if(count == 0)//exit from search fun
    return;
start :
    int ind;
    int i;
    char ch;
    if(count>1)
    {
        printf("Enter index : ");
        scanf("%d",&ind);
        if(ind>count)
        {
            printf("Invalid option. Please try again.\n");
            goto start;
        }
        i = arr[ind-1];
        printf("Do you want to delete this contact ? (Y/N) :");
        getchar();
        scanf("%c",&ch);
    }
    else
    {
        i = arr[0];
        printf("Do you want to delete this contact ? (Y/N) :");
        getchar();
        scanf("%c",&ch);
    }

    if(ch == 'Y' || ch == 'y')
    {
        for(int j=i; j<addressBook -> contactCount; j++)
        {
            addressBook -> contacts[j] = addressBook -> contacts[j+1];
        }

        addressBook -> contactCount--;
    }
    else
    {
        return;//if don't delete
    }
}

int valid_num(char *phone)
{
    if(strlen(phone)!=10)//length must be 10
    return 0;

    for(int i=0; i<10 ; i++)
    {
        if(phone[i] < '0' || phone[i] > '9')//must be 0-9
        return 0;
    }

    return 1;
}

int unique_num(char *phone,AddressBook *addressBook)
{
    for(int i=0; i<addressBook -> contactCount ; i++)
    {
        if(strcmp(addressBook -> contacts[i].phone , phone) == 0 )
        {
            return 0;
        } 
    }

    return 1;
}

int valid_name(char *name)
{
    if(strlen(name) == 0 || name[0]==' ')//enter or space only is invalid name
    return 0;

    for(int i=0; name[i] != '\0' ; i++)
    {
        if( !( ( name[i] >= 'A' && name[i] <= 'Z' ) || ( name[i] >= 'a' && name[i] <= 'z' ) ||  name[i] == ' ' ) )
        return 0;
    }

    return 1;
}

int valid_email(char *email)
{
    int i = 0;
    int count = 0;

    //Check first letter must be alphabet(lowecase)
    if( !(email[0] >= 'a' && email[0] <= 'z' ) )
    {
        return 0;
    }

    //check email shouldn't have space,special characters,uppercase etc..
    while(email[i] != '\0' )
    {
        if( !((email[i] >= 'a' && email[i] <= 'z') ||
              (email[i] >= '0' && email[i] <= '9') ||
              email[i] == '.' || email[i] == '-' || email[i] == '_' || email[i] == '+' || email[i] == '@') )
        {
            return 0;
        }
        i++;
    }

    //check whether '@ present 
    char *ptr = strchr(email,'@');

    if( ptr == NULL )// '@' not present
    {
        return 0;
    }

    int position = ptr - email;//@ position

    //after @ must be a to z atleast 1
    if(!(email[position + 1] >= 'a' && email[position + 1] <= 'z'))
    {
        return 0;
    }
    
    i = 0;
    //check '@' must be 1
    while(email[i] != '\0')
    {
        if(email[i] == '@' )
        count++;
        i++;
    }

    if(count>1)
    {
        return 0;
    }

    // after '@' must be lowercase alphabets and dot
    for(i = position+1 ; email[i] != '\0' ; i++)
    {
        if( !(email[i] >= 'a' && email[i] <= 'z' || email[i] == '.') )
        {
            return 0;
        }
    }

    // email must ends with .com 
    int length = strlen(email);
    if(strcmp(&email[length-4],".com") != 0 )
    return 0;

    return 1;
}

int unique_email(char *email,AddressBook *addressBook)
{
    for(int i=0; i<addressBook -> contactCount ; i++)
    {
        if(strcmp(addressBook -> contacts[i].email , email) == 0 )
        {
            return 0;
        } 
    }
    
    return 1;
}