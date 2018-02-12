using System;
using System.Diagnostics;

namespace SharpMatrix
{
    class Program
    {
        static void Main(string[] args)
        {
            Stopwatch start = new Stopwatch();
            start.Start();
            int row = 14000;
            int col = 14000;
            int[,] array1 = new int[row, col];
            int[] array2 = new int[row];
            int[] result = new int[row];

            int count = 0;
            for(int i = 0; i < row; i++)
            {
                array2[i] = i;
                for(int j = 0; j < col; j++)
                {
                    array1[i,j] = count;
                    count++;
                }
            }
            int total = 0;
            
            for (int i = 0; i < row; i++)
            {
                total = 0;
                for (int j = 0; j < col; j++)
                {
                    total += array1[i,j] * array2[j];
                }
                result[i] = total;
            }
            start.Stop();
            Console.WriteLine("7888x788: " + array1[7888, 788]);
            Console.WriteLine("Time: " + start.ElapsedMilliseconds + " ms");
            Console.ReadLine();
        }
    }
}
