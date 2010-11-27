#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"

#include "ut_cstl_vector_aux.h"

/*
 * test _vector_iterator_belong_to_vector
 */
void test__vector_iterator_belong_to_vector__null_container_pointer(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    expect_assert_failure(_vector_iterator_belong_to_vector(NULL, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_container_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_iterator_type(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__invalid_iterator_different_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._pt_container = NULL;

    expect_assert_failure(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__less_than_begin(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);
    it_iter._t_pos._pc_corepos = NULL;

    assert_false(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__within_vector(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_begin(pvec);

    assert_true(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__end_iterator(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);

    assert_true(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

void test__vector_iterator_belong_to_vector__greater_than_end(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_iterator_t it_iter;

    vector_init_n(pvec, 10);
    it_iter = vector_end(pvec);
    it_iter._t_pos._pc_corepos += pvec->_t_typeinfo._pt_type->_t_typesize;

    assert_false(_vector_iterator_belong_to_vector(pvec, it_iter));

    vector_destroy(pvec);
}

