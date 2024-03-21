# Zuckerman Numbers
 Algorithm for counting and finding the Zuckerman numbers.

[Zuckerman_dfs.cpp](https://github.com/hqztrue/ZuckermanNumbers/blob/main/backup/Zuckerman_dfs.cpp):  
The old basic single-core meet-in-the-middle implementation. Enumerate all possible set of digits.

[Zuckerman_arr.cpp](https://github.com/hqztrue/ZuckermanNumbers/blob/main/backup/Zuckerman_arr.cpp):  
New single-core meet-in-the-middle implementation. Speed up by merging sets of digits with the same product, and precomputes the list of numbers corresponding to each half product.  
Complexity: O((b-1)^{N/2}*N^O(b/log b)).

[Zuckerman_parallel_thread.cpp](https://github.com/hqztrue/ZuckermanNumbers/blob/main/Zuckerman_parallel_thread.cpp):  
Parallel implementation using std::thread. Using the same algorithm as Zuckerman_parallel_omp.cpp.

[Zuckerman_parallel_omp.cpp](https://github.com/hqztrue/ZuckermanNumbers/blob/main/Zuckerman_parallel_omp.cpp):  
Parallel implementation using OpenMP.  
The current fastest version (works for general b, but has special optimization for b=10).  
Generally speaking we can prune using the last few digits for composite b.


Remark:  
1. All codes work for general b.
2. For numbers larger than n=10^20 for b=10, we need to use __int128 to store the modulus M. Simply turn on the LARGE_NUM macro.

