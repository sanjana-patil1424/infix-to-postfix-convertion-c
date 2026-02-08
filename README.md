# infix-to-postfix-convertion-c

C program to convert infix expressions into postfix notation using a stack implementation. Supports parentheses, operator precedence, exponentiation (`^`), and alphanumeric operands.

## Description
## Features

Converts infix expressions to postfix notation
Uses stack-based implementation
Supports arithmetic operators: +, -, *, /, ^
Handles parentheses ( and )
Maintains correct operator precedence and associativity
Works with single-character operands (variables or digits)
Simple command-line interface
Demonstrates practical use of stacks in C

## Algorithm

Initialize an empty stack for operators.
Scan the infix expression from left to right.
If the character is an operand, add it to the postfix expression.
If the character is an operator:
Pop operators from the stack with higher or equal precedence.
Push the current operator onto the stack.
If the character is (, push it onto the stack.
If the character is ), pop and add operators until ( is found.
After scanning the expression, pop all remaining operators from the stack.
Display the postfix expression.

## Technologies Used

Language: C

## Data Structure
Stack

## Compiler
GCC (or any standard C compiler)

## How to Run
gcc infix_to_postfix.c -o infix_to_postfix
./infix_to_postfix

## Project Structure
infix-to-postfix/
│── infix_to_postfix.c
│── README.md

## Concepts Covered

Stack data structure
Expression conversion
Operator precedence and associativity
C programming fundamentals

## Files

- `infix_to_postfix.c` — C implementation that reads infix expressions from standard input and prints the postfix form.

## Code

```c
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
```

## Example output

Sample run (three expressions piped to the program):

```txt
Infix: a+b*c
Postfix: abc*+

Infix: (A+B)*C
Postfix: AB+C*

Infix: A+B*C^D-E
Postfix: ABCD^*+E-
```

To reproduce locally:

```bash
gcc infix_to_postfix.c -o infix_to_postfix
printf "a+b*c\n(A+B)*C\nA+B*C^D-E\n" | ./infix_to_postfix
```
## Author
Sanjana Patil

