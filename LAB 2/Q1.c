#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/* ================= SHARED DATA STRUCTURES ================= */

typedef struct{
    int *items;
    int count;
} ArrayList;

typedef struct SNode{
    int value;
    struct SNode *next;
} SNode;

typedef struct DNode{
    int value;
    struct DNode *previous;
    struct DNode *next;
} DNode;

typedef struct{
    DNode *first;
    DNode *last;
} DoublyList;


/* ================= 1. UNSORTED ARRAY ================= */

int unsortedArraySearch(ArrayList *arr, int target){
    for (int i = 0; i < arr->count; i++)
    {
        if (arr->items[i] == target)
            return i;
    }

    return -1;
}

void unsortedArrayInsert(ArrayList *arr, int value){
    arr->items[arr->count++] = value;
}

void unsortedArrayDelete(ArrayList *arr, int position){
    // Replace deleted element with the last element
    arr->items[position] = arr->items[--arr->count];
}

int unsortedArrayMax(ArrayList *arr){
    int largest = INT_MIN;

    for (int i = 0; i < arr->count; i++)
    {
        if (arr->items[i] > largest)
            largest = arr->items[i];
    }

    return largest;
}

int unsortedArrayMin(ArrayList *arr){
    int smallest = INT_MAX;

    for (int i = 0; i < arr->count; i++)
    {
        if (arr->items[i] < smallest)
            smallest = arr->items[i];
    }

    return smallest;
}

int unsortedArrayPredecessor(ArrayList *arr, int index){
    int predecessor = INT_MIN;

    for (int i = 0; i < arr->count; i++)
    {
        if (arr->items[i] < arr->items[index] &&
            arr->items[i] > predecessor)
        {
            predecessor = arr->items[i];
        }
    }

    return predecessor;
}

int unsortedArraySuccessor(ArrayList *arr, int index){
    int successor = INT_MAX;

    for (int i = 0; i < arr->count; i++)
    {
        if (arr->items[i] > arr->items[index] &&
            arr->items[i] < successor)
        {
            successor = arr->items[i];
        }
    }

    return successor;
}


/* ================= 2. SORTED ARRAY ================= */

int sortedArraySearch(ArrayList *arr, int target){
    int left = 0;
    int right = arr->count - 1;

    // Binary search works because the array is sorted
    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        if (arr->items[middle] == target)
            return middle;

        if (arr->items[middle] < target)
            left = middle + 1;
        else
            right = middle - 1;
    }

    return -1;
}

void sortedArrayInsert(ArrayList *arr, int value){
    int position = arr->count - 1;

    // Shift larger elements one position to the right
    while (position >= 0 && arr->items[position] > value)
    {
        arr->items[position + 1] = arr->items[position];
        position--;
    }

    arr->items[position + 1] = value;
    arr->count++;
}

void sortedArrayDelete(ArrayList *arr, int position){
    // Shift elements left to fill the deleted position
    for (int i = position; i < arr->count - 1; i++)
        arr->items[i] = arr->items[i + 1];

    arr->count--;
}

int sortedArrayMax(ArrayList *arr){
    return arr->count ? arr->items[arr->count - 1] : INT_MIN;
}

int sortedArrayMin(ArrayList *arr){
    return arr->count ? arr->items[0] : INT_MAX;
}

int sortedArrayPredecessor(ArrayList *arr, int index){
    return index > 0 ? arr->items[index - 1] : INT_MIN;
}

int sortedArraySuccessor(ArrayList *arr, int index){
    return index < arr->count - 1 ? arr->items[index + 1] : INT_MAX;
}


/* ================= 3. SINGLY LINKED UNSORTED ================= */

SNode *unsortedSinglySearch(SNode *head, int target){
    while (head)
    {
        if (head->value == target)
            return head;

        head = head->next;
    }

    return NULL;
}

void unsortedSinglyInsert(SNode **head, int value){
    SNode *newNode = malloc(sizeof(SNode));

    newNode->value = value;
    newNode->next = *head;

    *head = newNode;
}

void unsortedSinglyDelete(SNode **head, SNode *target){
    if (*head == target){
        *head = (*head)->next;
        free(target);
        return;
    }

    SNode *current = *head;

    while (current && current->next != target)
        current = current->next;

    if (current){
        current->next = target->next;
        free(target);
    }
}

