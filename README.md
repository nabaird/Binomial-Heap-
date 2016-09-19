# Binomial-Heap-
My implementation of a priority queue which supports merging 

Binomial trees are defined as follows:
  A tree of height 0 consists of one node.
  A tree of height n consists of 1 of every tree of height less than n. 
  
  This allows us to organize our queue very efficiently. We have an array of pointers, each pointing to the root of a binomial tree. The root of each tree is the smallest value in the tree. The height of each tree is the index where the tree is stored. When two trees of the same height must be combined (which occurs during merges, insertions and deletions) they are easily combined and stored in the following index (if the following index is occupied, the process is repeated).
  
  Merging binomial trees takes constant time. This is because the same number of links need to be adjusted, regardless of how large the trees are. So merging two binomial queues occures at logarithmic speed. 
