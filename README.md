# os_assignment
OS ASSIGNMENT-1 README

-----------------------------------------------------------------------------------------------------------
- SUBMITTED BY : SIVANGI SINGH
- ROLL NO. : 2018201001

-----------------------------------------------------------------------------------------------------------


The project has two modes for the terminal-
1. Normal mode
2. Command(Canonical) mode
 One can shift from command mode to normal mode and vice versa.
 
Press 'q' to get back to the original terminal.

1. NORMAL MODE

* to shift from normal mode to command mode press “:” button from keyboard.
 It is basically same the “ls -l” command of terminal with some advanced features-

* Read and display list of Files and Directories in current Folder, and shows the following attributes-
	File name
	Permissions
	Ownership (User & Group)
	File size
	Last modified
  Directories can be differentiated by giving it’s name a different colour(Blue).

* User will be able to navigate up & down the file list using corresponding arrow keys.

* The file explorer Handles Scrolling, in case the directory has a lot of files.

* The file explorer also shows the entries “.” & “..” for current and parent directory respectively.

* Open files & directories-  When enter is pressed-
	Directory- Clears the screen and Navigate into the directory and
	show the files & directories inside it.
	Files- Your file explorer should be able to open files using the corresponding 	default application.

* Traversal-
	Go Back- On pressing left arrow key the file explorer goes back to the	previously visited directory.
	Go Forward- On pressing right arrow key the file explorer goes forward to the 	next directory .
	Up one level- On pressing backspace goes up one level.
	Home - On pressing ‘h’ key, goes to the home folder.

2. COMMAND MODE

* to switch from command mode to Normal mode  press “Esc” button.

* Create file ‘create_file <file_name(s)> <destination_path>’
	- creates file in the absolute path specified.

* Create directory ‘:create_dir <dir_name> <destination_path>’
	- creates directory in the absolute path specified.

* Goto: ‘goto <directory_path>’
	- goes to absolute path specified.

* Rename: 'rename <original_file_name> <final_file_name>'
	- renames the file.

* Copy: 'copy_file <file_path> <copiedfile_path>'
	-copies file from original path to new path.

* Move: 'move_file <original_filepath> <Destination_filepath>'
	-moves file from original path to new path.

