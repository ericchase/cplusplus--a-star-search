# cplusplus-a-star-search
Two implementations of the A* search algorithm that can be found online. Performance comparison and improvements to the implementation.

From my initial understanding, there were two different ways to implement the A* algorithm. After further analysis, I realized that the two implementations in question were simply incomplete. One uses a priority queue for the open list and neglects the closed list. The other uses sets for the open and closed lists. Use of the closed list results in significant performance changes. Whether or not one version is an improvement over the other is subject to extensive testing. However, the implementation which uses the closed list was slightly flawed to begin with, so I made the necessary corrections. Note that the priority queue works similarly to an ordered set, but the set provides more functionality to the user.

I would prefer the second implementation to the first, as my rudimentary profiling expedition showed some promising results. The problem domain for my project is not ideal for testing further. I enjoyed working with the search algorithm and see myself using it again in the future. When that time comes, I will profile the implementations again and update this repository.

From my initial comments in a-star-search.cpp:
<pre>
// A* one
// The first A* implementation uses a priority queue for the open list
// but does not have a closed list. It skips the overhead of checking
// the closed list, which seems like a clever move at first. However,
// it uses nearly 1/3 more loops than if a closed list was used. One
// would need to profile both implementations for accurate details.

// A* two
// The second A* implementation uses two sets (ideally an ordered set
// and an unordered set, but for C++ there's a ton of groundwork needed
// for A* and I ran into some issues with the unordered version). Most
// sources do a check into the open list when dealing with neighbors,
// but I found it to be a useless check. They also check the closed list
// for each neighbor, which is good, but they don't check the closed
// list for the current node, which is bad. This extra check is able to
// pass over a significant amount of cost and heuristic function calls.

// Profiling (in Release configuration)
// I'm not an expert with profiling, but one of the details that stood
// out to me was the call count to std::lower_bound. In one instance,
// A* one showed 24,415 calls whereas A* two showed only 8,238. This was
// the most significant difference. Since the 8puzzle problem is fairly
// easy to solve, even with a ton of moves, a more complicated domain
// will be necessary to compare the A* implementations effectively.

// Conclusion
// My educated guess says that using the closed list will improve overall
// performance for the A* algorithm.
</pre>
