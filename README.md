# A Brain F*** interpreter 🧠 written in c++

![Build status](https://github.com/prashanthKumar0/bf-interpreter/actions/workflows/build-test.yml/badge.svg)

## What is Brain F*** ?


<br>

    Brain F*** is an esoteric (or 'joke') programming language
    which just means it was designed to be a joke among programming nerds


> for further details about the language have a look at <a href="https://en.wikipedia.org/wiki/Brainfuck">This Wikipedia Page</a>

<br>
<br>

# Why do i care about this language?


<br>

    This language is really challenging and exciting to code in.
    You would get a great excitement while developing some new techinques 
    and its good to test and practice your algorithm and problem solving skills.

> although brain f*** is not used in real world programming . imo its good for even beginners to start thinking logically. and it helps to learn a lots of tactics for intermediates.

<br>
<br>

# About This Interpreter


<br>

    This interpreter is a little playground for 
    working with brain f*** . It has a nice interactive mode 
    which has some nice features 
    (new ideas are always welcomed)


<br>
<br>

# Features of This Interpreter

> * Execute A brain f*** file with <code> bf_interpreter.exe -f ./fielName.bf </code>

* __Interactive mode with rich IDE like experience__  the interactive mode has following commands 
    * <code> @exit</code> to exit the program
    * <code> @clear</code> clears the screen
    * <code> @reset</code> resets all cells and move data pointer to 0
    * <code> @cell_used</code> prints number of cells used by the program
    * <code> @init_log  [fileName.bf]</code> logs the commands you enter into the file filename.bf
    * <code> @stop_log</code> stops logging in the file
    * <code> @help</code> prints all these commands for help if you are stuck

<br>
<br>

# Compiling the program

use the following command :

## on windows
<code> g++ ./bf_interpreter.cpp -o ./bf_interpreter.exe </code>

or run <a href="./automake.bat">./automake.bat</a>


## on linux
<code> g++ ./bf_interpreter.cpp -o ./bf_interpreter </code>
<br>
and make it executable by
<code>chmod +x ./bf_interpreter </code>
<br>
its recommended to copy it in /bin or /usr/bin or change <kbd>$PATH</kbd> environment variable
  <br>
> the [./bf](./bf) folder contains some sample brain f*** programs



<br>
<br>

<center>
<h1> THANK YOU FOR READING !  </h1>
Contributions are always welcomed !
</center>

