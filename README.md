# APIProject
Project developed for the course of Algoritmi e Principi dell'informatica (Algorithms and Computer Science Principles) @ Politecnico di Milano (academic year 2017-2018).
The course covered the fundamentals of algorithms, information theory, data structures and code optimization. 

Full syllabus here: https://www11.ceda.polimi.it/schedaincarico/schedaincarico/controller/scheda_pubblica/SchedaPublic.do?&evn_default=evento&c_classe=667856&polij_device_category=DESKTOP&__pj0=0&__pj1=de552ec089058c1ac72c8ea354915622

## Project review:
The project consists in developing a **Non Deterministic Turing Machine** using ANSII-C (no extra libraries allowed besides the standard one), following time and memory constraint imposed by teachers. The implementation meets all the costraint and achieved a grade of **30L/30**.

The code reads an input file with the following structure: 
```
tr
1 a a R 1
0 x x R 0
0 y y R 0
0 a x R 1
0 a a L 7
0 c c R 7
0 b b R 7
1 y y R 1
2 _ _ R 0
0 _ _ L 3
3 y y L 3
3 x x L 4
4 x x L 4
2 a a L 2
2 b b L 2
2 x x L 2
2 y y L 2
1 b y L 2
4 _ _ R 5
6 _ _ S 7
7 _ _ S 7
acc
5
max
5000
run
bbbbbbbbbbbaaaaaaaaaaaaaaaaaaa
```
Where the ```tr``` section represents the transaction of our Turing Machine. Each transaction is composed by 5 elements (from left to right):
1) Starting state
2) Read input char
3) Write char
4) Move memory head (Left,Right, no movement)
5) Next state

The ```acc``` section represents the accepting states.
```max``` represents the maximum number of computations before stopping the simulation 
```run``` contains all the input string to be simulated.

The Turing Machine outputs 3 possible ending charachters:
1) 1 -> the simulation has ended on a accepting state for the given input string. NB: in order to accept, all the branches of the simulation must end on an accepting state
2) 0 -> the simulation has ended on a NON accepting state. NB: it is sufficient to have a single non-accepting state to refuse the input string
3) U -> Undefined, one or more of the branches has reached the maximum amount of allowed computation (specified inside ```max```), thus the output is unknown

Example of output:
```U
0
0
1
U
0```
