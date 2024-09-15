#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <cstddef>

struct array {
    int * data;
    size_t len;
    size_t cap;
};

struct array * array_new(void);
struct array * array_new_calloc(void);
void array_free(struct array * array);
void array_free_leak(struct array * array);
size_t array_length(struct array * array);
size_t array_capacity(struct array * array);
int array_element(struct array * array, size_t index);
int array_append(struct array * array, int value);
int array_append_reallocarray(struct array * array, int value);

void * wrapped_reallocarray (void * ptr, size_t nmemb, size_t size);

class array_cpp {    
public:
    array_cpp ();
    ~array_cpp ();
    void append (int value);

    const size_t length (void) const { return len; }
    const size_t capacity (void) const { return cap; }
    const int * get_data (void) const { return data; }
    int operator [](int i) const { return data[i]; }

    const static size_t initial_cap = 8;
private:
    int * data;
    size_t len;
    size_t cap;
};

array_cpp * array_cpp_new (void);
void array_cpp_delete (array_cpp *array);

void double_free (void);
void double_delete (void);
void double_delete_array (void);

void non_malloc_free (void);
void non_new_delete (void);
void non_new_array_delete (void);

void * malloc_zero_size (void);
void * realloc_zero_size (void * ptr);


void new_object_free (void);
void new_array_object_free (void);


void malloc_object_delete (void);
void new_array_object_delete (void);

void malloc_object_delete_array (void);
void new_object_delete_array (void);


void populate_static_vector (void);
void clear_static_vector (void);
void populate_static_vector_ptr (void);
void clear_static_vector_ptr (void);

#endif
