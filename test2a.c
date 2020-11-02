#include <stdio.h>
#include <string.h>
#include "my_lib.h"


struct my_data {
   int val;
   char name[8];
};
 
int main() {
   struct my_stack *s;
   struct my_data *data1, *data2;
   char *names[]={"Xisco", "Cati"};

    //inicializamos la pila
   s = my_stack_init(sizeof(struct my_data));
   //introducimos 2 nodos en la pila
   printf ("Introduciendo los nodos en la pila:\n");
   for (int i = 0; i < 2; i++) {
       data1 = malloc(sizeof(struct my_data));
       data1->val = i;
       strcpy(data1->name, names[i]);
       my_stack_push(s,data1);
       printf("Valor: %d\t", data1->val);
       printf("Nombre: %s\n", data1->name);
   }
   printf ("Extrayendo los %d nodos de la pila:\n",my_stack_len(s));
   while ((data2 = my_stack_pop(s))) {//extraemos los nodos con pop
       printf("Valor: %d\t", data2->val);
       printf("Nombre: %s\n", data2->name);
       free(data2);
   }

   printf ("Introducimos de nuevo los nodos en la pila:\n");
   for (int i = 0; i < 2; i++) {
       data1 = malloc(sizeof(struct my_data));
       data1->val = i;
       strcpy(data1->name, names[i]);
       my_stack_push(s,data1);
       printf("Valor: %d\t", data1->val);
       printf("Nombre: %s\n", data1->name);
   }

   //liberamos todo el espacio ocupado por la pila
   printf ("Liberamos %lu bytes de la pila, %lu de los nodos y %lu de los datos. Total: %d\n", sizeof (struct my_stack), sizeof (struct my_stack_node)*2, sizeof(struct my_data)*2, my_stack_purge(s));
}
