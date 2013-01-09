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

#include "shouter.h"
#include <shout/shout.h>
#include "log.h"

#include "configurer.h"
#include <sourcefifo.h>

#include <string.h>

Shouter::Shouter() {
    mountpoint = "/stream.mp3";
    protocol = SHOUT_PROTOCOL_ICY;
    port = 8000;
    shout = NULL;
    source = NULL;
    format = SHOUT_FORMAT_MP3;
}

bool Shouter::initialize() {

    source->initialize();

    shout_init();

    if (!(shout = shout_new())) {
        printf("Could not allocate shout_t\n");
        return 0;
    }

    if (shout_set_host(shout, hostname.c_str()) != SHOUTERR_SUCCESS) {
        printf("Error setting hostname: %s\n", shout_get_error(shout));
        return 0;
    }

    if (shout_set_protocol(shout, protocol) != SHOUTERR_SUCCESS) {
        printf("Error setting protocol: %s\n", shout_get_error(shout));
        return 0;
    }

    if (shout_set_port(shout, port) != SHOUTERR_SUCCESS) {
        printf("Error setting port: %s\n", shout_get_error(shout));
        return 0;
    }

    if (shout_set_password(shout, password.c_str()) != SHOUTERR_SUCCESS) {
        printf("Error setting password: %s\n", shout_get_error(shout));
        return 0;
    }
    if (shout_set_mount(shout, mountpoint.c_str()) != SHOUTERR_SUCCESS) {
        printf("Error setting mount: %s\n", shout_get_error(shout));
        return 0;
    }

    if (shout_set_user(shout, user_name.c_str()) != SHOUTERR_SUCCESS) {
        printf("Error setting user: %s\n", shout_get_error(shout));
        return 0;
    }

    if (shout_set_format(shout, format) != SHOUTERR_SUCCESS) {
        printf("Error setting user: %s\n", shout_get_error(shout));
        return 0;
    }
}

void Shouter::start() {
    char buffer[4096];
    size_t read,ret;


    if (shout_open(shout) == SHOUTERR_SUCCESS) {
        printf("Connected to server...\n");
        while (1) {
            read = source->get_data(buffer, 4096);

            if (read > 0) {
                ret = shout_send(shout, (unsigned char*)buffer, read);
                if (ret != SHOUTERR_SUCCESS) {
                    printf("DEBUG: Send error: %s\n", shout_get_error(shout));
                    break;
                }
            } else {
                break;
            }

            shout_sync(shout);
        }
    } else {
        printf("Error connecting: %s\n", shout_get_error(shout));
    }
}

void Shouter::stop() {

}

Shouter::~Shouter() {
    shout_close(shout);
    shout_shutdown();

}


Shouter* Shouter::create_from_file(const char* filename) {
    Shouter *shouter = new Shouter();

    Configurer conf(filename);
    conf.parse();

    conf.read_string("stream/server/hostname", shouter->hostname);
    conf.read_string("stream/server/user", shouter->user_name);
    conf.read_string("stream/server/password", shouter->password);
    conf.read_string("stream/server/mountpoint", shouter->mountpoint);
    conf.read_int("stream/server/port", shouter->port);

    std::string proto;
    conf.read_string("stream/server/protocol", proto);

    if(proto.compare("icy") == 0)
        shouter->protocol = SHOUT_PROTOCOL_ICY;
    else if (proto.compare("http") == 0)
        shouter->protocol = SHOUT_PROTOCOL_HTTP;
    else if (proto.compare("xaudio") == 0)
        shouter->protocol = SHOUT_PROTOCOL_XAUDIOCAST;
    else {
        log(0,"Unknown protocol : " + proto);
        return NULL;
    }

    conf.read_string("stream/name", shouter->stream_name);
    conf.read_string("stream/genre", shouter->stream_genre);
    conf.read_string("stream/description", shouter->stream_description);
    conf.read_string("stream/url", shouter->stream_url);

    std::string format;
    conf.read_string("stream/format", format);

    if(format.compare("mp3")==0)
        shouter->format = SHOUT_FORMAT_MP3;
    else if(format.compare("ogg")==0) {
        shouter->format = SHOUT_FORMAT_VORBIS;
        std::cout << "FORMATO VORBIS\n";
    }
    else {
        log(0,"Unknown format : " + proto);
        return NULL;
    }

    //TODO: ADD source factory

    std::string source_type;
    conf.read_string("source/type", source_type);

    if(source_type.compare("fifo")!=0) {
        delete shouter;
        log(0,"Could not create a source: Source type not supported (" + source_type + ")");
        return NULL;
    }

    std::string fifo_file, meta_file;

    conf.read_string("source/fifo-name", fifo_file);
    conf.read_string("source/metadata-file", meta_file);

    SourceFifo *source = new SourceFifo(fifo_file, meta_file);

    shouter->source = source;
    return shouter;
}
