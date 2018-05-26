#ifndef _ADMINUSER_H_
#define _ADMINUSER_H_

#include "user.h"

class AdminUser : public User {
public:
  AdminUser();
  virtual ~AdminUser();
};

#endif // _ADMINUSER_H_
