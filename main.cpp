#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

const char FILENAME[] = "onegin.txt";

char* read_file(const char filename[], const size_t fsize);
size_t get_file_size(const char filename[]);
int compare1(const char* a, const char* b);
int compare2(const char* a, const char* b);
void switch_p(char** a, char** b);
void fill_arr(char* all[], char* buf, const size_t fsize);
unsigned int get_line_count(char* buf, const size_t fsize);
void my_sort(char* all[], int left, int right, int (*compare)(const char*, const char*));

int main()
    {
    const size_t fsize = get_file_size(FILENAME) + 1;
    char* buf = read_file(FILENAME, fsize);
    int counter = (int)get_line_count(buf, fsize) - 1;

    char* all[(long unsigned int)counter] = {};
    fill_arr(all, buf, fsize);

    my_sort(all, 0, counter - 1, compare1);
    FILE* fp = fopen("result1.txt", "w");
    for (long int i = 0; i < counter; i++)
        fprintf(fp, "%s\n", all[i]);

    my_sort(all, 0, counter - 1, compare2);
    FILE* f2p = fopen("result2.txt", "w");
    for (long int i = 0; i < counter; i++)
        fprintf(f2p, "%s\n", all[i]);

    free(buf);
    return 0;
    }

size_t get_file_size(const char filename[])
    {
    assert(filename);
    struct stat fst = {};
    stat(filename, &fst);
    return (size_t)fst.st_size;
    }

char* read_file(const char filename[], const size_t fsize)
    {
    assert(filename && fsize);
    FILE* fp = nullptr;
    assert(fp = fopen(filename, "r"));
    void* buf = calloc(fsize, sizeof(char));
    fread(buf, sizeof(char), fsize + 1, fp);
    fclose(fp);
    return (char*)buf;
    }

unsigned int get_line_count(char* buf, const size_t fsize)
    {
    assert(buf && fsize);
        char* i = buf;
    unsigned int counter = 1;
    for ( ;i < buf + fsize && *i != EOF; i++)
        if (*i == '\n' || *i == '\r')
            {
            *i = '\0';
            if (*(i + 1) != '\n' && *(i + 1) != '\r')
                counter += 1;
            }
    return counter;
    }

void fill_arr(char* all[], char* buf, const size_t fsize)
    {
    assert(all && buf);
    all[0] = buf;
    int j = 1;
    for (char* i = buf; i < buf + fsize - 1 && *i != EOF; i++)
        if (*i == '\0' && *(i + 1) != '\0')
            all[j++] = i + 1;
    return;
    }

int compare1(const char* a, const char* b)
    {
    assert(a && b);
    int i = 0;
    for (i = 0; a[i] && b[i]; i++)
        {
        if (a[i] < b[i]) return 1;
        else if (a[i] > b[i]) return -1;
        }
    if (a[i] < b[i]) return 1;
    else if (a[i] > b[i]) return -1;
    return 0;
    }

int compare2(const char* a, const char* b)
    {
    assert(a && b);
    int i = 0, j = 0;
    for (i = 0; a[i]; i++);
    for (j = 0; b[j]; j++);
    for ( ;i >= 0 && j >= 0; i--, j--)
        {
        while (!(65 <= a[i] && a[i] <= 122)) i--;
        while (!(65 <= b[j] && b[j] <= 122)) j--;
        if (a[i] < b[j]) return 1;
        else if (a[i] > b[i]) return -1;
        }


    if (i == -1 && j != -1) return 1;
    else if (i != -1 && j == -1) return -1;
    return 0;
    }

void my_sort(char* all[], int left, int right, int (*compare)(const char*, const char*))
    {
    assert(all);
    int start = left, end = right;
    if (right - left <= 0) return;
    if (right - left == 1 && (*compare)(all[right], all[left]) != 1) return;
    if (right - left == 1 && (*compare)(all[right], all[left]) == 1) return switch_p(&all[right], &all[left]);
    left++;
    char* mid = all[start];
    while(left < right)
        {
        for ( ; (*compare)(all[right], mid) != 1 && right >= left; right--);
        for ( ; (*compare)(all[left], mid) != -1 && left <= right ; left++);
        if (right > left) switch_p(&all[left], &all[right]);
        }
    if ((*compare)(all[right], all[start]) == 1) switch_p(&all[right], &all[start]);
    if (right <= left) return my_sort(all, start, right - 1, *compare), my_sort(all, right + 1, end, *compare);
    }

void switch_p(char** a, char** b)
    {
    char* t = *a;
    *a = *b;
    *b = t;
    return;
    }
