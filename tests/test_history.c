#include "history.h"

int main(void)
{
    add_to_history("pwd\n");
    add_to_history("ls\n");
    add_to_history("history\n");

    show_history();

    return 0;
}