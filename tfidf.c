#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#define NUM_OF_FILES 100
#define MAX_SIZE_STR 20
#define LOG 0


char path[NUM_OF_FILES][MAX_SIZE_STR];

size_t load_files_from_dir(const char* name, char path[NUM_OF_FILES][MAX_SIZE_STR]) {
	DIR *d = opendir(name);
	struct dirent *dir;    //Intermidiead object
	if(d == NULL)
		return -1;
	size_t counter = 0;
	while((dir = readdir(d)) != NULL) {

		strcpy(path[counter++],dir->d_name);
		char pom[20];
		strcpy(pom,name);
		strcat(pom,path[counter - 1]);
		strcpy(path[counter - 1],pom);
#if LOG == 1
		printf("%s\n",path[counter - 1]);
#endif
		assert(counter <= NUM_OF_FILES);
		}
	closedir(d);
	return counter;
	}



typedef struct {

	size_t tf;
	double idf;

	} TF_IDF;


size_t calculate_tf(const char *name,char *word, TF_IDF *tf) {

	size_t num_of_file = load_files_from_dir(name,path);
#if LOG == 1
	printf("num of files is %d\n",(int)num_of_file);
#endif
	char buffer[100];
	//FILE *f;
	for(size_t i = 2; i < num_of_file; i++) {

		//char pom[20];
		FILE *f = fopen(path[i],"r");
		if(f == NULL)
			system("exit");


		int counter = 1;
		while(!feof(f)) {
			counter++;
			//printf("%d\n",counter);
			fgets(buffer,100,f);
			if(strstr(buffer,word) != 0)
				tf[i].tf++;
			}
		tf[i].idf += (double)tf[i].tf / (double)counter;
#if LOG == 1
		printf("\nWord '%s' is repeted %d time in file '%s'\n",word,(int)tf[i].tf,path[i]);
		printf("\nIdf for '%s' is  %.4f\n\n",word,tf[i].idf);
#endif
		fclose(f);

		}
	// CALC
	return num_of_file;


	}

void reset_tf_idf(TF_IDF *tf) {

	for(size_t i = 0; i < NUM_OF_FILES; i++) {
		tf[i].idf = 0.0f;
		tf[i].tf  = 0;
		}

	}
// Sorts tf structure and PATH string
void sort_tf(TF_IDF *tf,size_t num_of_file) {

	TF_IDF pom;
	pom.tf = 0;
	pom.idf = 0;
	char spom[MAX_SIZE_STR];
	for(size_t i = 2; i < num_of_file; i++) {
		for(size_t j = i + 1; j < num_of_file; j++) {
			if(tf[i].tf < tf[j].tf) {

				pom.idf   =  tf[i].idf;
				pom.tf    =  tf[i].tf;

				tf[i].idf =  tf[j].idf;
				tf[i].tf  =  tf[j].tf;

				tf[j].idf =   pom.idf;
				tf[j].tf  =   pom.tf;

				//SORTING PATHS
				strcpy(spom, path[i]);
				strcpy(path[i], path[j]);
				strcpy(path[j], spom);


				}
			}

		}

	}

void print_tf(TF_IDF *tf, size_t num_of_file) {

	for(size_t i = 2; i < num_of_file; i++) {
		printf("tf[%d] = %d\n", (int)(i - 2),(int)tf[i].tf);
		}
	}


// Sorts tf structure and PATH string
void sort_idf(TF_IDF *tf,size_t num_of_file) {

	TF_IDF pom;
	pom.tf = 0;
	pom.idf = 0;
	
	for(size_t i = 2; i < num_of_file; i++) {
		for(size_t j = i + 1; j < num_of_file; j++) {
			if(tf[i].idf < tf[j].idf) {

				pom.idf   =  tf[i].idf;
				pom.tf    =  tf[i].tf;

				tf[i].idf =  tf[j].idf;
				tf[i].tf  =  tf[j].tf;

				tf[j].idf =   pom.idf;
				tf[j].tf  =   pom.tf;

				//SORTING PATHS
				char spom[MAX_SIZE_STR];
				strcpy(spom, path[i]);
				strcpy(path[i], path[j]);
				strcpy(path[j], spom);


				}
			}

		}

	}

void print_idf(TF_IDF *tf, size_t num_of_file) {

	for(size_t i = 2; i < num_of_file; i++) {
		printf("idf[%d] = %f\n", (int)(i - 2),tf[i].idf);
		}
	}



int main() {

	//char path[100][20];
	//size_t num_of_files = load_files_from_dir("a",path);
	//printf("Path %s", path[2]);
	//return 0;
	//TF je broj koliko se rijec ponavlja
	//IDF je broj koliko se rijec ponavlja / ukupno rijec u textu (Kao suma)
	TF_IDF tf[NUM_OF_FILES];
	reset_tf_idf(tf);
	//calculate_tf("a\\","ar",tf);

	while(1) {
		
		system("pause");
		system("cls");
		
		printf("\n_______________________________________________________\n");
		printf("\t CLI DOCS SEARCH(tf - idf) ENGINE\n");
		printf("\n_______________________________________________________\n");
		printf("Input term you want to search:\n>  ");
		char phrase[50];
		fgets(phrase,50,stdin);
		printf("Phrase %s\n",phrase);
		size_t num_of_file = calculate_tf("a\\",phrase,tf);
		//system("pause");
		char *token = strtok(phrase," ");
		
	
		while(token != NULL){
			//system("cls");
			printf("Token %s\n",token);
			//system("pause");
			num_of_file =  calculate_tf("a\\",token,tf);
			token = strtok(0," ");	
			
			}
		   //Calculate tf idf for words on it 
		sort_idf(tf,num_of_file);
		printf("\n");
		printf("Idf: \n\n");
		print_idf(tf,num_of_file);
		printf("path %s\n", path[2]);
		system(path[2]);
		reset_tf_idf(tf);
		//phrase[0] = '\0';
		}

	return 0;
	}