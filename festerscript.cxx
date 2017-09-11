#include <iostream>
#include <regex>
#include <cctype>

const std::regex fester_seq_regex("(?:-?[0-9]+[, ]*)+");

int main(int argc, char** argv) {
  std::string text;

  if (argc == 2) {
    text = argv[1];
  } else {
    std::getline(std::cin, text);
  }
  if (text.empty()) {
    std::cout << "Usage: " << std::endl << "\t" << argv[0] << " text_or_festersequence"
                           << std::endl << "\t" << "echo \"text_or_festersequence\" | " << argv[0] << std::endl;
    return 1;
  }

  if (std::regex_match(text, fester_seq_regex)) {
    // Decode festerscript
    std::regex ws_re("[, ]+");
    std::vector<std::string> parts;
    std::copy(std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1),
              std::sregex_token_iterator(),
              std::back_inserter(parts));
    for (auto& part : parts) {
      std::cout << static_cast<char>(static_cast<int>('a') + atoi(part.c_str()) - 1);
    }
  } else {
    // Encode text
    // Let's do this in lowercase
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    unsigned int i = 0;
    std::for_each(text.begin(), text.end(),
      [&i, &text](const std::string::value_type& c) {
        std::cout << static_cast<int>(c) - static_cast<int>('a') + 1 << (++i < text.size() ? "," : "");
      });
  }
  std::cout << std::endl;

  return 0;
}

