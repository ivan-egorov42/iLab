# ARC cache

This program is an ARC(*adaptive replacement cache*) implementation. 

You can count hits in ARC with this program on various data types.

There are two modes of operation of this program. You can enter data from terminal(stdin stream) or from file(file stream).
By default, the program has the 1st mode of operation.


  **1. Stdin stream**
 
In terminal:
  
  Use makefile
``` 
make all
./cache
``` 
Enter size of cache and amount of pages. After enter pages.

  **2. File stream**

In this operating mode you need to change stream from stdin_ to filein_ in main.cpp:
```
const Streams stream = filein_;
```
Then you need enter name of file:
``` 
make all
./cache "Name_of_file" 
``` 
Size of cache and amount of pages should be in file.

**Testing program**

If you want to enable testing use makefile:
```
make testing
./cache (or ./cache "Name_of_file" )
```

You will get information about testing results in output. Then programm will work in default operation mode and will request input data.

***ARC program***

***(c) Banana_nigga, 2021***
