## CPP-Matrix
CPP-Matrix was my last year project offering matrix creation, modifying, and also various 
operations like addition/subtraction multiplication/division by a scaler, multiplication of two 
matrices, Transpose, Ecehelon form, Determinant all for NxN Square matrix
<br>

what's `*new` is i extended this idea for NxM i.e. any matrix which means now ecehelon can also be evaluated for general matrices, also by improving the readability, speed and logic of the code.

## Features

1. Creation of Matrix via a 2D `std::vector<T>` inside an initializer list
   <br>

   ```
   Matrix M = {
         {
            {1, 2},
            {3, 4}
         } 
   };
   ```
2. with operator overloading of `[]` operator you can just directly modify the data in matrix.
   <br>

   ```
   Matrix M = {
        {
            {2, 1}
        }
   };
   M[0][0] = 9;
   ```
3. you can add/subtract, multiply/divide by a scaler, multiply two matrices, take transpose using 
   basic arithematic operators 

   <br>

   ```
   + -> add
   - -> subtract
   * -> multiply by scaler OR multiply two matrices
        ex auto O = M*2 OR O = M*N
   / -> divide by a scaler
   ~ -> Transpose
   ```

   <br>
    also seperate function of these are also present 

4. Ecehelon form and Determinant are eveluated via <a href="https://en.wikipedia.org/wiki/Gaussian_elimination"> Gauss Jordan's Elimination </a> algorithmically.

## Improvements
Old code was really unoptimized and unnecesserily long shortened significantly with enhanced readability.


=============================================================================

## Greetings to you, it is my program that can deal with matrix operations----
mainly the operations include
1. formation of a matrix via a SQmatrix class(currently limited to square matrices)
2. assigning values to your matrix as rows
3. transpose of a matrix by SQtranspose use SQprint_transpose to print it (also commented in code)
4. martix multiplications as m1 * m2 where m1 and m2 are different SQmatrix classes
5. you can find determinant of a matrix

it also has some passive features like:
1. printing an identity via identity_print(order) function or use identity as matrix via identity() function
2. also the SQdefault to accomodate and auto assign the rest of values to 0 if order is larger than the assigned values in rows
3. it can also convert a matrix to it's echelon form 

to run the code use g++ matrix.cpp -o matric.exe

# Image
<img width="297" height="298" alt="image" src="https://github.com/user-attachments/assets/9afce70d-7f86-4132-b1f6-29ebe18532f9" />
