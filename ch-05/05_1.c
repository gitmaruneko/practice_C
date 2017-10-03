#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);

char buf[BUFSIZE];
int bufp = 0;

int getint(int *pn) 
{
    int c, d, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); ///* it is not a number 
        return 0;
    }

    sign = ( c == '-') ? -1 : 1 ;
    if ( c=='+'||c=='-') {
        d = c;
        if (!isdigit(c=getch())) {
            if (c!=EOF) 
			    ungetch(c);
			else
			    ungetch(d);
			    
            return d;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    
    if (c != EOF)
        ungetch(c);
    return c;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) 
        printf("ungetch : Too much chars");
    else
        buf[bufp++] = c;
}

int  main()  
{ 
    int value, c = 0;
    while ((c = getint(&value)) != EOF && c != '+' && c != '-' && c != 0) {
        printf("value = %d\n", value);
    }
    printf("Return value = %d\n", c);

    while ((c = getchar()) != '\n')
        ;
    getchar();
}




