#include <stdio.h>
#include <string.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


/////////////////////////////////////////////////////////////////////////////
//*******   function to print the highlighted matched characters       ******

void print(int lineno, char c[100],char pat[100],int i){
	int m=0;
	int t=0;
	printf("%d : ",lineno);
	while(c[m]!='\n'){
		if(m==i){
			while((c[m]==pat[t] || pat[t]=='?') && t<strlen(pat)){
				printf(ANSI_COLOR_GREEN "%c",c[m] );
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

}
///////////////////////////////////////////////////////////////////////////
//*****************         function to get matching  *********************

int match(int lineno, char pat[100],char c[100]){
	int found=0;
	int flag=0;
	int k;
		for(int i=0;i<strlen(c);++i){
			if(c[i]==pat[0] || pat[0]=='?'){
				flag=0;
				int j=i;
				for(k=0; k<strlen(pat) && j<strlen(c);++k,++j){
					if(pat[k]=='?')
						continue;
					if(c[j]!=pat[k]){
						flag=1;
						break;
					}
				}
				if(j==strlen(c)&&k<strlen(pat))
					flag=1;
				if(flag==0){
					found=1;
					print(lineno,c,pat,i);
				}
			}
		}
		return found;
}
///////////////////////////////////////////////////////////////////////////

int main()
{
	FILE* fp;
	char pat[100];
	char pattern[100];
	int found=0,foundq=0;
	int c_found=0;
	char c[100];
	fp = fopen("inpt.txt", "r");
	printf("%s","Enter pattern to be matched : ");
	scanf("%s",pat);
	int k=0;
	int q =0;
	for(int i=0;i<strlen(pat);++i){
		if(pat[i]!='?')
			pattern[k++]=pat[i];
	}
	pattern[k]='\0';
	if(strcmp(pat,pattern)!=0)
		q=1;
	int flag=0;
	int lineno=0;	
	while(1){
		fgets(c,1024,fp);
		lineno++;
		found =match(lineno,pat,c);
		if(q==1)
			foundq =match(lineno,pattern,c); 

		if(found || foundq)
			c_found=1;

		if(feof(fp))
			break;
	}
	if(!c_found)
		printf("%s\n","Not Found any Match");
	fclose(fp);
	return 0;
}
