#ifndef DBPP_DATABASE_HPP
#define DBPP_DATABASE_HPP 1

#include <unordered_map>

#include "meta/utility.hpp"
#include "record.hpp"

namespace dbpp{
	/**
	 * class to hold values of a type of record
	 * 
	 * @tparam Record the type of record to hold values of
	 **/
	template<typename Record>
	class record_holder{ // olympic class, mind you
		public:
			using id_type = typename Record::id_type;
			
			/**
			 * create a record in the holder
			 * 
			 * @param[in] id_ the id of the new record
			 * @param[in,out] field_args arguments to pass individually to each of the record fields e.g. field(field_args)...
			 **/
			template<typename ... FieldArgs>
			decltype(auto) make_record(id_type id_, FieldArgs &&... field_args){
				{
					auto res = m_map.find(id_);
					if(res != std::end(m_map))
						throw std::runtime_error{"record already exists"};
				}
				
				auto res = m_map.insert({id_, {std::forward_as_tuple(std::forward<FieldArgs>(field_args)...)}});
				if(!res.second)
					throw std::runtime_error{"error in std::unordered_map::insert"};
				
				return res.first->second;
			}
			
			/**
			 * erase a record from the holder
			 * 
			 * @param[in] id_ the record id to erase
			 **/
			void erase_record(id_type id_){
				m_map.erase(id_);
			}
			
			/**
			 * get a record from the holder
			 * 
			 * @param[in] id_ the id of the record
			 **/
			decltype(auto) get_record(id_type id_){
				auto res = m_map.find(id_);
				if(res == std::end(m_map))
					throw std::runtime_error{"record doesn't exist"};
				
				return *res;
			}
			
			Record &operator [](const id_type &id_){
				return m_map[id_];
			}
			
		private:
			std::unordered_map<id_type, Record> m_map;
	};
	
	/**
	 * a generic database holding any number of record types
	 * 
	 * @tparam Records the types of record to hold
	 **/
	template<typename ... Records>
	class database{
		public:
			/**
			 * get a record database by id
			 * 
			 * @tparam RecordId the id of the record type
			 **/
			template<typename RecordId>
			decltype(auto) get(){
				return std::get<
					record_holder<
						meta::get_type_by_id_t<
							RecordId, meta::type_list<Records...>
						>
					>
				>(m_records);
			}
			
		private:
			std::tuple<record_holder<Records>...> m_records;
	};
}

#endif // DBPP_DATABASE_HPP
