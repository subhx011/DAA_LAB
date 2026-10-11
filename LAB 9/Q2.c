
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

Node *heap[200];
int size = 0;

Node *createNode(char ch, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));

    p->ch = ch;
    p->freq = freq;
    p->left = NULL;
    p->right = NULL;

    return p;
}

void insert(Node *p) {
    int i = size++;

    while (i > 0 && heap[(i - 1) / 2]->freq > p->freq) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap[i] = p;
}

Node *extractMin(void) {
    Node *root = heap[0];
    Node *last = heap[--size];
    int i = 0;

    while (2 * i + 1 < size) {
        int c = 2 * i + 1;

        if (c + 1 < size &&
            heap[c + 1]->freq < heap[c]->freq)
            c++;

        if (last->freq <= heap[c]->freq)
            break;

        heap[i] = heap[c];
        i = c;
    }

    if (size > 0)
        heap[i] = last;

    return root;
}

void printCodes(Node *root, char code[], int depth) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        if (depth == 0)
            code[depth++] = '0';

        code[depth] = '\0';
        printf("%c : %s\n", root->ch, code);
        return;
    }

    code[depth] = '0';
    printCodes(root->left, code, depth + 1);

    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

void freeTree(Node *root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    int n, i, freq;
    char ch, code[200];

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of symbols\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter symbol and frequency: ");
        scanf(" %c %d", &ch, &freq);

        if (freq <= 0) {
            printf("Frequency must be positive\n");
            return 1;
        }

        insert(createNode(ch, freq));
    }

    while (size > 1) {
        Node *a = extractMin();
        Node *b = extractMin();

        Node *parent = createNode('$', a->freq + b->freq);
        parent->left = a;
        parent->right = b;

        insert(parent);
    }

    printf("\nHuffman Codes:\n");
    printCodes(heap[0], code, 0);

    freeTree(heap[0]);
    return 0;
}
