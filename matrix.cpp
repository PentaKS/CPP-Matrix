#include <iostream>
#include <vector>

float Exp(float base, int power)
{
  float n=1;
  for (int i = 0; i < power; i++)
  {
    n = n*base;
  }
  return n;
}

class SQMatrix
{
public:
  const int order;
  std::vector<std::vector<float>> rows;
  SQMatrix(int orer) : order(orer) {};

  /////////////////////////////////////////////////////////////////////////////
  /////////////  making and printing our matrix  /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  void SQmake(std::vector<std::vector<float>> rows_in_order)
  { // make martix
    for (int j = 0; j < rows_in_order.size(); j++)
    {

      if (rows_in_order[j].size() < order + 1)
      {
        for (int i = rows_in_order.size(); i < order; i++)
        {
          rows_in_order[j].push_back(0);
        }
        rows.push_back(rows_in_order[j]);
      }

      if (rows_in_order.size() > order)
      {
        std::cout << "incompatible order with given input stream \n there is "
                     "not enough space to accomodate the required rows"
                  << std::endl;
      }
    }
  }

  void SQDefault()
  { // default mode to set values 0 if order is larger than values
    std::vector<float> null;
    for (int i = 0; i < order; i++)
    {
      null.push_back(0);
    }
    if (rows.size() < order + 1)
    {
      for (int i = rows.size(); i < order; i++)
      {
        rows.push_back(null);
      }
    }
  }

  bool no_negatives = true;
  std::string matrix_symbol;
  void SQprint()
  { // print function to print matrix
    // SQDefault();
    std::cout <<"The Matrix "<< matrix_symbol + " is :" << std::endl;
    for (int i = 0; i < order; i++)
    {
      std::vector<float> a =
          rows[i]; // releases the rows stored in row collescor
      // print start
      std::cout << "[";
      for (int j = 0; j < order; j++)
      {
        std::cout << " " << a[j] << " ";
      }
      std::cout << "]" << std::endl;
      // print end
    }
  }

  void SQprint_val(std::vector<std::vector<float>> v)
  { // print function to print matrix
    std::cout <<"The Matrix "<<matrix_symbol + " is :" << std::endl;
    for (int i = 0; i < order; i++)
    {
      std::vector<float> a = v[i]; // releases the rows stored in row collescor
      // print start
      std::cout << "[";
      for (int j = 0; j < order; j++)
      {
        std::cout << " " << a[j] << " ";
      }
      std::cout << "]" << std::endl;
      // print end
    }
  }

  //////////////////////////////////////////////////////////////
  ///////////////////////  transpose  //////////////////////////
  /////////////////////////////////////////////////////////////

  std::vector<std::vector<float>> columns;
  void SQtranspose()
  {
    for (int j = 0; j < order; j++)
    {
      std::vector<float> c;
      for (int i = 0; i < order; i++)
      {
        c.push_back(rows[i][j]);
      }
      columns.push_back(c);
    }
  }
  void SQtranspose_value(std::vector<std::vector<float>> matrix)
  {
    for (int j = 0; j < order; j++)
    {
      std::vector<float> c;
      for (int i = 0; i < order; i++)
      {
        c.push_back(matrix[i][j]);
      }
      columns.push_back(c);
    }
  }

  void SQprint_Transpose()
  {
    std::cout << std::endl;
    std::cout << "The Transpose (" + matrix_symbol + ")'" + " is :" << std::endl;
    for (int i = 0; i < order; i++)
    {
      std::vector<float> c = columns[i];
      std::cout << "[";
      for (int j = 0; j < order; j++)
      {
        std::cout << " " << c[j] << " ";
      }
      std::cout << "]" << std::endl;
    }
  }

  ///////////////////////////////////////////////////////////
  //////////////  matrix multiplication  ///////////////////
  /////////////////////////////////////////////////////////

