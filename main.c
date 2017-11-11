//
// Created by direnol on 11.11.17.
//

#include "window.h"
int main(int argc, char **argv)
{
    if (init()) {
        return err_destruct("init");
    }


    getch();
    desturct();
    return EXIT_SUCCESS;
}