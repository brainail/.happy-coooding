package utilities.matrix;

import static java.lang.Math.*;

import java.util.*;

public class CoppersmithWinograd
{
    public static void main(String[] args)
    {
        CoppersmithWinograd thisClass = new CoppersmithWinograd();

        double[][] entries = new double[4][4];
        entries[0] = new double[] { 2, 4, 11, 4 };
        entries[1] = new double[] { 6, 16, 7, 14 };
        entries[2] = new double[] { 3, 32, 3, 15 };
        entries[3] = new double[] { 9, 11, 3, 1 };
        Matrix m = new Matrix(entries);

        double[] e1 = new double[] { 1, 4, 2 };
        Matrix m1 = new Matrix(e1);
        System.out.println(m1);

        System.out.println(m);
        System.out.println(thisClass.simple(m));
        System.out.println(thisClass.coppersmithWinograd(m));

        // System.out.println(thisClass.coppersmithWinograd(m, m1));
        // System.out.println(thisClass.coppersmithWinograd(m1, null));
        // System.out.println(thisClass.coppersmithWinograd(null, m));
    }

    /**
     * Ensures matrix m1 & m2 are compatible for multiplication
     * 
     * @param m1
     * @param m2
     */
    private void checkDimensions(Matrix m1, Matrix m2)
    {
        if (m1 == null) {
            throw new RuntimeException(
                            "checkDimensions(): incompatible matrices(m1=" + m1
                                            + ",m2.rows=" + m2.rows + ")");
        }

        if (m2 == null) {
            throw new RuntimeException(
                            "checkDimensions(): incompatible matrices(m1.cols="
                                            + m1.cols + ",m2=" + m2);
        }

        if (m1.cols != m2.rows) {
            throw new RuntimeException(
                            "checkDimensions(): incompatible matrices(m1.cols="
                                            + m1.cols + ",m2.rows=" + m2.rows
                                            + ")");
        }
    }

    /**
     * Checks if the dimension of the two matrices meet the pre-condition of
     * using Strassen Algorithm or Coppersmith–Winograd
     * 
     * @param m1
     * @param m2
     */
    private boolean checkSize(Matrix m1, Matrix m2)
    {
        return !(m1.cols % 2 != 0 || m1.rows != m1.cols);
    }

    private boolean isEqualLength(FieldElement[] row, FieldElement[] col)
    {
        return row.length == col.length;
    }

    private FieldElement multiply(FieldElement[] row, FieldElement[] col)
    {
        FieldElement result = new FieldElement();
        if (isEqualLength(row, col)) {
            for (int i = 0; i < row.length; i++) {
                result.value += row[i].value * col[i].value;
            }
            return result;
        }
        return null;
    }

    /**
     * one argument supplied => self-multiplication
     * 
     * @param m
     */
    public Matrix simple(Matrix m)
    {
        return simple(m, m);
    }

    /**
     * Uses the standard method for multiplication of Matrix-objects.
     * Asymptotic runtime: 0(n^3)
     * 
     * @param m1
     * @param m2
     * @return m1 multiplied by m2
     */
    public Matrix simple(Matrix m1, Matrix m2)
    {
        checkDimensions(m1, m2);
        int resultRows = m1.rows, resultCols = m2.cols;
        Matrix resultMatrix = new Matrix(resultRows, resultCols);
        for (int i = 0; i < resultRows; i++) {
            for (int j = 0; j < resultCols; j++) {
                resultMatrix.set(i, j, multiply(m1.getRow(i), m2.getCol(j)));
            }
        }
        return resultMatrix;
    }

    /**
     * one argument supplied => self-multiplication
     * 
     * @param m
     */
    public Matrix coppersmithWinograd(Matrix m)
    {
        return coppersmithWinograd(m, m);
    }

    /**
     * The Algorithm of Coppersmith–Winograd for square matrix multiplication
     * 
     * @param m1
     * @param m2
     * @return m1 multiplied by m2
     */
    public Matrix coppersmithWinograd(Matrix m1, Matrix m2)
    {
        checkDimensions(m1, m2);
        if (checkSize(m1, m2)) {
            int endIndex = m1.rows, splitIndex = endIndex / 2;
            Matrix a11 = m1.getMatrix(1, splitIndex, 1, splitIndex);
            Matrix a12 = m1.getMatrix(1, splitIndex, splitIndex + 1, endIndex);
            Matrix a21 = m1.getMatrix(splitIndex + 1, endIndex, 1, splitIndex);
            Matrix a22 = m1.getMatrix(splitIndex + 1, endIndex, splitIndex + 1,
                endIndex);
            Matrix b11 = m2.getMatrix(1, splitIndex, 1, splitIndex);
            Matrix b12 = m2.getMatrix(1, splitIndex, splitIndex + 1, endIndex);
            Matrix b21 = m2.getMatrix(splitIndex + 1, endIndex, 1, splitIndex);
            Matrix b22 = m2.getMatrix(splitIndex + 1, endIndex, splitIndex + 1,
                endIndex);
            Matrix s1 = a21.add(a22);
            Matrix s2 = s1.subtract(a11);
            Matrix s3 = a11.subtract(a21);
            Matrix s4 = a12.subtract(s2);
            Matrix t1 = b12.subtract(b11);
            Matrix t2 = b22.subtract(t1);
            Matrix t3 = b22.subtract(b12);
            Matrix t4 = b21.subtract(t2);
            Matrix p1 = coppersmithWinograd(a11, b11);
            Matrix p2 = coppersmithWinograd(a12, b21);
            Matrix p3 = coppersmithWinograd(s1, t1);
            Matrix p4 = coppersmithWinograd(s2, t2);
            Matrix p5 = coppersmithWinograd(s3, t3);
            Matrix p6 = coppersmithWinograd(s4, b22);
            Matrix p7 = coppersmithWinograd(a22, t4);
            Matrix u1 = p1.add(p2);
            Matrix u2 = p1.add(p4);
            Matrix u3 = u2.add(p5);
            Matrix u4 = u3.add(p7);
            Matrix u5 = u3.add(p3);
            Matrix u6 = u2.add(p3);
            Matrix u7 = u6.add(p6);
            FieldElement[][] c11Entries = u1.getEntries();
            FieldElement[][] c12Entries = u7.getEntries();
            FieldElement[][] c21Entries = u4.getEntries();
            FieldElement[][] c22Entries = u5.getEntries();
            FieldElement[][] cEntries = new FieldElement[m1.rows][m2.cols];
            for (int i = 0; i < u1.rows; i++) {
                for (int j = 0; j < u1.cols; j++) {
                    cEntries[i][j] = c11Entries[i][j];
                }
            }
            for (int i = 0; i < u7.rows; i++) {
                for (int j = 0; j < u7.cols; j++) {
                    cEntries[i][j + splitIndex] = c12Entries[i][j];
                }
            }
            for (int i = 0; i < u4.rows; i++) {
                for (int j = 0; j < u4.cols; j++) {
                    cEntries[i + splitIndex][j] = c21Entries[i][j];
                }
            }
            for (int i = 0; i < u5.rows; i++) {
                for (int j = 0; j < u5.cols; j++) {
                    cEntries[i + splitIndex][j + splitIndex] = c22Entries[i][j];
                }
            }
            return new Matrix(cEntries);
        }
        return simple(m1, m2);
    }
}