  std::vector<float> /*void*/ SETmultiplication(std::vector<float> A, std::vector<float> B)
  {
    std::vector<float> product;
    for (int i = 0; i < order; i++)
    {
      product.push_back(A[i] * B[i]);
    }
    return product;
    // std::cout << "\n" << product[0] << "," << product[1] << "," <<
    // product[2];
  }

  int SETadd_all(std::vector<float> A)
  {
    int sum = 0;
    for (int i = 0; i < A.size(); i++)
    {
      sum = A[i] + sum;
    }
    // std::cout << sum;
    return sum;
  }

  SQMatrix SQmultiplication(SQMatrix B)
  {
    if (order == B.order)
    {

      B.SQtranspose();
      std::vector<std::vector<float>> temp_rows;
      for (int i = 0; i < order; i++)
      {
        std::vector<float> r;
        for (int j = 0; j < order; j++)
        {
          int t = SETadd_all(SETmultiplication(rows[i], B.columns[j]));
          // std::cout << t << ","<< std::endl;
          // SETmultiplication(rows[i], B.columns[j]);
          r.push_back(t);
          // int a11 = rows[i][j]*B.rows[j][i];
        }
        temp_rows.push_back(r);
      }
      std::cout << std::endl;

      for (int i = 0; i < order; i++)
      {
        std::vector<float> a =
            temp_rows[i]; // releases the temporary rows stored in row collescor
        // print start
        std::cout << "[";
        for (int j = 0; j < order; j++)
        {
          std::cout << " " << a[j] << " ";
        }
        std::cout << "]" << std::endl;
        // print end
      }
    }
    else
    {
      std::cout << "order not equal";
    }
    return 0;
  }

  SQMatrix operator*(const SQMatrix B)
  {
    std::cout << "Matrix multiplication of given matrices is:" << std::endl;
    return SQmultiplication(B);
  }

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////   exchanging row operator ///////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  void exchange(std::vector<std::vector<float>> &matrix, int row1_index, int row2_index)
  {
    std::vector<float> r1 = matrix[row1_index];
    std::vector<float> r2 = matrix[row2_index];

    matrix[row2_index] = r1;
    matrix[row1_index] = r2;
  }
  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////        Ecehelon Form       ///////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////
  std::vector<std::vector<float>> changed;
  std::vector<std::vector<float>> fixed;

  float product = 1;

