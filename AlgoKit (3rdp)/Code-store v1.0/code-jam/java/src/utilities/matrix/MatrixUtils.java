/*  Class Matrix
 *
 *   Defines a matrix and includes the methods needed
 *   for standard matrix manipulations, e.g. multiplation,
 *   and related procedures, e.g. solution of linear
 *   simultaneous equations
 *
 ***************************************************************************************/

package utilities.matrix;

import static java.lang.Math.*;
import static utilities.Constants.*;

import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;

/**
 * Jama = Java Matrix class.
 * <P>
 * The Java Matrix Class provides the fundamental operations of numerical linear
 * algebra. Various constructors create Matrices from two dimensional arrays of
 * double precision floating point numbers. Various "gets" and "sets" provide
 * access to submatrices and matrix elements. Several methods implement basic
 * matrix arithmetic, including matrix addition and multiplication, matrix
 * norms, and element-by-element array operations. Methods for reading and
 * printing matrices are also included. All the operations in this version of
 * the Matrix Class involve real matrices. Complex matrices may be handled in a
 * future version.
 * <P>
 * Five fundamental matrix decompositions, which consist of pairs or triples of
 * matrices, permutation vectors, and the like, produce results in five
 * decomposition classes. These decompositions are accessed by the Matrix class
 * to compute solutions of simultaneous linear equations, determinants, inverses
 * and other matrix functions. The five decompositions are:
 * <P>
 * <UL>
 * <LI>Cholesky Decomposition of symmetric, positive definite matrices.
 * <LI>LU Decomposition of rectangular matrices.
 * <LI>QR Decomposition of rectangular matrices.
 * <LI>Singular Value Decomposition of rectangular matrices.
 * <LI>Eigenvalue Decomposition of both symmetric and nonsymmetric square
 * matrices.
 * </UL>
 * <DL>
 * <DT><B>Example of use:</B></DT>
 * <P>
 * <DD>Solve a linear system A x = b and compute the residual norm, ||b - A x||.
 * <P>
 * 
 * <PRE>
 * double[][] vals = { { 1., 2., 3 }, { 4., 5., 6. }, { 7., 8., 10. } };
 * Matrix A = new Matrix(vals);
 * Matrix b = Matrix.random(3, 1);
 * Matrix x = A.solve(b);
 * Matrix r = A.times(x).minus(b);
 * double rnorm = r.normInf();
 * </PRE>
 * 
 * </DD>
 * </DL>
 * 
 * @author The MathWorks, Inc. and the National Institute of Standards and
 *         Technology.
 * @version 5 August 1998
 */
