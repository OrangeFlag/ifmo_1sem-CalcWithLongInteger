#include <stdio.h>
#include <stdlib.h>
#include "LongOperation2.h"

int main()
{
 LargeInt *a = (LargeInt*) malloc(sizeof(LargeInt));
 LargeInt_def(a);
 LargeInt *b = (LargeInt*) malloc(sizeof(LargeInt));
 LargeInt_def(b);
 int i;
 char a_c,b_c;
 int f = 1;
 scanf("%c", &a_c);
while (a_c != '\n'){
        if (a_c == '-'){
            scanf("%c", &a_c);
            f = -1;
            continue;
        }
        Push_end_Deck(Intg(a_c)*f, a);
        scanf("%c", &a_c);
        f = 1;
};
scanf("%c", &b_c);
while (b_c != '\n'){
        if (b_c == '-'){
                scanf("%c", &b_c);
                f = -1;
                continue;
        };

        Push_end_Deck(Intg(b_c)*f, b);
        scanf("%c", &b_c);
        f = 1;
};
//printf("%i\n", a -> Start -> sled -> data);
//printf("%i\n", b -> Start -> sled -> data);
printf("\n");

//PrintLargeInt(b);
a = Division(a, b);

PrintLargeInt(a);
}
