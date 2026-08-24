#include <iostream>
#include <vector>

class Order {
    size_t ROWS, COLS;
    Order () {}
    Order (size_t m, size_t n) : ROWS(m), COLS(n) 
    {}

    bool operator == (const Order& rhs) const {
        return (ROWS == rhs.ROWS) && (COLS == rhs.COLS);
    }

    friend class Matrix;
};

class Matrix {
    Order                         m_order;
    std::vector<std::vector<double>> m_data;
public:
    Matrix () {}
    Matrix (std::vector<std::vector<double>> inp_matrix) 
    : m_data(inp_matrix) ,m_order({inp_matrix.size(), inp_matrix[0].size()})
    {}
    Matrix (Order mat_order) : m_order(mat_order)
    {
        for (int y = 0; y < m_order.ROWS; y++) {
            std::vector<double> temp;
            for (int x = 0; x < m_order.COLS; x++)
                temp.push_back(0);
            m_data.push_back(temp);
        }
    }

    Matrix add ( Matrix& rhs, bool isNonNegative = true) const{
        Matrix SUM = *this;
        if (m_order==rhs.m_order) {
            std::cout << m_order.ROWS << " " << m_order.COLS << std::endl;
            for (int y = 0; y < m_order.ROWS; y++)
                for (int x = 0; x < m_order.COLS; x++) 
                    SUM[y][x] = SUM[y][x] +  rhs[y][x] * ((isNonNegative) ? (1) : (-1));
        } else {
            std::cout << "order not same for addition / subtraction" << std::endl;
        }
        return SUM;
    }

    Matrix operator + ( Matrix& rhs) const {return add(rhs);}
    Matrix operator - ( Matrix& rhs) const {return add(rhs, false);}
    void   operator +=( Matrix& rhs)       {*this = add(rhs);}
    void   operator -=( Matrix& rhs)       {*this = add(rhs, false);}

    Matrix scaler_multiply (double scaler) const {
        Matrix Product {{m_order.ROWS, m_order.COLS}};
        for (int y = 0; y < m_order.ROWS; y++)
            for (int x = 0; x < m_order.COLS; x++)
                Product[y][x] *= scaler;
        return Product;
    }

    Matrix multiply (Matrix& rhs) const{
        Matrix Product {{m_order.ROWS, rhs.m_order.COLS}};
        if (m_order.COLS == rhs.m_order.ROWS) {
            for (int y = 0; y < m_order.ROWS; y++)
                for (int x = 0; x < rhs.m_order.COLS; x++)
                    for (int k = 0; k < m_order.ROWS; k++)
                        Product[y][x] += m_data[y][k] * rhs[k][x];
        } else {
            std::cout << " no. of colunms of LHS must be equal to no. of rows of RHS" << std::endl;
        }
        return Product;
    }

    Matrix operator * (Matrix& rhs)   const {return multiply(rhs);}
    Matrix operator * (double scaler) const {return scaler_multiply(scaler);}
    Matrix operator / (double scaler) const {return scaler_multiply(1.0/scaler);}
    void   operator *=(Matrix& rhs)         {*this = multiply(rhs);}
    void   operator *=(double scaler)       {*this = scaler_multiply(scaler);}
    void   operator /=(double scaler)       {*this = scaler_multiply(1.0/scaler);}

    Matrix transpose () const{
        Matrix Transpose {{m_order.COLS, m_order.ROWS}};
        for (int y = 0; y < m_order.ROWS; y++)
            for (int x = 0; x < m_order.COLS; x++)
                Transpose[x][y] = m_data[y][x];
        return Transpose;
    }

    Matrix operator ~ () {return transpose();}

    std::pair<Matrix, int> ecehelon() const {
        Matrix Original  = *this;
        Matrix Ecehelon  = Original;
        int row_op = 0;
        int min = (m_order.ROWS > m_order.COLS) ? m_order.COLS : m_order.ROWS;
        int max = (m_order.ROWS < m_order.COLS) ? m_order.COLS : m_order.ROWS;
        
        for (int d = 0; d < min-1; d++) {
            // std::cout << "step: d=" << d << std::endl;
            for (int y = 1; y < m_order.ROWS; y++) {
                for (int x = 0; x < m_order.COLS; x++) {
                    if (y>=m_order.ROWS) {return {Original, 0};}
                    
                    if (Ecehelon[d][d]!=0 && Ecehelon[y][x]!=0) {
                        // std::cout << "ecehelon " << y << ", " << x << " = " << Ecehelon[y][x] << " - " << "(" << Ecehelon[y][x] << "/" << Ecehelon[d][d] <<")" << "*" << Original[d][x] << std::endl;
                        Ecehelon[y][x] = Ecehelon[y][x] - ( (Ecehelon[y][x]/Ecehelon[d][d]) * Original[d][x] );
                    } else if (Ecehelon[d][d] == 0) {
                        // exchange rows with non zero d
                        for (int ty = 0; ty < m_order.ROWS; ty++) {
                            if (Ecehelon[ty][0] != 0) {
                                auto temp1 = Ecehelon[0];
                                Ecehelon[0] = Ecehelon[ty];
                                Ecehelon[ty] = temp1;

                                auto temp2 = Original[0];
                                Original[0] = Original[ty];
                                Original[ty] = temp2;
                                break;
                            }
                        }
                        row_op++;
                    } else {
                        y++;
                    }
                }
            }
            Original = Ecehelon;
            Ecehelon.print();
        }
        // std::cout << "row operations : " << row_op << std::endl;
        return {Ecehelon, row_op};
    }

    double determinant () const {
        double determinant = 1;
        if (m_order.ROWS == m_order.COLS) {
            auto e        = ecehelon().first;
            auto row_op   = ecehelon().second;
            for (int d = 0; d < m_order.COLS; d++) {
                determinant *= e[d][d];
            }
            determinant *= ((row_op%2==0) ? (1) : (-1));
        } else {
            std::cout << "Matrix must be a Square Matrix for Determinant" << std::endl;
        }
        return determinant;
    }

    std::vector<double>& operator [] (size_t index) {
        return m_data[index];
    }
    // print
    void print () {
        for (auto & row : m_data) {
            for (auto & e : row)
                std::cout << e << " ";
            std::cout << std::endl;
        }
    }
};

int main () {
    Matrix M = {
        {
            {0, 2, 3},
            {4, 0, 6},
            {7, 8, 9},
        }
    };
    Matrix N = {
        {
            {2, 0, 0},
            {0, 2, 0},
            {0, 0, 2}
        }
    };

    M.print();
    auto O = N.determinant();
    std::cout << O << std::endl;
    return 0;
}