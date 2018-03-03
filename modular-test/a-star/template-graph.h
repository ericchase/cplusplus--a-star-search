class myGraph
{
public:

    // data

    class node
    {
        // data

        // constructors

        // comparator methods

        bool operator== (const node& other) const
        {
            // needs implementation

            return true;
        }

        bool operator!= (const node& other) const
        {
            return !operator==(other);
        }

        bool operator< (const node& other) const
        {
            // needs implementation

            return false;
        }
    };

    typedef int weight;

    // constructors

    // a-star required methods

    std::vector <node> get_neighbors_of (const node&)
    {
        std::vector <node> neighbors;

        // needs implementation

        return neighbors;
    }

    weight get_cost_between (const node&, const node&)
    {
        weight cost;

        // needs implementation

        return cost;
    }

    weight get_estimate_between (const node&, const node&)
    {
        weight estimate;

        // needs implementation

        return estimate;
    }
};
