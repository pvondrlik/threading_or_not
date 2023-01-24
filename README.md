# threading_or_not
The purpose of this project is to show, that threading is not always the better option.
In did this project as part of my OS class but added bonus parts and some extra implementaions. 

### Description
The programm executes 10 different calculations on a random initialized list saving the result in an output file.

### Execution
After calling `$ make` there are two programs which can be executed.

*thrNthr* ǵives you the opportunity to create several threads and split the task between those.

`$./thrNthr <number_of_integers> <number_threads>`

*noThread* will perform all operations in one thread making use of already calculated results.

`$./noThread <number_of_integers>`

### Time measuring [^1]
number of elements in list is 10,000,000
|n_threads | Processor time in s | Wall-clock time in s|
|---|---|---|
|“noThread” |0.135242| 0.134135|
|1 |0.227333| 0.227398|
|2 |0.233846 |0.139881|
|5 |0.277873 |0.084195|
|10 |0.318689 |0.071446|

[^1]:exluding the serial qsort +0.87s and list construction
+0.05s for processor and wall-clock time

### Analysis
#### Processor time:
Processor times increases with the number of threads, around 0.01 per thread. This is
caused by additional computation for creating and managing the threads and the increased
number of context-switches between threads since the threads share the CPU time of the
main thread (system-contention-scope).
#### Wall clock time
By doubling the number of threads, we get half of the wall clock time plus the 0.01s per
additional thread. The speed increases because the program makes use of multicore
architecture (scalability). However, we cannot see a great advantage from 5 to 10 threads
because of the extra computation and overhead.
#### Comparison of “noThread” and “thrNthr”
Comparing between threads 1 and “noThread” emphasize that multithreading is not always a
better solution, especially if task can make use of former results (e.g. reusing the already
calculated sum). This shows the difficulties of multithreading to divide activities and

### Note
The code does not catch every invalid argument.
