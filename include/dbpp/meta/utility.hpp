#ifndef DBPP_META_UTILITY_HPP
#define DBPP_META_UTILITY_HPP 1

#include "type_list.hpp"

#include "../id.hpp"

namespace dbpp{
	namespace meta{
		/**
		 * meta-function to get a type, based on id, from a type_list
		 * 
		 * @tparam Id the id of the type to get
		 * @tparam TypeList the list of id-ed types
		 **/
		template<typename Id, typename TypeList>
		struct get_type_by_id;
		
		template<char ... Chars, template<typename...> class HeadType, typename HeadId, typename ... HeadOther, typename ... Tail>
		struct get_type_by_id<id<Chars...>, type_list<HeadType<HeadId, HeadOther...>, Tail...>>{
			using type = typename get_type_by_id<id<Chars...>, type_list<Tail...>>::type;
		};
		
		template<char ... Chars, template<typename...> class HeadType, typename ... HeadOther, typename ... Tail>
		struct get_type_by_id<id<Chars...>, type_list<HeadType<id<Chars...>, HeadOther...>, Tail...>>{
			using type = HeadType<id<Chars...>, HeadOther...>;
		};

		/**
		 * helper meta-function to apply get_type_by_id to a list of types
		 **/
		template<typename Id, typename TypeList>
		using get_type_by_id_t = typename get_type_by_id<Id, TypeList>::type;
	}
}

#endif // DBPP_META_UTILITY_HPP
