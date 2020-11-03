#include <stdio.h>
#include "my_lib.h"

/*
Esta función calcula el nº de bytes de la cadena apuntada por str, sin incluir el carácter nulo de terminación ‘\0’ .
Devuelve la longitud de la cadena apuntada por str. No devuelve error.
*/
size_t my_strlen(const char *str)
{
    size_t len = 0;

    for (len = 0; len < str[len]; len++)
        ;
    return len;
}

/*
Esta función compara las cadenas apuntadas por str1 y str2.
Devuelve un entero:
    < 0 indica que str1 < str2.
    > 0 indica que str2 < str1.
    = 0 indica que str1 = str2.
No se basa en la longitud sino en los códigos ASCII. Cuando encuentra uno 
diferente reporta el resultado calculado como la resta de los códigos ASCII 
de los caracteres diferentes.
*/
int my_strcmp(const char *str1, const char *str2)
{
    int i = 0;
    int cmp = 0;

    while (str1[i] && (str1[i] != str2[i]))
    {
        if (str1[i] != str2[i])
        {
            //Realizamos la diferencia correspondiente a los caracteres ASCII
            //como hace srtcmp()
            cmp = *(const unsigned char *)str1 - *(const unsigned char *)str2;
        }
        i++;
    }

    return cmp;
}

/*
La función strcpy() copia la cadena apuntada por src (con el carácter de terminación ‘\0’) 
en la memoria apuntada por dest.
Devuelve el puntero dest. No devuelve error.
*/
char *my_strcpy(char *dest, const char *src)
{
    int c = 0;
    for (int i = 0; src[i]; i++, c++)
    {
        dest[c] = src[c];
    }
    dest[c] = '\0';
    return dest;
}

/*
La función strncpy() copia n caracteres de la cadena apuntada por src (con el carácter de terminación ‘\0’) 
en la memoria apuntada por dest. Devuelve el puntero dest. No devuelve error.
En caso de que strlen(src) < n, el resto de la cadena apuntada por dest ha de ser rellenado con 0s. 
*/
char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *paux = dest;
    int len = my_strlen(src);
    if (n <= len)
    { //Copiamos n caracteres sin '\0'
        while (n)
        {
            *paux = *src;
            paux++;
            src++;
            n--;
        }
    }
    else
    { //Copiamos todos los carácteres y rellenamos con '\0'
        int resto = n - (len + 1);
        while (len)
        {
            *paux = *src;
            paux++;
            src++;
            len--;
        }
        //Una vez copiados los carácteres añadimos '\0'
        *paux = '\0';
        while (resto)
        {
            paux++;
            resto--;
            *paux = '\0';
        }
    }
    return dest;
}

/*
La función strcat() añade la cadena apuntada por src (terminada con el carácter nulo) 
a la cadena apuntada por dest (también terminada con el carácter nulo).
El primer carácter de src sobreescribe el carácter nulo de dest. 
Devuelve el puntero dest. No devuelve error.
*/
char *my_strcat(char *dest, const char *src)
{
    char *new_dest = dest;

    //Nos movemos al final de dest
    while (*dest)
    {
        dest++;
    }

    //Concatenamos 'dest' con 'src'
    while (*src)
    {
        *dest++ = *src++;
    }

    //Añadimos el null a dest
    *dest = '\0';

    return new_dest;
}

/*
Reserva espacio para una variable de tipo struct my_stack, que contendrá el puntero al nodo 
superior de la pila y el tamaño de los datos, e inicializa esos valores con NULL, como valor 
del puntero al nodo superior de la pila, y con el tamaño de datos que nos pasan como parámetro.

Devuelve un puntero a la pila inicializada.
*/
struct my_stack *my_stack_init(int size)
{
    struct my_stack *stack = malloc(sizeof(struct my_stack));
    stack->first = NULL;
    stack->size = size;
    return stack;
}

/*
Inserta un nuevo nodo en los elementos de la pila (hay que reservar espacio de memoria para él).
El puntero a los datos de ese nodo nos lo pasan como parámetro.
*/
int my_stack_push(struct my_stack *stack, void *data)
{
    int r = -1;
    if (stack)
    {
        if (stack->size > 0)
        {   
            //Creamos un nuevo nodo con los datos de los parámetros
            //Y "actualizamos" el nuevo "top" de la pila, que sería nuestro first.
            struct my_stack_node *new_node = malloc(sizeof(new_node));
            new_node->data = data;
            new_node->next = stack->first;

            stack->first = new_node;
            r = 0;
        }
    }
    return r;
}

/*
Elimina el nodo superior de los elementos de la pila (y libera la memoria que ocupaba ese nodo!).
Devuelve el puntero a los datos del elemento eliminado. 

Si no existe nodo superior (pila vacía), retorna NULL.
*/

void *my_stack_pop(struct my_stack *stack)
{
    if (stack-> first)
    {
        struct my_stack_node *temp_node = malloc(sizeof(temp_node));
        //Creamos un nodo temporal
        temp_node= stack->first;

        //Copiamos los datos que a continuación se eliminarán
        void *datos = temp_node->data;

        //Asignamos el nuevo "top" del stack y así "borramos" el primer nodo
        stack->first = temp_node ->next;
        
        free(temp_node);
        return datos;
    }
    else
    {
        return NULL;
    }
}

/*
Recorre la pila y retorna el número de nodos totales que hay en los elementos de la pila.
*/
int my_stack_len(struct my_stack *stack)
{
    int i = 0;
    struct my_stack_node *temp_node = malloc(sizeof(temp_node));
    temp_node = stack->first;

    //Recorrido hasta el final de la pilay augmentamos el i
    while (temp_node)
    {
        temp_node = temp_node->next;
        i++;
    }

    free(temp_node);    //PREGUNNTAAAAAAAAAR!!! Si hay que liberar memoria
    return i;
}

/*
Recorre la pila liberando la memoria que habíamos reservado para cada uno de los datos 
(data) y la de cada nodo. Finalmente libera también la memoria que ocupa la pila. Es decir, toda la memoria que se reservó con malloc() en algún momento, se libera con la función free(). 

Devuelve el número de bytes liberados.  
*/
int my_stack_purge (struct my_stack *stack){
    int i = 0;

    struct my_stack_node *temp_node = malloc(sizeof(temp_node));
    struct my_stack_node *node_next = malloc(sizeof(node_next));

    temp_node = stack->first;

    //Recorrido hasta el final de la pila y augmentamos el i
    while (temp_node)
    {
        node_next = temp_node -> next;
        //liberamos el nodo temporal
        free(temp_node); 
        temp_node = node_next;
        i++;
    }

    i *= sizeof(temp_node);
    i *= sizeof(stack -> size);
    i += sizeof(stack);

    return i;
}
