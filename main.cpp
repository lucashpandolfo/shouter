#include "shouter.h"


int main(int argc, char **argv) {

    Shouter *shouter;

    shouter = Shouter::create_from_file("shout.lsp");

    shouter->initialize();
    shouter->start();
    delete shouter;
}
