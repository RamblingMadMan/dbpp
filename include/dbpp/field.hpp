#ifndef DBPP_FIELD_HPP
#define DBPP_FIELD_HPP 1

#include "id.hpp"

namespace dbpp{
	/**
	 * a field definition
	 * 
	 * @tparam Id the id of the field
	 * @tparam Value the value stored in the field
	 **/
	template<typename Id, typename Value>
	class field;
	
	template<char ... Chars, typename Value>
	class field<id<Chars...>, Value>{
		public:
			using id_type = id<Chars...>;
			
			field(){}
			
			field(const Value &val_): m_val{val_}{}
			field(Value &&val_): m_val{std::move(val_)}{}
			
			field &operator =(const Value &rhs){
				m_val = rhs;
				return *this;
			}
			
			field &operator =(Value &&rhs){
				m_val = std::move(rhs);
				return *this;
			}
			
			/**
			 * get a constant reference to the value stored
			 **/
			const Value &get() const noexcept{ return m_val; }
			
			/**
			 * get a reference to the value stored
			 **/
			Value &get() noexcept{ return m_val; }
			
		private:
			Value m_val;
	};
}

#endif // DBPP_FIELD_HPP
