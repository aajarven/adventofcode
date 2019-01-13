#define AADIFF 'a'-'A'

struct stacknode{
    char unit;
    int length; // length of the polymer up to this unit
    struct stacknode* previous;
};
