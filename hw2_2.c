#include <stdio.h>
#define I N 1
#define OUT 0
#define DEBUG 0

/*Solution A*/
int solutionA(char x1[]){
	char c = ' ';
	int i, nwhite, nother, nc;
    	int ndigit[10];
    	nwhite = nother = nc = 0;
    	for (i = 0; i < 10; ++i)
        	ndigit[i] = 0;
    	while ((c = x1[nc] ) != '\0') {
		++nc;
        	if (c >= '0' && c <= '9')
           		++ndigit[c-'0'];
       		 else if (c == ' ' || c == '\n' || c == '\t')
            		++nwhite;
        	else
            		++nother;
    		if(nc >= 100) {break;}
	}
	printf("Solution A, Arrays:\nDigits: ");
    	for (i = 0; i < 10; ++i)
        	printf(" %d", ndigit[i]);
    	printf(", White Space = %d, Other = %d\n",
        	nwhite, nother);
   	return 1;
}
/*Solution B*/
int solutionB(char x1[]){
	char *x1ptr = x1;
	char c = ' ';
        int i, nwhite, nother, nc;
        int ndigit[10];
        nwhite = nother = nc = 0;
        for (i = 0; i < 10; ++i)
                ndigit[i] = 0;
        while ((c = *(x1ptr + nc)) != '\0') {
                ++nc;
                if (c >= '0' && c <= '9')
                        ++ndigit[c-'0'];
                else if (c == ' ' || c == '\n' || c == '\t')
                        ++nwhite;
                else
                        ++nother;
        	if(nc >= 100) {break;}
	}
        printf("Solution B, Array Like Pointers:\nDigits: ");
        for (i = 0; i < 10; ++i)
                printf(" %d", ndigit[i]);
        printf(", White Space = %d, Other = %d\n",
                nwhite, nother);
        return 1;
}
/*Solution C*/
int solutionC(char x1[]){
        char *x1ptr = x1;
	int i, nwhite, nother;
        int ndigit[10];
        nwhite = nother = 0;
        for (i = 0; i < 10; ++i)
                ndigit[i] = 0;
	i = 0;
        while (*x1ptr != '\0') {
		++i;
                if (*x1ptr >= '0' && *x1ptr <= '9')
                        ++ndigit[(*x1ptr)-'0'];
                else if (*x1ptr == ' ' || *x1ptr == '\n' || *x1ptr == '\t')
                        ++nwhite;
                else
                        ++nother;
        	if(i >= 100) {break;}
		++x1ptr;
	}
        printf("Solution C, Native Pointers:\nDigits: ");
        for (i = 0; i < 10; ++i)
                printf(" %d", ndigit[i]);
        printf(", White Space = %d, Other = %d\n",
                nwhite, nother);
        return 1;
}
int main() {
	char x1[100]  = "The 25 quick brown foxes jumped over the 27 lazy dogs 17 times.";
	printf("Bobola,E. HW2. P2.\nString: %s\n",x1);
	solutionA(x1);
	solutionB(x1);
	solutionC(x1);
	printf("\n");
	return 0;
}
