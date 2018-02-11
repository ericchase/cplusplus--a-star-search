#pragma once

namespace Circle
{
    std::vector <int> getNeighbors (const int& value)
    {
        std::vector <int> neighbors;

        if (value == 1)
            neighbors.push_back(8);
        if (value == 8)
            neighbors.push_back(1);
        if (value > 1)
            neighbors.push_back(value - 1);
        if (value < 8)
            neighbors.push_back(value + 1);

        return neighbors;
    }

    int getCost (const int& value_a, const int& value_b)
    {
        return 1;
    }

    int getEstimate (const int& value_a, const int& value_b)
    {
        return 1;
        return std::abs(value_a - value_b);
    }

    std::string print (const int& value_a, const int& value_b)
    {
        std::stringstream out;
        out << " " << value_a << " " << value_b << std::endl;
        return out.str();
    }
}

int test_8circle ()
{
    int start = 1, goal = 5;

    std::stack <int> optimal_path_one
            = a_star_one <int, int>(
                start, goal,
                Circle::getNeighbors,
                Circle::getCost,
                Circle::getEstimate
            );

    std::stack <int> optimal_path_two
            = a_star_two <int, int>(
                start, goal,
                Circle::getNeighbors,
                Circle::getCost,
                Circle::getEstimate
            );

    const size_t solution_count_one = optimal_path_one.size();
    const size_t solution_count_two = optimal_path_two.size();

    const size_t max = std::max(solution_count_one, solution_count_two);
    for (size_t a = 0; a < max; ++a)
    {
        static int value_a, value_b;

        if (!optimal_path_one.empty())
        {
            value_a = optimal_path_one.top();
            optimal_path_one.pop();
        }

        if (!optimal_path_two.empty())
        {
            value_b = optimal_path_two.top();
            optimal_path_two.pop();
        }

        std::cout << Circle::print(value_a, value_b);
    }
    std::cout << std::endl;

    std::cout << "Solution count (one): " << solution_count_one << " moves." << std::endl;
    std::cout << "Solution count (two): " << solution_count_two << " moves." << std::endl;
    std::cout << std::endl;

    return 0;
}
