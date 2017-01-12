bool isPalindrome(string s) {
  string cleanStr;
  for (int i = 0; i != s.size(); ++i) {
    if (isalnum(s[i]))
      cleanStr.push_back(tolower(s[i]));
  }
  int i = 0, j = cleanStr.size()-1;
  while (i<j && cleanStr[i] == cleanStr[j]) {
    ++i; 
    --j;
  }
  return i>=j ? true: false;
}
