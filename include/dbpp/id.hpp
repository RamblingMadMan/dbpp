#ifndef DBPP_ID_HPP
#define DBPP_ID_HPP 1

#include <cstddef>
#include <stdexcept>

#include "typestring.hh"

namespace dbpp{
	/**
	 * id used for identifying types
	 **/
	template<char ... Chars>
	using id = irqus::typestring<Chars...>;
}

#define dbpp_id(str) typestring_is(str)

#endif // DBPP_ID_HPP
