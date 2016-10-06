#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *removeDuplicates(char word[]);
void initializeEncryptArray(char key[], char encrypt[]);
void initializeDecryptArray(char encrypt[], char decrypt[]);
void processInput(FILE *inf, FILE *outf, char substitute[]);
void alphaArray(char x[]);
char *flipArray(char x[]);
void printArray(char x[]);
void toUpper(char x[]);

//Input: [cmd code] [key] [input] [output]
int main(int argc, char* argv[]){
	char encrypt[26], decrypt[26];
	FILE *inf, *outf;
	
	if (argc != 5){
		printf("Input format: [cmd code] [key] [input_file] [output_file]\n");
		printf("Cmd Codes: 1 for encryption. 2 for decryption.\n");
		printf("Key: Word or combination consisting of letters only.\n");
		printf("ie. >> project.exe 1 stealth input.txt output.txt\n");
		exit(1);
	}

	char *word = argv[2];
	
	initializeEncryptArray(word, encrypt);
	initializeDecryptArray(encrypt, decrypt);
	
	//Read file
	inf = fopen(argv[3], "r");
	//Write file
	outf = fopen(argv[4], "w"); 
	
	if (inf ==  NULL){
		printf("File could not ,jb;kjbbe opened.\n");
		exit(1);
	}

	if(atoi(argv[1]) == 0){
		processInput(inf, outf, encrypt);
	}else if(atoi(argv[1]) == 1){
		processInput(inf, outf, decrypt);
	}else exit(1);
	
	return 0;
}

char *removeDuplicates(char word[]){
	toUpper(word);
	int size = strlen(word);
		
	for(int i = 0; i < size; i++){
		for(int j = i + 1; j < size;){
			if(word[j] == word[i]){
				for(int k = j; k < size; k++){
					word[k] = word[k + 1];
				}
				size--;
			}else
				j++;
		}
	}
	char *ptr = malloc(size);
	strcpy(ptr, word);
	return ptr;	
}

void initializeEncryptArray(char key[], char encrypt[]){
	alphaArray(encrypt);	
	char temp[strlen(encrypt)], combo[strlen(key)+strlen(encrypt)];
	strcpy(temp, flipArray(encrypt));
	strcpy(combo, strcat(key, temp));
	strcpy(encrypt, removeDuplicates(combo));
} 

void initializeDecryptArray(char encrypt[], char decrypt[]){
	alphaArray(decrypt);
	char temp[strlen(decrypt)];
	for(int i = 0; i < strlen(decrypt); i++){
		temp[(int)encrypt[i]-65] = 65 + i;
	}
	strcpy(decrypt, temp);
}

void processInput(FILE *inf, FILE *outf, char substitute[]){
	char ch;
	
	if (inf ==  NULL || outf == NULL){
		printf("File could not be opened.\n");
		exit(1);
	}
	
	while (fscanf(inf, "%c", &ch) != EOF ){
		for(int i = 0; i < strlen(substitute); i++){
			if(toupper(ch) == substitute[i]){
				fprintf(outf, "%c", (char)65+i);
			}
		}
		if(((int)ch >= 32 && (int)ch <= 64) || ch == '\n')
			fprintf(outf, "%c", ch);	
		
	}

	fclose(inf);
	fclose(outf);
}


void alphaArray(char x[]){
	char temp[27] = {'A','B','C','D','E','F','G','H','I',
		'J','K','L','M','N','O','P','Q','R',
		'S','T','U','V','W','X','Y','Z', '\0'};
	for(int i = 0; i < strlen(temp); i++){
		x[i] = temp[i];
	}
}

char *flipArray(char x[]){
	int size = strlen(x);
	char *flip = malloc(size);
	
	for(int i = 0; i < size; i++){
		flip[i] = x[size - 2 - i];
	}
	flip[size] = '\0';
	strcpy(x,flip);
	free(flip);
	return x;
}

void printArray(char x[]){
	int size = strlen(x);
	
	printf("\n");
	for (int i = 0; i < size; i++) {
      printf("%c", x[i]);
	}
	printf("\n");
}

void toUpper(char x[]){
	for(int i = 0; i < strlen(x); i++){
		x[i] = (char)toupper(x[i]);
	}
}

