int repetitionEncryption(String letter) {
  Pattern pattern = Pattern.compile(
    "([a-zA-Z]+)[^a-zA-Z]+(\\1\\b)", Pattern.CASE_INSENSITIVE);
  Matcher matcher = pattern.matcher(letter);

  int res = 0;
  while (matcher.find()) {
    res++;
  }
  return res;
}
