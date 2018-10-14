fun merge(sequence: MutableList<Int>, left: Int, middle: Int, right: Int) {
  val result: MutableList<Int> = mutableListOf();
  var i = left;
  var j = middle;

  while (i < middle && j < right) {
    if (sequence[i] < sequence[j]) {
      result.add(sequence[i]);
      i++;
    }
    else {
      result.add(sequence[j]);
      j++;
    }
  }

  while (i < middle) {
    result.add(sequence[i]);
    i++;
  }

  while (j < right) {
    result.add(sequence[j]);
    j++;
  }

  for (i in left..right - 1) {
    sequence[i] = result[i - left];
  }
}

fun split(sequence: MutableList<Int>, left: Int, right: Int) {
  if (right <= left + 1) return
  val middle = (left + right) / 2;
  split(sequence, left, middle);
  split(sequence, middle, right);
  merge(sequence, left, middle, right);
}

fun mergeSort(sequence: MutableList<Int>): MutableList<Int> {
  split(sequence, 0, sequence.size);
  return sequence;
}