class FieldElement
{
    public double value;

    public FieldElement()
    {
    }

    public FieldElement(double value)
    {
        this.value = value;
    }

    public FieldElement add(FieldElement other)
    {
        return new FieldElement(value + other.value);
    }

    public FieldElement subtract(FieldElement other)
    {
        return new FieldElement(value - other.value);
    }

    @Override
    public String toString()
    {
        return Double.toString(value);
    }
}

class Matrix
{
    public int rows, cols;
    public FieldElement[][] entries;

    public Matrix(int rows, int cols)
    {
        this.rows = rows;
        this.cols = cols;
        entries = new FieldElement[rows][cols];
    }

    public Matrix(double[] entries)
    {
        this.rows = 1;
        this.cols = entries.length;

        FieldElement[][] fieldEntries = new FieldElement[1][cols];
        for (int i = 0; i < entries.length; i++) {
            fieldEntries[0][i] = new FieldElement(entries[i]);
        }

        this.entries = fieldEntries;
    }

    public Matrix(double[][] entries)
    {
        this.rows = entries.length;
        this.cols = entries[0].length;

        FieldElement[][] fieldEntries = new FieldElement[entries.length][entries[0].length];
        for (int i = 0; i < entries.length; i++) {
            for (int j = 0; j < entries[0].length; j++) {
                fieldEntries[i][j] = new FieldElement(entries[i][j]);
            }
        }

        this.entries = fieldEntries;
    }

    public Matrix(FieldElement[][] entries)
    {
        this.rows = entries.length;
        this.cols = entries[0].length;
        this.entries = entries;
    }

    public FieldElement[] getRow(int i)
    {
        return entries[i];
    }

    public FieldElement[] getCol(int j)
    {
        FieldElement[] column = new FieldElement[rows];
        for (int i = 0; i < rows; i++) {
            column[i] = entries[i][j];
        }
        return column;
    }

    public FieldElement[][] getEntries()
    {
        return entries;
    }

    /**
     * pre: 1-based element indexing
     * 
     * @param startRow
     * @param endRow
     * @param startCol
     * @param endCol
     */
    public Matrix getMatrix(int startRow, int endRow, int startCol, int endCol)
    {
        int subMatrixRows = abs(endRow - startRow) + 1;
        int subMatrixCols = abs(endCol - startCol) + 1;
        Matrix subMatrix = new Matrix(subMatrixRows, subMatrixCols);

        int tempStart = startRow, tempEnd = endRow;
        startRow = min(tempStart, tempEnd);
        endRow = max(tempStart, tempEnd);

        tempStart = startCol;
        tempEnd = endCol;
        startCol = min(tempStart, tempEnd);
        endCol = max(tempStart, tempEnd);

        for (int i = startRow - 1; i <= endRow - 1; i++) {
            for (int j = startCol - 1; j <= endCol - 1; j++) {
                subMatrix.entries[i - startRow + 1][j - startCol + 1] = entries[i][j];
            }
        }
        return subMatrix;
    }

    public void set(int i, int j, FieldElement result)
    {
        entries[i][j] = result;
    }

    private boolean isEqualSize(Matrix m)
    {
        return (rows == m.rows) && (cols == m.cols);
    }

    public Matrix add(Matrix m)
    {
        if (isEqualSize(m)) {
            Matrix result = new Matrix(rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    // add corresponding entries
                    result.entries[i][j] = entries[i][j].add(m.entries[i][j]);
                }
            }
            return result;
        }
        return null;
    }

    public Matrix subtract(Matrix m)
    {
        Matrix result = new Matrix(rows, cols);
        if (isEqualSize(m)) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    // add corresponding entries
                    result.entries[i][j] = entries[i][j]
                                    .subtract(m.entries[i][j]);
                }
            }
            return result;
        }
        return null;
    }

    @Override
    public String toString()
    {
        String result = "Matrix [rows=" + rows + ", cols=" + cols + "]\n";
        for (int i = 0; i < rows; i++) {
            result += Arrays.toString(entries[i]) + "\n";
        }
        return result;
    }
}
