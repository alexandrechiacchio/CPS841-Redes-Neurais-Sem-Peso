
// #include "/home/chiacchio/UFRJ/rnsp/wisardpkgTst/include/wisardpkg.hpp"
// #include <random>
// #include <bits/stdc++.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <random>
#include <numeric>
// #include "./wisardpkgTst/src/common/exceptions.cc"

class KernelCanvas2
{
public:
    KernelCanvas2(std::pair<int, int> _shape, int _numberOfKernels, int _bitsPerKernel = 1, float _activationDegree = 0.07)
    {
        if (_numberOfKernels < 1)
            throw std::invalid_argument("Error: the number of kernels can not be lesser than 1!");
        if (_bitsPerKernel < 1)
            throw std::invalid_argument("Error: the number of bits by kernel can not be lesser than 1!");
        if (_activationDegree > 1 || _activationDegree < 0)
            throw std::invalid_argument("Error: the activation degree must be between 0 and 1!");

        shape = _shape;
        numberOfKernels = _numberOfKernels;
        bitsPerKernel = _bitsPerKernel;
        activationDegree = _activationDegree;
        kernel_points.resize(numberOfKernels * bitsPerKernel);
        closestKernel.resize(shape.first, std::vector<int>(shape.second, -1));

        makeKernel();
        findClosestKernels();
    }

    std::vector<int_fast8_t> transform(std::vector<std::vector<float>> &data)
    {
        // if (data.empty() || data[0].size() != 2)
        //     throw std::invalid_argument("Error: input data must be a 2D vector with two columns!");

        std::vector<int_fast8_t> output(numberOfKernels * bitsPerKernel, 0);
        
        for (size_t i = 0; i < data.size(); i++)
        {
            for (size_t j = 0; j < data[i].size(); j++)
            {
                if (data[i][j] > activationDegree)
                {
                    output[closestKernel[i][j]] = 1;
                }
            }
        }

        return output;
    }

    void tst()
    {
        std::cout << "test sucessful!" << std::endl;
    }

    void mutateKernel(double mutationFactor = 0.1){
        if (mutationFactor < 0 || mutationFactor > 1)
            throw std::invalid_argument("Error: mutation factor must be between 0 and 1!");

        std::vector<int> randIndexes(kernel_points.size());
        std::iota(randIndexes.begin(), randIndexes.end(), 0);

        std::shuffle(randIndexes.begin(), randIndexes.end(), std::mt19937{std::random_device{}()});
        randIndexes.resize(static_cast<int>(mutationFactor * kernel_points.size()));

        std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };  // up, down, left, right

        for (int i : randIndexes) {
            int row = kernel_points[i].first;
            int col = kernel_points[i].second;
            int direction = std::rand() % directions.size();
            int new_row = row + directions[direction].first;
            int new_col = col + directions[direction].second;

            if (new_row >= 0 && new_row < shape.first && new_col >= 0 && new_col < shape.second) {
                bool repeated = false;
                for (const auto &kp : kernel_points) {
                    if (kp.first == new_row && kp.second == new_col) {
                        repeated = true;
                        break;
                    }
                }
                if(!repeated) kernel_points[i] = { new_row, new_col };
            }
        }

        findClosestKernels();
    }


    std::vector<std::pair<int, int>> getKernelPoints() const
    {
        return kernel_points;
    }
    std::vector<std::vector<int>> getClosestKernel() const
    {
        return closestKernel;
    }
    std::pair<int, int> getShape() const
    {
        return shape;
    }
    int getNumberOfKernels() const
    {
        return numberOfKernels;
    }

    std::pair<int, int> shape;
    int numberOfKernels;
    int bitsPerKernel;
    float activationDegree;
    std::vector<std::pair<int, int>> kernel_points;
    std::vector<std::vector<int>> closestKernel;
    
    void findClosestKernels()
    {
        for (int i = 0; i < shape.first; i++)
        {
            for (int j = 0; j < shape.second; j++)
            {
                std::pair<int, int> point = {i, j};
                closestKernel[i][j] = findClosestKernel(point);
            }
        }
    }
    
    protected:

    float squareDistance(std::pair<int, int> &a, std::pair<int, int> &b)
    {
        return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
    }

    void makeKernel()
    {
        int total_points = shape.first * shape.second;
        std::vector<int> points(total_points);
        std::iota(points.begin(), points.end(), 0);

        std::shuffle(points.begin(), points.end(), std::mt19937{std::random_device{}()});

        for (int i = 0; i < numberOfKernels; ++i)
        {
            kernel_points[i] = {points[i] % shape.first, points[i] / shape.first};
        }
    }
    
    int findClosestKernel(std::pair<int, int> &point)
    {
        int ret = -1;
        for (size_t i = 0, dist = 1e9; i < kernel_points.size(); i++)
        {
            if (squareDistance(point, kernel_points[i]) < dist)
            {
                dist = squareDistance(point, kernel_points[i]);
                ret = i;
            }
        }
        return ret;
    }
    
};