// #include <string.h>
#include <stdio.h>
#include <cassert>
// #include <TXLib.h>

char *strcpy (char dest[], const char src[]);
char *strncpy (char dest[], const char src[], size_t n);
void ascii_print(const char src[]);
int strcmp (const char s1[], const char s2[]);
const char *strchr (const char s[], int c);
size_t strlen (const char* s);
char *strstr(char *haystack, const char *needle);
void ascii_print_2d(const int arr[]);
void print_triangle_arr(const int arr[], const size_t size_i);
const int* adressation_for_2d(const int arr[], size_t i, size_t j);


int main()
    {
    // char old[] = "132456789";
    // char new_[15] = {0, 0};
    // strncpy(new_, old, 5);
    // ascii_print(new_);

    // char str0[] = "abc";
    // char* str1 = "abc";
    // printf("%p %p\n", str0, str1);
    // str1[1] = 15;
    // printf("%p", str1);


    // size_t counter = 0;
    // long int al[] = {12345};
    // long int* i = al - 10;
    // for (counter = 0; counter < 30; counter++)
    //     {
    //     printf("%p: %ld (%li bytes)\n", i, *i, sizeof(*i));
    //     i++;
    //     }

    // printf("%s\n", strstr("qwertytyuiop", "ty"));

    // char** str2 = &str1;  0x7fff16928cf4 0x7ffc83217734:
    // char*** str3 = &str2;
    // char**** str4 = &str3;
    // char***** str5 = &str4;
    // (****str5)[0] = 'b';
    // printf("%p %p %p %p %p %p", str0, str1, str2, str3, str4, str5);

    // printf("%li", strlen("123"));

    // char al[] = "123456789";
    // printf("%p %p %p %p", strchr(al, '1'), strchr(al, '2'), strchr(al, '\0'), strchr(al, '0'));

    const size_t size = 4;
    int my_arr[int(((size + 1) / 2.0) * size)]  =  {1,
                                                    2, 2,
                                                    3, 3, 3,
                                                    4, 4, 4, 4};
    print_triangle_arr(my_arr, size);
    putchar('\n');

    // const size_t i = 5, j = 7;
    // char new_arr[i][j]  =  {{'a', 'b', 'c', 'd', 'e'},
    //                         {'f', 'g', 'h'},
    //                         "123"};
    int arr[]  =  {3, 4,
                            1, 2, 3, 4,
                            9, 8, 7, 6,
                            20, 10, 30, 40};

    ascii_print_2d((int*)arr);

    return 0;
    }

/* Copy SRC to DEST.  */
char *strcpy (char dest[], const char src[])
{
    assert(dest && src);
    assert(dest != src);
    size_t i = 0;
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    i++;
    dest[i] = '\0';
    return dest;
}

/* Copy no more than N characters of SRC to DEST.  */
char *strncpy (char dest[], const char src[], size_t n)
    {
    assert(dest && src);
    assert(dest != src);
    size_t i = 0;
    for (i = 0; src[i] != '\0' && i < n; i++)
        dest[i] = src[i];
    i++;
    dest[i] = '\0';
    return dest;
    }


void ascii_print(const char src[])
    {
    assert(src);
    size_t i = 0;
    while (src[i] != '\0')
        {
        printf("%c(%i)", src[i], int(src[i]));
        i++;
        }
    printf("%c(%i)", '\0', int('\0'));
    }


/* Compare S1 and S2.  */
int strcmp (const char s1[], const char s2[])
    {
    size_t i = 0;
    for(i = 0; s1[i] != 0 && s2[i] != 0; i++)
        {
        if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return -1;
        }
    if (s1[i] > s2[i])
        return 1;
    else if (s1[i] < s2[i])
        return -1;
    return 0;
    }

/* Find the first occurrence of C in S.  */
const char *strchr (const char s[], int c)
    {
    assert(s);
    size_t i = 0;
    for (i = 0; s[i] != 0; i++)
        {
        if (c == s[i])
            return s + i;
        }
    if (c == '\0')
        return s + i;
    return nullptr;
    }

/* Return the length of S.  */
size_t strlen (const char* s)
    {
    assert(s);
    size_t i = 0;
    for(i = 0; s[i] != 0; i++);
    return i;
    }

/* Find the first occurrence of NEEDLE in HAYSTACK. */
char *strstr(char haystack[], const char needle[])
    {
    assert(haystack && needle);
    size_t i = 0;
    for (i = 0; haystack[i] ; i++)
        {
        size_t j = 0;
        for (j = 0; needle[j] && haystack[i] ; j++)
            {
            if (haystack[i] != needle[j])
                break;
            if (!needle[j + 1])
                return haystack + i - j;
            i++;
            }
        }
    return nullptr;
    }

//---------------------------------------------------------------------------------------------------------------------------

/* Prints 2-dimensional array */
void ascii_print_2d(const int arr[])
    {
    assert(arr);
    for (size_t i = 0; (int)i < arr[0]; i++)
        {
        for (size_t j = 0; (int)j < arr[1]; j++)
            printf("%d ", *(adressation_for_2d(arr, i, j)));
        putchar('\n');
        }
    return;
    }


/* Prints triangle array */
void print_triangle_arr(const int arr[], const size_t size_i)
    {
    assert(arr);

    for (size_t i = 0; i < size_i; i++)
        {
        for (size_t j = 0; j < i + 1; j++)
            printf("%i ", *(arr + int((i + 1) * i / 2) + j));
        putchar('\n');
        }
    return;
    }


/* Returns adress of arr[i][j] , where arr[0] & arr[1] - sizes of array*/
const int* adressation_for_2d(const int arr[], size_t i, size_t j)
    {
    assert(arr);
    assert(arr[0] > 0 && arr[1] > 0);
    return (arr + (int)i * arr[1] + j + 2);
    // return nullptr;
    }
