#ifndef DBPP_META_TYPE_LIST_HPP
#define DBPP_META_TYPE_LIST_HPP 1

#include <cstddef>

namespace dbpp{
	namespace meta{
		/**
		 * a basic list of types
		 **/
		template<typename...>
		struct type_list;
		
		/**
		 * type to hold a numeric index into something
		 **/
		template<std::size_t Idx>
		struct idx;
		
		/**
		 * meta-function to get a type, based on index, from a type_list
		 * 
		 * @tparam Idx the index of the type to get
		 * @tparam TypeList the list of types to get the type from
		 **/
		template<typename Idx, typename TypeList>
		struct get_type_by_index;
		
		template<std::size_t Idx, typename Head, typename ... Tail>
		struct get_type_by_index<idx<Idx>, type_list<Head, Tail...>>{
			using type = typename get_type_by_index<idx<Idx-1>, type_list<Tail...>>::type;
		};
		
		template<typename Head, typename ... Tail>
		struct get_type_by_index<idx<0>, type_list<Head, Tail...>>{
			using type = Head;
		};
		
		/**
		 * generic meta-function to get a type from a list based on another meta-function
		 * 
		 * @tparam Idx the index used
		 * @tparam TypeList the list of types to index
		 * @tparam GetTypeFn the meta function to use to get the type
		 **/
		template<typename Idx, typename TypeList, template<typename...> class GetTypeFn>
		struct get_type{
			using type = typename GetTypeFn<Idx, TypeList>::type;
		};
		
		template<typename Idx, typename TypeList, template<typename...> class GetTypeFn>
		using get_type_t = typename get_type<Idx, TypeList, GetTypeFn>::type;
		
		template<std::size_t Idx, typename TypeList>
		using get_type_by_index_t = typename get_type_by_index<idx<Idx>, TypeList>::type;
	}
}

#endif // DBPP_META_TYPE_LIST_HPP
