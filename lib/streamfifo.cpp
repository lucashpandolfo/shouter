/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "streamfifo.h"

#include "log.h"

#include <fcntl.h>
#include <unistd.h>

StreamFifo::StreamFifo(const char* fifo_name, const char* metadata_filename) {
    this->fifo_name = fifo_name;
    this-> metadata_filename = metadata_filename;
}

bool StreamFifo::initialize() {
    fifo = open(fifo_name.c_str(), O_RDONLY);
    log(0, "Could not open fifo " + fifo_name + " for reading");
    return fifo > 0;
}

size_t StreamFifo::get_data(char* buffer, size_t n) {
    return read(fifo, buffer, n);
}

StreamFifo::~StreamFifo() {
    if(fifo>0)
        close(fifo);
    fifo = -1;
}
