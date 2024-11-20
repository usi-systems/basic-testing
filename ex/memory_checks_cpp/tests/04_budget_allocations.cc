#include "basic_testing.h"
#include "../array.h"
#include <new>



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
    MEM_SET_ALLOCATION_BUDGET (0);
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
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    struct array * array2 = array_new ();
    CHECK (array2 == NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (free_increment_budget) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    struct array * array2 = array_new ();
    CHECK (array2 != NULL);
    array_free (array2);
    TEST_PASSED;
}


TEST (budget_realloc_null) {
    MEM_SET_ALLOCATION_BUDGET (1);
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
    MEM_SET_ALLOCATION_BUDGET (2);
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
    MEM_SET_ALLOCATION_BUDGET (0);
    struct array * array = array_new ();
    CHECK (array == NULL);
    MEM_RESET_ALLOCATOR ();
    array = array_new ();
    CHECK (array != NULL);
    array_free (array);
    TEST_PASSED;
}


TEST (realloc_null_budget_reset) {
    MEM_SET_ALLOCATION_BUDGET (1);
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
    MEM_SET_ALLOCATION_BUDGET (2);
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
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_CHANGE_ALLOCATION_BUDGET (1);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (change_higher_budget_malloc) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_CHANGE_ALLOCATION_BUDGET (2);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    for (int i = 8; i < 16; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    MEM_CHANGE_ALLOCATION_BUDGET (3);
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 16; ++i)
	CHECK (array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (change_lower_budget_malloc) {
    MEM_SET_ALLOCATION_BUDGET (4);
    struct array * array = array_new ();
    MEM_CHANGE_ALLOCATION_BUDGET (2);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (!array_append (array, 9));
    MEM_CHANGE_ALLOCATION_BUDGET (1);
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
    MEM_SET_ALLOCATION_BUDGET (3);
    struct array * array = array_new ();
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    MEM_CHANGE_ALLOCATION_BUDGET (2);
    CHECK (!array_append (array, 17));
    array_free (array);
    TEST_PASSED;
}


TEST (set_same_budget) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_SET_ALLOCATION_BUDGET (1);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (set_higher_budget_malloc) {
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    MEM_SET_ALLOCATION_BUDGET (2);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    for (int i = 8; i < 16; ++i)
	CHECK (array_append (array, i));
    array_free (array);
    MEM_SET_ALLOCATION_BUDGET (3);
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 16; ++i)
	CHECK (array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (set_lower_budget_malloc) {
    MEM_SET_ALLOCATION_BUDGET (4);
    struct array * array = array_new ();
    MEM_SET_ALLOCATION_BUDGET (1);
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    CHECK (!array_append (array, 9));
    array_free (array);
    array = array_new ();
    CHECK (array != NULL);
    for (int i = 0; i < 8; ++i)
	CHECK (!array_append (array, i));
    array_free (array);
    TEST_PASSED;
}


TEST (set_lower_budget_after_allocations_malloc) {
    MEM_SET_ALLOCATION_BUDGET (3);
    struct array * array = array_new ();
    for (int i = 0; i < 8; ++i)
	CHECK (array_append (array, i));
    MEM_SET_ALLOCATION_BUDGET (1);
    for (int i = 8; i < 16; ++i)
	CHECK (array_append (array, i));
    CHECK (!array_append (array, 16));
    array_free (array);
    TEST_PASSED;
}


TEST (zero_budget_calloc) {
    MEM_SET_ALLOCATION_BUDGET (0);
    struct array * array = array_new_calloc ();
    CHECK (array == NULL);
    TEST_PASSED;
}


TEST (simple_budget_calloc) {
    MEM_SET_ALLOCATION_BUDGET (1);
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
    MEM_SET_ALLOCATION_BUDGET (1);
    struct array * array = array_new_calloc ();
    CHECK (array != NULL);
    for (int i = 0; i < 4; ++i)
	CHECK (!array_append_reallocarray (array, i));
    CHECK_CMP (array_length (array),==,0);
    CHECK_CMP (array_capacity (array),==,0);
    MEM_SET_ALLOCATION_BUDGET (2);
    for (int i = 0; i < 4; ++i)
	CHECK (array_append_reallocarray (array, i));
    CHECK_CMP (array_length (array),==,4);
    CHECK_CMP (array_capacity (array),==,8);
    array_free (array);
    TEST_PASSED;
}


TEST (zero_budget_new) {
    MEM_SET_ALLOCATION_BUDGET (0);
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
    MEM_SET_ALLOCATION_BUDGET (1);
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
    MEM_SET_ALLOCATION_BUDGET (1);
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    array_cpp_delete (array);
    array_cpp * array2 = array_cpp_new ();
    CHECK (array2 != nullptr);
    array_cpp_delete (array2);
    TEST_PASSED;
}


TEST (new_budget_reset) {
    MEM_SET_ALLOCATION_BUDGET (0);

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
    MEM_SET_ALLOCATION_BUDGET (1);

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
    MEM_SET_ALLOCATION_BUDGET (0);
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
    MEM_SET_ALLOCATION_BUDGET (1);
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	array_cpp * array2 = array_cpp_new ();
	array_cpp_delete (array2);
    } catch (const std::bad_alloc& e) {
	MEM_CHANGE_ALLOCATION_BUDGET (1);
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
    MEM_SET_ALLOCATION_BUDGET (1);
    array_cpp array;
    for (int i = 0; i < 8; ++i)
	array.append (i);
    try {
	array.append (9);
    } catch (const std::bad_alloc& e) {
	MEM_CHANGE_ALLOCATION_BUDGET (1);
	try {
	    array.append (9);
	} catch (const std::bad_alloc& e) {
	    TEST_PASSED;
	}
    }

    TEST_FAILED;
}


TEST (change_higher_budget_new) {
    MEM_SET_ALLOCATION_BUDGET (1);
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	for (int i = 0; i < 8; ++i)
	    array->append (i);
    } catch (const std::bad_alloc& e) {
	MEM_CHANGE_ALLOCATION_BUDGET (2);
	for (int i = 0; i < 8; ++i)
	    array->append (i);
	try {
	    for (int i = 8; i < 16; ++i)
		array->append (i);
	} catch (const std::bad_alloc& e) {
	    array_cpp_delete (array);
	    MEM_CHANGE_ALLOCATION_BUDGET (3);
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
    MEM_SET_ALLOCATION_BUDGET (4);
    array_cpp * array = array_cpp_new ();
    MEM_CHANGE_ALLOCATION_BUDGET (2);
    for (int i = 0; i < 8; ++i)
	array->append (i);
    try {
	array->append (9);
    } catch (const std::bad_alloc& e) {
	MEM_CHANGE_ALLOCATION_BUDGET (1);

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
    MEM_SET_ALLOCATION_BUDGET (3);
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    for (int i = 0; i < 8; ++i)
	array->append (i);
    MEM_CHANGE_ALLOCATION_BUDGET (2);

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
    MEM_SET_ALLOCATION_BUDGET (1);
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	array_cpp * array2 = array_cpp_new ();
	array_cpp_delete (array2);
    } catch (const std::bad_alloc& e) {
	MEM_SET_ALLOCATION_BUDGET (1);
	array_cpp * array2 = array_cpp_new ();
	array_cpp_delete (array2);
	array_cpp_delete (array);
	TEST_PASSED;
    }

    array_cpp_delete (array);
    TEST_FAILED;
}


TEST (set_same_budget_new_array) {
    MEM_SET_ALLOCATION_BUDGET (1);
    array_cpp array;
    for (int i = 0; i < 8; ++i)
	array.append (i);
    try {
	array.append (9);
    } catch (const std::bad_alloc& e) {
	MEM_SET_ALLOCATION_BUDGET (1);
	array.append (9);
	TEST_PASSED;
    }

    TEST_FAILED;
}


TEST (set_higher_budget_new) {
    MEM_SET_ALLOCATION_BUDGET (1);
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    try {
	for (int i = 0; i < 8; ++i)
	    array->append (i);
    } catch (const std::bad_alloc& e) {
	MEM_SET_ALLOCATION_BUDGET (2);
	for (int i = 0; i < 16; ++i)
	    array->append (i);

	array_cpp_delete (array);
	MEM_SET_ALLOCATION_BUDGET (3);
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
    MEM_SET_ALLOCATION_BUDGET (4);
    array_cpp * array = array_cpp_new ();
    MEM_SET_ALLOCATION_BUDGET (1);
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
    MEM_SET_ALLOCATION_BUDGET (2);
    array_cpp * array = array_cpp_new ();
    CHECK (array != nullptr);
    for (int i = 0; i < 8; ++i)
	array->append (i);
    try {
	array->append (16);
    } catch(const std::bad_alloc& e) {
	MEM_SET_ALLOCATION_BUDGET (1);
	for (int i = 8; i < 16; ++i)
	    array->append (i);
	array_cpp_delete (array);
	TEST_PASSED;
    }
    array_cpp_delete (array);
    TEST_FAILED;
}




MAIN_TEST_DRIVER ();
