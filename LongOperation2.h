#ifndef LongOperation2
#define LongOperation2

#include <math.h>
#include <stdlib.h>

int Intg(char a)
{
    return (int)a - (int)'0';
};

char Chr(int a)
{
    return (char)(a + (int)'0');
};

long int Max(long int a, long int b)
{
    if (a>b) {return a;}
    else {return b;};
};


typedef struct Deck
{
    short int data;
    struct Deck *prev;
    struct Deck *sled;
}Deck;

typedef struct
{
    Deck *Start, *End;
    int len;
}LargeInt;

void LargeInt_def (LargeInt *L){
    L -> Start = (Deck*) malloc(sizeof(Deck));
    L -> End = (Deck*) malloc(sizeof(Deck));
    L -> Start -> data = 20;
    L -> Start -> prev = NULL;
    L -> Start -> sled = L -> End;


    L -> End -> data = 20;
    L -> End -> prev = L -> Start;
    L -> End -> sled = NULL;

    L -> len = 0;
};

void Push_st_Deck(short int a, LargeInt *INT){
    Deck *De = (Deck*) malloc(sizeof(Deck));
    De -> data = a;

    De -> sled = INT -> Start -> sled;
    De -> prev = INT -> Start;

    INT -> Start -> sled -> prev = De;
    INT -> Start -> sled = De;
    INT -> len += 1;
};

void DelLidZero(LargeInt *INT)
{
    if (INT->len <= 1) return;
    Deck *temp;
    while (INT -> Start -> sled -> data == 0)
    {
        temp = INT -> Start -> sled;
        INT -> Start -> sled = INT -> Start -> sled-> sled;
        INT -> Start -> sled -> prev = INT -> Start;
        free(temp);
    };
};

void Push_Number_st(long int a, LargeInt *INT)
{
    while (a != 0)
    {
        Push_st_Deck(a%10, INT);
        a /= 10;
    };
};

void Push_end_Deck(short int a, LargeInt *INT){
    Deck *De = (Deck*) malloc(sizeof(Deck));
    De -> data = a;

    De -> sled = INT -> End;
    De -> prev = INT -> End -> prev;

    INT -> End -> prev -> sled = De;
    INT -> End -> prev = De;
    INT -> len += 1;

};

void Push_Number_end(long int a, LargeInt *INT)
{
    if (a/10 == 0) {Push_end_Deck(a, INT);}
    else
    {
        Push_Number_end(a/10, INT);
        Push_end_Deck(a%10, INT);
    };
};
void PrintLargeInt(LargeInt *input)
{
    Deck *A;
    A = input -> Start -> sled;
    while (A -> data != 20){
        printf("%i", A -> data);
        A = A -> sled;
    };
    printf("\n");
};

void MemoryClear(LargeInt *INT)
{
    if (INT == 0) return;
    Deck *El, *LastEl;
    LastEl = INT -> Start;
    El = INT -> Start -> sled;
    while (El->data != 20)
    {
        free(LastEl);
        LastEl = El;
        El = El->sled;
    };
    free(LastEl);
    free(El);
    free(INT);
};

void Copy(LargeInt *input, LargeInt *out){
    out -> len = input -> len;
    Deck *El_Input = input -> Start -> sled;
    while (El_Input -> data != 20){
            Push_end_Deck(El_Input -> data, out);
            El_Input = El_Input -> sled;

    }
}

int LenLargeInt(LargeInt *input)
{
    Deck *A;
    A = input -> Start -> sled;
    int i = 0;
    while (A -> data != 20){
        i++;
        A = A -> sled;
    };
    return i;
};


