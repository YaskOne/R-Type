#ifndef EXCEPTIONS_H_
# define EXCEPTIONS_H_

# include <exception>
# include <string>
# include <string.h>
# include <errno.h>

namespace Exceptions
{
  class NetworkExcept : public std::exception
  {
  public:
    NetworkExcept(std::string const& msg, int error) throw()
      : _msg(msg), _errorCode(error) {}
    NetworkExcept(const NetworkExcept& other) throw()
      : _msg(other._msg), _errorCode(other._errorCode) {}
    virtual ~NetworkExcept() throw() {}
    virtual const char*	what() const throw()
    {
      return std::string(_msg + " : " + strerror(_errorCode)).c_str();
    }

  private:
    std::string		_msg;
    int			_errorCode;
    
    NetworkExcept &operator=(const NetworkExcept &) throw();
  };

  class ConnectionExcept : public std::exception
  {
  public:
    ConnectionExcept(std::string const& msg) throw()
      : _msg(msg) {}
    ConnectionExcept(const ConnectionExcept& other) throw()
      : _msg(other._msg) {}
    virtual ~ConnectionExcept() throw() {}
    virtual const char*	what() const throw()
    {
      return _msg.c_str();
    }

  private:
    ConnectionExcept	&operator=(const ConnectionExcept &) throw();
    std::string		_msg;
  };
  
  class BadHeaderRequest : public std::exception
  {
  public:
    BadHeaderRequest(std::string const& msg) throw()
      : _msg(msg) {}
    BadHeaderRequest(const BadHeaderRequest& other) throw()
      : _msg(other._msg) {}
    virtual ~BadHeaderRequest() throw() {}
    virtual const char*	what() const throw()
    {
      return _msg.c_str();
    }
    
  private:
    std::string		_msg;
    BadHeaderRequest	&operator=(const BadHeaderRequest &) throw();
  };

  class FactoryExcept : public std::exception
  {
  public:
    FactoryExcept(std::string const& msg) throw()
      : _msg(msg) {}
    FactoryExcept(const FactoryExcept& other) throw()
      : _msg(other._msg) {}
    virtual ~FactoryExcept() throw() {}
    virtual const char* what() const throw()
    {
      return _msg.c_str();
    }
    
  private:
    std::string         _msg;
    FactoryExcept	&operator=(const FactoryExcept &) throw();
  };

  class ObjectExcept : public std::exception
  {
  public:
    ObjectExcept(std::string const &msg) throw()
      :_msg(msg) {}

    ObjectExcept(const ObjectExcept & other) throw()
      :_msg(other._msg){}

    virtual ~ObjectExcept() throw() {}

    virtual const char*     what() const throw()
    {
      return _msg.c_str();
    }

  private:
    std::string			_msg;
    ObjectExcept		&operator=(const ObjectExcept &) throw();
  };
};


#endif /* !EXCEPTIONS_H_ */