int unsortedSinglyMax(SNode *head)
{
    int largest = INT_MIN;

    while (head)
    {
        if (head->value > largest)
            largest = head->value;

        head = head->next;
    }

    return largest;
}

int unsortedSinglyMin(SNode *head)
{
    int smallest = INT_MAX;

    while (head)
    {
        if (head->value < smallest)
            smallest = head->value;

        head = head->next;
    }

    return smallest;
}

int unsortedSinglyPredecessor(SNode *head, SNode *target)
{
    int predecessor = INT_MIN;

    while (head)
    {
        if (head->value < target->value &&
            head->value > predecessor)
        {
            predecessor = head->value;
        }

        head = head->next;
    }

    return predecessor;
}

int unsortedSinglySuccessor(SNode *head, SNode *target)
{
    int successor = INT_MAX;

    while (head)
    {
        if (head->value > target->value &&
            head->value < successor)
        {
            successor = head->value;
        }

        head = head->next;
    }

    return successor;
}


/* ================= 4. SINGLY LINKED SORTED ================= */

SNode *sortedSinglySearch(SNode *head, int target)
{
    while (head && head->value <= target)
    {
        if (head->value == target)
            return head;

        head = head->next;
    }

    return NULL;
}

void sortedSinglyInsert(SNode **head, int value)
{
    SNode *newNode = malloc(sizeof(SNode));

    newNode->value = value;

    if (!*head || (*head)->value >= value)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    SNode *current = *head;

    while (current->next && current->next->value < value)
        current = current->next;

    newNode->next = current->next;
    current->next = newNode;
}

void sortedSinglyDelete(SNode **head, SNode *target)
{
    unsortedSinglyDelete(head, target);
}

int sortedSinglyMax(SNode *head)
{
    if (!head)
        return INT_MIN;

    while (head->next)
        head = head->next;

    return head->value;
}

int sortedSinglyMin(SNode *head)
{
    return head ? head->value : INT_MAX;
}

SNode *sortedSinglyPredecessor(SNode *head, SNode *target)
{
    if (!head || head == target)
        return NULL;

    while (head->next && head->next != target)
        head = head->next;

    return head;
}

SNode *sortedSinglySuccessor(SNode *target)
{
    return target ? target->next : NULL;
}


/* ================= 5. DOUBLY LINKED UNSORTED ================= */

DNode *unsortedDoublySearch(DNode *head, int target)
{
    while (head)
    {
        if (head->value == target)
            return head;

        head = head->next;
    }

    return NULL;
}

void unsortedDoublyInsert(DNode **head, int value)
{
    DNode *newNode = malloc(sizeof(DNode));

    newNode->value = value;
    newNode->previous = NULL;
    newNode->next = *head;

    if (*head)
        (*head)->previous = newNode;

    *head = newNode;
}

void unsortedDoublyDelete(DNode **head, DNode *target)
{
    if (*head == target)
        *head = target->next;

    if (target->next)
        target->next->previous = target->previous;

    if (target->previous)
        target->previous->next = target->next;

    free(target);
}

int unsortedDoublyMax(DNode *head)
{
    int largest = INT_MIN;

    while (head)
    {
        if (head->value > largest)
            largest = head->value;

        head = head->next;
    }

    return largest;
}

int unsortedDoublyMin(DNode *head)
{
    int smallest = INT_MAX;

    while (head)
    {
        if (head->value < smallest)
            smallest = head->value;

        head = head->next;
    }

    return smallest;
}

int unsortedDoublyPredecessor(DNode *head, DNode *target)
{
    int predecessor = INT_MIN;

    while (head)
    {
        if (head->value < target->value &&
            head->value > predecessor)
        {
            predecessor = head->value;
        }

        head = head->next;
    }

    return predecessor;
}

int unsortedDoublySuccessor(DNode *head, DNode *target)
{
    int successor = INT_MAX;

    while (head)
    {
        if (head->value > target->value &&
            head->value < successor)
        {
            successor = head->value;
        }

        head = head->next;
    }

    return successor;
}


/* ================= 6. DOUBLY LINKED SORTED ================= */