short int Bigger(LargeInt *one, LargeInt *two)
{
    if (one -> len > two -> len){
        return 1;
    };

    if (one -> len < two -> len){
        return -1;
    };

    Deck *one_El = one -> Start -> sled;
    Deck *two_El = two -> Start -> sled;
    while ((one_El -> data == two_El -> data) && (one_El -> sled -> data != 20)){
        one_El = one_El -> sled;
        two_El = two_El -> sled;
    };
    if (one_El -> data > two_El -> data){
        return 1;
    };
    if (one_El -> data < two_El -> data){
        return -1;
    };

    return 0;
};
LargeInt* Minus(LargeInt *one, LargeInt *two);
LargeInt* Plus(LargeInt *one, LargeInt *two){ //Пихаем начала двух LargeInt

    Deck *one_El = one -> End -> prev;
    Deck *two_El = two -> End -> prev;
    int one_int, two_int;
    short int modif = 0;
    short int res;
    if ((one -> Start -> sled -> data < 0) && (two -> Start -> sled -> data < 0))
    {
        one -> Start -> sled -> data = -(one -> Start -> sled -> data);
        two -> Start -> sled -> data = -(two -> Start -> sled -> data);
    }
    else
    {
        if (one -> Start -> sled -> data < 0)
        {
            one -> Start -> sled -> data = -(one -> Start -> sled -> data);
            return Minus(two, one);
        }

        if (two -> Start -> sled -> data < 0)
        {
            two -> Start -> sled -> data = -(two -> Start -> sled -> data);
            return Minus(one, two);
        };
    };

    LargeInt *out = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(out);
    out -> len = Max(one -> len, two -> len);

    while ((one_El -> data != 20) || (two_El -> data != 20)){
      if (one_El->data != 20)
      {
          one_int = one_El -> data;
          one_El = one_El -> prev;
      }
      else one_int = 0;

      if (two_El->data != 20)
      {
          two_int = two_El -> data;
          two_El = two_El -> prev;
      }
      else two_int = 0;

      res = one_int+two_int + modif;
      modif = res / 10;

      Push_st_Deck(res % 10, out);
    };
    if (modif != 0){
        Push_st_Deck(modif, out);
        out -> len ++;
    };
    return out;
};

LargeInt* Minus(LargeInt *one, LargeInt *two){
    Deck *one_El = one -> End -> prev;
    Deck *two_El = two -> End -> prev;
    short int one_int, two_int;
    short int modif = 0;
    short int res;
    LargeInt *out;


    if ((one ->Start -> sled -> data < 0) && (two ->Start -> sled -> data < 0))
    {
           two -> Start -> sled -> data = -(two -> Start -> sled -> data);
           one -> Start -> sled -> data = -(one -> Start -> sled -> data);
           out = Minus(one, two);
           out -> Start -> sled -> data = -(out -> Start -> sled -> data);
           return out;
    }

    if (one ->Start -> sled -> data < 0)
    {
        one -> Start -> sled -> data = -(one -> Start -> sled -> data);
        out = Plus(one, two);
        out -> Start -> sled -> data = -(out -> Start -> sled -> data);
        return out;
    }

    if (two ->Start -> sled -> data < 0)
    {
        two -> Start -> sled -> data = -(two -> Start -> sled -> data);
        out = Plus(one, two);
        return out;
    };





    if (Bigger(one, two) == -1)
    {
        out = Minus(two, one);
        out -> Start -> sled -> data = -(out -> Start -> sled -> data);
        return out;
    };


    out = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(out);

    if (Bigger(one, two) == 0)
    {
        Push_st_Deck(0, out);
        return out;
    };

    while ((one_El -> data != 20) || (two_El -> data != 20))
    {
      if (one_El->data != 20)
      {
          one_int = one_El -> data;
          one_El = one_El -> prev;
      }
      else one_int = 0;

      if (two_El->data != 20)
      {
          two_int = two_El -> data;
          two_El = two_El -> prev;
      }
      else two_int = 0;

      res = one_int - two_int - modif;
      if (res < 0)
      {
          modif = 1;
          res += 10;
      } else modif = 0;


      Push_st_Deck(res, out);
    };

    DelLidZero(out);
    out -> len = LenLargeInt(out);
    return out;
};

