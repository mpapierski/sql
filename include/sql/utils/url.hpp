#if !defined(SQL_URL_INCLUDED_)
#define SQL_URL_INCLUDED_

#include <string>

struct url
{
    std::string protocol_, host_, path_, query_;
    std::string user_, password_;
    explicit url(std::string const & url_s);
};


#endif /* SQL_URL_INCLUDED_ */
