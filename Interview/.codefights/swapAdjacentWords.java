String swapAdjacentWords(String s) {
  return s.replaceAll("(\\S+)\\s(\\S+)", "$2 $1");
}
