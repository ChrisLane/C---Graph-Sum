struct A {
    struct A *a, *b, *c;
    long n;
};

long sumA(struct A *node);

void deallocateA(struct A *node);