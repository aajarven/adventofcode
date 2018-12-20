// binary tree
struct Node {
    int value;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int value);
bool find_or_insert(struct Node *root, int value);
