#pragma once

struct Board
{
    // can change board size if desired
    static const int rows = 3;
    static const int cols = 3;

    Board ()
    {
        for (int i = 0; i < rows * cols; ++i)
        {
            data[i] = i;
        }
        zero = 0;
    }

    Board (const int values...)
    {
        va_list args;
        va_start(args, values);

        data[0] = values;
        for (int i = 1; i < rows * cols; ++i)
        {
            data[i] = va_arg(args, int);
        }

        for (int i = 0; i < rows * cols; ++i)
        {
            if (data[i] == 0)
            {
                zero = i;
                break;
            }
        }

        va_end(args);
    }

    // copy constructor
    Board (const Board& original)
    {
        for (int i = 0; i < rows * cols; ++i)
        {
            data[i] = original.data[i];
        }
        zero = original.zero;
    }

    int data[rows * cols] = {};
    int zero = 0;

    bool operator== (const Board& other) const
    {
        for (int i = 0; i < rows * cols; ++i)
        {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    bool operator!= (const Board& other) const
    {
        return !operator==(other);
    }

    bool operator< (const Board& other) const
    {
        for (int i = 0; i < rows * cols; ++i)
        {
            if (data[i] < other.data[i])
                return true;
            if (data[i] > other.data[i])
                return false;
        }
        return false;
    }

    bool canMoveLeft () const
    {
        if (zero % cols == 0)
            return false;
        return true;
    }

    bool canMoveUp () const
    {
        if (zero < cols)
            return false;
        return true;
    }

    bool canMoveRight () const
    {
        if (zero % cols == cols - 1)
            return false;
        return true;
    }

    bool canMoveDown () const
    {
        if (zero > cols * rows - cols - 1)
            return false;
        return true;
    }

    Board moveLeft () const
    {
        Board newBoard(*this);
        std::swap(newBoard.data[newBoard.zero], newBoard.data[newBoard.zero - 1]);
        newBoard.zero--;
        return newBoard;
    }

    Board moveUp () const
    {
        Board newBoard(*this);
        std::swap(newBoard.data[newBoard.zero], newBoard.data[newBoard.zero - cols]);
        newBoard.zero -= cols;
        return newBoard;
    }

    Board moveRight () const
    {
        Board newBoard(*this);
        std::swap(newBoard.data[newBoard.zero], newBoard.data[newBoard.zero + 1]);
        newBoard.zero++;
        return newBoard;
    }

    Board moveDown () const
    {
        Board newBoard(*this);
        std::swap(newBoard.data[newBoard.zero], newBoard.data[newBoard.zero + cols]);
        newBoard.zero += cols;
        return newBoard;
    }

    int indexOf (const int n) const
    {
        for (int i = 0; i < rows * cols; ++i)
        {
            if (data[i] == n)
                return i;
        }
        return -1;
    }

    static std::queue <Board> shuffleBoard (Board& board)
    {
        std::queue <Board> shuffle_boards;
        shuffle_boards.push(board);

        const int count = rand() % 16 + 5;
        for (int i = 0; i < count; ++i)
        {
            std::vector <int> allowed_moves;
            if (board.canMoveLeft())
                allowed_moves.push_back(0);
            if (board.canMoveUp())
                allowed_moves.push_back(1);
            if (board.canMoveRight())
                allowed_moves.push_back(2);
            if (board.canMoveDown())
                allowed_moves.push_back(3);

            switch (allowed_moves.at(rand() % allowed_moves.size()))
            {
                case 0:
                    board = board.moveLeft();
                    break;
                case 1:
                    board = board.moveUp();
                    break;
                case 2:
                    board = board.moveRight();
                    break;
                case 3:
                    board = board.moveDown();
                    break;
                default:
                    assert(false);
            }
            shuffle_boards.push(board);
        }
        return shuffle_boards;
    }

    static std::vector <Board> getNeighbors (const Board& board)
    {
        std::vector <Board> neighbors;
        if (board.canMoveLeft()) neighbors.push_back(board.moveLeft());
        if (board.canMoveUp()) neighbors.push_back(board.moveUp());
        if (board.canMoveRight()) neighbors.push_back(board.moveRight());
        if (board.canMoveDown()) neighbors.push_back(board.moveDown());
        return neighbors;
    }

    static int getCost (const Board& board_a, const Board& board_b)
    {
        return 1;
    }

    static int manhattanHeuristic (const int index_a, const int index_b)
    {
        const int a_row = index_a / Board::rows;
        const int a_col = index_a % Board::cols;
        const int b_row = index_b / Board::rows;
        const int b_col = index_b % Board::cols;
        return std::abs(a_row - b_row) + std::abs(a_col - b_col);
    }

    static int getEstimate (const Board& board_a, const Board& board_b)
    {
        int sum = 0;
        for (int i = 0; i < Board::rows * Board::cols; ++i)
        {
            sum += manhattanHeuristic(i, board_b.indexOf(board_a.data[i]));
        }
        return sum;
    }
};

namespace Puzzle
{
    std::string print (const Board& board)
    {
        // convert grid size into string
        std::stringstream ss;
        ss << Board::rows * Board::cols;
        std::string s;
        ss >> s;

        // number of characters in the grid-size-string
        const size_t len = s.size();

        // not really made for grids with side size other than 3
        // but this can be easily implemented for other sizes by the user
        std::stringstream out;
        out << "+board+" << std::setw(len) << "\n";
        for (int r = 0; r < Board::rows; ++r)
        {
            for (int c = 0; c < Board::cols; ++c)
            {
                out << "|" << std::setw(len) << board.data[r * Board::cols + c];
            }
            out << "|" << "\n";
        }
        out << "+-----+" << "\n" << std::endl;
        return out.str();
    }

    std::string print (const Board& board_a, const Board& board_b)
    {
        // convert grid size into string
        std::stringstream ss;
        ss << Board::rows * Board::cols;
        std::string s;
        ss >> s;

        // number of characters in the grid-size-string
        const size_t len = s.size();

        // not really made for grids with side size other than 3
        // but this can be easily implemented for other sizes by the user
        std::stringstream out;
        out << "+board+   +board+" << std::setw(len) << "\n";
        for (int r = 0; r < Board::rows; ++r)
        {
            for (int c = 0; c < Board::cols; ++c)
            {
                out << "|" << std::setw(len) << board_a.data[r * Board::cols + c];
            }
            out << "|" << "   ";
            for (int c = 0; c < Board::cols; ++c)
            {
                out << "|" << std::setw(len) << board_b.data[r * Board::cols + c];
            }
            out << "|" << "\n";
        }
        out << "+-----+   +-----+" << "\n" << std::endl;
        return out.str();
    }


    size_t shuffled_to_base (Board& start, Board& goal)
    {
        std::cout << "Shuffling board." << "\n" << std::endl;
        std::queue <Board> shuffle_boards = Board::shuffleBoard(start);
        const size_t shuffle_count = shuffle_boards.size() - 1;
        while (!shuffle_boards.empty())
        {
            std::cout << print(shuffle_boards.front());
            shuffle_boards.pop();
        }
        std::cout << "Shuffle done. Attempting to solve." << "\n" << std::endl;
        return shuffle_count;
    }
}

int test_8puzzle ()
{
    Board start, goal;

#if 0
    const size_t shuffle_count = shuffled_to_base(start, goal) - 1;
#else
    start = Board(5, 4, 6, 3, 1, 8, 2, 0, 7);
    //start = Board(1, 2, 3, 0, 4, 7, 5, 6, 8);
    const size_t shuffle_count = 0;
#endif

    std::stack <Board> optimal_path_one
            = a_star_one <Board, int>(
                start, goal,
                Board::getNeighbors,
                Board::getCost,
                Board::getEstimate
            );

    std::stack <Board> optimal_path_two
            = a_star_two <Board, int>(
                start, goal,
                Board::getNeighbors,
                Board::getCost,
                Board::getEstimate
            );

    const size_t solution_count_one = optimal_path_one.size();
    const size_t solution_count_two = optimal_path_two.size();

    const size_t max = std::max(solution_count_one, solution_count_two);
    for (size_t a = 0; a < max; ++a)
    {
        static Board board_a, board_b;

        if (!optimal_path_one.empty())
        {
            board_a = optimal_path_one.top();
            optimal_path_one.pop();
        }
        else board_a = Board(0, 0, 0, 0, 0, 0, 0, 0, 0);

        if (!optimal_path_two.empty())
        {
            board_b = optimal_path_two.top();
            optimal_path_two.pop();
        }
        else board_b = Board(0, 0, 0, 0, 0, 0, 0, 0, 0);

        std::cout << Puzzle::print(board_a, board_b);
    }

    std::cout << "Shuffle count: " << shuffle_count << " moves." << std::endl;
    std::cout << "Solution count (one): " << solution_count_one << " moves." << std::endl;
    std::cout << "Solution count (two): " << solution_count_two << " moves." << std::endl;
    std::cout << std::endl;

    return 0;
}

int test_8puzzle_performance ()
{
    Board start, goal;

#if 0
    const size_t shuffle_count = shuffled_to_base(start, goal) - 1;
#else
    start = Board(5, 4, 6, 3, 1, 8, 2, 0, 7);
    //start = Board(1, 2, 3, 0, 4, 7, 5, 6, 8);
    const size_t shuffle_count = 0;
#endif

#if 0
    std::stack <Board> optimal_path_one
            = a_star_one <Board, int>(
                start, goal,
                Board::getNeighbors,
                Board::getCost,
                Board::getEstimate
            );
#else
    std::stack <Board> optimal_path_two
            = a_star_two <Board, int>(
                start, goal,
                Board::getNeighbors,
                Board::getCost,
                Board::getEstimate
            );
#endif

    return 0;
}
