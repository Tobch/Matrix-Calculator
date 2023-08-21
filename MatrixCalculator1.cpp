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



int main() 
{
    
    int n1=1, m1=1, n2=1, m2=1, check=0;
    float scalar = 999999999;
    float matrix1 [101][101] = {0};
    float matrix2 [101][101] = {0};
    float matrix3 [101][101] = {0};
    char operation;
    char input[100001] = {};
    
    
    // Input Matrix1 / Scalar
    
    cin.getline(input, 100000, '\n');
    if (input[0] == '[')
    {
        int count =1,st=1;
        

        while(true)
        {
            if (input[count] == ']')
            {
                if (input[count-1] == ' ' || input[count-1] == '[')
                {
                    n1--;
                    if ((check - n1) && check)
                    {
                        cout << "ERROR!" << endl << n1 << check;
                        return 0;
                    }
                    break;
                }
                if (input[count-1] == '-')
                {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                if (count - st) matrix1[m1][n1] = to_mat (input, count, st);
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
                if (input[count-1] == '-')
                {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                if(input[count-1] == ' ' || input[count-1] == '[')
                {
                    count++;
                    st = count;
                    continue;
                }
                if (count-st) matrix1[m1][n1] = to_mat (input, count, st);
                n1++;
                count++;
                st = count;
            }
            else if (input[count] == ',')
            {
                if (input[count-1] == ' ') n1--;
                if (input[count-1] == '-')
                {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                if (count - st) matrix1[m1][n1] = to_mat (input, count, st);
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
    }
    else
    {
        scalar = to_mat(input, strlen(input), 0);
    }
    
    
    // Determine Operation
    {
        cin >> operation;
    }
    
    
    // Input Matrix2 / Scalar
    
    
    input[100000] = {NULL};
    
    cin.getline(input, 100000, EOF);
    if (input[1] == '[')
    {
        int count =2,st=2;
        check =0;

        while(true)
        {
            if (input[count] == ']')
            {
                if (input[count-1] == '-')
                {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                if (input[count-1] == ' ' || input[count-1] == '[')
                {
                    n2--;
                    if ((check - n2) && check)
                    {
                        cout << "ERROR!" << endl;
                        return 0;
                    }
                    break;
                }
                if (count-st) matrix2[m2][n2] = to_mat (input, count, st);
                count++;
                st = count;
                if ((check - n2) && check)
                {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                break;
            }
            else if (input[count] == ' ')
            {
                if (input[count-1] == '-')
                {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                if(input[count-1] == ' ' || input[count-1] == '[')
                {
                    count++;
                    st = count;
                    continue;
                }
                if (count - st) matrix2[m2][n2] = to_mat (input, count, st);
                n2++;
                count++;
                st = count;
            }
            else if (input[count] == ',')
            {
                if (input[count-1] == '-')
                {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                if(count - st) matrix2[m2][n2] = to_mat (input, count, st);
                m2++;

                if (m2 == 2)
                {
                    check = n2;
                }
                else
                {
                    if (check - n2)
                    {
                        cout << "ERROR!" << endl;
                        return 0;
                    }
                }

                n2 = 0;
                count++;
                st = count;
            }
            else
            {
                count++;
            }
        }
    }
    else
    {
        scalar = to_mat(input, strlen(input), 1);
    }
    
    
    // Operation 1 : Addition
    
    if (operation == '+')
    {
        if (n1 != n2 || m1 != m2)
        {
            cout << "ERROR!" << endl;
            return 0;
        }
        
        for (int i =1; i<=m1; i++)
        {
            for (int j=1; j<=n1; j++)
            {
                matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        
        
        
        for (int i =1; i<=m1; i++)
        {
            for (int j=1; j<=n1; j++)
            {
                (i==1 && j==1 ? cout << "[" << matrix3[1][1], j++ : 1);
                if (j<=n1) cout << " " << matrix3[i][j];
            }
            (i<m2 ? cout << ',' : cout << ']');
        }
    }
    
    
    
    // Operation 2 : Subtraction
    
    if (operation == '-')
    {
        if (n1 != n2 || m1 != m2)
        {
            cout << "ERROR!" << endl;
            return 0;
        }
        
        for (int i =1; i<=m1; i++)
        {
            for (int j=1; j<=n1; j++)
            {
                matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
            }
        }
        
        
        
        for (int i =1; i<=m1; i++)
        {
            for (int j=1; j<=n1; j++)
            {
                (i==1 && j==1 ? cout << "[" << matrix3[1][1], j++ : 1);
                if (j<=n1) cout << " " << matrix3[i][j];
            }
            (i<m2 ? cout << ',' : cout << ']');
        }
    }
    
    
    
    // Operation 3 : Multiplication (Matrix * Matrix)
    
    if (operation == '*' && scalar == 999999999)
    {
        if (n1 != m2)
        {
            cout << "ERROR!" << endl;
            return 0;
        }
        
        for (int i =1; i<=m1; i++)
        {
            for (int j=1; j<=n2; j++)
            {
                for (int k =1; k<=m2; k++)
                {
                    matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        
        for (int i =1; i<=m1; i++)
        {
            for (int j=1; j<=n2; j++)
            {
                (i==1 && j==1 ? cout << "[" << matrix3[1][1], j++ : 1);
                if (j<=n2) cout << " " << matrix3[i][j];
            }
            (i<m1 ? cout << ',' : cout << ']');
        }
    }
    
    
    
    // Operation 4 : Multiplication (Matrix * Scalar)
    
    if (operation == '*' && scalar != 999999999)
    {
        if (m1 < m2 || n1 < n2)
        {
            m1 = m2;
            n1 = n2;
        }
        
        for (int i =1; i<=m1; i++)
        {
            for (int j=1; j<=n1; j++)
            {
                matrix3[i][j] = (matrix1[i][j] + matrix2[i][j]) * scalar;
            }
        }
        
        
        
        for (int i =1; i<=m1; i++)
        {
            for (int j=1; j<=n1; j++)
            {
                (i==1 && j==1 ? cout << "[" << matrix3[1][1], j++ : 1);
                if (j<=n1) cout << " " << matrix3[i][j];
            }
            (i<m1 ? cout << ',' : cout << ']');
        }
    }
    
 
    return 0;
}
