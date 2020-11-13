README for dvrouting.c

If you have issues and/or questions, message over slack Jordan Jock. I should respond quickly, but I believe the code should be fairly stright forward

Please read the entire file, I will try to encompass all of the potential issues that might arrise from running. This code works for the input.txt file and I believe it works with DVInput.txt

HOW TO RUN:

1. Run 'make all' inside of the directory with dvrouting.c and the Makefile inside.
2. Run './dvrouting {FILE.txt}'
3. The output is printed into results.txt

ISSUES:

1. I'd advise not trying to understand the code; It's all over the place and not well commented. I didn't fully understand the problem at hand when I started; which resulted in code that is all over the place. Given more time I could go through it and make it easier to read and understand.
2. I believe the code is case sensitive.
3. The arrays are static for the most part, but should be able to handle almost anything.

CODE IMPROVEMENTS:

1. Use mostly int arrays; this would cut down on many loops that were used to look through the char arrays. This would cut down many lines of code and complexity.
2. Make better variable names.
3. Comment the code better and reduce loops by doing multiple things inside of loops

ASSIGNMENT IMPROVEMENTS:

1. Make the first line of the input file the same as the rest of the input. (ex. {A,B,2}; ....) This would make it so one major loop could be used to traverse through.
