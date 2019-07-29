# Game Of Life

A Game Of Life simulator written in C++.

[Conway's game of life wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

### How to build

Make sure you have cmake installed and a compiler that supports at least C++11 (clang, gnu)

Checkout this repo then run in the project root folder
```
cmake .
make
```

to run the application you just execute:

``` 
./gameOfLife 
```

Then use left mouseclick to activate cells and then space to start and stop the simulation.

#### Todos:

* Adjustable size of the universe
* Selectable smaller tiles default now is 32x32px
* customizable colors to cells
* fix bug when pausing and changing active cells it will continue from last state.
* reset entire universe command
* predefined patterns
