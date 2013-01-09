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

#include <fcntl.h>
#include <unistd.h>

#include "sexp.h"
#include "sexp_ops.h"

#include <string.h>


Shouter::Shouter() {
    mountpoint = "/stream.mp3";
    protocol = SHOUT_PROTOCOL_ICY;
    port = 8000;
    shout = NULL;
    stream = NULL;
    format = SHOUT_FORMAT_MP3;
}

bool Shouter::initialize() {
    if (!(shout = shout_new())) {
        log(0, "Could not allocate shout_t");
        return 0;
    }
    return connect();
}

void Shouter::start() {
    stop_requested = false;
    if (shout_open(shout) == SHOUTERR_SUCCESS) {
        log(0,"Connected to server...");

        size_t read=0;
        char buffer[4096];

        while (!stop_requested) {
            read = stream->get_data(buffer,4096);

            if (read > 0) {

                if (shout_send(shout, (unsigned char *)buffer, read) != SHOUTERR_SUCCESS) {
                    log(0, "DEBUG: Send error: " + std::string(shout_get_error(shout)));
                    break;
                }
            } else {
                log(0, "No data read");
                break;
            }

            shout_sync(shout);
        }
    } else {
        log(0,"Error connecting: " + std::string(shout_get_error(shout)));
    }
}

void Shouter::stop() {
    stop_requested = true;
    log(0, "Requesting stop.....");
}

Shouter::~Shouter() {
    stop();
    shout_shutdown();
}


bool Shouter::connect() {
    if (shout_set_protocol(shout, protocol) != SHOUTERR_SUCCESS) {
        log(0, "Error setting protocol: " +  std::string(shout_get_error(shout)));
        return 0;
    }
    if (shout_set_port(shout, port) != SHOUTERR_SUCCESS) {
        log(0,"Error setting port: %s\n" + std::string(shout_get_error(shout)));
        return 0;
    }

    if (shout_set_password(shout, password.c_str()) != SHOUTERR_SUCCESS) {
        log(0,"Error setting password: " + std::string(shout_get_error(shout)));
        return 0;
    }
    if (shout_set_mount(shout, mountpoint.c_str()) != SHOUTERR_SUCCESS) {
        log(0,"Error setting mount: " + std::string(shout_get_error(shout)));
        return 0;
    }

    if (shout_set_user(shout, user_name.c_str()) != SHOUTERR_SUCCESS) {
        log(0,"Error setting user: " + std::string(shout_get_error(shout)));
        return 0;
    }

    if (shout_set_format(shout, format) != SHOUTERR_SUCCESS) {
        log(0,"Error setting user: " + std::string(shout_get_error(shout)));
        return 0;
    }
    return 1;
}


static bool listp(sexp_t* sx) {
    return (sx && (sx->ty == SEXP_LIST));
}

static bool null(sexp_t* sx) {
    return sx==NULL;
}

void read_config_string(sexp_t* sx, const char* name, std::string &variable){
     sexp_t* var = bfs_find_sexp(name,sx);
     if(var)
	variable = var->val;
}

void read_config_int(sexp_t* sx, const char* name, int &variable){
     sexp_t* var = bfs_find_sexp(name,sx);
     if(var)
	variable = atoi(var->val);
}


Shouter* Shouter::create_from_file(const char* filename) {
    int fd;
    sexp_t *sx, *param;
    sexp_iowrap_t *iow;

    Shouter *shouter = new Shouter();
    
    fd = open(filename,O_RDONLY);
    iow = init_iowrap(fd);

    while(!null(sx = read_one_sexp(iow))) {
        if(listp(sx) && sx->list->val) {
	    if(strcmp("server",sx->list->val)==0){
	      sexp_t* server = sx->list;

	      read_config_string(server, "user", shouter->user_name);
	      read_config_string(server, "password", shouter->password);
	      read_config_string(server, "hostname", shouter->hostname);
	      read_config_string(server, "mountpoint", shouter->mountpoint);
	      read_config_int(server, "port", shouter->port);
	    }
        }
    }

    destroy_sexp(sx);
    destroy_iowrap(iow);
    
    return shouter;
}
