#include "basic_testing.h"
#include <cstdlib>
#include "../array.h"



TEST (compile) {
    TEST_PASSED;
}


TEST (no_budget_set) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    for (int i = 0; i < 100; ++i)
	CHECK (array_append (array, i));
 
    CHECK_CMP (array_length (array),==,100);
    CHECK_CMP (array_capacity (array),>=,100);

    for (int i = 0; i < 100; ++i)
	CHECK_CMP (array_element (array, i),==,i);
    
    array_free (array);
    TEST_PASSED;
}


TEST (zero_budget) {
    MEM_SET_BYTES_BUDGET (0);
    struct array * array = array_new ();
    CHECK (array == NULL);
    TEST_PASSED;
}


TEST (reset_after_budget) {
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (simple_budget) {
    MEM_SET_BYTES_BUDGET (sizeof (struct array));
    struct array * array = array_new ();
    CHECK (array != NULL);
    struct array * array2 = array_new ();
    CHECK (array2 == NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (free_increment_budget) {
    MEM_SET_BYTES_BUDGET (sizeof (struct array));
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    struct array * array2 = array_new ();
    CHECK (array2 != NULL);
    array_free (array2);
    TEST_PASSED;
}


TEST (budget_realloc_null) {
    MEM_SET_BYTES_BUDGET (sizeof (struct array));
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);
    
    array_free (array);
    TEST_PASSED;
}


TEST (reset_after_budget_realloc_null) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);
    
    array_free (array);
    TEST_PASSED;
}


TEST (budget_realloc) {
    MEM_SET_BYTES_BUDGET (sizeof (struct array) + 8*sizeof (int));
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);

    array_free (array);
    TEST_PASSED;
}


TEST (reset_after_budget_realloc) {
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,20);
    CHECK_CMP (array_capacity (array),==,32);

    array_free (array);
    TEST_PASSED;
}


