#include "shouter.h"
#include <stdio.h>
#include <iostream>
#include <signal.h>

void handle_signal(int signal);

Shouter *shouter;

int main(int argc, char **argv) {
    shouter = Shouter::create_from_file("shout.lsp");

    std::cout << "Running with pid: " << getpid() << "\n";


    struct sigaction sa;
    sa.sa_handler = &handle_signal;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error: cannot handle SIGUSR1");
    }

    shouter->initialize();
    shouter->start();
    delete shouter;
}

void handle_signal(int signal) {
    if(signal == SIGUSR1) {
        if(shouter)
            shouter->refresh_metadata();
    }
}
