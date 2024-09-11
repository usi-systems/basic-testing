#include "array.h"
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <vector>

static size_t initial_cap = 8;

static std::vector<int> vec;
static std::vector<int *> vec_ptr;

struct array * array_new (void) {
    struct array * a = (struct array *) std::malloc(sizeof(struct array));
    if (!a) return NULL;

    a->data = NULL;
    a->len = 0;
    a->cap = 0;
    return a;
}

struct array * array_new_calloc (void) {
    return (struct array *) std::calloc(1, sizeof(struct array));
}

void array_free (struct array * array) {
    if (array->cap) std::free(array->data);
    std::free(array);
}

void array_free_leak (struct array * array) {
    std::free(array);
}

size_t array_length (struct array * array) {
    return array->len;
}

size_t array_capacity (struct array * array) {
    return array->cap;
}

int array_element (struct array * array, size_t index) {
    return array->data[index];
}

int array_append (struct array * array, int element) {
    if (array->len == array->cap) {
	size_t new_cap = array->cap ? 2*array->cap : initial_cap;

	int * new_data = (int *) std::realloc(array->data, new_cap*sizeof(int));
	if (!new_data) return 0;

	array->data = new_data;
	array->cap = new_cap;
    }

    array->data[array->len++] = element;
    return 1;
}

int array_append_reallocarray (struct array * array, int element) {
    if (array->len == array->cap) {
	size_t new_cap = array->cap ? 2*array->cap : initial_cap;

#ifdef __APPLE__
	int * new_data = (int *) realloc (array->data, new_cap*sizeof(int));
#else
	int * new_data = (int *) reallocarray (array->data, new_cap, sizeof(int));
#endif
	if (!new_data) return 0;

	array->data = new_data;
	array->cap = new_cap;
    }

    array->data[array->len++] = element;
    return 1;
}

array_cpp::array_cpp () : data{nullptr}, len{0}, cap{0} {}

array_cpp::~array_cpp () {
    if (data) delete[] data;
}

void array_cpp::append (int value) {
    if (len == cap) {
	size_t new_cap = cap ? 2*cap : initial_cap;
	int * new_data = new int[new_cap];
	std::copy_n (data, cap, new_data);
	if (data) delete[] data;
	data = new_data;
	cap = new_cap;
    }

    data[len++] = value;
}

array_cpp * array_cpp_new (void) {
    return new array_cpp {};
}

void array_cpp_delete (array_cpp *array) {
    delete array;
}

void double_free (void) {
    int a = 10;
    void * p = std::malloc (10);
    if (a < 20) std::free (p);
    std::free (p);
}

void double_delete (void) {
    int a = 10;
    int * p = new int {10};
    if (a < 20) delete p;
    delete p;
}

void double_delete_array (void) {
    int a = 10;
    int * p = new int[10];
    if (a < 20) delete[] p;
    delete[] p;
}

void non_malloc_free (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20) p = &a;
    std::free (p);
}

void non_new_delete (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20) p = &a;
    delete p;
}

void non_new_array_delete (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20) p = &a;
    delete[] p;

}

void * malloc_zero_size (void) {
    return std::malloc (0);
}

void * realloc_zero_size (void * ptr) {
    return std::realloc (ptr, 0);
}

void new_object_free (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20)
	p = new int{10};
    std::free (p);
}

void new_array_object_free (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20)
	p = new int[10];
    std::free(p);
}

void malloc_object_delete (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20)
	p = (int *) std::malloc (sizeof(int));
    delete p;
}

void new_array_object_delete (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20)
	p = new int[10];
    delete p;
}

void malloc_object_delete_array (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20)
	p = (int *) std::malloc (sizeof(int));
    delete[] p;
}

void new_object_delete_array (void) {
    int a = 10;
    int * p = nullptr;
    if (a < 20)
	p = new int {10};
    delete[] p;
}

void populate_static_vector (void) {
    for (int i = 0; i < 1000; ++i)
	vec.push_back (i);
}

void clear_static_vector (void) {
    vec.clear ();
}

void populate_static_vector_ptr (void) {
    for (int i = 0; i < 1000; ++i)
	vec_ptr.push_back (new int {i});
}

void clear_static_vector_ptr (void) {
    for (auto p : vec_ptr)
	delete p;
    vec_ptr.clear ();
}
