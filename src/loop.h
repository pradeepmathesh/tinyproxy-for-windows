

typedef enum {
	CHILD_MAXCLIENTS,
	CHILD_MAXSPARESERVERS,
	CHILD_MINSPARESERVERS,
	CHILD_STARTSERVERS,
	CHILD_MAXREQUESTSPERCHILD
} child_config_t;


void child_main();

int child_listen(uint16_t port);

short int child_configure(child_config_t type, unsigned int val);