TEST (malloc_budget_reset) {
    MEM_SET_BYTES_BUDGET (0);
    struct array * array = array_new ();
    CHECK (array == NULL);
    MEM_RESET_ALLOCATOR ();
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (realloc_null_budget_reset) {
    MEM_SET_BYTES_BUDGET (sizeof (struct array));
    struct array * array = array_new ();
    CHECK (array != NULL);

    for (int i = 0; i < 4; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);

    MEM_RESET_ALLOCATOR ();

    for (int i = 0; i < 4; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);

    array_free (array);
    TEST_PASSED;
}


TEST (realloc_budget_reset) {
    MEM_SET_BYTES_BUDGET (sizeof (struct array) + 8*sizeof (int));
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    
    for (int i = 4; i < 16; ++i)
	CHECK (!array_append (array, i));

    CHECK_CMP (array_length (array),==,8);
    CHECK_CMP (array_capacity (array),==,8);
    MEM_RESET_ALLOCATOR ();
    for (int i = 4; i < 16; ++i)
	CHECK (array_append (array, i));

    CHECK_CMP (array_length (array),==,20);
    CHECK_CMP (array_capacity (array),==,32);
    array_free (array);
    TEST_PASSED;
}


TEST (change_same_budget_malloc) {
    MEM_SET_BYTES_BUDGET (sizeof(struct array));
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_CHANGE_BYTES_BUDGET (sizeof(struct array));
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (change_higher_budget_malloc) {
    MEM_SET_BYTES_BUDGET (sizeof(struct array));
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_CHANGE_BYTES_BUDGET (sizeof(struct array) + 8*sizeof(int));
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    for (int i = 8; i < 16; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    MEM_CHANGE_BYTES_BUDGET (sizeof(struct array) + 16*sizeof(int));
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 16; ++i)
	CHECK (array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (change_lower_budget_malloc) {
    MEM_SET_BYTES_BUDGET (sizeof(struct array) + 32*sizeof(int));
    struct array * array = array_new ();
    MEM_CHANGE_BYTES_BUDGET (sizeof(struct array) + 8*sizeof(int));
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (!array_append (array, 9));
    MEM_CHANGE_BYTES_BUDGET (sizeof(struct array));
    for (int i = 8; i < 16; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (change_lower_budget_after_allocations_malloc) {
    MEM_SET_BYTES_BUDGET (sizeof(struct array) + 16*sizeof(int));
    struct array * array = array_new ();
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    MEM_CHANGE_BYTES_BUDGET (sizeof(struct array) + 8*sizeof(int));
    CHECK (!array_append (array, 17));
    array_free (array);
    TEST_PASSED;
}


TEST (set_same_budget_malloc) {
    MEM_SET_BYTES_BUDGET (sizeof(struct array));
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_SET_BYTES_BUDGET (sizeof(int)*8);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (set_higher_budget_malloc) {
    MEM_SET_BYTES_BUDGET (sizeof(struct array));
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_SET_BYTES_BUDGET (8*sizeof(int));
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    for (int i = 8; i < 16; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    MEM_SET_BYTES_BUDGET (sizeof(struct array) + 16*sizeof(int));
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 16; ++i)
	CHECK (array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (set_lower_budget_malloc) {
    MEM_SET_BYTES_BUDGET (sizeof(struct array) + 32*sizeof(int));
    struct array * array = array_new ();
    MEM_SET_BYTES_BUDGET (sizeof(struct array) + 8*sizeof(int));
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (!array_append (array, 9));
    MEM_SET_BYTES_BUDGET (sizeof(struct array));
    for (int i = 8; i < 16; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (set_lower_budget_after_allocations_malloc) {
    MEM_SET_BYTES_BUDGET (sizeof(struct array) + 16*sizeof(int));
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    MEM_SET_BYTES_BUDGET (sizeof(struct array));
    CHECK (!array_append (array, 17));
    array_free (array);
    array = array_new ();
    CHECK (array != NULL);
    CHECK (!array_append (array, 17));
    array_free (array);
    TEST_PASSED;
}


TEST (smaller_size_realloc) {
    MEM_SET_BYTES_BUDGET (8*sizeof (int));
    int * p = (int *) malloc (8*sizeof (int));
    CHECK (p != NULL);
    int * i = (int *) malloc (sizeof (int));
    CHECK (i == NULL);
    p = (int *) realloc (p, 4*sizeof (int));
    CHECK (p != NULL);
    i = (int *) malloc (sizeof (int));
    CHECK (i != NULL);
    free (p);
    free (i);
    TEST_PASSED;
}


TEST (zero_budget_calloc) {
    MEM_SET_BYTES_BUDGET (0);
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    TEST_PASSED;
}


TEST (simple_budget_calloc) {
    MEM_SET_BYTES_BUDGET (sizeof (struct array));
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    struct array * array2 = array_new_calloc ();
    CHECK (array2 == NULL);
    array2 = array_new ();
    CHECK (array2 == NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (reallocarray_budget) {
    MEM_SET_BYTES_BUDGET (sizeof (struct array));
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append_reallocarray (array, i));
    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);
    MEM_SET_BYTES_BUDGET (sizeof(struct array) + sizeof (int)*8);
    for (int i = 0; i < 4; ++i)
	CHECK (array_append_reallocarray (array, i));
    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);
    array_free (array);
    TEST_PASSED;
}


TEST (zero_budget_new) {
    MEM_SET_BYTES_BUDGET (0);
    try {
	array_cpp * array = array_cpp_new ();
	array_cpp_delete (array);
    } catch (const std::bad_alloc& e) {
	TEST_PASSED;
    }
    TEST_FAILED;
}


TEST (reset_after_budget_new) {
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    array_cpp_delete (array);
    TEST_PASSED;
}


TEST (simple_budget_new) {
    MEM_SET_BYTES_BUDGET (sizeof(array_cpp));
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	array_cpp * array2 = array_cpp_new ();
	array_cpp_delete (array2);
    } catch (const std::bad_alloc& e) {
	array_cpp_delete(array);
	TEST_PASSED;
    }
    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (delete_increment_budget) {
    MEM_SET_BYTES_BUDGET (sizeof(array_cpp));
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    array_cpp_delete (array);
    array_cpp * array2 = array_cpp_new ();
    CHECK (array2 != nullptr);
    array_cpp_delete (array2);
    TEST_PASSED;
}


TEST (new_budget_reset) {
    MEM_SET_BYTES_BUDGET (0);
    try {
	array_cpp *  array = array_cpp_new ();
	array_cpp_delete(array);
    } catch (const std::bad_alloc& e) {
	MEM_RESET_ALLOCATOR ();
	array_cpp * array = array_cpp_new ();
	CHECK (array != nullptr);
	array_cpp_delete (array);
	TEST_PASSED;
    }
    TEST_FAILED;
}


TEST (budget_new_array) {
    array_cpp array;
    MEM_SET_BYTES_BUDGET (array_cpp::initial_cap*sizeof(int));

    try {
	for (int i = 0; i < 100; ++i)
	    array.append (i);
    } catch (const std::bad_alloc& e) {
	CHECK_CMP (array.length (),==,array_cpp::initial_cap);
	CHECK_CMP (array.capacity (),==,array_cpp::initial_cap);
	TEST_PASSED;
    }

    TEST_FAILED;
}


TEST (reset_after_budget_new_array) {
    array_cpp array;

    CHECK_CMP (array.length (),==,0);
    CHECK_CMP (array.capacity (),==,0);

    for (int i = 0; i < 4; ++i)
	array.append (i);

    CHECK_CMP (array.length (),==,4);
    CHECK_CMP (array.capacity (),==,array_cpp::initial_cap);
    TEST_PASSED;
}


TEST (reset_budget_new_array) {
    MEM_SET_BYTES_BUDGET (0);
    array_cpp array;

    try {
	for (int i = 0; i < 4; ++i)
	    array.append (i);
    } catch (const std::bad_alloc& e) {
	CHECK_CMP (array.length (),==,0);
	CHECK_CMP (array.capacity (),==,0);

	MEM_RESET_ALLOCATOR ();
	for (int i = 0; i < 4; ++i)
	    array.append (i);

	CHECK_CMP (array.length (),==,4);
	CHECK_CMP (array.capacity (),==,array_cpp::initial_cap);
	TEST_PASSED;
    }

    TEST_FAILED;
}


TEST (change_same_budget_new) {
    MEM_SET_BYTES_BUDGET (sizeof(array_cpp));
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	array_cpp * array2 = array_cpp_new ();
	array_cpp_delete (array2);
    } catch (const std::bad_alloc& e) {
	MEM_CHANGE_BYTES_BUDGET (sizeof(array_cpp));
	try {
	    array_cpp * array2 = array_cpp_new ();
	    array_cpp_delete (array2);
	} catch (const std::bad_alloc& e) {
	    array_cpp_delete (array);
	    TEST_PASSED;
	}
    }

    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (change_same_budget_new_array) {
    MEM_SET_BYTES_BUDGET (array_cpp::initial_cap*sizeof(int));
    array_cpp array;
    for (int i = 0; i < 8; ++i)
	array.append (i);
    try {
	array.append (9);
    } catch (const std::bad_alloc& e) {
	MEM_CHANGE_BYTES_BUDGET (array_cpp::initial_cap*sizeof(int));
	try {
	    array.append (9);
	} catch (const std::bad_alloc& e) {
	    TEST_PASSED;
	}
    }

    TEST_FAILED;
}


TEST (change_higher_budget_new) {
    MEM_SET_BYTES_BUDGET (sizeof(array_cpp));
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	for (int i = 0; i < 8; ++i)
	    array->append (i);
    } catch (const std::bad_alloc& e) {
	MEM_CHANGE_BYTES_BUDGET (sizeof(array_cpp) + array_cpp::initial_cap*sizeof(int));
	for (int i = 0; i < 8; ++i)
	    array->append (i);
	try {
	    for (int i = 8; i < 16; ++i)
		array->append (i);
	} catch (const std::bad_alloc& e) {
	    array_cpp_delete (array);
	    MEM_CHANGE_BYTES_BUDGET (sizeof(array_cpp) + array_cpp::initial_cap*3*sizeof(int));
	    array = array_cpp_new ();
	    CHECK (array != nullptr);
	    for (int i = 0; i < 16; ++i)
		array->append (i);
	    array_cpp_delete (array);
	    TEST_PASSED;
	}
    }
    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (change_lower_budget_new) {
    MEM_SET_BYTES_BUDGET (sizeof(array_cpp) + 100*sizeof(int));
    array_cpp * array = array_cpp_new ();
    MEM_CHANGE_BYTES_BUDGET (sizeof(array_cpp) + 8*sizeof(int));
    for (int i = 0; i < 8; ++i)
	array->append (i);
    
    try {
	array->append (9);
    } catch (const std::bad_alloc& e) {
	MEM_CHANGE_BYTES_BUDGET (sizeof(array_cpp));

	try {
	    for (int i = 8; i < 16; ++i)
		array->append (i);
	} catch (const std::bad_alloc& e) {
	    array_cpp_delete (array);
	    array = array_cpp_new ();
	    CHECK (array != nullptr);

	    try {
		for (int i = 0; i < 8; ++i)
		    array->append (i);
	    } catch (const std::bad_alloc& e) {
		array_cpp_delete (array);
		TEST_PASSED;
	    }
	}
    }

    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (change_lower_budget_after_allocations_new) {
    MEM_SET_BYTES_BUDGET (sizeof(array_cpp) + 16*sizeof(int));
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    for (int i = 0; i < 8; ++i)
	array->append (i);
    MEM_CHANGE_BYTES_BUDGET (sizeof(array_cpp) + 8*sizeof(int));
    try {
	array->append (17);
    } catch(const std::bad_alloc& e) {
	array_cpp_delete (array);
	TEST_PASSED;
    }
    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (set_same_budget_new) {
    MEM_SET_BYTES_BUDGET (sizeof(array_cpp));
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	array_cpp * array2 = array_cpp_new ();
	array_cpp_delete (array2);
    } catch (const std::bad_alloc& e) {
	MEM_SET_BYTES_BUDGET (sizeof(array_cpp));
	array_cpp * array2 = array_cpp_new ();
	array_cpp_delete (array2);
	array_cpp_delete (array);
	TEST_PASSED;
    }

    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (set_same_budget_new_array) {
    MEM_SET_BYTES_BUDGET (array_cpp::initial_cap*sizeof(int));
    array_cpp array;
    for (int i = 0; i < 8; ++i)
	array.append (i);
    try {
	array.append (9);
    } catch (const std::bad_alloc& e) {
	MEM_SET_BYTES_BUDGET (array_cpp::initial_cap*sizeof(int));
	array_cpp array2;
	for (int i = 0; i < 8; ++i)
	    array2.append (i);
	try {
	    array2.append (9);
	} catch (const std::bad_alloc& e) {
	    TEST_PASSED;
	}
    }

    TEST_FAILED;
}


TEST (set_higher_budget_new) {
    MEM_SET_BYTES_BUDGET (sizeof(array_cpp));
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	for (int i = 0; i < 8; ++i)
	    array->append (i);
    } catch (const std::bad_alloc& e) {
	MEM_SET_BYTES_BUDGET (3*array_cpp::initial_cap*sizeof(int));
	for (int i = 0; i < 16; ++i)
	    array->append (i);

	array_cpp_delete (array);
	MEM_SET_BYTES_BUDGET (3*array_cpp::initial_cap*sizeof(int)+sizeof(array_cpp));
	array = array_cpp_new ();
	CHECK (array != nullptr);
	for (int i = 0; i < 16; ++i)
	    array->append (i);
	array_cpp_delete (array);
	TEST_PASSED;
    }
    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (set_lower_budget_new) {
    MEM_SET_BYTES_BUDGET (4*array_cpp::initial_cap*sizeof(int)+sizeof(array_cpp));
    array_cpp * array = array_cpp_new ();
    MEM_SET_BYTES_BUDGET (array_cpp::initial_cap*sizeof(int));
    for (int i = 0; i < 8; ++i)
	array->append (i);
    try {
	array->append (9);
    } catch (const std::bad_alloc& e) {
	array_cpp_delete (array);
	array = array_cpp_new ();
	CHECK (array != nullptr);

	try {
	    for (int i = 0; i < 8; ++i)
		array->append (i);
	} catch (const std::bad_alloc& e) {
	    array_cpp_delete (array);
	    TEST_PASSED;
	}
    }

    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (set_lower_budget_after_allocations_new) {
    MEM_SET_BYTES_BUDGET (array_cpp::initial_cap*sizeof(int)+sizeof(array_cpp));
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    for (int i = 0; i < 8; ++i)
	array->append (i);
    try {
	array->append (16);
    } catch(const std::bad_alloc& e) {
	MEM_SET_BYTES_BUDGET (2*array_cpp::initial_cap*sizeof(int));
	for (int i = 8; i < 16; ++i)
	    array->append (i);
	array_cpp_delete (array);
	TEST_PASSED;
    }
    array_cpp_delete (array);
    TEST_FAILED;
}



MAIN_TEST_DRIVER ();
