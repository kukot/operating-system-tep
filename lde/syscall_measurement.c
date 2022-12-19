#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    long secs = 0;
    long micro_sec = 0;
    struct timeval this_call;

    struct timeval first_call_time;
    struct timeval second_call_time;

    gettimeofday(&first_call_time, NULL);
    for (int i = 0; i < 1000000000; ++i) {
        gettimeofday(&this_call, NULL);
        secs += this_call.tv_sec;
        micro_sec += this_call.tv_usec;
    }
    gettimeofday(&second_call_time, NULL);
    printf("Total time to run 1 billion syscall = %ld secs & %d micro secs", second_call_time.tv_sec - first_call_time.tv_sec, second_call_time.tv_usec - first_call_time.tv_usec);
    return 0;
}