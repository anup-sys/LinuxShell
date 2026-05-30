#include "jobs.h"

int main(void)
{
    add_job(1234, "sleep");
    add_job(5678, "vim");

    list_jobs();

    return 0;
}