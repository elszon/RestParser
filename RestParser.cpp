#include "RestParser.h"

#include <iterator>

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/range/algorithm/transform.hpp>

#include <boost/utility/string_ref.hpp>
#include <boost/tokenizer.hpp>

RestRequest parseRest(const std::string& restRequest){

    using Tokenizer =  boost::tokenizer<boost::char_separator<char>>;

    const std::string& lowerRestRequest = boost::to_lower_copy(restRequest);
    const boost::string_ref request{lowerRestRequest};
    const auto& itemsBegin = request.find('?');

    const auto& urlSeparator = boost::char_separator<char>{"/"};
    const auto& itemsSeparator = boost::char_separator<char>{"&"};

    const Tokenizer path{request.substr(0, itemsBegin), urlSeparator};
    const boost::string_ref allItems = itemsBegin != boost::string_ref::npos ? request.substr(itemsBegin+1)
                                                                             : boost::string_ref{};

    RestRequest::Items items;
    boost::transform(Tokenizer{allItems, itemsSeparator},
                     std::inserter(items, items.end()),
                     [](const std::string& s){
        const std::string::size_type keyEnd = s.find('=');
        if ( keyEnd == std::string::npos ){
            throw std::runtime_error{"couldn't split item"};
        }
        return std::make_pair(s.substr(0, keyEnd), s.substr(keyEnd+1));
    });

    return RestRequest{RestRequest::Path{path.begin(),path.end()}, items};
}
