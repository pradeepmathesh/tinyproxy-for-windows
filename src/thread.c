VOID Thread (PVOID pvoid)
{
	listenfd = listen_sock(port, &addrlen);
	close(listenfd);
	//return listenfd;
}

DWORD WINAPI ThreadFunc( LPVOID lpParam )  
{ 
    char szMsg[80];

    wsprintf( szMsg, "ThreadFunc: Parameter = %d\n", *lpParam ); 
    MessageBox( NULL, szMsg, "Thread created.", MB_OK );

    return 0; 
} 
 
VOID main( VOID ) 
{ 
    DWORD dwThreadId, dwThrdParam = 1; 
    HANDLE hThread; 
    hThread = CreateThread( 
        NULL,                        // no security attributes 
        0,                           // use default stack size  
        ThreadFunc,                  // thread function 

        &dwThrdParam,                // argument to thread function 
        0,                           // use default creation flags 
        &dwThreadId);                // returns the thread identifier 
 
   // Check the return value for success. 
 
   if (hThread == NULL) 
      ErrorExit( "CreateThread failed." ); 

   CloseHandle( hThread );
} 
 
void main( VOID )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
 
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);

    // Start the child process. 
    if( !CreateProcess( NULL, // No module name (use command line). 
        "MyChildProcess", // Command line. 
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        0,                // No creation flags. 

        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
        ErrorExit( "CreateProcess failed." );

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );

    CloseHandle( pi.hThread );
}

 
  _beginthread (Thread, 0, NULL) ;
  
  
  
#include "tinyproxy.h"

#include "child.h"
#include "daemon.h"
#include "filter.h"
#include "heap.h"
#include "log.h"
#include "reqs.h"
#include "sock.h"
#include "utils.h"

static int listenfd;
static socklen_t addrlen;

/*
 * Stores the internal data needed for each child (connection)
 */
enum child_status_t { T_EMPTY, T_WAITING, T_CONNECTED };
struct child_s {
	pid_t tid;
	unsigned int connects;
	enum child_status_t status;
};

/*
 * A pointer to an array of children. A certain number of children are
 * created when the program is started.
 */
static struct child_s *child_ptr;

static struct child_config_s {
	unsigned int maxclients, maxrequestsperchild;
	unsigned int maxspareservers, minspareservers, startservers;
} child_config;

static unsigned int* servers_waiting;



  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static void
child_main(struct child_s* ptr)
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

	ptr->connects = 0;

	while (!config.quit) {
		ptr->status = T_WAITING;

		clilen = addrlen;

		connfd = accept(listenfd, cliaddr, &clilen);

#ifndef NDEBUG
		/*
		 * Enable the TINYPROXY_DEBUG environment variable if you
		 * want to use the GDB debugger.
		 */
/* 		if (getenv("TINYPROXY_DEBUG")) {
			/* Pause for 10 seconds to allow us to connect debugger */
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

		ptr->status = T_CONNECTED;

		//SERVER_DEC();

		handle_connection(connfd);
		ptr->connects++;

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

	ptr->status = T_EMPTY;

	safefree(cliaddr);
	exit(0);
}