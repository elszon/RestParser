#ifndef RESTPARSER_H
#define RESTPARSER_H

#include <map>
#include <string>
#include <type_traits>
#include <vector>

#include <boost/core/enable_if.hpp>


class RestRequest {
public:
    using Path = std::vector<std::string>;
    using ItemKey = std::string;
    using ItemValue = std::string;
    using Items = std::map<ItemKey, ItemValue>;

    template< class P, class I,
              class = typename boost::enable_if<std::is_convertible<P, Path>>::type,
              class = typename boost::enable_if<std::is_convertible<I, Items>>::type>
    RestRequest(P&& path, I&& items)
        : path{std::forward<Path>(path)}
        , items{std::forward<Items>(items)}{
    }

    const Path& getPath() const { return path; }

private:
    Path path;
    Items items;
};

RestRequest parseRest(const std::string& restRequest);

#endif // RESTPARSER_H
