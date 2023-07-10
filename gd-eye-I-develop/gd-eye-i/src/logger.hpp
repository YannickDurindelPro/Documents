#ifndef EYE_I_LOGER_HPP
#  define EYE_I_LOGER_HPP

#  include <iostream>
#  include <sstream>

// ****************************************************************************
// Logging
// ****************************************************************************
#define EYEI_DEBUG()                                                      \
  std::cout << "[GDEyeI][GDEyeI::" << __func__ << "]" << std::endl
#define EYEI_DEBUG_VAL(x)                                                 \
  std::cout << "[GDEyeI][GDEyeI::" << __func__ << "] " << x << std::endl
#define EYEI_ERROR(x)                                                     \
  std::cerr << "[GDEyeI][GDEyeI::" << __func__ << "] " << x << std::endl

#endif // EYE_I_LOGER_HPP