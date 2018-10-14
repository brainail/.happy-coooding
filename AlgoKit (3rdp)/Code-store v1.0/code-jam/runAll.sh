#!/bin/bash
NAME=$1
TEST=$2
BASEPATH=/home/leewei/Downloads/GoogleCodeJam2011
SRCPATH=src/codejam
FILE=$SRCPATH/Problem$NAME.java	# ProblemA.java

# codejam.ProblemA

# sanity check for arguments
if [ $# -eq 0 ]; then
	echo "Usage: ./runAll.sh <A|B|C|D> <test-input 'A-small'>";
	exit 1
fi

# sanity check for existence of test input file
if [ ! -f $BASEPATH/$TEST.in ]; then
  echo "File $TEST.in does not exist!"
  exit 1
fi

# rename problem name in java source code
cd $BASEPATH
sed -e 's/PROBLEM_NAME = ".*";/PROBLEM_NAME = "'$TEST'";/' $FILE > $SRCPATH/temp
mv $SRCPATH/temp $FILE

# compile all class files to bin folder
rm -rf bin; mkdir bin
javac -sourcepath src $SRCPATH/*.java -d bin

# run problem
cp -pR $TEST.in bin/
java -Duser.dir=$BASEPATH/bin codejam.Problem$NAME
