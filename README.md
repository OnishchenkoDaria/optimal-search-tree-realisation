#The optimal binary search algorithm using threads
---
##*the project shows the work of the algorithm of finding the vertex for optimal B tree completed in only and multiple threads with the time comparison*

---
The program has 3 classes: 

- Rational represents the rational digits presented as a irreducible fraction;
- OptimalBST which represents the B tree as the structure;
- runTests which has only function which run sequential and parallel tests fo the algorithm "finding the vertex for optimal B tree". During work the result (found vertex) and the thread where each chunk of the code was processed;

At the end the time of each test is displayed for user to compare
For example in this realization our program takes 100 records of prepared vertexes dataset from `index.txt`
The time difference is following:

![image](https://github.com/OnishchenkoDaria/optimal-search-tree-realisation/assets/145560302/a0cb1a21-2ed9-4749-b3c5-7abb0ad970da)

![image](https://github.com/OnishchenkoDaria/optimal-search-tree-realisation/assets/145560302/6c883db0-ae65-445e-aaf5-90da00ffb811)


so we can see that with enlarging the dataset the time effectiveness would grow that is why using multiple threads is benefitial

---

The unit tests are done with `google tests` and the documentation is done with `doxygen`
