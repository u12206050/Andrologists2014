

int main()
{
	if (case)

	if (WINDOWS)
	{
		LPCTSTR lpApplicationName = "C:/Windows/System32/cmd.exe"; /* The program to be executed */

		LPSTARTUPINFO lpStartupInfo;
		LPPROCESS_INFORMATION lpProcessInfo;

		memset(&lpStartupInfo, 0, sizeof(lpStartupInfo));
		memset(&lpProcessInfo, 0, sizeof(lpProcessInfo));
		              
		/* Create the process */
		if (!CreateProcess(lpApplicationName,
		                   NULL, NULL, NULL,
		                   NULL, NULL, NULL, NULL,
		                   lpStartupInfo,
		                   lpProcessInformation
		                  )
		   ) {
		    std::cerr << "Uh-Oh! CreateProcess() failed to start program \"" << lpApplicationName << "\"\n";
		    exit(1);
		}

		std::cout << "Started program \"" << lpApplicationName << "\" successfully\n";

	}
	if (LINUX)
	{
		char* programPath = "/bin/bash";

		pid_t pid = fork(); /* Create a child process */

		switch (pid) {
		case -1: /* Error */
		std::cerr << "Uh-Oh! fork() failed.\n";
		exit(1);
		case 0: /* Child process */
		execl(programPath, NULL); /* Execute the program */
		std::cerr << "Uh-Oh! execl() failed!"; /* execl doesn't return unless there's an error */
		exit(1);
		default: /* Parent process */
		std::cout << "Process created with pid " << pid << "\n";
		int status;

		while (!WIFEXITED(status)) {
		waitpid(pid, status, 0); /* Wait for the process to complete */
		}

		std::cout << "Process exited with " << WEXITSTATUS(status) << "\n";

		return 0;
		}
	}
}