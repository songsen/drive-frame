
#include <stdint.h>
#include <stdio.h>

#define size_t long

#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({				\
	void *__mptr = (void *)(ptr);					\
	((type *)(__mptr - offsetof(type, member))); })

struct attribute {
    int attr;
};

struct test_kobj_attribute
{
    struct attribute attr;
    int value;
    int key;
};


int main()
{
    struct test_kobj_attribute *test_kobj_attr;
    struct test_kobj_attribute xxx;
    struct attribute *attr = &xxx.attr;
    test_kobj_attr = container_of(attr, struct test_kobj_attribute, attr);

    //int i = (int)({int x = 2; x-3;});

    // (struct test_kobj_attribute *)  (__mptr - ((int)&((struct test_kobj_attribute *)0)->attr));

    //printf("i = %d\n", i);
    printf("%lx\n", &xxx);
    printf("%lx\n", test_kobj_attr);
    return 0;
}