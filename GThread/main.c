#include <glib.h>
#include <stdio.h>

void *
thread_func(gpointer data)
{
    int i = 0;
    for (i = 0; i < 20; i++) {
        printf("number %d thread %d\n", i, *((int*)data));
    }
    return NULL;
}

int
main()
{
    GThread *thread1, *thread2;
    int t1 = 1;
    int t2 = 2;

    thread1 = g_thread_new("1", thread_func, (gpointer)&t1);
    thread2 = g_thread_new("2", thread_func, (gpointer)&t2);

    g_thread_join(thread1);
    g_thread_join(thread2);
    return 0;
}
