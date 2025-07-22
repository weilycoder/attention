#ifndef EXCEPT_HPP
#define EXCEPT_HPP

#include <stdexcept>
#include <string>

class not_implemented : public std::logic_error {
public:
  explicit not_implemented(const std::string &feature) : logic_error(feature + " not implemented") {}
};

#endif // EXCEPT_HPP
