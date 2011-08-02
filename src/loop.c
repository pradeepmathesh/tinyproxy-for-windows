#include "tinyproxy.h"

#include "loop.h"
#include "daemon.h"
#include "filter.h"
#include "heap.h"
#include "log.h"
#include "reqs.h"
#include "sock.h"
#include "utils.h"

static int listenfd;
static socklen_t addrlen;

int child_listen(uint16_t port)
{
	listenfd = listen_sock(port, &addrlen);
	return listenfd;
}


void child_main()
{
	int connfd;
	struct sockaddr *cliaddr;
	socklen_t clilen;

	cliaddr = (struct sockaddr*)safemalloc(addrlen);
	if (!cliaddr) {
		log_message(LOG_CRIT,
			    "Could not allocate memory for child address.");
		exit(0);
	}

	//ptr->connects = 0;

	while (!config.quit) {
	//ptr->status = T_WAITING; 
		

		clilen = addrlen;

		connfd = accept(listenfd, cliaddr, &clilen);

#ifndef NDEBUG
		/*
		 * Enable the TINYPROXY_DEBUG environment variable if you
		 * want to use the GDB debugger.
		 */
/* 		if (getenv("TINYPROXY_DEBUG")) {
			//Pause for 10 seconds to allow us to connect debugger 
			fprintf(stderr,
				"Process has accepted connection: %u\n", ptr->tid);
			sleep(10);
			fprintf(stderr, "Continuing process: %u\n", ptr->tid);
		} */
#endif

		/*
		 * Make sure no error occurred...
		 */
		if (connfd < 0) {
			log_message(LOG_ERR, "Accept returned an error (%s) ... retrying.", strerror(errno));
			continue;
		}

		//ptr->status = T_CONNECTED;

		//SERVER_DEC();

		handle_connection(connfd);
		//ptr->connects++;

/* 		if (child_config.maxrequestsperchild != 0) {
			DEBUG2("%u connections so far...", ptr->connects);

			if (ptr->connects == child_config.maxrequestsperchild) {
				log_message(LOG_NOTICE,
					    "Child has reached MaxRequestsPerChild (%u). Killing child.",
					    ptr->connects);
				break;
			}
		}

		//SERVER_COUNT_LOCK();
		if (*servers_waiting > child_config.maxspareservers) { */
			/*
			 * There are too many spare children, kill ourself
			 * off.
			 */
/* 			log_message(LOG_NOTICE,
				    "Waiting servers (%d) exceeds MaxSpareServers (%d). Killing child.",
				    *servers_waiting, child_config.maxspareservers);
			SERVER_COUNT_UNLOCK();

			break;
		} else {
			SERVER_COUNT_UNLOCK();
		}

		SERVER_INC(); */
	}

	//ptr->status = T_EMPTY;

	safefree(cliaddr);
	exit(0);
}

short int
child_configure(child_config_t type, unsigned int val)
{
/* 	switch (type) {
	case CHILD_MAXCLIENTS:
		child_config.maxclients = val;
		break;
	case CHILD_MAXSPARESERVERS:
		child_config.maxspareservers = val;
		break;
	case CHILD_MINSPARESERVERS:
		child_config.minspareservers = val;
		break;
	case CHILD_STARTSERVERS:
		child_config.startservers = val;
		break;
	case CHILD_MAXREQUESTSPERCHILD:
		child_config.maxrequestsperchild = val;
		break;
	default:
		DEBUG2("Invalid type (%d)", type);
		return -1;
	} */

	return 0;
}