DNode *sortedDoublySearch(DoublyList *list, int target)
{
    DNode *current = list->first;

    while (current && current->value <= target)
    {
        if (current->value == target)
            return current;

        current = current->next;
    }

    return NULL;
}

void sortedDoublyInsert(DoublyList *list, int value)
{
    DNode *newNode = malloc(sizeof(DNode));

    newNode->value = value;
    newNode->previous = NULL;
    newNode->next = NULL;

    if (!list->first)
    {
        list->first = list->last = newNode;
        return;
    }

    if (list->first->value >= value)
    {
        newNode->next = list->first;
        list->first->previous = newNode;
        list->first = newNode;
        return;
    }

    DNode *current = list->first;

    while (current->next && current->next->value < value)
        current = current->next;

    newNode->next = current->next;
    newNode->previous = current;

    if (current->next)
        current->next->previous = newNode;
    else
        list->last = newNode;

    current->next = newNode;
}

void sortedDoublyDelete(DoublyList *list, DNode *target)
{
    if (list->first == target)
        list->first = target->next;

    if (list->last == target)
        list->last = target->previous;

    if (target->next)
        target->next->previous = target->previous;

    if (target->previous)
        target->previous->next = target->next;

    free(target);
}

int sortedDoublyMax(DoublyList *list)
{
    return list->last ? list->last->value : INT_MIN;
}

int sortedDoublyMin(DoublyList *list)
{
    return list->first ? list->first->value : INT_MAX;
}

DNode *sortedDoublyPredecessor(DNode *target)
{
    return target ? target->previous : NULL;
}

DNode *sortedDoublySuccessor(DNode *target)
{
    return target ? target->next : NULL;
}


/* ================= GRAPH GENERATION ================= */

