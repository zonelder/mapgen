#pragma once
#include<memory>
#include "System.h"


template<class T>
class Matrix
{
public:
    using num_type = T;
    using size_type = std::size_t;
    using arr_ptr_type = std::unique_ptr<num_type[]>;
private:
    int roudness = 1;
    int min_bound = 0;
    size_type n, m;
    std::unique_ptr<arr_ptr_type[]> Array;
public:
    Matrix()
    {
        n = 0; m = 0;
        Array = nullptr;
    }
    Matrix(std::size_t n, std::size_t m) : n(n), m(m), Array(std::make_unique<arr_ptr_type[]>(n))
    {
        for (std::size_t i = 0; i < n; ++i)
            Array[i] = std::make_unique<num_type[]>(m);
    }
    num_type& operator()(size_type i, size_type j) {
        return Array[i][j];
    }
    void setMin_bound(T value) { min_bound = value; }
    size_type getRowCount() { return n; }
    void setRoudness(int r) { roudness = r; }
    int getRoudness() { return roudness; }
    size_type getColCount() { return m; }
    void show()
    {
        for (size_type i = 0; i < n; i++) {
            for (size_type j = 0; j < m; j++)
                std::cout << Array[i][j] << ' ' << std::setw(2);
            std::cout << '\n';
        }
    }
    void fill(T value)
    {
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                Array[i][j] = value;
    }
    void Scaling(T max_value)
    {
        T max = Array[0][0];
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                if (max < Array[i][j])
                    max = Array[i][j];
        float div = float(max_value) / float(max);
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                Array[i][j] *= div;

    }
    void squareStep(int x, int y, int reach, unsigned int _width)
    {
        int count = 0;
        float avg = 0.0f;
        if (edgeCondition(x, y, reach, _width))
        {
            Array[x][y] = 0;
            return;
        }
        if (x - reach >= 0 && y - reach >= 0)
        {
            avg += Array[x - reach][y - reach];
            count++;
        }
        if (x - reach >= 0 && y + reach < _width)
        {
            avg += Array[x - reach][y + reach];
            count++;
        }
        if (x + reach < _width && y - reach >= 0)
        {
            avg += Array[x + reach][y - reach];
            count++;
        }
        if (x + reach < _width && y + reach < _width)
        {
            avg += Array[x + reach][y + reach];
            count++;
        }
        avg += random(int(-roudness * reach), int(roudness * reach));
        avg /= count;
        if (avg < min_bound)
                avg =  min_bound;
        Array[x][y] = int(avg);
    }
    void diamondStep(int x, int y, int reach, unsigned int _width)
    {
        int count = 0;
        float avg = 0.0f;
        if (edgeCondition(x, y, reach, _width))
        {
            Array[x][y] = 0;
            return;
        }

        {
            if (x - reach >= 0)
            {
                avg += Array[x - reach][y];
                count++;
            }
            if (x + reach < _width)
            {
                avg += Array[x + reach][y];
                count++;
            }
            if (y - reach >= 0)
            {
                avg += Array[x][y - reach];
                count++;
            }
            if (y + reach < _width)
            {
                avg += Array[x][y + reach];
                count++;
            }
            avg += random(-roudness * reach, roudness * reach);
            avg /= count;
            if (avg < min_bound)
               avg = min_bound;
                Array[x][y] = int(avg);
        }
    }
    void diamondSquare(int size, unsigned int _width)
    {
        int half = size / 2;
        if (half < 1)
            return;
        for (int y = half; y < _width; y += size)
            for (int x = half; x < _width; x += size)
                squareStep(x % _width, y % _width, half, _width);
        int col = 0;
        for (int x = 0; x < _width; x += half)
        {
            col++;
            //If this is an odd column.
                for (int z = half*(col % 2); z < _width; z += size)
                    diamondStep(x % _width, z % _width, half, _width);
        }
        diamondSquare(size / 2, _width);
    }
    void generate()//flag can be "diamondSquare" or "linear"
    {
        srand(time(0));
        int _width = n;
        int size = _width / 2;
            diamondSquare(size, _width);
            

    }
    T Max()
    {
        T max = Array[0][0];
        for (size_type i = 0; i < n; i++)
            for (size_type j = 0; j < m; j++)
                if (Array[i][j] > max)
                    max = Array[i][j];

        return max;
    }
    void WaterLvl_setting(unsigned int persent,int _width)
    {
        int waterLvl = 0;
        int fullArea = 0;
        int dirt = 0;

        fullArea = _width * _width;
        int real_persent = 0;
        for (int step = 0; step < 100; step++) {
                if (real_persent < persent)
                waterLvl -= 1;
              if (real_persent > persent)
                waterLvl += 1;

            for (int i = 0; i < _width; i++)
                for (int j = 0; j < _width; j++)
                {
                    if (Array[i][ j] > waterLvl)
                        dirt++;
                }
           real_persent = float(dirt) / float(fullArea) * 100;
            dirt = 0;
        }

        for (int i = 0; i < _width; i++)
            for (int j = 0; j < _width; j++)
            {
                //if (Array[i][j] > waterLvl)
                    Array[i][j] -= waterLvl;
                //else
                  //  Array[i][j] = 0;//что то сделать с дном
            }
        this->Scaling(255);
    }
    
};
