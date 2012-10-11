% Assignment 1 - Introduction
% TDT4195 - Image Techniques
% ================================================
% Add code to this file where indicated and deliver on Itslearning before deadline

% A few notes about matlab
% - Almost all variables are matrices
% - You don't have to specify datatypes (like int, char, string etc.)
% - Matlab do not use curly braces {} or parantheses, instead it use the keyword end 
% - Most statements that don't end with a ; will print out a result, thus it don't have the exact same meaning as ; in Java and C. Still, it can be used to seperate statements on the same line
% - Matrices are accessed using y,x like A(y,x)

% ------------------------------------------------

% Task 1: Basic Matlab. Do not use any loop structures in this first task

% Task 1.1: Create a 4x6 matrix, A, where every element is 1 

A = ones(4, 6)


% Task 1.2: Print the contents of the matrix to the screen

%disp(A)

% Task 1.3: Create another 6x4 matrix, B, with random values

B = rand(6,4)

% Task 1.4: Print the contents of the new matrix to the screen

%disp(B)

% Task 1.5: Do matrix multiplication on A and B and print result (resulting matrix should be 4x4)

disp('A*B')

disp(A*B)

% Task 1.6: Do element-by-element multiplication on B and B (note the difference from task 1.5)

disp('A.*B')

disp(B.*B)

% Task 1.7: Change element x=2,y=4 in A to 2 (remember Matlab indexes start with 1)

A(4, 2) = 2

% Task 1.8: Set all elements in matrix A with x index 2 and 5 and y index from 2 to 3 to 4 without using any loops

vec = A(:, 2)
vec(2:3) = 4

A(:, 2) = vec

vec = A(:, 5)
vec(2:3) = 4

A(:, 5) = vec

% Task 1.9: Add 0.5 to the first row in matrix B (again no loops)

B(1, :) += 0.5

% Task 1.10: Substract 0.5 from all elements in B that are above 1 (again no loops)



% Task 1.11: Type whos to see details of current variables

% Task 1.12: Type clear A to delete matrix A

% Task 2: Control structures and functions in matlab

% Task 2.1: Create a for loop on the variable i from 4 to 20 with step 2 and print i*2 and i if i > 10

% Task 2.2: Create a function (and a file for it) called magnitude that takes a vector (one dimension in the matrix has size 1) in and computes the magnitude of it. magnitude = sqrt(x^2 + y^2 + z^2...)

% Task 2.3: Call your magnitude function on B(:) ( the (:) statement makes B into a vector) (note that this can be done without any loops or ifs)

% Task 3: Basic image processing in matlab (see functions that start with im in matlab)

% Task 3.1: Read image (assignment.png) from disk into a matrix

% Task 3.2: Convert image to grayscale

% Task 3.3: Convert image to floating point (double) representation

% Task 3.4: Show image on screen (remember to put figure; before this and all other commands that displays something on screen to insure that all images are shown)

% Task 3.5: For all pixels (elements in the image matrix) with values above 0.7 set the pixel value to 1.0 (recall task 1.10)

% Task 3.6: Show image on screen

% Task 3.7: Create and show histogram of image

% Task 3.8: Save image to disk and call it result.png
