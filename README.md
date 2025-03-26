#Linear Regression in C

This project implements **linear regression** using the **normal equation** method in C. It includes matrix operations like multiplication, transposition, and inversion—essential components of solving for regression weights without external libraries.

---

## Files

- `main.c`: Entry point; tests the linear regression implementation on a sample dataset.
- `model.h`: Header file defining data structures and function declarations.
- `model.c`: Implements matrix operations and the linear regression algorithm.

---

## How It Works

1. **Data Setup**: `main.c` initializes a dataset with 4 samples and 3 features (including a bias term).
2. **Training**: Weights are computed using the normal equation:
   ```
   W = (X^T X)^(-1) X^T Y
   ```
3. **Prediction**: A test input is passed to the model to predict an output.
4. **Output**: The predicted value and learned weights are printed to the console.

---

## Building and Running

Compile the program using GCC:

```bash
gcc -o linear_regression main.c model.c -lm
```

Run the executable:

```bash
./linear_regression
```

Expected output:

```
Prediction for [1, 5, 9]: 14.000000
Learned Weights:
-0.000000 
1.000000 
1.000000 
```

---

## Core Concepts Used

- Matrix Multiplication
- Matrix Transposition
- Matrix Inversion (via Gauss-Jordan elimination)
- Dynamic Memory Management
- Struct-based data abstraction for matrices and models

---

## Sample Dataset

| Bias | Feature1 | Feature2 | Output |
|------|----------|----------|--------|
| 1    | 2        | 3        | 5      |
| 1    | 3        | 5        | 8      |
| 1    | 1        | 1        | 2      |
| 1    | 4        | 6        | 10     |

The model learns the relationship:
```
y = 1 * x0 + 1 * x1 + 1 * x2
```

---

## License

This project is open source.
