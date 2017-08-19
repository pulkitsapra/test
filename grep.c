#include <stdio.h>
#include <string.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
int main()
{
	FILE* fp;
	char pat[100];
	char pattern[100];
	char cpy[100];
	char *ret;
	char c[100];
	fp = fopen("inpt.txt", "r");
	printf("%s","Enter pattern to be matched : ");
	scanf("%s",pat);
	int flag=0;
	int lineno=0;
	int found=0;
	int k;
	while(1)
	{

		fgets(c,1024,fp);
		lineno++;
		int flag=0;
		for(int i=0;i<strlen(c);++i){
			if(c[i]==pat[0]){
				flag=0;
				int j=i;
				for(k=0; k<strlen(pat) && j<strlen(c);++k,++j){
					if(c[j]!=pat[k]){
						flag=1;
						break;
					}
				}
				if(j==strlen(c)&&k<strlen(pat)){
					flag=1;
				}

				if(flag==0){
					int m=0;
					int t=0;
					printf("%d : ",lineno);
					while(c[m]!='\n'){
						if(m==i){
							while(c[m]==pat[t] && t<strlen(pat)){
								printf(ANSI_COLOR_YELLOW "%c",c[m] );
								t++;
								m++;
							}
						}
						else{
							printf(ANSI_COLOR_RESET "%c",c[m] );
							m++;
						}					
					}
					printf("\n");
					found =1;
				}
			}
		} 

		if(feof(fp)){
			break;
		}
	}
	if(!found)
		printf("%s\n","Not Found any Match");


	return 0;
}