  void echelon_form()
  {
    /// one of the most beautiful algorithms i've ever created so far because of it's complexity;
    for (int k = 0; k < order; k++) //// 1.  starting with two copies of original matrix, one fixed and other changable
    {
      changed.push_back(rows[k]);
      fixed.push_back(rows[k]);
    }
    for (int m = 0; m < order; m++)/// 2. this for loop checks each row to make an echelon form
    {
      std::vector<float> pivot = fixed[m]; /// 3. Pivot element is initialized from the fixed one
      if (pivot[m] == 0)//// 4. check if pivot is 0 or not
      {
        // std::cout << m << "th row centereis zero";
        std::cout << "Since, a"<<m+1<<m+1<<" is zero That is we need to Exchange rows.\n";
        SQtranspose_value(changed);
        SQprint_Transpose();
        std::cout << "It is convenient to Transpose and then do all calculations as we do for rows.\n";
        int r_index = 0;
        for (int j = m; j < order; j++) //// 5. if so than find the next non-zero element in same column
        {
          if (columns[m][j] != 0)
          {
            r_index = j;
            break;
          }
        }
        exchange(changed, m, r_index);//// 6. if found exchange that row with original one and apply changes only in changable copy
        // std::cout << "\n " << columns[m][0] << " " << r_index << " " << m << "\n";
        std::cout << "Exchanged Matrix :----v ";
        SQprint_val(changed);
        // pivot[m] = changed[m][m];
        pivot = changed[m]; /// 7. also change the pivot to new pivot
      }


      for (int i = m; i < order - 1; i++) // 8. dbl for loop as there are (order)^2 elements
      {
        std::vector<float> &t_row = changed[i + 1];// this '&' means that we want to change the elements of changed with each call
        // std::cout << changed[1][1] << " is a22 \n";

        fixed = changed;/// 9. change the fixed one to changed one to update the fixed matrix

        for (int j = m; j < order; j++)
        {
          t_row[j] = t_row[j] - ((fixed[i + 1][m] / pivot[m]) * pivot[j]);// 10. the only reason we have fixed matrix in the first place is to get direct element asscess of previously updated fixed matrix without caring about changes being made in changed matrix
          std::cout <<"Current pivot for cloumn"<<j+1<<" is :"<< pivot[m] << std::endl;
        }
        std::cout << "\nFinally Echelon Form----v ";
        SQprint_val(changed);// 11. finally print the output.
        std::cout << "\n";
      }
      // SQprint_val(fixed);
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  ////////////////////////  Determinant  /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////

  void SQdeterminant()
  {

    echelon_form();
    for (int i = 0; i < order; i++)
    {
      product *= changed[i][i];
    }
    float sign = Exp(-1, order);
    std::cout << "\nby multiplying the diagonal elements of our ecehelon form matrix we can get the desired determinant\n\n" << "determinant of this matrix is : " << sign*product;

  }
};

//////////////////////////////////////////////////////////////////////////////////
////////////////////////  Identity  //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

SQMatrix Identity(int n)
{
  SQMatrix Identity(n);
  Identity.matrix_symbol = "I";
  std::vector<std::vector<float>> i_Collector;
  for (int i = 0; i < n; i++)
  {
    std::vector<float> i_rows;
    for (int j = 0; j < n; j++)
    {
      i_rows.push_back(0);
    }
    i_rows[i] = 1;

    i_Collector.push_back(i_rows);
  }
  Identity.SQmake(i_Collector);
  std::cout << "\n";
  return Identity;
}

void Identity_print(int n)
{
  SQMatrix Identity(n);
  Identity.matrix_symbol = "I";
  std::vector<std::vector<float>> i_Collector;
  for (int i = 0; i < n; i++)
  {
    std::vector<float> i_rows;
    for (int j = 0; j < n; j++)
    {
      i_rows.push_back(0);
    }
    i_rows[i] = 1;

    i_Collector.push_back(i_rows);
  }
  Identity.SQmake(i_Collector);
  std::cout << "\n";
  Identity.SQprint();
}


//////////////////////////////////////////////////////////////////////////////////
////////////////////////    Main   //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


int main()
{
  SQMatrix MyMatrix(4);
  // SQMatrix MyMatrix(13);
  MyMatrix.matrix_symbol = "A";
  std::vector<float> row1 = {0, 1, 2};
  std::vector<float> row2 = {0, 0, -3};
  std::vector<float> row3 = {1, 5, 0};
  // std::vector<float> row4 = {11, 15, -2, 7};

  MyMatrix.SQmake({row1, row2, row3});
  MyMatrix.SQDefault();
  MyMatrix.SQprint();

  // SQMatrix MyMatrix2(3);
  // MyMatrix2.matrix_symbol = "B";
  // std::vector<int> row12 = {1, 0, 0};
  // std::vector<int> row22 = {0, 1,0};
  // std::vector<int> row32 = {0, 0, 1};
  // MyMatrix2.SQmake({row12, row22, row32});
  // MyMatrix2.SQDefault();
  // MyMatrix2.SQprint() ;
  // MyMatrix * MyMatrix2;
  // MyMatrix * Identity(5);

  MyMatrix.SQdeterminant();
  // MyMatrix.SQtranspose();
  // MyMatrix.SQprint_Transpose();
  // MyMatrix.SQmultiplication(MyMatrix2);
  // MyMatrix.SETadd_all({1,2,-3});

  // Identity(10);
  // Identity_print(15);

  return 0;
}