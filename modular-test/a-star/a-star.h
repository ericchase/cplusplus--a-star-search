#pragma once

template <typename GRAPH>
std::stack <typename GRAPH::node>
    a_star
    (
        const typename GRAPH& graph,
        const typename GRAPH::node& start,
        const typename GRAPH::node& goal
    )
{
    typedef std::pair <typename GRAPH::weight, typename GRAPH::node> weighted_node;

    std::set <weighted_node> open;
    std::set < typename GRAPH::node > closed;

    std::map < typename GRAPH::node, typename GRAPH::node > parent_of;
    std::map < typename GRAPH::node, typename GRAPH::weight > path_cost_of;

    open.emplace(0, start);
    parent_of[start] = start;
    path_cost_of[start] = 0;

    //static int loopCount = 0;
    while (!open.empty())
    {
        // can't be a reference
        const typename GRAPH::node current = open.begin()->second;

        if (current == goal)
            break;

        open.erase(open.begin());

        if (closed.find(current) != closed.end())
            continue;
        closed.insert(current);

        for (typename GRAPH::node neighbor : graph.get_neighbors_of(current))
        {
            if (closed.find(neighbor) != closed.end())
                continue;

            //loopCount++;

            const typename GRAPH::weight g_n = path_cost_of[current] + graph.get_cost_between(current, neighbor);

            if (path_cost_of.find(neighbor) != path_cost_of.end())
                if (path_cost_of[neighbor] < g_n)
                    continue;

            typename GRAPH::weight f_n = g_n + graph.get_estimate_between(neighbor, goal);

            open.emplace(f_n, neighbor);
            parent_of[neighbor] = current;
            path_cost_of[neighbor] = g_n;
        }
    }

    std::stack < typename GRAPH::node > optimal_path;

    if (!open.empty())
    {
        // cannot be const or reference
        typename GRAPH::node node = open.begin()->second;

        optimal_path.push(node);
        while (parent_of.at(node) != node)
        {
            node = parent_of.at(node);
            optimal_path.push(node);
        }
    }

    return optimal_path;
}
