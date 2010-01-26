#include "gspot.h"

bool exitloop = false;
pthread_t mainthread = 0;

void
sessionloop()
{
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGIO);

	while(!exitloop) {
		int timeout = -1;
		pthread_sigmask(SIG_BLOCK, &sigset, NULL);
		spotify->ProcessEvents(&timeout);
		pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);
		usleep(timeout * 1000);
	}

}

static void sigIgn(int signo)
{
}


int
main(int argc, char* argv[])
{
	mainthread = pthread_self();
	signal(SIGIO, &sigIgn);


	if(spotify->InitSession())
		printf("valid session.\n");
	else
		printf("invalid session.\n");

	spotify->SetCredentials("user", "password");
	spotify->Login();

	sessionloop();

	delete spotify;

	return EXIT_SUCCESS;
}
