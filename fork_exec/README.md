# Description of the practical work

This practical work hilights the system call**fork()**'s fuction and the process work. Furthermore, the family system call **exec..()** permets to a process to execute a new one,ie replace a process by new one. In this PW, we worked on creating a new process Childs with fork then exec.

## Answer of questions

**1-simple**
In the child process, we used *execlp()*, there fore the new process has the same *pid* as the child pid. Because the new process tok the child place.

**2-Gnuplot**
I tried to undersatnd the result of *htop* but I couldn't, but I think Gnuplot created a process.

Normaly based on the code, both <Enter> or <Exit> close the Gunplot and turn on *wait*.

**4-Sons**
The difference between *execlp()* and *execvp()* :

*execlp()* : *l* means list, that means, we fit the arguments one by one, like a list and we finish by *NULL*.
for instance :
```C
execlp("gedit", "gedit", "hello.txt", NULL);
```
*execvp()* : *v* means vector, as a reslut, we fit a charachter table (<char *argv[]>).
for instance :
```C
char *args[] = {"gedit", "hello.txt", NULL};
execvp("gedit", args);
```
In short:
 *execlp* = list of arguments hard coding
 *execvp* = table of arguments, more flexible.   



## Author

**Mohamed El Mokhtar**