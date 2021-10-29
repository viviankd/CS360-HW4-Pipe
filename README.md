# CS360-HW4-Pipe
# Created by Vivian Duong

Write a program (in C) called assignment4.c targeted at the Linux platform that performs like a shell pipeline. Example: # ./assignment4 ls : sort = # ls | sort
Where the colon breaks argv into a left (ls) and right (sort) portion. 
./assignment4 <arg1> : <arg2>
Where: <arg1> and <arg2> are optional parameters that specify the programs to be run. If <arg1> is specified but <arg2> is not, then <arg1> should be run as though there was not a colon. Same for if <arg2> is specified but <arg1> is not.
