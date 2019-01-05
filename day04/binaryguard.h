

/*
 * A binary tree node with unique id and an array for stroring sleep minutes
 */
struct guard{
    int id;
    int minutes[60];
    struct guard* left;
    struct guard* right;
};

struct guard* find_or_insert(struct guard*, int);
struct guard* create_guard(int);
int totalminutes(struct guard*);
struct guard* find_sleepiest(struct guard*);
