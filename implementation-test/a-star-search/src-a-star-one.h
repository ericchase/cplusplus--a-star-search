// Influenced by:
// https://www.redblobgames.com/pathfinding/a-star/implementation.html#orge3d18c2


#pragma once

template <typename NODE, typename WEIGHT>
std::stack <NODE> a_star_one
    (
        NODE start, NODE goal,
        std::vector <NODE> (*get_neighbors_of) (const NODE&),
        WEIGHT (*get_cost_of) (const NODE&, const NODE&),
        WEIGHT (*get_estimate_of) (const NODE&, const NODE&)
    )
{
    typedef std::pair <WEIGHT, NODE> weighted_node;
    std::priority_queue <weighted_node, std::deque <weighted_node>, std::greater <weighted_node>> fringe;
    std::set <NODE> closed;
    std::map <NODE, NODE> parent_of;
    std::map <NODE, WEIGHT> path_cost_of;

    fringe.emplace(0, start);
    parent_of[start] = start;
    path_cost_of[start] = 0;

    //static int loopCount = 0;
    while (!fringe.empty())
    {
        // can't be a reference
        const NODE current = fringe.top().second;

        if (current == goal)
            break;

        fringe.pop();

        //if (closed.find(current) != closed.end())
        //    continue;
        closed.insert(current);


        for (NODE neighbor : get_neighbors_of(current))
        {
            //loopCount++;

            const WEIGHT g_n = path_cost_of[current] + get_cost_of(current, neighbor);

            if (path_cost_of.find(neighbor) != path_cost_of.end())
                if (path_cost_of[neighbor] < g_n)
                    continue;

            WEIGHT f_n = g_n + get_estimate_of(neighbor, goal);

            fringe.emplace(f_n, neighbor);
            parent_of[neighbor] = current;
            path_cost_of[neighbor] = g_n;
        }
    }
    //std::cout << "Loops: " << loopCount << "\n" << std::endl;

    std::stack <NODE> optimal_path;

    if (!fringe.empty())
    {
        // cannot be const or reference
        NODE node = fringe.top().second;

        optimal_path.push(node);
        while (parent_of[node] != node)
        {
            node = parent_of[node];
            optimal_path.push(node);
        }
    }

    return optimal_path;
}
