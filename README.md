svm
===

In this project, our initial aim was to rank various algorithms for multi-class Support Vector Machines, not based on their test accuracies but only using the training data.
We applied Data Envelopment Analysis (DEA) to assign relative efficiencies for each of the hyper-plane that is constructed. These efficiencies are used to rank the methods. Conventionally, the ranking of various methods has been done only on the basis of test accuracies. We believe that this method to compare is not just inadequate but is also highly dependent on the data-sets used.
Thus, we propose a method to rank these hyper-planes based on their characteristics like S-span, margin, training accuracy and fraction of Support Vectors. The methods that are compared are One-vs-One, One-vs-All, Dense and Sparse.
To accomplish this, we slightly modified the library libsvm to compute the above parameters for each hyper-plane. Then, to compute the relative CCR efficiencies, we used a tool called GNU Linear Programming Kit (GLPK).