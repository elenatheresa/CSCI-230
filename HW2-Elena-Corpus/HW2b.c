#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct stackType
{
   int top;
   int items[100];

}stack;

// evaluator functions
int precedence(char op);
int calculate(int a, int b, char op);
int evaluate(char* tokens);

// stack functions
void push(stack* stck, int value);
int pop(stack* stck);
int peek(stack* stck);
int empty(stack* stck);

int main()
{
   char exp[100];
   printf("Enter Expresssion: ");
   scanf("%s", exp);

   printf("Evaluate: %s\n", exp);
   printf("%d\n", evaluate(exp));
   return 0;
}

int precedence(char op) {
   if (op == '+' || op == '-')
      return 1;
   else if (op == '*' || op == '/')
      return 2;
   else return 0;
}

int calculate(int a, int b, char op)
{
   switch (op)
   {
   case '+': return a + b;
   case '-': return a - b;
   case '*': return a * b;
   case '/':

      if (b == 0)
      {
         printf("divide by zero encountered\n");
            return 0;
      }

      else
      {
         return a / b;
      }

      default: return 0;
   }
}

int evaluate(char* exp) {

   unsigned int i = 0;
   int number = 0;
   int number1;
   int number2;
   int result;
   char op;

   stack values_stck;
   values_stck.top = 0;

   stack ops_stck;
   ops_stck.top = 0;

   for (i = 0; i < strlen(exp); i++)
   {

      if (exp[i] == ' ')
         continue;

      else if (exp[i] == '(')
      {
         push(&ops_stck, exp[i]);
      }

      else if (isdigit(exp[i]))
      {
         number = 0;

         while (i < strlen(exp) && isdigit(exp[i]))
         {
            number = (number * 10) + (exp[i] - '0');
            i++;
         }
         i--;

         push(&values_stck, number);
         }

      else if (exp[i] == ')')
      {
         while (!empty(&ops_stck) && peek(&ops_stck) != '(')
         {
            number2 = pop(&values_stck);
            number1 = pop(&values_stck);
            op = pop(&ops_stck);
            result = calculate(number1, number2, op);
            push(&values_stck, result);
         }

         if (!empty(&ops_stck))
            pop(&ops_stck);
      }

      else
      { 
         while (!empty(&ops_stck) && precedence(peek(&ops_stck)) >= precedence(exp[i]))
         {
            number2 = pop(&values_stck);
            number1 = pop(&values_stck);
            op = pop(&ops_stck);
            result = calculate(number1, number2, op);
            push(&values_stck, result);
         }

         push(&ops_stck, exp[i]);
      }
   }
   while (!empty(&ops_stck))
   {
      number2 = pop(&values_stck);
      number1 = pop(&values_stck);
      op = pop(&ops_stck);
      result = calculate(number1, number2, op);
      push(&values_stck, result);
   }
   result = pop(&values_stck);
   return result;
}


void push(stack* stck, int value)
{
   stck->items[stck->top] = value;
   (stck->top)++;
}

int pop(stack* stck)
{
   int value = 0;
   (stck->top)--;
   value = stck->items[stck->top];
   return value;
}

int peek(stack* stck)
{
   int value = stck->items[(stck->top) - 1];
   return value;
}

int empty(stack* stck)
{
   return stck->top == 0;
}

