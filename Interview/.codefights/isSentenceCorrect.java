boolean isSentenceCorrect(String sentence) {
  String regex = "[A-Z][^.?!]*[.?!]";
  return sentence.matches(regex);
}
