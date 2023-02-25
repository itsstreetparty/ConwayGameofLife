# ConwayGameofLife
ConwayGameofLife


#LOGIC OF THE RULES OF LIFE

* Input matrix that represents the initial state of the cells in the Game of Life. The matrix is typically initialized with a random distribution of live and dead cells.

* iterate over each element in the matrix, one element at a time, to determine the state of the cell in the next generation.

* Determine whether it is a live cell or a dead cell based on its value (1 for live, 0 for dead).

* Count the number of live cells in the 8 neighboring cells around the current element. These 8 neighboring cells are the ones directly above, below, to the left, to the right, and in the diagonal directions.

* If the current cell is a live cell and has 2 or 3 live neighbors, it survives to the next generation and its value in the new matrix is set to 1. If the cell has any other number of live neighbors, it dies and its value in the new matrix is set to 0.

* If the current cell is a dead cell and has exactly 3 live neighbors, it becomes a live cell in the next generation and its value in the new matrix is set to 1. If the cell has any other number of live neighbors, it remains dead and its value in the new matrix is set to 0.

# IMPROVEMENTS

1. Use toroidal wrapping to avoid the need for special edge handling (DONE)
2. Use bitsets if the matrix is not sparse (i.e., has a low density of live cells) (NOT POSSIBLE BECAUSE dimensions of the matrix know at COMPILE TIME)
3. Use parallel programming if the matrix is large and the number of available cores is sufficient. #todo
4. Use a sparse matrix representation if the matrix is sparse (i.e., has a high density of zeros) #TODO
5. Use caching to improve performance. For example, you can precompute the neighbors of each cell and store them in a data structure to avoid recomputing them for each iteration of the game (DONE)
6. Avoid unnecessary memory allocations. For example, you can reuse the same matrix for each iteration of the game rather than allocating a new matrix each time. (DONE)
7. Consider using SIMD (Single Instruction, Multiple Data) instructions if they are available on your system. SIMD instructions can perform the same operation on multiple data elements in parallel, which can significantly improve performance.
8. Optimize the order in which you update the cells. For example, you can update the cells in a raster scan order (i.e., left-to-right, top-to-bottom) to improve locality of reference and cache usage. #todo


