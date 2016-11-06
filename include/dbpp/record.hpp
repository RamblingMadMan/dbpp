#ifndef DBPP_RECORD_HPP
#define DBPP_RECORD_HPP 1

#include <tuple>

#include "field.hpp"
#include "meta/utility.hpp"

namespace dbpp{
	/**
	 * a type of record
	 * 
	 * @tparam Id the id of the record type
	 * @tparam IdType the type of id to use for values of this record
	 * @tparam Fields the fields contained in the record
	 **/
	template<typename Id, typename IdType, typename ... Fields>
	class record{
		public:
			using id_type = IdType;
			
			record(){}
			
			template<typename ... FieldArgs>
			record(std::tuple<FieldArgs...> args)
				: record(std::make_index_sequence<sizeof...(FieldArgs)>{}, args){}
			
			/**
			 * get a field from the record instance, by id
			 * 
			 * @tparam FieldId the id of the field
			 **/
			template<typename FieldId>
			decltype(auto) get(){
				return std::get<
					meta::get_type_by_id_t<
						FieldId, meta::type_list<Fields...>
					>
				>(m_fields);
			}

		private:
			template<typename ... FieldArgs, std::size_t ... Indices>
			record(std::index_sequence<Indices...>, std::tuple<FieldArgs...> &args){
				using dummy = int[];
				(void)dummy{0, (std::get<Indices>(m_fields) = std::get<Indices>(args), 0)...};
			}
			
			std::tuple<Fields...> m_fields;
	};
}

#endif // DBPP_RECORD_HPP
