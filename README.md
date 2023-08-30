### Memory Paging Optimization Project

The objective of this project is to devise a paging strategy that enhances memory access performance within a specified set of pre-defined programs. I have implemented two distinct algorithms: the Last Recently Used (LRU) algorithm and a Predictive Paging algorithm.

The LRU algorithm, located in `pager-lru.c`, aims to minimize page faults. However, it may lead to program slowdowns due to the occurrence of frequent page faults. To address this challenge, I have also developed the Predictive Paging algorithm, accessible in `pager-predict.c`.

The project's execution involves a paging simulator that orchestrates a suite of 5 pre-defined programs. These programs operate within the constraints of a limited number of shared physical pages. The objective is to employ the paging algorithm effectively, ensuring the necessary pages are paged in based on the algorithm's logic.

The Predictive Paging algorithm takes a forward-looking approach by predicting the pages each program will require in the near future. By preemptively swapping in these pages before they are needed, it significantly reduces page faults and optimizes performance. This predictive mechanism operates ahead of program execution by approximately 100 to 200 ticks.

To achieve these predictions, I employ Markov State Models to classify program behavior, such as linear, loop, or double nested. This classification enables the algorithm to intelligently page in the corresponding pages based on the anticipated program trajectory.

Feel free to explore the codebase and delve into the intricacies of these paging algorithms. This project serves as a testament to my expertise in memory optimization techniques and algorithmic problem-solving.
