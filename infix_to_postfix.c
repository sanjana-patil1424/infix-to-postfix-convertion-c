#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1) stack[++top] = c;
}

char pop() {
    if (top >= 0) return stack[top--];
    return '\0';
}

char peek() {
    if (top >= 0) return stack[top];
    return '\0';
}

int isEmpty() { return top == -1; }

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

void infixToPostfix(const char *infix, char *postfix) {
    top = -1;
    int k = 0;
    for (int i = 0; infix[i]; ++i) {
        char c = infix[i];
        if (isspace((unsigned char)c)) continue;
        if (isalnum((unsigned char)c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (!isEmpty() && peek() != '(') postfix[k++] = pop();
            if (!isEmpty() && peek() == '(') pop();
        } else { // operator
            while (!isEmpty() && ((precedence(peek()) > precedence(c)) ||
                   (precedence(peek()) == precedence(c) && c != '^'))) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }
    while (!isEmpty()) postfix[k++] = pop();
    postfix[k] = '\0';
}

int main() {
    char line[256];
    while (fgets(line, sizeof(line), stdin)) {
        size_t n = strcspn(line, "\r\n");
        line[n] = '\0';
        if (strlen(line) == 0) continue;
        char out[512];
        infixToPostfix(line, out);
        printf("Infix: %s\nPostfix: %s\n\n", line, out);
    }
    return 0;
}
