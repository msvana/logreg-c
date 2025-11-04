# Logistic Regression in C

Why? Because I can. And also becuase I'm an ML guy who wants to learn C.
Besides Logistic Regression itself, the project also contains simple
implementations of required primives:

- 2D array
- Dataset struct and loader
- Train and test split
- Accuracy calculation

## Compilation

```bash
mkdir build
cd build
cmake ..
make
```

Cmake creates two targets:
- A static library `liblogreg.a`
- A binary called `logreg` with a simple usage example

## Examp

```bash
./logreg ../iris.csv
```



