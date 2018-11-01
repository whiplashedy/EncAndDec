/*
Nursultan Altayev 2nd Assignment

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void key(FILE *fin, char subarr[])
{
    char keySymb;
    int i=0;
    do
    {
        keySymb = getc(fin); //function to take every sign from key.254
        subarr[i] = keySymb;
        i++;
    }
    while(keySymb != EOF);

}


void encrypt( FILE *fin, FILE *fout, char subarr[], char pass[] )
{
    int encrypted, k=0;
    char findSymb;
    int length = strlen(pass);   //password's length
    while(findSymb !=EOF)
    {
        if(findSymb == EOF)
        {
            break; //it helps to do not count newline/EOF as a character
        }
        findSymb = getc(fin);
        encrypted = (((unsigned char)findSymb + pass[k%length])%255); //here pass[k%length] means its' repeating from 0 to 3 and again...
        k++;
        fprintf(fout, "%c", subarr[encrypted]); //prints out chars from subarr to our created new file

    }
}

void decrypted( FILE *fin, FILE *fout, char subarr[], char pass[] )
{
    int decrypted, k=0,i;
    char findSymb;
    int length = strlen(pass);
    do
    {

        findSymb = fgetc(fin);
//            if(findSymb < pass[k%length]){
//                findSymb= findSymb + 255;
//            }
        for(i=0; i<255; i++)
        {
            if(subarr[i] == findSymb)
            {
                break; // when subarr == findSymb we break loop, to save its index i when it is equal to findSymb
            }
        }
        decrypted = (i - (unsigned char)pass[k%length])%255;
        k++;
        // printf("HIIIII");
        fprintf(fout, "%c", (char)decrypted);
        //printf("HOOOOOOO");



    }
    while(!feof(fin));
}

int main()
{
    int infiniteLoop = 1; //used to infinite menu
    char subarr[256], password[256], button[100], fileName[256], encryptedFile[256], nameFile[256], decryptedFile[256];
    FILE *encFile, *encedFile, *keyFile;
    keyFile = fopen("key.254","r");
    key(keyFile, subarr);
    printf("Welcome to the encryption service.\n");
    printf("Enter your password\n");
    scanf(" %s", password);
    while(infiniteLoop > 0)
    {
        printf("MENU: <e>ncode, <d>ecode>, or <q>uit\n");
        scanf("%s", button);
        if(button[0] == 'e') //reads only the first character
        {
            printf("ENTER a file to encrypt\n");
            scanf(" %s", fileName);
            // printf("%s", fileName);
            encFile = fopen(fileName, "r");
            /*do{
                char findSymb = getc(encFile);
                if(findSymb == EOF)break;
                printf("%c", findSymb);
            }while(1);*/
            if(encFile == NULL)
            {
                printf("CAN NOT OPEN FILE %s\n", fileName);
                continue;
            }
            else
            {
                printf("Enter a filename for the encrypted file.\n");
                scanf(" %s", encryptedFile);
                //printf("%s", encryptedFile);
                encedFile = fopen(encryptedFile, "w");
                if(encedFile == NULL)
                {
                    printf("CAN NOT OPEN FILE %s\n", encryptedFile);
                    continue;
                }
                else
                {
                    encrypt(encFile, encedFile, subarr, password);
                    fclose(encFile);
                    fclose(encedFile);
                }
            }

        }
        else if(button[0] == 'd')
        {
            printf("ENTER a file to decrypt\n");
            scanf("%s", nameFile);
            encFile = fopen(nameFile, "r");
            if(encFile == NULL)
            {
                printf("CAN NOT OPEN FILE %s\n", nameFile);
                continue;
            }
            printf("ENTER a filename for the decrypted file\n");
            scanf("%s", decryptedFile);
            encedFile = fopen(decryptedFile, "w");
            if(encedFile == NULL)
            {
                printf("CAN NOT OPEN FILE %s\n", decryptedFile);
                continue;
            }
            decrypted(encFile, encedFile, subarr, password);
            fclose(encFile);
            fclose(encedFile);
        }
        else if(button[0] == 'q')
        {
            printf("BYE!\n");
            exit(1); //exits the program
        }
        else
        {
            printf("UNRECOGNIZED %s\n", button);
        }
    }

    return 0;
}
