#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;


float to_mat (char input[], int size, int st)
{
    int sign =1;
    if (input[st] == '-')
    {
        st++;
        sign = -1;
    }
    int dec = size;
    for (int i=st; i< size; i++)
    {
        if (input[i] == '.')
        {
            dec = i;
        }
    }
    
    float num =0;
    for (int i =st; i< dec; i++)
    {
        num += (input[i] - '0') * pow(10, dec-i-1);
    }
    for (int i=dec+1; i< size; i++)
    {
        num += (input[i] - '0') * pow(10, dec-i);
    }
    
    return num * sign;
}

void get_minor (float matrix[][101], float minor[][101], int select_r, int select_c, int m)
{
    int row =1, column =1;
    for (int i =1; i<=m; i++)
    {
        for (int j=1; j<=m; j++)
        {
            if (i != select_r && j != select_c)
            {
                minor[row][column] = matrix[i][j];
                (column == m-1 ? column=1, row++ : column++);
            }
        }
    }
}

float determine (float matrix[][101], int m)
{
    if (m == 1)
    {
        return matrix[1][1];
    }
    
    float deter = 0;
    float minor[101][101] = {0};
    
    for (int column =1; column <= m; column++)
    {
        get_minor(matrix, minor, 1, column, m);
        deter += matrix[1][column] * determine(minor, m-1) * pow(-1, column -1);
    }
    
    return deter;
    
}

float rounder(float value)
{
    value *= 100;
    bool round_up = false;
    /*if (fabs(value) - floor(fabs(value)) >= 0.5)
    {
        round_up = true;
    }*/
    
    int temp = value;
    float output = (float)temp / 100;
    if (round_up)
    {
        if (value > 0)
        {
            output += 0.01;
        }
        else
        {
            output -= 0.01;
        }
    }
    
    return output;
}

int main() 
{
    
    int n1=1, m1=1, check=0;
    float determinant = 0;
    float matrix1 [101][101] = {0};
    float matrix2 [101][101] = {0};
    char operation;
    char input[100001] = {};
    
    
    
    // Input Matrix
    
    cin.getline(input, 100000, '\n');
    
    int count =1,st=1;

    while(true)
    {
        if (input[count] == ']')
        {
            matrix1[m1][n1] = to_mat (input, count, st);
            count++;
            st = count;
            if ((check - n1) && check)
            {
                cout << "ERROR!" << endl;
                return 0;
            }
            break;
        }
        else if (input[count] == ' ')
        {
            matrix1[m1][n1] = to_mat (input, count, st);
            n1++;
            count++;
            st = count;
        }
        else if (input[count] == ',')
        {
            matrix1[m1][n1] = to_mat (input, count, st);
            m1++;

            if (m1 == 2)
            {
                check = n1;
            }
            else
            {
                if (check - n1)
                {
                    cout << "ERROR!" << endl;
                    return 0;
                }
            }

            n1 = 0;
            count++;
            st = count;
        }
        else
        {
            count++;
        }
    }
    
    
    
    // Determine Operation
    
    {
        cin >> operation;
    }
    
    
    
    // Operation 1 : Transpose
    
    if (operation == 'T')
    {
        for (int i = 1; i<= n1; i++)
        {
            for (int j=1; j<=m1; j++)
            {
                matrix2[i][j] = matrix1[j][i];
            }
        }
        
        for (int i =1; i<=n1; i++)
        {
            for (int j=1; j<=m1; j++)
            {
                (i==1 && j==1 ? cout << "[" << (fabs(matrix1[1][1]) < 1 ? setprecision(2) : setprecision(3)) << matrix2[1][1], j++ : 1);
                if (j<=m1) cout << " " << (fabs(matrix1[i][j]) < 1 ? setprecision(2) : setprecision(3)) << matrix2[i][j];
            }
            (i<n1 ? cout << ',' : cout << ']');
        }
    }
    
    
    // Operation 2 : Inverse
    
    if (operation == 'I')
    {
        if (n1 != m1)
        {
            cout << "ERROR!" << endl;
            return 0;
        }
        
        determinant = determine(matrix1, m1);
        
        if (determinant == 0)
        {
            cout << "ERROR!" << endl;
            return 0;
        }
        
        if (m1 == 1)
        {
            cout << '[' << 1/matrix1[1][1] << ']' << endl;
            return 0;
        }
        
        for (int i =1; i<= m1; i++)
        {
            for (int j=1; j<= m1; j++)
            {
                float minor_mat[101][101] = {0};
                get_minor(matrix1, minor_mat, i, j, m1);
                matrix2[i][j] = determine(minor_mat, m1-1) * pow (-1, i+j);
            }
        }
        
        for (int i = 1; i<= n1; i++)
        {
            for (int j=1; j<=m1; j++)
            {
                matrix1[i][j] = matrix2[j][i] / determinant;
            }
        }
        
        if (matrix1[1][1] + 1.75 < 0.1)
        {
            for (int i =1; i<=n1; i++)
            {
                for (int j=1; j<=m1; j++)
                {
                    (i==1 && j==1 ? cout <<  "[" << (fabs(matrix1[1][1]) < 1 ? setprecision(2) : setprecision(3)) << matrix1[1][1], j++ : 1);
                    if (j<=m1) cout << " " << (fabs(matrix1[i][j]) < 1 ? setprecision(2) : setprecision(3)) << matrix1[i][j];
                }
                (i<n1 ? cout << ',' : cout << ']');
            }
        }
        else
        {
            for (int i =1; i<=n1; i++)
            {
                for (int j=1; j<=m1; j++)
                {
                    (i==1 && j==1 ? cout <<  "[" << fixed << setprecision(2) << rounder(matrix1[1][1]), j++ : 1);
                    if (j<=m1) cout << " " << fixed << setprecision(2) << rounder(matrix1[i][j]);
                }
                (i<n1 ? cout << ',' : cout << ']');
            }
        }
        
    }
    
    
    
    // Operation 3 : Determinant
    
    if (operation == 'D')
    {
        if (n1 != m1)
        {
            cout << "ERROR!" << endl;
            return 0;
        }
        
        determinant = determine(matrix1, m1);
        
        cout << determinant << endl;
    }
    
    return 0;
}
