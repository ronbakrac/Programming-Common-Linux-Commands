# About This Project
This project contains programs of recreated Linux commands a user would use, programmed in C. These will only work in a Linux environment. You can call 'make' to create an executable file for all the programs.




<strong>myls-Bakrac.c</strong>

can run myls normally for it to print out all files in the current working directoy
can use argument of -l to specify information regarding all files in current working directory.
can use -l and then a directory location as an argument to do the above command in any directory
_ex_: <br>``./myls``</br>
``./myls -l``
<br>``./myls -l ./innerpath/innerpath2``</br>

<strong>mystat-Bakrac.c</strong>

Run by calling the program and having a single argument being the file you want to stat (must be in same directory).
_ex_: <br>``./mystat myfile.txt``</br>


<strong>mytail-Bakrac.c</strong>

Prints the last x characters of a file. To run, have arguments of how many of the last characters to read and then the filename (must be in same directory).
_ex_: <br>``./mytail 15 myfile.txt``</br>


<strong>mysearch-Bakrac.c</strong>

Prints out every file/directory starting from a base directory (basically a tree that visits every node and prints the contents, where nodes are directories). Can run with no arguments to print all files in current working directory/sub directories or can have 1 argument of which directory to start with (can be a directory before cwd if full path is specified).
_ex_: <br>``./mysearch``</br>
``./mysearch ./innerpath/innerpath2``