public class MatrixUtils
    implements Cloneable, Serializable
{
    /**
     * 
     */
    private static final long serialVersionUID = 3862860787333698622L;
    /*
     * ------------------------ Class variables ------------------------
     */
    private int numberOfRows = 0; // number of rows
    private int numberOfColumns = 0; // number of columns
    private double matrix[][] = null; // 2-D Matrix
    private final double hessenberg[][] = null; // 2-D Hessenberg equivalent
    private final boolean hessenbergDone = false; // = true when Hessenberg
                                                  // matrix
    // calculated
    private int permutationIndex[] = null; // row permutation index
    private double rowSwapIndex = 1.0D; // row swap index
    private final int numberOfRotations = 0; // number of rotations in Jacobi
    private boolean matrixCheck = true; // check on matrix status
                                        // true - no problems encountered in LU
                                        // decomposition
                                        // false - attempted a LU decomposition
                                        // on a singular matrix
    private boolean suppressErrorMessage = false; // true - LU decompostion
                                                  // failure message supressed
    private double tiny = 1.0e-100; // small number replacing zero in LU
                                    // decomposition

    /*
     * ------------------------ Constructors ------------------------
     */

    /**
     * Constructs a square matrix by default (wrapper method)
     */
    public MatrixUtils(int numberOfRows)
    {
        this(numberOfRows, numberOfRows);
    }

    /**
     * Construct a numberOfRows-by-numberOfColumns matrix of zeros.
     * 
     * @param numberOfRows Number of rows.
     * @param numberOfColumns Number of colums.
     */
    public MatrixUtils(int numberOfRows, int numberOfColumns)
    {
        this.numberOfRows = numberOfRows;
        this.numberOfColumns = numberOfColumns;
        this.matrix = new double[numberOfRows][numberOfColumns];
        this.permutationIndex = new int[numberOfRows];
        for (int i = 0; i < numberOfRows; i++) {
            this.permutationIndex[i] = i;
        }
    }

    /**
     * Construct a numberOfRows-by-numberOfColumns constant matrix.
     * 
     * @param numberOfRows Number of rows.
     * @param numberOfColumns Number of colums.
     * @param constant Fill the matrix with this scalar value.
     */
    public MatrixUtils(int numberOfRows, int numberOfColumns, double constant)
    {
        this.numberOfRows = numberOfRows;
        this.numberOfColumns = numberOfColumns;
        this.matrix = new double[numberOfRows][numberOfColumns];
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++)
                this.matrix[i][j] = constant;
        }
        this.permutationIndex = new int[numberOfRows];
        for (int i = 0; i < numberOfRows; i++)
            this.permutationIndex[i] = i;
    }

    // Construct matrix with a copy of an existing numberOfRows x
    // numberOfColumns 2-D array of variables
    public MatrixUtils(double[][] twoD)
    {
        this.numberOfRows = twoD.length;
        this.numberOfColumns = twoD[0].length;
        this.matrix = new double[this.numberOfRows][this.numberOfColumns];
        for (int i = 0; i < numberOfRows; i++) {
            if (twoD[i].length != numberOfColumns)
                throw new IllegalArgumentException(
                                "All rows must have the same length");
            for (int j = 0; j < numberOfColumns; j++) {
                this.matrix[i][j] = twoD[i][j];
            }
        }
        this.permutationIndex = new int[numberOfRows];
        for (int i = 0; i < numberOfRows; i++)
            this.permutationIndex[i] = i;
    }

    // Construct matrix with a copy of an existing numberOfRows x
    // numberOfColumns 2-D array of longs
    public MatrixUtils(long[][] twoD)
    {
        this.numberOfRows = twoD.length;
        this.numberOfColumns = twoD[0].length;
        for (int i = 1; i < numberOfRows; i++) {
            if (twoD[i].length != numberOfColumns)
                throw new IllegalArgumentException(
                                "All rows must have the same length");
        }
        this.matrix = new double[this.numberOfRows][this.numberOfColumns];
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                this.matrix[i][j] = twoD[i][j];
            }
        }
        this.permutationIndex = new int[numberOfRows];
        for (int i = 0; i < numberOfRows; i++)
            this.permutationIndex[i] = i;
    }

    // Construct matrix with a copy of an existing numberOfRows x
    // numberOfColumns 2-D array of ints
    public MatrixUtils(int[][] twoD)
    {
        this.numberOfRows = twoD.length;
        this.numberOfColumns = twoD[0].length;
        for (int i = 1; i < numberOfRows; i++) {
            if (twoD[i].length != numberOfColumns)
                throw new IllegalArgumentException(
                                "All rows must have the same length");
        }
        this.matrix = new double[this.numberOfRows][this.numberOfColumns];
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                this.matrix[i][j] = twoD[i][j];
            }
        }
        this.permutationIndex = new int[numberOfRows];
        for (int i = 0; i < numberOfRows; i++)
            this.permutationIndex[i] = i;
    }

    // Construct matrix with a copy of an existing numberOfRows x
    // numberOfColumns 2-D array of BigDecimals
    public MatrixUtils(BigDecimal[][] twoD)
    {
        this.numberOfRows = twoD.length;
        this.numberOfColumns = twoD[0].length;
        for (int i = 1; i < numberOfRows; i++) {
            if (twoD[i].length != numberOfColumns)
                throw new IllegalArgumentException(
                                "All rows must have the same length");
        }
        this.matrix = new double[this.numberOfRows][this.numberOfColumns];
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                this.matrix[i][j] = twoD[i][j].doubleValue();
            }
        }
        this.permutationIndex = new int[numberOfRows];
        for (int i = 0; i < numberOfRows; i++)
            this.permutationIndex[i] = i;
    }

    // Construct matrix with a copy of an existing numberOfRows x
    // numberOfColumns 2-D array of BigIntegers
    public MatrixUtils(BigInteger[][] twoD)
    {
        this.numberOfRows = twoD.length;
        this.numberOfColumns = twoD[0].length;
        for (int i = 1; i < numberOfRows; i++) {
            if (twoD[i].length != numberOfColumns)
                throw new IllegalArgumentException(
                                "All rows must have the same length");
        }
        this.matrix = new double[this.numberOfRows][this.numberOfColumns];
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                this.matrix[i][j] = twoD[i][j].doubleValue();
            }
        }
        this.permutationIndex = new int[numberOfRows];
        for (int i = 0; i < numberOfRows; i++)
            this.permutationIndex[i] = i;
    }

    // METHODS
    // SET VALUES
    // reset value of tiny used to replace zero in LU decompostions
    // If not set: 1e-100 used
    public void resetLUzero(double zeroValue)
    {
        this.tiny = zeroValue;
    }

    // Set the matrix with a copy of an existing numberOfRows x numberOfColumns
    // 2-D matrix of variables
    public void setTwoDarray(double[][] aarray)
    {
        if (this.numberOfRows != aarray.length)
            throw new IllegalArgumentException(
                            "row length of this Matrix differs from that of the 2D array argument");
        if (this.numberOfColumns != aarray[0].length)
            throw new IllegalArgumentException(
                            "column length of this Matrix differs from that of the 2D array argument");
        for (int i = 0; i < numberOfRows; i++) {
            if (aarray[i].length != numberOfColumns)
                throw new IllegalArgumentException(
                                "All rows must have the same length");
            for (int j = 0; j < numberOfColumns; j++) {
                this.matrix[i][j] = aarray[i][j];
            }
        }
    }

    // Set an individual array element
    // i = row index
    // j = column index
    // aa = value of the element
    public void setElement(int i, int j, double aa)
    {
        this.matrix[i][j] = aa;
    }

    // Set a sub-matrix starting with row index i, column index j
    public void setSubMatrix(int i, int j, double[][] subMatrix)
    {
        int k = subMatrix.length;
        int l = subMatrix[0].length;
        if (i + k - 1 >= this.numberOfRows)
            throw new IllegalArgumentException(
                            "Sub-matrix position is outside the row bounds of this Matrix");
        if (j + l - 1 >= this.numberOfColumns)
            throw new IllegalArgumentException(
                            "Sub-matrix position is outside the column bounds of this Matrix");

        int m = 0;
        int n = 0;
        for (int p = 0; p < k; p++) {
            n = 0;
            for (int q = 0; q < l; q++) {
                this.matrix[i + p][j + q] = subMatrix[m][n];
                n++;
            }
            m++;
        }
    }

    // Set a sub-matrix starting with row index i, column index j
    // and ending with row index k, column index l
    // See setSubMatrix above - this method has been retained for compatibility
    // purposes
    public void setSubMatrix(int i, int j, int k, int l, double[][] subMatrix)
    {
        this.setSubMatrix(i, j, subMatrix);
    }

    // Set a sub-matrix
    // row = array of row indices
    // col = array of column indices
    public void setSubMatrix(int[] row, int[] col, double[][] subMatrix)
    {
        int n = row.length;
        int m = col.length;
        for (int p = 0; p < n; p++) {
            for (int q = 0; q < m; q++) {
                this.matrix[row[p]][col[q]] = subMatrix[p][q];
            }
        }
    }

    // Get the value of matrixCheck
    public boolean getMatrixCheck()
    {
        return this.matrixCheck;
    }

    // SPECIAL MATRICES
    // Construct a square identity matrix
    public static MatrixUtils identityMatrix(int numberOfRows)
    {
        MatrixUtils special = new MatrixUtils(numberOfRows, numberOfRows);
        for (int i = 0; i < numberOfRows; i++) {
            special.matrix[i][i] = 1.0;
        }
        return special;
    }

    // Construct a square unit matrix
    public static MatrixUtils unitMatrix(int numberOfRows)
    {
        MatrixUtils special = new MatrixUtils(numberOfRows, numberOfRows);
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfRows; j++) {
                special.matrix[i][j] = 1.0;
            }
        }
        return special;
    }

    // Construct a rectangular unit matrix
    public static MatrixUtils unitMatrix(int numberOfRows, int numberOfColumns)
    {
        MatrixUtils special = new MatrixUtils(numberOfRows, numberOfColumns);
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                special.matrix[i][j] = 1.0;
            }
        }
        return special;
    }

    // Construct a square scalar matrix
    public static MatrixUtils scalarMatrix(int numberOfRows, double diagconst)
    {
        MatrixUtils special = new MatrixUtils(numberOfRows, numberOfRows);
        double[][] specialArray = special.getArray();
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = i; j < numberOfRows; j++) {
                if (i == j) {
                    specialArray[i][j] = diagconst;
                }
            }
        }
        return special;
    }

    // Construct a rectangular scalar matrix
    public static MatrixUtils scalarMatrix(
        int numberOfRows,
        int numberOfColumns,
        double diagconst)
    {
        MatrixUtils special = new MatrixUtils(numberOfRows, numberOfColumns);
        double[][] specialArray = special.getArray();
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = i; j < numberOfColumns; j++) {
                if (i == j) {
                    specialArray[i][j] = diagconst;
                }
            }
        }
        return special;
    }

    // Construct a square diagonal matrix
    public static MatrixUtils diagonalMatrix(int numberOfRows, double[] diag)
    {
        if (diag.length != numberOfRows)
            throw new IllegalArgumentException(
                            "matrix dimension differs from diagonal array length");
        MatrixUtils special = new MatrixUtils(numberOfRows, numberOfRows);
        double[][] specialArray = special.getArray();
        for (int i = 0; i < numberOfRows; i++) {
            specialArray[i][i] = diag[i];
        }
        return special;
    }

    // Construct a rectangular diagonal matrix
    public static MatrixUtils diagonalMatrix(
        int numberOfRows,
        int numberOfColumns,
        double[] diag)
    {
        if (diag.length != numberOfRows)
            throw new IllegalArgumentException(
                            "matrix dimension differs from diagonal array length");
        MatrixUtils special = new MatrixUtils(numberOfRows, numberOfColumns);
        double[][] specialArray = special.getArray();
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = i; j < numberOfColumns; j++) {
                if (i == j) {
                    specialArray[i][j] = diag[i];
                }
            }
        }
        return special;
    }

    // GET VALUES
    // Return the number of rows
    public int getNumRows()
    {
        return this.numberOfRows;
    }

    // Return the number of columns
    public int getNumColumns()
    {
        return this.numberOfColumns;
    }

    // Return a reference to the internal 2-D array
    public double[][] getArray()
    {
        return this.matrix;
    }

    // Return a copy of the internal 2-D array
    public double[][] getArrayCopy()
    {
        double[][] c = new double[this.numberOfRows][this.numberOfColumns];
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                c[i][j] = this.matrix[i][j];
            }
        }
        return c;
    }

    // Return a copy of a row
    public double[] getRowCopy(int i)
    {
        if (i >= this.numberOfRows)
            throw new IllegalArgumentException("Row index, " + i
                            + ", must be less than the number of rows, "
                            + this.numberOfRows);
        if (i < 0)
            throw new IllegalArgumentException("Row index, " + i
                            + ", must be zero or positive");

        double[] copy = new double[matrix[i].length];
        System.arraycopy(this.matrix[i], 0, copy, 0, this.matrix[i].length);
        return copy;
    }

    // Return a copy of a column
    public double[] getColumnCopy(int ii)
    {
        if (ii >= this.numberOfColumns)
            throw new IllegalArgumentException("Column index, " + ii
                            + ", must be less than the number of columns, "
                            + this.numberOfColumns);
        if (ii < 0)
            throw new IllegalArgumentException("column index, " + ii
                            + ", must be zero or positive");
        double[] col = new double[this.numberOfRows];
        for (int i = 0; i < numberOfRows; i++) {
            col[i] = this.matrix[i][ii];
        }
        return col;
    }

    // Return a single element of the internal 2-D array
    public double getSingleElement(int i, int j)
    {
        return this.matrix[i][j];
    }

    // Return a single element of the internal 2-D array
    // included for backward compatibility with incorrect earlier documentation
    public double getSingleElementCopy(int i, int j)
    {
        return this.matrix[i][j];
    }

    // Return a single element of the internal 2-D array
    // included for backward compatibility with incorrect earlier documentation
    public double getSingleElementPointer(int i, int j)
    {
        return this.matrix[i][j];
    }

    // Return a sub-matrix starting with row index i, column index j
    // and ending with row index k, column index l
    public MatrixUtils getSubMatrix(int i, int j, int k, int l)
    {
        if (i > k) throw new IllegalArgumentException("row indices inverted");
        if (j > l)
            throw new IllegalArgumentException("column indices inverted");
        if (k >= this.numberOfRows)
            throw new IllegalArgumentException(
                            "Sub-matrix position is outside the row bounds of this Matrix");
        if (l >= this.numberOfColumns)
            throw new IllegalArgumentException(
                            "Sub-matrix position is outside the column bounds of this Matrix"
                                            + i + " " + l);

        int n = k - i + 1, m = l - j + 1;
        MatrixUtils subMatrix = new MatrixUtils(n, m);
        double[][] sarray = subMatrix.getArray();
        for (int p = 0; p < n; p++) {
            for (int q = 0; q < m; q++) {
                sarray[p][q] = this.matrix[i + p][j + q];
            }
        }
        return subMatrix;
    }

    // Return a sub-matrix
    // row = array of row indices
    // col = array of column indices
    public MatrixUtils getSubMatrix(int[] row, int[] col)
    {
        int n = row.length;
        int m = col.length;
        MatrixUtils subMatrix = new MatrixUtils(n, m);
        double[][] sarray = subMatrix.getArray();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sarray[i][j] = this.matrix[row[i]][col[j]];
            }
        }
        return subMatrix;
    }

    // Return a reference to the permutation index array
    public int[] getIndexReference()
    {
        return this.permutationIndex;
    }

    // Return a reference to the permutation index array
    // included for backward compatibility with incorrect earlier documentation
    public int[] getIndexPointer()
    {
        return this.permutationIndex;
    }

    // Return a copy of the permutation index array
    public int[] getIndexCopy()
    {
        int[] indcopy = new int[this.numberOfRows];
        for (int i = 0; i < this.numberOfRows; i++) {
            indcopy[i] = this.permutationIndex[i];
        }
        return indcopy;
    }

    // Return the row swap index
    public double getSwap()
    {
        return this.rowSwapIndex;
    }

    // COPY
    /**
     * Performs a deep copy of a matrix
     */
    // Copy a Matrix [static method]
    public static MatrixUtils copy(MatrixUtils a)
    {
        if (a == null) {
            return null;
        } else {
            int nr = a.numberOfRows;
            int nc = a.numberOfColumns;
            double[][] aarray = a.getArray();
            MatrixUtils b = new MatrixUtils(nr, nc);
            b.numberOfRows = nr;
            b.numberOfColumns = nc;
            double[][] barray = b.getArray();
            for (int i = 0; i < nr; i++) {
                for (int j = 0; j < nc; j++) {
                    barray[i][j] = aarray[i][j];
                }
            }
            for (int i = 0; i < nr; i++)
                b.permutationIndex[i] = a.permutationIndex[i];
            return b;
        }
    }

    // Copy a Matrix [instance method]
    public MatrixUtils copy()
    {
        if (this == null) {
            return null;
        } else {
            int nr = this.numberOfRows;
            int nc = this.numberOfColumns;
            MatrixUtils b = new MatrixUtils(nr, nc);
            double[][] barray = b.getArray();
            b.numberOfRows = nr;
            b.numberOfColumns = nc;
            for (int i = 0; i < nr; i++) {
                for (int j = 0; j < nc; j++) {
                    barray[i][j] = this.matrix[i][j];
                }
            }
            for (int i = 0; i < nr; i++)
                b.permutationIndex[i] = this.permutationIndex[i];
            return b;
        }
    }

    // Clone a Matrix
    @Override
    public Object clone()
    {
        if (this == null) {
            return null;
        } else {
            int nr = this.numberOfRows;
            int nc = this.numberOfColumns;
            MatrixUtils b = new MatrixUtils(nr, nc);
            double[][] barray = b.getArray();
            b.numberOfRows = nr;
            b.numberOfColumns = nc;
            for (int i = 0; i < nr; i++) {
                for (int j = 0; j < nc; j++) {
                    barray[i][j] = this.matrix[i][j];
                }
            }
            for (int i = 0; i < nr; i++)
                b.permutationIndex[i] = this.permutationIndex[i];
            return b;
        }
    }

    // COLUMN MATRICES
    // Converts a 1-D array of doubles to a column matrix
    public static MatrixUtils columnMatrix(double[] darray)
    {
        int nr = darray.length;
        MatrixUtils pp = new MatrixUtils(nr, 1);
        for (int i = 0; i < nr; i++)
            pp.matrix[i][0] = darray[i];
        return pp;
    }

    // ROW MATRICES
    // Converts a 1-D array of doubles to a row matrix
    public static MatrixUtils rowMatrix(double[] darray)
    {
        int nc = darray.length;
        MatrixUtils pp = new MatrixUtils(1, nc);
        for (int i = 0; i < nc; i++)
            pp.matrix[0][i] = darray[i];
        return pp;
    }

    // ADDITION
    // Add this matrix to matrix B. This matrix remains unaltered [instance
    // method]
    public MatrixUtils plus(MatrixUtils bmat)
    {
        if ((this.numberOfRows != bmat.numberOfRows)
                        || (this.numberOfColumns != bmat.numberOfColumns)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }
        int nr = bmat.numberOfRows;
        int nc = bmat.numberOfColumns;
        MatrixUtils cmat = new MatrixUtils(nr, nc);
        double[][] carray = cmat.getArray();
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                carray[i][j] = this.matrix[i][j] + bmat.matrix[i][j];
            }
        }
        return cmat;
    }

    /**
     * C = A + B
     * 
     * Add this matrix to 2-D array B. This matrix remains unaltered [instance
     * method]
     * 
     * @param B another matrix
     * @return A + B
     */
    //
    public MatrixUtils plus(double[][] bmat)
    {
        int nr = bmat.length;
        int nc = bmat[0].length;
        if ((this.numberOfRows != nr) || (this.numberOfColumns != nc)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }

        MatrixUtils cmat = new MatrixUtils(nr, nc);
        double[][] carray = cmat.getArray();
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                carray[i][j] = this.matrix[i][j] + bmat[i][j];
            }
        }
        return cmat;
    }

    // Add matrices A and B [static method]
    public static MatrixUtils plus(MatrixUtils amat, MatrixUtils bmat)
    {
        if ((amat.numberOfRows != bmat.numberOfRows)
                        || (amat.numberOfColumns != bmat.numberOfColumns)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }
        int nr = amat.numberOfRows;
        int nc = amat.numberOfColumns;
        MatrixUtils cmat = new MatrixUtils(nr, nc);
        double[][] carray = cmat.getArray();
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                carray[i][j] = amat.matrix[i][j] + bmat.matrix[i][j];
            }
        }
        return cmat;
    }

    /**
     * A = A + B
     * 
     * Add matrix B to this matrix [equivalence of +=]
     * 
     * @param B another matrix
     * @return A + B
     */
    public void plusEquals(MatrixUtils bmat)
    {
        if ((this.numberOfRows != bmat.numberOfRows)
                        || (this.numberOfColumns != bmat.numberOfColumns)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }
        int nr = bmat.numberOfRows;
        int nc = bmat.numberOfColumns;

        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                this.matrix[i][j] += bmat.matrix[i][j];
            }
        }
    }

    // SUBTRACTION
    /**
     * Unary minus
     * 
     * @return -A
     */
    public MatrixUtils uMinus()
    {
        MatrixUtils X = new MatrixUtils(numberOfRows, numberOfColumns);
        double[][] C = X.matrix;
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                C[i][j] *= -matrix[i][j];
            }
        }
        return X;
    }

    /**
     * C = A - B
     * 
     * Subtract matrix B from this matrix. This matrix remains unaltered
     * [instance method]
     * 
     * @param B another matrix
     * @return A - B
     */
    public MatrixUtils minus(MatrixUtils bmat)
    {
        if ((this.numberOfRows != bmat.numberOfRows)
                        || (this.numberOfColumns != bmat.numberOfColumns)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }
        int nr = this.numberOfRows;
        int nc = this.numberOfColumns;
        MatrixUtils cmat = new MatrixUtils(nr, nc);
        double[][] carray = cmat.getArray();
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                carray[i][j] = this.matrix[i][j] - bmat.matrix[i][j];
            }
        }
        return cmat;
    }

    // Subtract a 2-D array from this matrix. This matrix remains unaltered
    // [instance method]
    public MatrixUtils minus(double[][] bmat)
    {
        int nr = bmat.length;
        int nc = bmat[0].length;
        if ((this.numberOfRows != nr) || (this.numberOfColumns != nc)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }

        MatrixUtils cmat = new MatrixUtils(nr, nc);
        double[][] carray = cmat.getArray();
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                carray[i][j] = this.matrix[i][j] - bmat[i][j];
            }
        }
        return cmat;
    }

    // Subtract matrix B from matrix A [static method]
    public static MatrixUtils minus(MatrixUtils amat, MatrixUtils bmat)
    {
        if ((amat.numberOfRows != bmat.numberOfRows)
                        || (amat.numberOfColumns != bmat.numberOfColumns)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }
        int nr = amat.numberOfRows;
        int nc = amat.numberOfColumns;
        MatrixUtils cmat = new MatrixUtils(nr, nc);
        double[][] carray = cmat.getArray();
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                carray[i][j] = amat.matrix[i][j] - bmat.matrix[i][j];
            }
        }
        return cmat;
    }

    /**
     * A = A - B
     * 
     * Subtract matrix B from this matrix [equivalent of -=]
     * 
     * @param B another matrix
     * @return A - B
     */
    public void minusEquals(MatrixUtils bmat)
    {
        if ((this.numberOfRows != bmat.numberOfRows)
                        || (this.numberOfColumns != bmat.numberOfColumns)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }
        int nr = bmat.numberOfRows;
        int nc = bmat.numberOfColumns;

        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                this.matrix[i][j] -= bmat.matrix[i][j];
            }
        }
    }

    // MULTIPLICATION
    /** Check if size(A) == size(B) **/
    public void checkMatrixDimensions(MatrixUtils B)
    {
        if (B.numberOfRows != numberOfRows
                        || B.numberOfColumns != numberOfColumns) {
            throw new IllegalArgumentException("Matrix dimensions must agree.");
        }
    }

    /**
     * Linear algebraic matrix multiplication, A * B
     * 
     * Multiply this matrix by a matrix. [instance method]
     * 
     * @param B another matrix
     * @return Matrix product, A * B
     * @exception IllegalArgumentException Matrix inner dimensions must agree.
     */
    // This matrix remains unaltered.
    public MatrixUtils times(MatrixUtils bmat)
    {
        if (this.numberOfColumns != bmat.numberOfRows)
            throw new IllegalArgumentException("Nonconformable matrices");

        MatrixUtils cmat = new MatrixUtils(this.numberOfRows,
                        bmat.numberOfColumns);
        double[][] carray = cmat.getArray();
        double sum = 0.0D;

        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < bmat.numberOfColumns; j++) {
                sum = 0.0D;
                for (int k = 0; k < this.numberOfColumns; k++) {
                    sum += this.matrix[i][k] * bmat.matrix[k][j];
                }
                carray[i][j] = sum;
            }
        }
        return cmat;
    }

    // Multiply this matrix by a 2-D array. [instance method]
    // This matrix remains unaltered.
    public MatrixUtils times(double[][] bmat)
    {
        int nr = bmat.length;
        int nc = bmat[0].length;

        if (this.numberOfColumns != nr)
            throw new IllegalArgumentException("Nonconformable matrices");

        MatrixUtils cmat = new MatrixUtils(this.numberOfRows, nc);
        double[][] carray = cmat.getArray();
        double sum = 0.0D;

        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < nc; j++) {
                sum = 0.0D;
                for (int k = 0; k < this.numberOfColumns; k++) {
                    sum += this.matrix[i][k] * bmat[k][j];
                }
                carray[i][j] = sum;
            }
        }
        return cmat;
    }

    /**
     * Multiply a matrix by a scalar constant [instance method], C = s*A
     * 
     * @param s scalar
     * @return s*A
     */
    public MatrixUtils times(double constant)
    {
        MatrixUtils cmat = new MatrixUtils(this.numberOfRows,
                        this.numberOfColumns);
        double[][] carray = cmat.getArray();

        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                carray[i][j] = this.matrix[i][j] * constant;
            }
        }
        return cmat;
    }

    // Multiply two matrices {static method]
    public static MatrixUtils times(MatrixUtils amat, MatrixUtils bmat)
    {
        if (amat.numberOfColumns != bmat.numberOfRows)
            throw new IllegalArgumentException("Nonconformable matrices");

        MatrixUtils cmat = new MatrixUtils(amat.numberOfRows,
                        bmat.numberOfColumns);
        double[][] carray = cmat.getArray();
        double sum = 0.0D;

        for (int i = 0; i < amat.numberOfRows; i++) {
            for (int j = 0; j < bmat.numberOfColumns; j++) {
                sum = 0.0D;
                for (int k = 0; k < amat.numberOfColumns; k++) {
                    sum += (amat.matrix[i][k] * bmat.matrix[k][j]);
                }
                carray[i][j] = sum;
            }
        }
        return cmat;
    }

    // Multiply a Matrix by a 2-D array of doubles [static method]
    public static MatrixUtils times(MatrixUtils amat, double[][] bmat)
    {
        if (amat.numberOfColumns != bmat.length)
            throw new IllegalArgumentException("Nonconformable matrices");

        MatrixUtils cmat = new MatrixUtils(amat.numberOfRows, bmat[0].length);
        MatrixUtils dmat = new MatrixUtils(bmat);
        double[][] carray = cmat.getArray();
        double sum = 0.0D;

        for (int i = 0; i < amat.numberOfRows; i++) {
            for (int j = 0; j < dmat.numberOfColumns; j++) {
                sum = 0.0D;
                for (int k = 0; k < amat.numberOfColumns; k++) {
                    sum += (amat.matrix[i][k] * dmat.matrix[k][j]);
                }
                carray[i][j] = sum;
            }
        }
        return cmat;
    }

    // Multiply a matrix by a constant [static method]
    public static MatrixUtils times(MatrixUtils amat, double constant)
    {
        MatrixUtils cmat = new MatrixUtils(amat.numberOfRows,
                        amat.numberOfColumns);
        double[][] carray = cmat.getArray();

        for (int i = 0; i < amat.numberOfRows; i++) {
            for (int j = 0; j < amat.numberOfColumns; j++) {
                carray[i][j] = amat.matrix[i][j] * constant;
            }
        }
        return cmat;
    }

    // Multiply this matrix by a matrix [equivalence of *=]
    public void timesEquals(MatrixUtils bmat)
    {
        if (this.numberOfColumns != bmat.numberOfRows)
            throw new IllegalArgumentException("Nonconformable matrices");

        MatrixUtils cmat = new MatrixUtils(this.numberOfRows,
                        bmat.numberOfColumns);
        double[][] carray = cmat.getArray();
        double sum = 0.0D;

        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < bmat.numberOfColumns; j++) {
                sum = 0.0D;
                for (int k = 0; k < this.numberOfColumns; k++) {
                    sum += this.matrix[i][k] * bmat.matrix[k][j];
                }
                carray[i][j] = sum;
            }
        }

        this.numberOfRows = cmat.numberOfRows;
        this.numberOfColumns = cmat.numberOfColumns;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                this.matrix[i][j] = cmat.matrix[i][j];
            }
        }
    }

    /**
     * Multiply a matrix by a scalar constant in place [equivalence of *=], A =
     * s*A
     * 
     * @param s scalar
     * @return replace A by s*A
     */
    public void timesEquals(double constant)
    {

        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                this.matrix[i][j] *= constant;
            }
        }
    }

    // DIVISION
    // Divide this Matrix by a Matrix - instance method
    public MatrixUtils divide(MatrixUtils bmat)
    {
        if ((this.numberOfRows != bmat.numberOfRows)
                        || (this.numberOfColumns != bmat.numberOfColumns)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }
        return this.times(bmat.inverse());
    }

    // Divide a Matrix by a Matrix - static method.
    public MatrixUtils divide(MatrixUtils amat, MatrixUtils bmat)
    {
        if ((amat.numberOfRows != bmat.numberOfRows)
                        || (amat.numberOfColumns != bmat.numberOfColumns)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }
        return amat.times(bmat.inverse());
    }

    // Divide this Matrix by a 2-D array of doubles.
    public MatrixUtils divide(double[][] bmat)
    {
        int nr = bmat.length;
        int nc = bmat[0].length;
        if ((this.numberOfRows != nr) || (this.numberOfColumns != nc)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }

        MatrixUtils cmat = new MatrixUtils(bmat);
        return this.times(cmat.inverse());
    }

    // Divide a Matrix by a 2-D array of doubles - static method.
    public MatrixUtils divide(MatrixUtils amat, double[][] bmat)
    {
        int nr = bmat.length;
        int nc = bmat[0].length;
        if ((amat.numberOfRows != nr) || (amat.numberOfColumns != nc)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }

        MatrixUtils cmat = new MatrixUtils(bmat);
        return amat.times(cmat.inverse());
    }

    // Divide a 2-D array of doubles by a Matrix - static method.
    public MatrixUtils divide(double[][] amat, MatrixUtils bmat)
    {
        int nr = amat.length;
        int nc = amat[0].length;
        if ((bmat.numberOfRows != nr) || (bmat.numberOfColumns != nc)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }

        MatrixUtils cmat = new MatrixUtils(amat);
        return cmat.times(bmat.inverse());
    }

    // Divide a 2-D array of doubles by a 2-D array of doubles - static method.
    public MatrixUtils divide(double[][] amat, double[][] bmat)
    {
        int nr = amat.length;
        int nc = amat[0].length;
        if ((bmat.length != nr) || (bmat[0].length != nc)) {
            throw new IllegalArgumentException("Array dimensions do not agree");
        }

        MatrixUtils cmat = new MatrixUtils(amat);
        MatrixUtils dmat = new MatrixUtils(bmat);
        return cmat.times(dmat.inverse());
    }

    // INVERSE
    /**
     * Matrix inverse or pseudoinverse Inverse of a square matrix [instance
     * method]
     * 
     * @return inverse(A) if A is square, pseudoinverse otherwise.
     */
    public MatrixUtils inverse()
    {
        int n = this.numberOfRows;
        if (n != this.numberOfColumns)
            throw new IllegalArgumentException("Matrix is not square");
        MatrixUtils invmat = new MatrixUtils(n, n);

        if (n == 1) {
            double[][] hold = this.getArrayCopy();
            if (hold[0][0] == 0.0)
                throw new IllegalArgumentException("Matrix is singular");
            hold[0][0] = 1.0 / hold[0][0];
            invmat = new MatrixUtils(hold);
        } else {
            if (n == 2) {
                double[][] hold = this.getArrayCopy();
                double det = hold[0][0] * hold[1][1] - hold[0][1] * hold[1][0];
                if (det == 0.0)
                    throw new IllegalArgumentException("Matrix is singular");
                double[][] hold2 = new double[2][2];
                hold2[0][0] = hold[1][1] / det;
                hold2[1][1] = hold[0][0] / det;
                hold2[1][0] = -hold[1][0] / det;
                hold2[0][1] = -hold[0][1] / det;
                invmat = new MatrixUtils(hold2);
            } else {
                double[] col = new double[n];
                double[] xvec = new double[n];
                double[][] invarray = invmat.getArray();
                MatrixUtils ludmat;

                ludmat = this.luDecomp();
                for (int j = 0; j < n; j++) {
                    for (int i = 0; i < n; i++)
                        col[i] = 0.0D;
                    col[j] = 1.0;
                    xvec = ludmat.luBackSub(col);
                    for (int i = 0; i < n; i++)
                        invarray[i][j] = xvec[i];
                }
            }
        }
        return invmat;
    }

    // Inverse of a square matrix [static method]
    public static MatrixUtils inverse(MatrixUtils amat)
    {
        int n = amat.numberOfRows;
        if (n != amat.numberOfColumns)
            throw new IllegalArgumentException("Matrix is not square");
        MatrixUtils invmat = new MatrixUtils(n, n);

        if (n == 1) {
            double[][] hold = amat.getArrayCopy();
            if (hold[0][0] == 0.0)
                throw new IllegalArgumentException("Matrix is singular");
            hold[0][0] = 1.0 / hold[0][0];
            invmat = new MatrixUtils(hold);
        } else {
            if (n == 2) {
                double[][] hold = amat.getArrayCopy();
                double det = hold[0][0] * hold[1][1] - hold[0][1] * hold[1][0];
                if (det == 0.0)
                    throw new IllegalArgumentException("Matrix is singular");
                double[][] hold2 = new double[2][2];
                hold2[0][0] = hold[1][1] / det;
                hold2[1][1] = hold[0][0] / det;
                hold2[1][0] = -hold[1][0] / det;
                hold2[0][1] = -hold[0][1] / det;
                invmat = new MatrixUtils(hold2);
            } else {
                double[] col = new double[n];
                double[] xvec = new double[n];
                double[][] invarray = invmat.getArray();
                MatrixUtils ludmat;

                ludmat = amat.luDecomp();
                for (int j = 0; j < n; j++) {
                    for (int i = 0; i < n; i++)
                        col[i] = 0.0D;
                    col[j] = 1.0;
                    xvec = ludmat.luBackSub(col);
                    for (int i = 0; i < n; i++)
                        invarray[i][j] = xvec[i];
                }
            }
        }
        return invmat;
    }

    // TRANSPOSE
    // Transpose of a matrix [instance method]
    public MatrixUtils transpose()
    {
        MatrixUtils tmat = new MatrixUtils(this.numberOfColumns,
                        this.numberOfRows);
        double[][] tarray = tmat.getArray();
        for (int i = 0; i < this.numberOfColumns; i++) {
            for (int j = 0; j < this.numberOfRows; j++) {
                tarray[i][j] = this.matrix[j][i];
            }
        }
        return tmat;
    }

    // Transpose of a matrix [static method]
    public static MatrixUtils transpose(MatrixUtils amat)
    {
        MatrixUtils tmat = new MatrixUtils(amat.numberOfColumns,
                        amat.numberOfRows);
        double[][] tarray = tmat.getArray();
        for (int i = 0; i < amat.numberOfColumns; i++) {
            for (int j = 0; j < amat.numberOfRows; j++) {
                tarray[i][j] = amat.matrix[j][i];
            }
        }
        return tmat;
    }

    // OPPOSITE
    // Opposite of a matrix [instance method]
    public MatrixUtils opposite()
    {
        MatrixUtils opp = MatrixUtils.copy(this);
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                opp.matrix[i][j] = -this.matrix[i][j];
            }
        }
        return opp;
    }

    // Opposite of a matrix [static method]
    public static MatrixUtils opposite(MatrixUtils amat)
    {
        MatrixUtils opp = MatrixUtils.copy(amat);
        for (int i = 0; i < amat.numberOfRows; i++) {
            for (int j = 0; j < amat.numberOfColumns; j++) {
                opp.matrix[i][j] = -amat.matrix[i][j];
            }
        }
        return opp;
    }

    // TRACE

    /**
     * Trace of a matrix [instance method]
     * 
     * @return sum of the diagonal elements.
     */
    public double trace()
    {
        double trac = 0.0D;
        for (int i = 0; i < Math
                        .min(this.numberOfColumns, this.numberOfColumns); i++) {
            trac += this.matrix[i][i];
        }
        return trac;
    }

    // Trace of a matrix [static method]
    public static double trace(MatrixUtils amat)
    {
        double trac = 0.0D;
        for (int i = 0; i < Math
                        .min(amat.numberOfColumns, amat.numberOfColumns); i++) {
            trac += amat.matrix[i][i];
        }
        return trac;
    }

    // DETERMINANT
    // Returns the determinant of a square matrix [instance method]
    public double determinant()
    {
        int n = this.numberOfRows;
        if (n != this.numberOfColumns)
            throw new IllegalArgumentException("Matrix is not square");
        double det = 0.0D;
        if (n == 2) {
            det = this.matrix[0][0] * this.matrix[1][1] - this.matrix[0][1]
                            * this.matrix[1][0];
        } else {
            MatrixUtils ludmat = this.luDecomp();
            det = ludmat.rowSwapIndex;
            for (int j = 0; j < n; j++) {
                det *= ludmat.matrix[j][j];
            }
        }
        return det;
    }

    /**
     * Matrix determinant
     * 
     * Returns the determinant of a square matrix [static method] - Matrix input
     * 
     * @return determinant
     */
    public static double determinant(MatrixUtils amat)
    {
        int n = amat.numberOfRows;
        if (n != amat.numberOfColumns)
            throw new IllegalArgumentException("Matrix is not square");
        double det = 0.0D;

        if (n == 2) {
            double[][] hold = amat.getArrayCopy();
            det = hold[0][0] * hold[1][1] - hold[0][1] * hold[1][0];
        } else {
            MatrixUtils ludmat = amat.luDecomp();
            det = ludmat.rowSwapIndex;
            for (int j = 0; j < n; j++) {
                det *= (ludmat.matrix[j][j]);
            }
        }
        return det;
    }

    // Returns the determinant of a square matrix [static method] - [][] array
    // input
    public static double determinant(double[][] mat)
    {
        int n = mat.length;
        for (int i = 0; i < n; i++)
            if (n != mat[i].length)
                throw new IllegalArgumentException("Matrix is not square");
        double det = 0.0D;

        if (n == 2) {
            det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        } else {
            MatrixUtils amat = new MatrixUtils(mat);
            MatrixUtils ludmat = amat.luDecomp();
            det = ludmat.rowSwapIndex;
            for (int j = 0; j < n; j++) {
                det *= (ludmat.matrix[j][j]);
            }
        }
        return det;
    }

    // Returns the log(determinant) of a square matrix [instance method].
    // Useful if determinant() underflows or overflows.
    public double logDeterminant()
    {
        int n = this.numberOfRows;
        if (n != this.numberOfColumns)
            throw new IllegalArgumentException("Matrix is not square");
        double det = 0.0D;
        MatrixUtils ludmat = this.luDecomp();

        det = ludmat.rowSwapIndex;
        det = Math.log(det);
        for (int j = 0; j < n; j++) {
            det += Math.log(ludmat.matrix[j][j]);
        }
        return det;
    }

    // Returns the log(determinant) of a square matrix [static method] - matrix
    // input.
    // Useful if determinant() underflows or overflows.
    public static double logDeterminant(MatrixUtils amat)
    {
        int n = amat.numberOfRows;
        if (n != amat.numberOfColumns)
            throw new IllegalArgumentException("Matrix is not square");
        double det = 0.0D;
        MatrixUtils ludmat = amat.luDecomp();

        det = ludmat.rowSwapIndex;
        det = Math.log(det);
        for (int j = 0; j < n; j++) {
            det += Math.log(ludmat.matrix[j][j]);
        }
        return det;
    }

    // Returns the log(determinant) of a square matrix [static method]
    // double[][] input.
    // Useful if determinant() underflows or overflows.
    public static double logDeterminant(double[][] mat)
    {
        int n = mat.length;
        for (int i = 0; i < n; i++)
            if (n != mat[i].length)
                throw new IllegalArgumentException("Matrix is not square");
        MatrixUtils amat = new MatrixUtils(mat);
        return amat.determinant();
    }

    // REDUCED ROW ECHELON FORM
    public MatrixUtils reducedRowEchelonForm()
    {

        double[][] mat = new double[this.numberOfRows][this.numberOfColumns];
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                mat[i][j] = this.matrix[i][j];
            }
        }

        int leadingCoeff = 0;
        int rowPointer = 0;

        boolean testOuter = true;
        while (testOuter) {
            int counter = rowPointer;
            boolean testInner = true;
            while (testInner && mat[counter][leadingCoeff] == 0) {
                counter++;
                if (counter == this.numberOfRows) {
                    counter = rowPointer;
                    leadingCoeff++;
                    if (leadingCoeff == this.numberOfColumns)
                        testInner = false;
                }
            }
            if (testInner) {
                double[] temp = mat[rowPointer];
                mat[rowPointer] = mat[counter];
                mat[counter] = temp;

                double pivot = mat[rowPointer][leadingCoeff];
                for (int j = 0; j < this.numberOfColumns; j++)
                    mat[rowPointer][j] /= pivot;

                for (int i = 0; i < this.numberOfRows; i++) {
                    if (i != rowPointer) {
                        pivot = mat[i][leadingCoeff];
                        for (int j = 0; j < this.numberOfColumns; j++)
                            mat[i][j] -= pivot * mat[rowPointer][j];
                    }
                }
                leadingCoeff++;
                if (leadingCoeff >= this.numberOfColumns) testOuter = false;
            }
            rowPointer++;
            if (rowPointer >= this.numberOfRows || !testInner)
                testOuter = false;
        }

        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (mat[i][j] == -0.0) mat[i][j] = 0.0;
            }
        }

        return new MatrixUtils(mat);
    }

    /**
     * FROBENIUS NORM of a matrix, aka EUCLIDEAN NORM
     * 
     * @return sqrt of sum of squares of all elements.
     */
    public double normFrobenius()
    {
        double norm = 0.0D;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                norm = hypot(norm, Math.abs(matrix[i][j]));
            }
        }
        return norm;
    }

    /**
     * ONE NORM of a matrix
     * 
     * @return maximum column sum.
     */
    public double normOne()
    {
        double norm = 0.0D;
        double sum = 0.0D;
        for (int i = 0; i < this.numberOfRows; i++) {
            sum = 0.0D;
            for (int j = 0; j < this.numberOfColumns; j++) {
                sum += abs(this.matrix[i][j]);
            }
            norm = max(norm, sum);
        }
        return norm;
    }

    /**
     * INFINITY NORM of a matrix
     * 
     * @return maximum row sum.
     */
    public double normInfinity()
    {
        double norm = 0.0D;
        double sum = 0.0D;
        for (int i = 0; i < this.numberOfRows; i++) {
            sum = 0.0D;
            for (int j = 0; j < this.numberOfColumns; j++) {
                sum += abs(this.matrix[i][j]);
            }
            norm = max(norm, sum);
        }
        return norm;
    }

    // SUM OF THE ELEMENTS
    // Returns sum of all elements
    public double sum()
    {
        double sum = 0.0;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                sum += this.matrix[i][j];
            }
        }
        return sum;
    }

    // Returns sums of the rows
    public double[] rowSums()
    {
        double[] sums = new double[this.numberOfRows];
        for (int i = 0; i < this.numberOfRows; i++) {
            sums[i] = 0.0;
            for (int j = 0; j < this.numberOfColumns; j++) {
                sums[i] += this.matrix[i][j];
            }
        }
        return sums;
    }

    // Returns sums of the columns
    public double[] columnSums()
    {
        double[] sums = new double[this.numberOfColumns];
        for (int i = 0; i < this.numberOfColumns; i++) {
            sums[i] = 0.0;
            for (int j = 0; j < this.numberOfRows; j++) {
                sums[i] += this.matrix[j][i];
            }
        }
        return sums;
    }

    // MEAN OF THE ELEMENTS
    // Returns mean of all elements
    public double mean()
    {
        double mean = 0.0;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                mean += this.matrix[i][j];
            }
        }
        mean /= this.numberOfRows * this.numberOfColumns;
        return mean;
    }

    // Returns means of the rows
    public double[] rowMeans()
    {
        double[] means = new double[this.numberOfRows];
        for (int i = 0; i < this.numberOfRows; i++) {
            means[i] = 0.0;
            for (int j = 0; j < this.numberOfColumns; j++) {
                means[i] += this.matrix[i][j];
            }
            means[i] /= this.numberOfColumns;
        }
        return means;
    }

    // Returns means of the columns
    public double[] columnMeans()
    {
        double[] means = new double[this.numberOfColumns];
        for (int i = 0; i < this.numberOfColumns; i++) {
            means[i] = 0.0;
            for (int j = 0; j < this.numberOfRows; j++) {
                means[i] += this.matrix[j][i];
            }
            means[i] /= this.numberOfRows;
        }
        return means;
    }

    // SUBTRACT THE MEAN OF THE ELEMENTS
    // Returns a matrix whose elements are the original elements minus the mean
    // of all elements
    public MatrixUtils subtractMean()
    {
        MatrixUtils mat = new MatrixUtils(this.numberOfRows,
                        this.numberOfColumns);

        double mean = 0.0;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                mean += this.matrix[i][j];
            }
        }
        mean /= this.numberOfRows * this.numberOfColumns;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                mat.matrix[i][j] = this.matrix[i][j] - mean;
            }
        }
        return mat;
    }

    // Returns a matrix whose rows are the elements are the original row minus
    // the mean of the elements of that row
    public MatrixUtils subtractRowMeans()
    {
        MatrixUtils mat = new MatrixUtils(this.numberOfRows,
                        this.numberOfColumns);

        for (int i = 0; i < this.numberOfRows; i++) {
            double mean = 0.0;
            for (int j = 0; j < this.numberOfColumns; j++) {
                mean += this.matrix[i][j];
            }
            mean /= this.numberOfColumns;
            for (int j = 0; j < this.numberOfColumns; j++) {
                mat.matrix[i][j] = this.matrix[i][j] - mean;
            }
        }
        return mat;
    }

    // Returns matrix whose columns are the elements are the original column
    // minus the mean of the elements of that olumnc
    public MatrixUtils subtractColumnMeans()
    {
        MatrixUtils mat = new MatrixUtils(this.numberOfRows,
                        this.numberOfColumns);

        for (int i = 0; i < this.numberOfColumns; i++) {
            double mean = 0.0;
            for (int j = 0; j < this.numberOfRows; j++) {
                mean += this.matrix[j][i];
            }
            mean /= this.numberOfRows;
            for (int j = 0; j < this.numberOfRows; j++) {
                mat.matrix[j][i] = this.matrix[j][i] - mean;
            }
        }
        return mat;
    }

    // MAXIMUM ELEMENT
    // Returns the value, row index and column index of the maximum element
    public double[] maximumElement()
    {
        // {value, row, col}
        double[] ret = new double[3];
        ret[0] = Double.MIN_VALUE;
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                if (matrix[i][j] >= ret[0]) {
                    ret[0] = matrix[i][j];
                    ret[1] = i;
                    ret[2] = j;
                }
            }
        }
        return ret;
    }

    // Returns maxima of the rows
    public double[] rowMaxima()
    {
        double[] maxima = new double[this.numberOfRows];
        for (int i = 0; i < this.numberOfRows; i++) {

            double rowMax = Double.MIN_VALUE;
            for (int j = 0; j < numberOfColumns; j++) {
                rowMax = max(rowMax, matrix[i][j]);
            }

            maxima[i] = rowMax;
        }

        return maxima;
    }

    // Returns maxima of the columns
    public double[] columnMaxima()
    {
        double[] maxima = new double[this.numberOfRows];
        for (int i = 0; i < this.numberOfColumns; i++) {

            double colMax = Double.MIN_VALUE;
            for (int j = 0; j < numberOfRows; j++) {
                colMax = max(colMax, matrix[j][i]);
            }

            maxima[i] = colMax;
        }

        return maxima;
    }

    // MINIMUM ELEMENT
    // Returns the value, row index and column index of the minimum element
    public double[] minimumElement()
    {
        // {value, row, col}
        double[] ret = new double[3];
        ret[0] = Double.MAX_VALUE;
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                if (matrix[i][j] <= ret[0]) {
                    ret[0] = matrix[i][j];
                    ret[1] = i;
                    ret[2] = j;
                }
            }
        }
        return ret;
    }

    // Returns minima of the rows
    public double[] rowMinima()
    {
        double[] minima = new double[this.numberOfRows];
        for (int i = 0; i < this.numberOfRows; i++) {

            double rowMin = Double.MAX_VALUE;
            for (int j = 0; j < numberOfColumns; j++) {
                rowMin = max(rowMin, matrix[i][j]);
            }

            minima[i] = rowMin;
        }

        return minima;
    }

    // Returns minima of the columns
    public double[] columnMinima()
    {
        double[] minima = new double[this.numberOfRows];
        for (int i = 0; i < this.numberOfColumns; i++) {

            double colMin = Double.MAX_VALUE;
            for (int j = 0; j < numberOfRows; j++) {
                colMin = max(colMin, matrix[j][i]);
            }

            minima[i] = colMin;
        }

        return minima;
    }

    // RANGE
    // Returns the range of all the elements
    public double range()
    {
        return this.maximumElement()[0] - this.minimumElement()[0];
    }

    // Returns ranges of the rows
    public double[] rowRanges()
    {
        double[] maximums = rowMaxima();
        double[] minimums = rowMinima();

        double[] ranges = new double[this.numberOfRows];
        for (int i = 0; i < this.numberOfRows; i++) {
            ranges[i] = maximums[i] - minimums[i];
        }

        return ranges;
    }

    // Returns ranges of the columns
    public double[] columnRanges()
    {
        double[] maximums = columnMaxima();
        double[] minimums = columnMinima();

        double[] ranges = new double[this.numberOfColumns];
        for (int i = 0; i < this.numberOfColumns; i++) {
            ranges[i] = maximums[i] - minimums[i];
        }

        return ranges;
    }

    // PIVOT
    // Swaps rows and columns to place absolute maximum element in position
    // matrix[0][0]
    public int[] pivot()
    {
        double[] max = this.maximumElement();
        int maxI = (int) max[1];
        int maxJ = (int) max[2];
        double[] min = this.minimumElement();
        int minI = (int) min[1];
        int minJ = (int) min[2];
        if (Math.abs(min[0]) > Math.abs(max[0])) {
            maxI = minI;
            maxJ = minJ;
        }
        int[] ret = { maxI, maxJ };

        double[] hold1 = this.matrix[0];
        this.matrix[0] = this.matrix[maxI];
        this.matrix[maxI] = hold1;
        double hold2 = 0.0;
        for (int i = 0; i < this.numberOfRows; i++) {
            hold2 = this.matrix[i][0];
            this.matrix[i][0] = this.matrix[i][maxJ];
            this.matrix[i][maxJ] = hold2;
        }

        return ret;
    }

    // MATRIX TESTS
    // Check if a matrix is square
    public boolean isSquare()
    {
        boolean test = false;
        if (this.numberOfRows == this.numberOfColumns) test = true;
        return test;
    }

    // Check if a matrix is symmetric
    public boolean isSymmetric()
    {
        boolean test = true;
        if (this.numberOfRows == this.numberOfColumns) {
            for (int i = 0; i < this.numberOfRows; i++) {
                for (int j = i + 1; j < this.numberOfColumns; j++) {
                    if (this.matrix[i][j] != this.matrix[j][i]) test = false;
                }
            }
        } else {
            test = false;
        }
        return test;
    }

    // Check if a matrix is zero
    public boolean isZero()
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (this.matrix[i][j] != 0.0D) test = false;
            }
        }
        return test;
    }

    // Check if a matrix is unit
    public boolean isUnit()
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (this.matrix[i][j] != 1.0D) test = false;
            }
        }
        return test;
    }

    // Check if a matrix is diagonal
    public boolean isDiagonal()
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (i != j && this.matrix[i][j] != 0.0D) test = false;
            }
        }
        return test;
    }

    // Check if a matrix is upper triagonal
    public boolean isUpperTriagonal()
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (j < i && this.matrix[i][j] != 0.0D) test = false;
            }
        }
        return test;
    }

    // Check if a matrix is lower triagonal
    public boolean isLowerTriagonal()
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (i > j && this.matrix[i][j] != 0.0D) test = false;
            }
        }
        return test;
    }

    // Check if a matrix is tridiagonal
    public boolean isTridiagonal()
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (i < (j + 1) && this.matrix[i][j] != 0.0D) test = false;
                if (j > (i + 1) && this.matrix[i][j] != 0.0D) test = false;
            }
        }
        return test;
    }

    // Check if a matrix is a identity matrix
    public boolean isIdentity()
    {
        boolean test = true;
        if (this.numberOfRows == this.numberOfColumns) {
            for (int i = 0; i < this.numberOfRows; i++) {
                if (this.matrix[i][i] != 1.0D) test = false;
                for (int j = i + 1; j < this.numberOfColumns; j++) {
                    if (this.matrix[i][j] != 0.0D) test = false;
                    if (this.matrix[j][i] != 0.0D) test = false;
                }
            }
        } else {
            test = false;
        }
        return test;
    }

    // Check if a matrix is symmetric within a given tolerance
    public boolean isNearlySymmetric(double tolerance)
    {
        boolean test = true;
        if (this.numberOfRows == this.numberOfColumns) {
            for (int i = 0; i < this.numberOfRows; i++) {
                for (int j = i + 1; j < this.numberOfColumns; j++) {
                    if (Math.abs(this.matrix[i][j] - this.matrix[j][i]) > Math
                                    .abs(tolerance)) test = false;
                }
            }
        } else {
            test = false;
        }
        return test;
    }

    // Check if a matrix is zero within a given tolerance
    public boolean isNearlyZero(double tolerance)
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (Math.abs(this.matrix[i][j]) > Math.abs(tolerance))
                    test = false;
            }
        }
        return test;
    }

    // Check if a matrix is unit within a given tolerance
    public boolean isNearlyUnit(double tolerance)
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (Math.abs(this.matrix[i][j] - 1.0D) > Math.abs(tolerance))
                    test = false;
            }
        }
        return test;
    }

    // Check if a matrix is upper triagonal within a given tolerance
    public boolean isNearlyUpperTriagonal(double tolerance)
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (j < i && Math.abs(this.matrix[i][j]) > Math.abs(tolerance))
                    test = false;
            }
        }
        return test;
    }

    // Check if a matrix is lower triagonal within a given tolerance
    public boolean isNearlyLowerTriagonal(double tolerance)
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (i > j && Math.abs(this.matrix[i][j]) > Math.abs(tolerance))
                    test = false;
            }
        }
        return test;
    }

    // Check if a matrix is an identy matrix within a given tolerance
    public boolean isNearlyIdenty(double tolerance)
    {
        boolean test = true;
        if (this.numberOfRows == this.numberOfColumns) {
            for (int i = 0; i < this.numberOfRows; i++) {
                if (Math.abs(this.matrix[i][i] - 1.0D) > Math.abs(tolerance))
                    test = false;
                for (int j = i + 1; j < this.numberOfColumns; j++) {
                    if (Math.abs(this.matrix[i][j]) > Math.abs(tolerance))
                        test = false;
                    if (Math.abs(this.matrix[j][i]) > Math.abs(tolerance))
                        test = false;
                }
            }
        } else {
            test = false;
        }
        return test;
    }

    // Check if a matrix is tridiagonal within a given tolerance
    public boolean isTridiagonal(double tolerance)
    {
        boolean test = true;
        for (int i = 0; i < this.numberOfRows; i++) {
            for (int j = 0; j < this.numberOfColumns; j++) {
                if (i < (j + 1)
                                && Math.abs(this.matrix[i][j]) > Math
                                                .abs(tolerance)) test = false;
                if (j > (i + 1)
                                && Math.abs(this.matrix[i][j]) > Math
                                                .abs(tolerance)) test = false;
            }
        }
        return test;
    }

    // Check if a matrix is singular
    public boolean isSingular()
    {
        boolean test = false;
        double det = this.determinant();
        if (det == 0.0) test = true;
        return test;
    }

    // Check if a matrix is singular within a given tolerance
    public boolean isNearlySingular(double tolerance)
    {
        boolean test = false;
        double det = this.determinant();
        if (Math.abs(det) <= Math.abs(tolerance)) test = true;
        return test;
    }

    // Check for identical rows
    // Returns the number of pairs of identical rows followed by the row indices
    // of the identical row pairs
    public ArrayList<Integer> identicalRows()
    {
        ArrayList<Integer> ret = new ArrayList<Integer>();
        int nIdentical = 0;
        for (int i = 0; i < this.numberOfRows - 1; i++) {
            for (int j = i + 1; j < this.numberOfRows; j++) {
                int m = 0;
                for (int k = 0; k < this.numberOfColumns; k++) {
                    if (this.matrix[i][k] == this.matrix[j][k]) m++;
                }
                if (m == this.numberOfColumns) {
                    nIdentical++;
                    ret.add(new Integer(i));
                    ret.add(new Integer(j));
                }
            }
        }
        ret.add(0, new Integer(nIdentical));
        return ret;
    }

    // Check for identical columnss
    // Returns the number of pairs of identical columns followed by the column
    // indices of the identical column pairs
    public ArrayList<Integer> identicalColumns()
    {
        ArrayList<Integer> ret = new ArrayList<Integer>();
        int nIdentical = 0;
        for (int i = 0; i < this.numberOfColumns; i++) {
            for (int j = i + 1; j < this.numberOfColumns - 1; j++) {
                int m = 0;
                for (int k = 0; k < this.numberOfRows; k++) {
                    if (this.matrix[k][i] == this.matrix[k][j]) m++;
                }
                if (m == this.numberOfRows) {
                    nIdentical++;
                    ret.add(new Integer(i));
                    ret.add(new Integer(j));
                }
            }
        }
        ret.add(0, new Integer(nIdentical));
        return ret;
    }

    // Check for zero rows
    // Returns the number of columns of all zeros followed by the column indices
    public ArrayList<Integer> zeroRows()
    {
        ArrayList<Integer> ret = new ArrayList<Integer>();
        int nZero = 0;
        for (int i = 0; i < this.numberOfRows; i++) {
            int m = 0;
            for (int k = 0; k < this.numberOfColumns; k++) {
                if (this.matrix[i][k] == 0.0) m++;
            }
            if (m == this.numberOfColumns) {
                nZero++;
                ret.add(new Integer(i));
            }
        }
        ret.add(0, new Integer(nZero));
        return ret;
    }

    // Check for zero columns
    // Returns the number of columns of all zeros followed by the column indices
    public ArrayList<Integer> zeroColumns()
    {
        ArrayList<Integer> ret = new ArrayList<Integer>();
        int nZero = 0;
        for (int i = 0; i < this.numberOfColumns; i++) {
            int m = 0;
            for (int k = 0; k < this.numberOfRows; k++) {
                if (this.matrix[k][i] == 0.0) m++;
            }
            if (m == this.numberOfRows) {
                nZero++;
                ret.add(new Integer(i));
            }
        }
        ret.add(0, new Integer(nZero));
        return ret;
    }

    // LU DECOMPOSITION OF MATRIX A
    // For details of LU decomposition
    // See Numerical Recipes, The Art of Scientific Computing
    // by W H Press, S A Teukolsky, W T Vetterling & B P Flannery
    // Cambridge University Press, http://www.nr.com/
    // This method has followed their approach but modified to an object
    // oriented language
    // Matrix ludmat is the returned LU decompostion
    // int[] index is the vector of row permutations
    // rowSwapIndex returns +1.0 for even number of row interchanges
    // returns -1.0 for odd number of row interchanges
    public MatrixUtils luDecomp()
    {
        if (this.numberOfRows != this.numberOfColumns)
            throw new IllegalArgumentException("A matrix is not square");
        int n = this.numberOfRows;
        int imax = 0;
        double dum = 0.0D, temp = 0.0D, big = 0.0D;
        double[] vv = new double[n];
        double sum = 0.0D;
        double dumm = 0.0D;

        this.matrixCheck = true;

        MatrixUtils ludmat = MatrixUtils.copy(this);
        double[][] ludarray = ludmat.getArray();

        ludmat.rowSwapIndex = 1.0D;
        for (int i = 0; i < n; i++) {
            big = 0.0D;
            for (int j = 0; j < n; j++)
                if ((temp = Math.abs(ludarray[i][j])) > big) big = temp;
            if (big == 0.0D) {
                if (!this.suppressErrorMessage) {
                    System.out.println("Attempted LU Decomposition of a singular matrix in Matrix.luDecomp()");
                    System.out.println("NaN matrix returned and matrixCheck set to false");
                }
                this.matrixCheck = false;
                for (int k = 0; k < n; k++)
                    for (int j = 0; j < n; j++)
                        ludarray[k][j] = Double.NaN;
                return ludmat;
            }
            vv[i] = 1.0 / big;
        }
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < j; i++) {
                sum = ludarray[i][j];
                for (int k = 0; k < i; k++)
                    sum -= ludarray[i][k] * ludarray[k][j];
                ludarray[i][j] = sum;
            }
            big = 0.0D;
            for (int i = j; i < n; i++) {
                sum = ludarray[i][j];
                for (int k = 0; k < j; k++)
                    sum -= ludarray[i][k] * ludarray[k][j];
                ludarray[i][j] = sum;
                if ((dum = vv[i] * Math.abs(sum)) >= big) {
                    big = dum;
                    imax = i;
                }
            }
            if (j != imax) {
                for (int k = 0; k < n; k++) {
                    dumm = ludarray[imax][k];
                    ludarray[imax][k] = ludarray[j][k];
                    ludarray[j][k] = dumm;
                }
                ludmat.rowSwapIndex = -ludmat.rowSwapIndex;
                vv[imax] = vv[j];
            }
            ludmat.permutationIndex[j] = imax;

            if (ludarray[j][j] == 0.0D) {
                ludarray[j][j] = this.tiny;
            }
            if (j != n - 1) {
                dumm = 1.0 / ludarray[j][j];
                for (int i = j + 1; i < n; i++) {
                    ludarray[i][j] *= dumm;
                }
            }
        }
        return ludmat;
    }

    // Solves the set of n linear equations A.X=B using not A but its LU
    // decomposition
    // bvec is the vector B (input)
    // xvec is the vector X (output)
    // index is the permutation vector produced by luDecomp()
    public double[] luBackSub(double[] bvec)
    {
        int ii = 0, ip = 0;
        int n = bvec.length;
        if (n != this.numberOfColumns)
            throw new IllegalArgumentException(
                            "vector length is not equal to matrix dimension");
        if (this.numberOfColumns != this.numberOfRows)
            throw new IllegalArgumentException("matrix is not square");
        double sum = 0.0D;
        double[] xvec = new double[n];
        for (int i = 0; i < n; i++) {
            xvec[i] = bvec[i];
        }
        for (int i = 0; i < n; i++) {
            ip = this.permutationIndex[i];
            sum = xvec[ip];
            xvec[ip] = xvec[i];
            if (ii == 0) {
                for (int j = ii; j <= i - 1; j++) {
                    sum -= this.matrix[i][j] * xvec[j];
                }
            } else {
                if (sum == 0.0) ii = i;
            }
            xvec[i] = sum;
        }
        for (int i = n - 1; i >= 0; i--) {
            sum = xvec[i];
            for (int j = i + 1; j < n; j++) {
                sum -= this.matrix[i][j] * xvec[j];
            }
            xvec[i] = sum / matrix[i][i];
        }
        return xvec;
    }

    // Suppress printing of LU decompostion failure message
    public void suppressErrorMessage()
    {
        this.suppressErrorMessage = true;
    }

    // Return the number of rotations used in the Jacobi procedure
    public int getNumberOfJacobiRotations()
    {
        return this.numberOfRotations;
    }

    /**
     * Round 1A 2008: Problem C - Fast matrix exponentiation
     * 
     * @param A
     * @param n
     * @return
     */
    public static int[][] fastExponentiation(int[][] A, int n)
    {
        if (n == 1) {
            return A;
        } else {
            if (n % 2 == 0) {
                int[][] A1 = fastExponentiation(A, n / 2);
                return matrixMultHelper(A1, A1);
            } else {
                return matrixMultHelper(A, fastExponentiation(A, n - 1));
            }
        }
    }

    /**
     * Helper method for {@link #fastExponentiation(int[][] A, int n)
     * fastExponentiation}
     * 
     * @param A
     * @param B
     * @return
     */
    private static int[][] matrixMultHelper(int[][] A, int[][] B)
    {
        int[][] C = new int[A.length][B[0].length];
        for (int i = 0; i < C.length; i++) {
            for (int j = 0; j < C[0].length; j++) {
                for (int k = 0; k < A[0].length; k++) {
                    C[i][k] += (A[i][j] * B[j][k]) % 1000;
                }
            }
        }
        return C;
    }

    /**
     * Print the matrix to stdout. Line the elements up in columns with a
     * Fortran-like 'Fw.d' style format.
     * 
     * @param w Column width.
     * @param d Number of digits after the decimal.
     */

    public void print(int w, int d)
    {
        print(new PrintWriter(System.out, true), w, d);
    }

    /**
     * Print the matrix to the output stream. Line the elements up in columns
     * with a Fortran-like 'Fw.d' style format.
     * 
     * @param output Output stream.
     * @param w Column width.
     * @param d Number of digits after the decimal.
     */

    public void print(PrintWriter output, int w, int d)
    {
        DecimalFormat format = new DecimalFormat();
        format.setDecimalFormatSymbols(new DecimalFormatSymbols(Locale.US));
        format.setMinimumIntegerDigits(1);
        format.setMaximumFractionDigits(d);
        format.setMinimumFractionDigits(d);
        format.setGroupingUsed(false);
        print(output, format, w + 2);
    }

    /**
     * Print the matrix to the output stream. Line the elements up in columns.
     * Use the format object, and right justify within columns of width
     * characters. Note that is the matrix is to be read back in, you probably
     * will want to use a NumberFormat that is set to US Locale.
     * 
     * @param output the output stream.
     * @param format A formatting object to format the matrix elements
     * @param width Column width.
     * @see java.text.DecimalFormat#setDecimalFormatSymbols
     */
    public void print(PrintWriter output, NumberFormat format, int width)
    {
        output.println(); // start on new line.
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                String s = format.format(matrix[i][j]); // format the number
                int padding = Math.max(1, width - s.length()); // At _least_ 1
                                                               // space
                for (int k = 0; k < padding; k++)
                    output.print(' ');
                output.print(s);
            }
            output.println();
        }
        output.println(); // end with blank line.
    }

    @Override
    public String toString()
    {
        // begin on a new line
        String result = System.getProperty("line.separator");
        for (int i = 0; i < numberOfRows; i++) {
            for (int j = 0; j < numberOfColumns; j++) {
                String s = DECIMAL_FORMAT.format(matrix[i][j]); // format the
                                                                // number
                int padding = Math.max(1, numberOfColumns - s.length()); // At
                                                                         // _least_
                                                                         // 1
                // space
                for (int k = 0; k < padding; k++) {
                    result += ' ';
                }

                result += s;
            }
            result += "\n";
        }
        result += "\n"; // end with blank line.
        return result;
    }

    /**
     * Generate matrix with random elements
     * 
     * @param m Number of rows.
     * @param n Number of colums.
     * @return An m-by-n matrix with uniformly distributed random elements.
     */
    public static MatrixUtils random(int m, int n)
    {
        MatrixUtils A = new MatrixUtils(m, n);
        double[][] X = A.matrix;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                X[i][j] = Math.random();
            }
        }
        return A;
    }
}