LargeInt* MultiplyOnSmall(LargeInt *one, int two){

    Deck *one_El = one -> End -> prev;
    short int one_int;
    short int modif = 0;
    short int res;

    short int f_minus = 0;
    if (two < 0){
        f_minus = 1;
        two = - two;
    };

    LargeInt *out = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(out);

    while (one_El -> data != 20){
      one_int = one_El -> data;
      one_El = one_El -> prev;
      res = one_int * two  + modif;
      modif = res / 10;

      Push_st_Deck(res%10, out);
    };
    Push_Number_st(modif, out);

    out -> len = LenLargeInt(out);
    if (f_minus == 1) out -> Start -> sled -> data = -(out -> Start -> sled -> data);
    return out;
};

LargeInt* Multiply(LargeInt *one, LargeInt *two){
    Deck *two_El = two -> Start -> sled;
    short int f_minus = 0;
    if (two_El -> data < 0)
    {
        f_minus++;
        two_El -> data = -(two_El -> data);
    };

    if (one -> Start -> sled -> data < 0)
    {
        f_minus++;
        one -> Start -> sled -> data = -(one -> Start -> sled -> data);
    };

    LargeInt *out = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(out);

    LargeInt *temp = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(temp);

    while (two_El -> data != 20)
    {
        MemoryClear(temp);
        temp = (LargeInt*) malloc(sizeof(LargeInt));
        LargeInt_def(temp);
        Copy(one, temp);

        temp = MultiplyOnSmall(temp, two_El -> data);
        two_El = two_El -> sled;
        out = Plus(out, temp);
        if (two_El -> data != 20) Push_end_Deck( 0 , out);
    };
    MemoryClear(temp);
    out -> len = LenLargeInt(out);
    if (f_minus == 1) out -> Start -> sled -> data = -(out -> Start -> sled -> data);
    return out;

};


LargeInt* DivisionOnSmall(LargeInt *one, int two)
{
    int res, modif;
    modif = 0;

    Deck* one_El = one -> Start -> sled;

    LargeInt *out = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(out);
    while (one_El -> data != 20)
    {
            res = (modif *10 + one_El -> data) / two;
            modif = (modif *10 + one_El -> data) % two;
            Push_Number_end(res, out);
            one_El = one_El -> sled;
    };
    DelLidZero(out);
    out -> len = LenLargeInt(out);
    return out;

};

LargeInt* Division(LargeInt *one, LargeInt *two)
{

    LargeInt *up = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(up);
    LargeInt *down = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(down);

    short int Sr;
    Push_end_Deck(0, down);
    Push_end_Deck(1, up);
    int i = 0;
    while (i < (one -> len) - (two -> len) + 1)
    {
        Push_end_Deck(0, up);
        i++;
    };

    short int f_minus = 0;
    if (one->Start->sled->data < 0)
    {
        one->Start->sled->data = -(one->Start->sled->data);
        f_minus++;
    };
    if (two->Start->sled->data < 0)
    {
        two->Start->sled->data = -(two->Start->sled->data);
        f_minus++;
    };

    LargeInt *temp = 0;

    LargeInt *Odin = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(Odin);
    Push_end_Deck(1, Odin);

    while (Bigger(Minus(up, Odin), down) == 1){

        MemoryClear(temp);
        temp = (LargeInt*) malloc(sizeof(LargeInt));
        LargeInt_def(temp);
        Copy(two, temp);

        temp = Multiply(temp, DivisionOnSmall(Plus(up, down),2));
        Sr = Bigger(temp, one);

        if (Sr < 0) {down = DivisionOnSmall(Plus(up, down),2); continue;};
        if (Sr > 0) {up = DivisionOnSmall(Plus(up, down),2); continue;};
        //Sr == 0
        up = DivisionOnSmall(Plus(up, down),2);
        down = up;
    };

    PrintLargeInt(up);
    PrintLargeInt(down);
    LargeInt *out = (LargeInt*) malloc(sizeof(LargeInt));
    LargeInt_def(out);
    out = DivisionOnSmall(Plus(up, down),2);
    PrintLargeInt(out);
    MemoryClear(up);
    MemoryClear(down);
    MemoryClear(temp);
    MemoryClear(Odin);

    if (f_minus == 1) out -> Start -> sled -> data = -(out -> Start -> sled -> data);
    DelLidZero(out);
    out -> len = LenLargeInt(out);
    return out;
};



#endif // LongOperation2
