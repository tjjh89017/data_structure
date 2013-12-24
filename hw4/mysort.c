#include <stdio.h>
#include <stdlib.h>

#include "mysort.h"

#define SWAP(a, b, size) \
{ \
	int _size = (size); \
	char *_a = (a), *_b = (b); \
	char _tmp; \
	while(_size--){ \
		_tmp = *_a; \
		*_a++ = *_b; \
		*_b++ = _tmp; \
	} \
}

void myheapsort(void *array_base, int len, int size, int (*cmp)(const void*, const void*))
{
	char *array = array_base;
	int i = 0;
	int son = 0;
	int parent = 0;
	char *s_ptr = NULL;
	char *p_ptr = NULL;

	for(i = 0; i < len; i++){
		son = i;
		parent = (son - 1) / 2;
		s_ptr = &array[son * size];
		p_ptr = &array[parent * size];
		while(parent >= 0 && (*cmp)((void*)s_ptr, (void*)p_ptr) > 0){
			SWAP(s_ptr, p_ptr, size);
			son = parent;
			parent = (son - 1) / 2;
			s_ptr = &array[son * size];
			p_ptr = &array[parent * size];
		}
	}

	parent = 0;
	son = parent * 2 + 1;
	p_ptr = &array[parent * size];
	s_ptr = &array[son * size];
	while(len > 0){
		SWAP(s_ptr, p_ptr, size);
		len--;
		parent = 0;
		son = parent * 2 + 1;
		p_ptr = &array[parent * size];
		s_ptr = &array[son * size];
		while(son < len){
			if(son < len - 1 && (*cmp)((void*)s_ptr, (void*)(s_ptr + size)) < 0){
				son++;
				s_ptr = &array[son * size];
			}
			if((*cmp)((void*)p_ptr, (void*)s_ptr) >= 0)
				break;
			SWAP(p_ptr, s_ptr, size);
			parent = son;
			son = parent * 2 + 1;
			p_ptr = &array[parent * size];
			s_ptr = &array[son * size];
		}
	}
}