void createComplexityGraph(const char *fileName)
{
    FILE *file = fopen(fileName, "w");

    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    // Write the SVG header
    fprintf(file,
            "<svg xmlns=\"http://www.w3.org/2000/svg\" "
            "width=\"900\" height=\"650\">\n");

    // Set a dark background
    fprintf(file,
            "<rect width=\"100%%\" height=\"100%%\" fill=\"#1e1e1e\"/>\n");

    // Draw grid lines
    for (int i = 50; i <= 800; i += 50)
    {
        fprintf(file,
                "<line x1=\"%d\" y1=\"50\" x2=\"%d\" y2=\"550\" "
                "stroke=\"#333\" stroke-width=\"1\"/>\n",
                i, i);

        fprintf(file,
                "<line x1=\"50\" y1=\"%d\" x2=\"800\" y2=\"%d\" "
                "stroke=\"#333\" stroke-width=\"1\"/>\n",
                i, i);
    }

    // Draw X and Y axes
    fprintf(file,
            "<line x1=\"50\" y1=\"550\" x2=\"820\" y2=\"550\" "
            "stroke=\"white\" stroke-width=\"2\"/>\n");

    fprintf(file,
            "<line x1=\"50\" y1=\"550\" x2=\"50\" y2=\"30\" "
            "stroke=\"white\" stroke-width=\"2\"/>\n");

    // Add graph labels
    fprintf(file,
            "<text x=\"400\" y=\"590\" fill=\"white\" "
            "font-family=\"sans-serif\" font-size=\"16\">"
            "Number of Elements (N)</text>\n");

    fprintf(file,
            "<text x=\"20\" y=\"300\" fill=\"white\" "
            "font-family=\"sans-serif\" font-size=\"16\" "
            "transform=\"rotate(-90 20,300)\">Time Taken</text>\n");

    fprintf(file,
            "<text x=\"50\" y=\"25\" fill=\"white\" "
            "font-family=\"sans-serif\" font-size=\"18\" "
            "font-weight=\"bold\">"
            "Asymptotic Time Complexity Comparison</text>\n");


    /* ---------- O(1) Curve ---------- */

    fprintf(file,
            "<polyline fill=\"none\" stroke=\"#4ade80\" "
            "stroke-width=\"4\" points=\"");

    for (int x = 50; x <= 800; x += 10)
        fprintf(file, "%d,530 ", x);

    fprintf(file, "\"/>\n");


    /* ---------- O(log N) Curve ---------- */

    fprintf(file,
            "<polyline fill=\"none\" stroke=\"#60a5fa\" "
            "stroke-width=\"4\" points=\"");

    for (int x = 50; x <= 800; x += 5)
    {
        double elements = x - 50;

        double y = 550 -
                   (elements > 0 ? 30 * log(elements + 1) : 0);

        fprintf(file, "%d,%d ", x, (int)y);
    }

    fprintf(file, "\"/>\n");


    /* ---------- O(N) Curve ---------- */

    fprintf(file,
            "<polyline fill=\"none\" stroke=\"#f87171\" "
            "stroke-width=\"4\" points=\"");

    for (int x = 50; x <= 800; x += 10)
    {
        double y = 550 - 0.6 * (x - 50);

        if (y > 40)
            fprintf(file, "%d,%d ", x, (int)y);
    }

    fprintf(file, "\"/>\n");


    // Label the three complexity curves
    fprintf(file,
            "<text x=\"750\" y=\"515\" fill=\"#4ade80\" "
            "font-family=\"monospace\" font-size=\"18\">O(1)</text>\n");

    fprintf(file,
            "<text x=\"750\" y=\"330\" fill=\"#60a5fa\" "
            "font-family=\"monospace\" font-size=\"18\">O(log N)</text>\n");

    fprintf(file,
            "<text x=\"750\" y=\"110\" fill=\"#f87171\" "
            "font-family=\"monospace\" font-size=\"18\">O(N)</text>\n");


    /* ---------- Legend ---------- */

    fprintf(file,
            "<rect x=\"80\" y=\"50\" width=\"400\" height=\"190\" "
            "fill=\"#2d2d2d\" stroke=\"#555\" rx=\"5\"/>\n");

    fprintf(file,
            "<text x=\"95\" y=\"75\" fill=\"white\" "
            "font-family=\"sans-serif\" font-size=\"14\" "
            "font-weight=\"bold\">"
            "Performance by Data Structure:</text>\n");

    const char *legend[] =
    {
        "<tspan fill=\"#f87171\">O(N)</tspan> Search, "
        "<tspan fill=\"#4ade80\">O(1)</tspan> Insert : "
        "Unsorted Array, DLL (Unsorted)",

        "<tspan fill=\"#60a5fa\">O(log N)</tspan> Search, "
        "<tspan fill=\"#f87171\">O(N)</tspan> Insert : "
        "Sorted Array",

        "<tspan fill=\"#f87171\">O(N)</tspan> Search, "
        "<tspan fill=\"#f87171\">O(N)</tspan> Insert : "
        "SLL (Sorted), DLL (Sorted)",

        "<tspan fill=\"#f87171\">O(N)</tspan> Search, "
        "<tspan fill=\"#4ade80\">O(1)</tspan> Delete : "
        "DLL (Sorted &amp; Unsorted)",

        "<tspan fill=\"#f87171\">O(N)</tspan> Search, "
        "<tspan fill=\"#4ade80\">O(1)</tspan> Insert : "
        "SLL (Unsorted)"
    };

    for (int i = 0; i < 5; i++)
    {
        fprintf(file,
                "<text x=\"95\" y=\"%d\" fill=\"#ccc\" "
                "font-family=\"sans-serif\" font-size=\"13\">"
                "%s</text>\n",
                100 + (i * 25), legend[i]);
    }

    fprintf(file, "</svg>\n");

    fclose(file);

    printf("SVG graph generated successfully: %s\n", fileName);
}


/* ================= MAIN FUNCTION ================= */

int main()
{
    DoublyList numbers = {NULL, NULL};

    // Insert values into the sorted doubly linked list
    sortedDoublyInsert(&numbers, 10);
    sortedDoublyInsert(&numbers, 5);
    sortedDoublyInsert(&numbers, 202);
    sortedDoublyInsert(&numbers, 101);
    sortedDoublyInsert(&numbers, 52);
    sortedDoublyInsert(&numbers, 201);
    sortedDoublyInsert(&numbers, 13);
    sortedDoublyInsert(&numbers, 54);
    sortedDoublyInsert(&numbers, 1);

    // Display minimum and maximum values
    printf("Minimum: %d\n", sortedDoublyMin(&numbers));
    printf("Maximum: %d\n", sortedDoublyMax(&numbers));

    // Generate the complexity graph
    createComplexityGraph("complexity_graph.svg");

    return 0;
}