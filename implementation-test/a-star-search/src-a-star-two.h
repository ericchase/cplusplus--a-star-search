// Code taken from
// https://github.com/ericchase/cplusplus-a-star-search

#pragma once

template <typename NODE, typename WEIGHT>
std::stack <NODE> a_star_two
    (
        const NODE start, const NODE goal,
        std::vector <NODE> (*get_neighbors_of) (const NODE&),
        WEIGHT (*get_cost_of) (const NODE&, const NODE&),
        WEIGHT (*get_estimate_of) (const NODE&, const NODE&)
    )
{
    typedef std::pair <WEIGHT, NODE> weighted_node;

    std::set <weighted_node> open;
    std::set <NODE> closed;

    std::map <NODE, NODE> parent_of;
    std::map <NODE, WEIGHT> path_cost_of;

    open.emplace(0, start);
    parent_of.emplace(start, start);
    path_cost_of.emplace(start, 0);

    //static int loopCount = 0;
    while (!open.empty())
    {
        // can't be a reference
        const NODE current = open.begin()->second;

        if (current == goal)
            break;

        open.erase(open.begin());

        if (closed.find(current) != closed.end())
            continue;
        closed.insert(current);

        for (NODE neighbor : get_neighbors_of(current))
        {
            if (closed.find(neighbor) != closed.end())
                continue;

            //loopCount++;

            const WEIGHT g_n = path_cost_of[current] + get_cost_of(current, neighbor);

            if (path_cost_of.find(neighbor) != path_cost_of.end())
                if (path_cost_of[neighbor] < g_n)
                    continue;

            WEIGHT f_n = g_n + get_estimate_of(neighbor, goal);

            open.emplace(f_n, neighbor);
            parent_of.at(neighbor) = current;
            path_cost_of.at(neighbor) = g_n;
        }
    }

    std::stack <NODE> optimal_path;

    if (!open.empty())
    {
        // cannot be const or reference
        NODE node = open.begin()->second;

        optimal_path.push(node);
        while (parent_of.at(node) != node)
        {
            node = parent_of.at(node);
            optimal_path.push(node);
        }
    }

    return optimal_path;
}
