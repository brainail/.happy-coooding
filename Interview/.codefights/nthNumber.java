String nthNumber(String s, int n) {
  Pattern pattern = Pattern.compile(
    "(?:(?:\\D*)0*(\\d+)){"+n+"}.*"
  );

  Matcher matcher = pattern.matcher(s);
  matcher.matches();
  return matcher.group(1);
}
