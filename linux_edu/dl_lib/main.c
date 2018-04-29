#include <stdio.h>

void (*func1)(void);

int main()
{
    void *ctx = dlopen("./libdllib.so", RTLD_LAZY);
    func1 = dlsym(ctx, "func1");
    
    func1();
    
    return 0;
}
