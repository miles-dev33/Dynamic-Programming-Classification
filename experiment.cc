///////////////////////////////////////////////////////////////////////////////
//// experiment.cc
////
////// Example code showing how to run an algorithm once and measure its elapsed
//// time precisely. You should modify this program to gather all of your
//// experimental data.
////
///////////////////////////////////////////////////////////////////////////////
//
//#include <iostream>
//
//#include "project1.hh"
//#include "timer.hh"
//
//using namespace std;
//
//int main() {
//
//  string_vector all_words;
//  if ( ! load_words(all_words, "words.txt") ) {
//    cerr << "error: cannot open \"words.txt\"" << endl;
//    return 1;
//  }
//
//  int n = 5;
//  string_vector n_words(all_words.begin(), all_words.begin() + n);
//  Timer timer;
//  auto output = longest_mirrored_string(n_words);
//  double elapsed = timer.elapsed();
//  cout << "longest_mirrored_string, "
//       << "n=" << n << ", "
//       << "output=\"" << output << "\", "
//       << "elapsed time=" << elapsed << " seconds" << endl;
// 
//  timer.reset();
//       output = character_mode(n_words);
//       elapsed = timer.elapsed();
//  cout << "character_mode, "
//	  << "n=" << n << ", "
//	  << "output=\"" << output << "\", "
//	  << "elapsed time=" << elapsed << " seconds" << endl;
//
//
//  timer.reset();
//  
//  vector <string> output3 = longest_substring_trio(n_words);
//  elapsed = timer.elapsed();
//  cout << "longest_substring_trio, "
//	  << "n=" << n << ", "
//	  << "output=\"";
//	  for (int i = 0; i < output3.size(); i++)
//	  {
//		cout << output3[i];
//	  }
//			cout  << "\", "
//	  << "elapsed time=" << elapsed << " seconds" << endl;
//
//  system("pause");
//  return 0;
//
//}
