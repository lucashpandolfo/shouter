
#include <shout/shout.h>
#include "stream.h"

#include <string>
#include <iostream>

#include "shouter.h"

int main(int argc, char **argv) {
    Shouter *shouter;
    shouter = Shouter::create_from_file("shout.lsp");
}
