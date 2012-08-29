#include <algorithm>
#include <stdexcept>
#include <sql/utils/url.hpp>

url::url(std::string const & url_s)
{
    const std::string prot_end("://");
    std::string::const_iterator prot_i = search(url_s.begin(), url_s.end(),
                                           prot_end.begin(), prot_end.end());
    if (prot_i == url_s.end())
        throw std::logic_error("Unknown URL: " + url_s);
    protocol_.reserve(distance(url_s.begin(), prot_i));
    std::transform(url_s.begin(), prot_i,
              back_inserter(protocol_),
              std::ptr_fun<int,int>(tolower)); // protocol is icase
    if( prot_i == url_s.end() )
        return;
    advance(prot_i, prot_end.length());
    std::string::const_iterator path_i = find(prot_i, url_s.end(), '/');
    host_.reserve(distance(prot_i, path_i));
    std::transform(prot_i, path_i,
              back_inserter(host_),
              std::ptr_fun<int,int>(tolower)); // host is icase
    std::string::const_iterator query_i = find(path_i, url_s.end(), '?');
    path_.assign(path_i, query_i);
    if( query_i != url_s.end() )
        ++query_i;
    query_.assign(query_i, url_s.end());
    
    // expand host
    
    if (host_.find('@') != std::string::npos)
    {
        std::string tmp;
        std::copy(host_.begin(), host_.begin() + host_.find('@'), back_inserter(tmp));
        host_ = host_.substr(host_.find('@') + 1);
        
        if (tmp.find(':') != std::string::npos)
        {
            std::copy(tmp.begin(), tmp.begin() + tmp.find(':'), back_inserter(user_));
            std::copy(tmp.begin() + tmp.find(':') + 1, tmp.end(), back_inserter(password_));
        }
        else
            user_ = tmp;
        
    }
    
    
}
